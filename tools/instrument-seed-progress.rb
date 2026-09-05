#!/usr/bin/env ruby
# Diagnostic bridge only. Never overwrite the canonical seed or promote the
# result: instrumentation can affect optimization and hide ownership defects.
require 'digest'
abort 'usage: instrument-seed-progress.rb INPUT.ll OUTPUT.ll' unless ARGV.length == 2
input, output = ARGV
abort 'input and output must differ' if File.expand_path(input) == File.expand_path(output)
abort 'output already exists' if File.exist?(output)
source = File.binread(input)
expected = '5d97f7dc3d692537a000e42f29c266c959764f748afa8ef095b4451abf8db17d'
abort 'unsupported seed: inspect and map the loop before changing this guard' unless Digest::SHA256.hexdigest(source) == expected
# runFrontend calls this function between str.104 (generic-body-check:start)
# and str.105 (done). Its outer loop loads fi into %9 and funcs.count into %13.
# Hook after the count is read: %9 counts completed declarations, not time.
definition = /^define void @gm1416_247107\(ptr %0\) \{\n.*?^\}/m
body = source[definition] or abort 'generic body checker definition missing'
anchor = "  %13 = call i64 @gm12_6139(%gs66 %12)\n"
abort 'unexpected loop shape' unless body.scan(anchor).length == 1
body = body.sub(anchor, anchor + "  call void @plew_seed_generic_progress(i64 %9, i64 %13)\n")
source = source.sub(definition, body)
source << "\ndeclare void @plew_seed_generic_progress(i64, i64)\n"
File.binwrite(output, source)
warn "seed instrumentation: generic declaration counter added; output=#{output}"
