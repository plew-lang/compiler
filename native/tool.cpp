// Native host services for the Plew tool. Compilation semantics and package
// resolution remain in Plew; self-spawned workers isolate their one-shot state.
#include "resources.h"
#include <llvm/Config/llvm-config.h>
#include <mach-o/dyld.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

extern char **environ;
namespace fs = std::filesystem;
namespace {
struct CommandFailure { int code; };
volatile sig_atomic_t activeChild = 0;
volatile sig_atomic_t receivedSignal = 0;

void forwardSignal(int signal) {
  receivedSignal = signal;
  if (activeChild > 0)
    kill(activeChild, signal);
}

struct TemporaryDirectory {
  fs::path path;
  TemporaryDirectory() {
    auto pattern = (fs::temp_directory_path() / "plew-XXXXXX").string();
    std::vector<char> bytes(pattern.begin(), pattern.end());
    bytes.push_back(0);
    if (!mkdtemp(bytes.data()))
      throw std::runtime_error("cannot create temporary directory");
    path = bytes.data();
  }
  ~TemporaryDirectory() { std::error_code error; fs::remove_all(path, error); }
};

struct PendingFile {
  fs::path path;
  explicit PendingFile(const fs::path &destination) {
    auto pattern = (destination.parent_path() / ".plew-XXXXXX").string();
    std::vector<char> bytes(pattern.begin(), pattern.end());
    bytes.push_back(0);
    int fd = mkstemp(bytes.data());
    if (fd < 0)
      throw std::runtime_error("cannot create output beside " + destination.string());
    close(fd);
    path = bytes.data();
  }
  ~PendingFile() { std::error_code error; fs::remove(path, error); }
  void commit(const fs::path &destination) { fs::rename(path, destination); }
};

std::string executablePath() {
  uint32_t size = 0;
  _NSGetExecutablePath(nullptr, &size);
  std::vector<char> path(size);
  if (_NSGetExecutablePath(path.data(), &size))
    throw std::runtime_error("cannot locate plew executable");
  return fs::canonical(path.data()).string();
}

int run(const std::vector<std::string> &arguments, const fs::path &output = {},
        const fs::path &directory = {}) {
  std::vector<char *> pointers;
  for (const auto &argument : arguments)
    pointers.push_back(const_cast<char *>(argument.c_str()));
  pointers.push_back(nullptr);
  posix_spawn_file_actions_t actions;
  posix_spawn_file_actions_init(&actions);
  int setup = 0;
  if (!output.empty())
    setup = posix_spawn_file_actions_addopen(&actions, STDOUT_FILENO,
                                            output.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (!setup && !directory.empty())
    setup = posix_spawn_file_actions_addchdir(&actions, directory.c_str());
  posix_spawnattr_t attributes;
  posix_spawnattr_init(&attributes);
  sigset_t signals, oldMask, childMask;
  sigemptyset(&signals);
  for (int signal : {SIGINT, SIGTERM, SIGHUP})
    sigaddset(&signals, signal);
  sigprocmask(SIG_BLOCK, &signals, &oldMask);
  childMask = oldMask;
  for (int signal : {SIGINT, SIGTERM, SIGHUP})
    sigdelset(&childMask, signal);
  posix_spawnattr_setsigmask(&attributes, &childMask);
  posix_spawnattr_setsigdefault(&attributes, &signals);
  // Keep the terminal's foreground group so applications can read stdin.
  // A supervising watchdog owns the entire process group, including children.
  posix_spawnattr_setflags(&attributes, POSIX_SPAWN_SETSIGMASK | POSIX_SPAWN_SETSIGDEF);
  struct sigaction previous[3], handler = {};
  handler.sa_handler = forwardSignal;
  sigemptyset(&handler.sa_mask);
  int index = 0;
  for (int signal : {SIGINT, SIGTERM, SIGHUP})
    sigaction(signal, &handler, &previous[index++]);
  receivedSignal = 0;
  pid_t pid = 0;
  int error = setup ? setup : posix_spawnp(&pid, pointers[0], &actions,
                                          &attributes, pointers.data(), environ);
  activeChild = error ? 0 : pid;
  sigprocmask(SIG_SETMASK, &oldMask, nullptr);
  posix_spawn_file_actions_destroy(&actions);
  posix_spawnattr_destroy(&attributes);
  int status = 0;
  pid_t waited = -1;
  if (!error) {
    do { waited = waitpid(pid, &status, 0); } while (waited < 0 && errno == EINTR);
  }
  sigprocmask(SIG_BLOCK, &signals, nullptr);
  activeChild = 0;
  int cancelled = receivedSignal;
  index = 0;
  for (int signal : {SIGINT, SIGTERM, SIGHUP})
    sigaction(signal, &previous[index++], nullptr);
  sigprocmask(SIG_SETMASK, &oldMask, nullptr);
  if (error || waited < 0)
    throw std::runtime_error("cannot run " + arguments[0] + ": " + std::to_string(error ? error : errno));
  if (cancelled)
    return 128 + cancelled;
  return WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
}

void checked(const std::vector<std::string> &arguments, const fs::path &output = {},
             const fs::path &directory = {}) {
  int status = run(arguments, output, directory);
  if (status)
    throw CommandFailure{status};
}

fs::path packageDirectory(fs::path path) {
  path = fs::absolute(path);
  if (!fs::is_directory(path))
    path = path.parent_path();
  while (!path.empty()) {
    if (fs::is_regular_file(path / "Plew.toml"))
      return path;
    auto parent = path.parent_path();
    if (parent == path) break;
    path = parent;
  }
  return {};
}

void resolve(const std::string &self, const fs::path &package) {
  if (package.empty())
    throw std::runtime_error("no Plew.toml found");
  PendingFile pending(package / "Plew.lock");
  checked({self, "--resolve-worker"}, pending.path, package);
  pending.commit(package / "Plew.lock");
  std::cerr << "plew: resolved -> " << (package / "Plew.lock") << '\n';
}

void resolveIfNeeded(const std::string &self, const fs::path &source,
                     const fs::path &temporary) {
  auto package = packageDirectory(source);
  if (package.empty() || fs::exists(package / "Plew.lock")) return;
  auto result = temporary / "needs-resolve";
  checked({self, "--needs-resolve-worker"}, result, package);
  std::ifstream stream(result);
  std::string answer;
  std::getline(stream, answer);
  if (answer == "1") {
    std::cerr << "plew: resolving dependencies (no Plew.lock)...\n";
    resolve(self, package);
  } else if (answer != "0") {
    throw std::runtime_error("invalid dependency resolution decision");
  }
}

void build(const std::string &self, const fs::path &source, const fs::path &output,
           const fs::path &temporary, bool gen, bool trace) {
  auto object = temporary / "program.o";
  std::vector<std::string> command = {self, "--compile-object", object.string()};
  if (gen) command.push_back("--gen");
  if (trace) command.push_back("--trace-phases");
  command.push_back(source.string());
  checked(command);
  auto runtime = temporary / "runtime.o";
  std::ofstream stream(runtime, std::ios::binary);
  stream.write(reinterpret_cast<const char *>(plew_embedded_runtime_data()),
               plew_embedded_runtime_size());
  stream.close();
  if (!stream) throw std::runtime_error("cannot write runtime object");
  const char *configured = std::getenv("CC");
  std::string linker = configured && *configured ? configured : "/usr/bin/cc";
  PendingFile pending(output);
  // clang's implicit local config must not select a different linker/target.
  setenv("CLANG_NO_DEFAULT_CONFIG", "1", 1);
  checked({linker, std::string("-mmacosx-version-min=") + plew_distribution_minimum_macos(),
           object.string(), runtime.string(), "-o", pending.path.string()});
  pending.commit(output);
}

void usage() {
  std::cerr << "usage: plew build <file.pw> [-o output]\n"
               "       plew run <file.pw> [args...]\n"
               "       plew gen <file.pw>...\n"
               "       plew resolve [directory|file]\n"
               "       plew --compiler [compiler options] <file.pw>\n"
               "       plew --version | --licenses\n";
}
} // namespace

extern "C" const char *plew_tool_std_root() {
  static std::string root;
  try {
    const char *value = std::getenv("PLEW_STD");
    if (!value || !*value) return "";
    auto path = fs::canonical(value);
    if (!fs::is_directory(path)) throw std::runtime_error("PLEW_STD must be a directory");
    root = path.string() + "/";
    return root.c_str();
  } catch (const std::exception &error) {
    std::cerr << "plew: " << error.what() << '\n';
    std::exit(1);
  }
}

extern "C" long long plew_tool_main(long long count, char **arguments) {
  try {
    auto self = executablePath();
    if (fs::path(arguments[0]).filename() == "plewc") {
      std::vector<std::string> command = {self, "--compiler"};
      command.insert(command.end(), arguments + 1, arguments + count);
      return run(command);
    }
    if (count == 2 && std::string(arguments[1]) == "--version") {
      std::cout << "plew " << plew_distribution_version() << " (LLVM " LLVM_VERSION_STRING ")\n";
      return 0;
    }
    if (count == 2 && std::string(arguments[1]) == "--licenses") {
      std::cout << plew_distribution_licenses() << '\n';
      return 0;
    }
    if (count < 2) { usage(); return 1; }
    std::string mode = arguments[1];
    if (mode == "--help" || mode == "-h") { usage(); return 0; }
    size_t first = 2;
    if (mode != "build" && mode != "run" && mode != "gen" && mode != "resolve") {
      mode = "build";
      first = 1;
    }
    if (mode == "resolve") {
      if (count > 3) { usage(); return 1; }
      fs::path target = count == 3 ? arguments[2] : ".";
      if (!fs::exists(target)) throw std::runtime_error("no such path: " + target.string());
      resolve(self, packageDirectory(target));
      return 0;
    }
    if (first >= static_cast<size_t>(count)) { usage(); return 1; }
    TemporaryDirectory temporary;
    bool trace = std::getenv("PLEW_TRACE_BUILD") != nullptr;
    auto sourceAt = [&](size_t index) {
      auto source = fs::absolute(arguments[index]);
      if (source.extension() != ".pw" || !fs::is_regular_file(source))
        throw std::runtime_error("not a source file: " + source.string());
      return source;
    };
    if (mode == "gen") {
      for (size_t index = first; index < static_cast<size_t>(count); ++index) {
        auto source = sourceAt(index);
        if (source.stem().extension() == ".gen") continue;
        auto harness = temporary.path / "harness";
        build(self, source, harness, temporary.path, true, trace);
        auto destination = source;
        destination.replace_extension(".gen.pw");
        PendingFile pending(destination);
        checked({harness.string()}, pending.path);
        pending.commit(destination);
        std::cout << "plew gen: " << source << " -> " << destination << '\n';
      }
      return 0;
    }
    auto source = sourceAt(first++);
    resolveIfNeeded(self, source, temporary.path);
    if (mode == "run") {
      auto binary = temporary.path / "app";
      build(self, source, binary, temporary.path, false, trace);
      std::vector<std::string> command = {binary.string()};
      command.insert(command.end(), arguments + first, arguments + count);
      return run(command);
    }
    auto output = fs::absolute(source.stem());
    if (first < static_cast<size_t>(count)) {
      if (first + 2 != static_cast<size_t>(count) || std::string(arguments[first]) != "-o") {
        usage(); return 1;
      }
      output = fs::absolute(arguments[first + 1]);
    }
    if (fs::weakly_canonical(output) == fs::canonical(source))
      throw std::runtime_error("output would overwrite the source");
    build(self, source, output, temporary.path, false, trace);
    std::cout << "plew: " << source << " -> " << output << '\n';
    return 0;
  } catch (const CommandFailure &failure) {
    return failure.code;
  } catch (const std::exception &error) {
    std::cerr << "plew: " << error.what() << '\n';
    return 1;
  }
}
