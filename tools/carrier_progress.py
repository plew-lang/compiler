"""LLDB-only observation for plewc-func-range-fixed's verified outer loop.

Load with `command script import tools/carrier_progress.py`, then
`script carrier_progress.install(lldb.debugger)`, before process launch.
No inferior expressions, memory writes, or return-value overrides are used.
"""
import time
import lldb

started = time.monotonic()
last_report = {}
last_completed = {}
backend_returns = 0
final_body_returns = 0


def report_final_body(frame, location, internal_dict):
    global final_body_returns
    final_body_returns += 1
    now = time.monotonic()
    if now - last_report.get("final-body", 0) >= 1:
        print("[carrier-progress] finalize-body-returns completed={} elapsed={:.1f}s".
              format(final_body_returns, now - started), flush=True)
        last_report["final-body"] = now
    return False


def report_backend(frame, location, internal_dict):
    global backend_returns
    backend_returns += 1
    now = time.monotonic()
    if now - last_report.get("backend", 0) >= 1:
        print("[carrier-progress] backend-body-returns completed={} elapsed={:.1f}s".
              format(backend_returns, now - started), flush=True)
        last_report["backend"] = now
    return False


def report(frame, location, internal_dict):
    return report_loop(frame, "generic-body-check", 0x60)


def report_record(frame, location, internal_dict):
    error = lldb.SBError()
    mode = frame.GetThread().GetProcess().ReadUnsignedFromMemory(
        frame.FindRegister("sp").GetValueAsUnsigned() + 0xf5c, 1, error)
    if error.Fail():
        print("[carrier-progress] cannot read record mode", flush=True)
        return True
    return report_loop(frame, "parametric-record:templates=" + str(mode), 0x80)


def report_loop(frame, phase, counter_offset):
    process = frame.GetThread().GetProcess()
    error = lldb.SBError()
    # +72: count returned in x0; fi remains in the verified frame slot.
    address = frame.FindRegister("x29").GetValueAsUnsigned() - counter_offset
    completed = process.ReadUnsignedFromMemory(address, 8, error)
    if error.Fail():
        print("[carrier-progress] cannot read fi: " + str(error), flush=True)
        return True
    total = frame.FindRegister("x0").GetValueAsUnsigned()
    if completed > total:
        print("[carrier-progress] invalid counter; stop for diagnosis", flush=True)
        return True
    now = time.monotonic()
    if completed != last_completed.get(phase) and (
            now - last_report.get(phase, 0) >= 1 or completed == total):
        print("[carrier-progress] {} completed={}/{} elapsed={:.1f}s".
              format(phase, completed, total, now - started), flush=True)
        last_report[phase] = now
        last_completed[phase] = completed
    return False


def install(debugger):
    target = debugger.GetSelectedTarget()
    if target.GetModuleAtIndex(0).GetUUIDString() != "1B4E4E49-3EB5-438F-965C-32FAECEE5F3D":
        raise RuntimeError("unsupported carrier: executable UUID mismatch")
    matches = target.FindSymbols("gm1805_323212", lldb.eSymbolTypeCode)
    if matches.GetSize() != 1:
        raise RuntimeError("unsupported carrier: checker symbol missing")
    symbol = matches.GetContextAtIndex(0).GetSymbol()
    instructions = symbol.GetInstructions(target)
    # Fail closed if the disassembled loop/frame shape changes.
    expected = {14: ("ldur", "x9, [x29, #-0x60]"),
                17: ("bl", None), 18: ("mov", "x1, x0")}
    for index, (mnemonic, operands) in expected.items():
        instruction = instructions.GetInstructionAtIndex(index)
        if instruction.GetMnemonic(target) != mnemonic or (
                operands is not None and instruction.GetOperands(target) != operands):
            raise RuntimeError("unsupported carrier: loop instruction mismatch")
    address = instructions.GetInstructionAtIndex(18).GetAddress()
    breakpoint = target.BreakpointCreateBySBAddress(address)
    breakpoint.SetScriptCallbackFunction(__name__ + ".report")
    print("[carrier-progress] installed verified generic outer-loop observer", flush=True)
    matches = target.FindSymbols("gm1691_323212", lldb.eSymbolTypeCode)
    if matches.GetSize() != 1:
        raise RuntimeError("unsupported carrier: record symbol missing")
    instructions = matches.GetContextAtIndex(0).GetSymbol().GetInstructions(target)
    expected = {108: ("ldur", "x9, [x29, #-0x80]"),
                111: ("bl", None), 112: ("mov", "x1, x0")}
    for index, (mnemonic, operands) in expected.items():
        instruction = instructions.GetInstructionAtIndex(index)
        if instruction.GetMnemonic(target) != mnemonic or (
                operands is not None and instruction.GetOperands(target) != operands):
            raise RuntimeError("unsupported carrier: record loop mismatch")
    breakpoint = target.BreakpointCreateBySBAddress(
        instructions.GetInstructionAtIndex(112).GetAddress())
    breakpoint.SetScriptCallbackFunction(__name__ + ".report_record")
    print("[carrier-progress] installed verified parametric record observer", flush=True)
    # The completed backend calls appear directly under gm2845's emission
    # loop in the sampled executable. Count returns, never entries or time.
    matches = target.FindSymbols("gm2890_323218", lldb.eSymbolTypeCode)
    if matches.GetSize() != 1:
        raise RuntimeError("unsupported carrier: backend symbol missing")
    instructions = matches.GetContextAtIndex(0).GetSymbol().GetInstructions(target)
    count = 0
    for instruction in instructions:
        if instruction.GetMnemonic(target) == "ret":
            breakpoint = target.BreakpointCreateBySBAddress(instruction.GetAddress())
            breakpoint.SetScriptCallbackFunction(__name__ + ".report_backend")
            count += 1
    if count == 0:
        raise RuntimeError("unsupported carrier: no backend return sites")
    print("[carrier-progress] installed backend return observer ({} sites)".
          format(count), flush=True)
    # gf3 calls finalizeCallables (gm2147), whose worklist calls gm2139.
    # gm2139 increments Comp.traceFinalBodyScans at +0x550, then reads
    # bodyInstances[bodyId - 1], matching scanFinalBodyInstance. Observe
    # returns rather than that entry counter: these are completed scans.
    matches = target.FindSymbols("gm2139_323212", lldb.eSymbolTypeCode)
    if matches.GetSize() != 1:
        raise RuntimeError("unsupported carrier: final body symbol missing")
    instructions = matches.GetContextAtIndex(0).GetSymbol().GetInstructions(target)
    count = 0
    for instruction in instructions:
        if instruction.GetMnemonic(target) == "ret":
            breakpoint = target.BreakpointCreateBySBAddress(instruction.GetAddress())
            breakpoint.SetScriptCallbackFunction(__name__ + ".report_final_body")
            count += 1
    if count == 0:
        raise RuntimeError("unsupported carrier: no final body return sites")
    print("[carrier-progress] installed final body return observer ({} sites)".
          format(count), flush=True)
