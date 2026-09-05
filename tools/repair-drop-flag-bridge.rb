# Diagnostic bootstrap repair for the one verified recovery LLVM snapshot.
# Repair only generated ConditionalDrop flag slots, never user values or ARC.
# The source fix belongs in Mid/Drop; this bridge only gets that fix executable.
require 'digest'

input, output = ARGV
abort 'usage: ruby repair-drop-flag-bridge.rb INPUT OUTPUT' unless input && output
abort 'input must remain intact' if File.expand_path(input) == File.expand_path(output)
source = File.binread(input)
expected = [
  '18fae20f064d7695854c9b0f2719f4df22edbf0fc7a3fbaa15e897c6947c17cf',
  # Source-fixed compiler, still emitted by the original faulty producer.
  '1ada9c8bd73a5c05ae660606ece7d14992e0cb3e6300e2938ced9bf3a71f3f6d'
]
abort 'unsupported recovery snapshot' unless expected.include?(Digest::SHA256.hexdigest(source))
functions = 0
slots = 0
repaired = source.gsub(/^define [^\n]*\{\n.*?^\}\n/m) do |function|
  flags = function.scan(/  (%\d+) = load i1, ptr (%\d+), align 1\n  br i1 \1, label %mid\.drop\d*, label %mid\.drop\.cont\d*\n/).map(&:last).uniq
  if flags.empty?
    function
  else
    flags.each do |flag|
      abort "flag has no boolean slot: #{flag}" unless function.include?("  #{flag} = alloca i1, align 1\n")
      function.lines.each do |line|
        next unless line.match?(/#{Regexp.escape(flag)}(?!\d)/)
        allowed = line.match?(/^  #{Regexp.escape(flag)} = alloca i1, align 1$/) ||
          line.match?(/^  %\d+ = load i1, ptr #{Regexp.escape(flag)}, align 1$/) ||
          line.match?(/^  store i1 (true|false), ptr #{Regexp.escape(flag)}, align 1$/)
        abort "unexpected flag use: #{line}" unless allowed
      end
    end
    abort 'unexpected entry shape' unless function.include?("  br label %body0\n")
    functions += 1
    slots += flags.length
    initializers = flags.map { |flag| "  store i1 false, ptr #{flag}, align 1\n" }.join
    function.sub("  br label %body0\n", initializers + "  br label %body0\n")
  end
end
abort 'no flags repaired' if slots.zero?
File.binwrite(output, repaired)
warn "drop-flag bridge: initialized #{slots} slots in #{functions} functions; source and seed unchanged"
