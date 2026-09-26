#!/usr/bin/env python3
"""Manual common-preparation boundary probe; see this directory README."""
from pathlib import Path
import subprocess,sys,json,os
import argparse
parser=argparse.ArgumentParser(description="Verify semantic preparation without linking LLVM")
parser.add_argument('--compiler', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args=parser.parse_args()
c=Path(__file__).resolve().parents[3];out=args.out.resolve();out.mkdir(parents=True,exist_ok=False);carrier=args.compiler.absolute()
sys.path.insert(0,str(c/'scripts/support'));from clang_environment import apply
apply();watch=[sys.executable,'-B',str(c/'scripts/support/watch-command.py'),'--']
with (out/'compile.stderr').open('wb') as log:
 subprocess.run([sys.executable,'-B',str(c/'scripts/support/trace-command.py'),str(out/'compile.log'),'--',str(carrier),'--emit-object',str(out/'check.o'),'--trace-phases',str(Path(__file__).with_name('PreparedProgram.pw'))],cwd=c,stderr=log,check=True)
with (out/'runtime.c').open('wb') as f:subprocess.run([*watch,str(carrier),'--runtime'],stdout=f,check=True)
subprocess.run([*watch,'/usr/bin/clang','-O2',str(out/'check.o'),str(out/'runtime.c'),'-o',str(out/'check')],check=True)
(out/'std').symlink_to(c/'std',target_is_directory=True)
results=[]
for kind,name in [('run','cow_struct'),('run','async_match'),('run','closure_return_boundaries'),('reject','unicode_escape_out_of_range'),('reject','unicode_escape_surrogate'),('reject', 'value_match_no_give'),('reject', 'value_if_no_give'),('reject', 'record_destructure_missing_field'),('reject', 'record_destructure_dup_field'),('reject', 'struct_destructure_missing_field'),('reject', 'struct_destructure_partial'),('reject', 'struct_destructure_type_mismatch'),('reject', 'for_destructure_mismatch'),('reject', 'match_pattern_dup_field'),('reject', 'dict_empty_array_literal'),('reject', 'float_literal_to_int'),('reject', 'array_literal_heterogeneous'),('reject', 'dict_literal_value_type'),('reject', 'compound_assign_literal_out_of_range'),('reject', 'record_constructor_literal_overflow'),('reject', 'generic_body_const_range'),('reject','any_nested_self_input'),('reject', 'duplicate_struct_field'),('reject', 'duplicate_param_label'),('reject', 'duplicate_type_name_struct_enum'),('reject', 'unique_copy'),('reject', 'unique_field_copy'),('reject', 'any_sendable_generic_missing_trait'),('reject', 'access_candidates_private'),('reject', 'any_is_not_static_bound_proof'),('reject', 'factory_gate_same_module'),('reject', 'member_private_method'),('reject', 'arrow_private_field_write'),('reject', 'duplicate_function'),('reject', 'extension_generic_concrete_overload'),('reject', 'extern_c_function_collides_with_function'),('reject','borrow_inout_argument'),('reject','receiver_read_inout_overlap'),('reject','receiver_read_inout_global'),('reject','missing_return'),('reject','move_fn_copyable'),('reject','deinit_on_non_unique'),('reject','unique_enum_deinit'),('reject','coalesce_removed'),('partreject','partfreefn/Main'),('reject','unique_field_not_unique'),('reject','enum_unique_payload_nomark'),('reject','array_unique'),('reject','generic_unique_arg'),('reject','any_unbound_assoc'),('reject','any_parameterized_trait'),('partreject','traitprovidedexternalimpl/Main'),('partreject','traitsubjectowner_aowner/Main'),('partreject','import_same_local_name/Main'),('partreject','importcycle/Main'),('partreject','crossmoduleprivate/Main'),('reject','eprint_not_imported'),('partreject','partmissing/Main'),('partreject','partdiamond/Main'),('partreject','phantomdep/Main'),('partreject', 'publicapiclosure/Main'),('partreject', 'publicapiclosure_assocbinding/Main'),('partreject', 'publicapiclosure_global/Main'),('partreject', 'publicapiclosure_newtype/Main'),('partreject', 'publicapiclosure_pkg_alias/Main'),('partreject', 'publicapiclosure_pkg_internal/Main'),('partreject', 'publicapiclosure_same_name/Main'),('partreject', 'publicapiclosure_trait_alias/Main'),('genreject','derive_hash_missing_import/App'),('genreject','derive_eq_missing_import/App'),('reject','async_borrow_param'),('reject','async_inout_param'),('reject','unique_param_no_mode'),('reject','generic_unique_param_no_mode'),('reject','copyable_borrow'),('reject','copyable_move'),('reject', 'trait_incomplete'),('reject', 'conform_unknown_trait'),('reject', 'supertrait_unmet'),('reject', 'via_missing_target'),('reject', 'field_default_refs_field'),('reject', 'field_default_refs_self'),('reject', 'param_default_refs_param'),('reject', 'param_default_refs_self'),('reject', 'field_default_await'),('reject', 'field_default_await_match_expr'),('reject', 'default_arg_await'),('reject', 'default_arg_await_match_expr'),('reject', 'match_unknown_field'),('reject', 'trait_subject_cycle_argument_bare'),('reject', 'trait_subject_cycle_argument_change_grows'),('reject', 'trait_subject_cycle_bare'),('reject', 'trait_subject_cycle_bare_self'),('reject', 'trait_subject_cycle_extension_bundle'),('reject', 'trait_subject_cycle_extension_generic_bundle'),('reject', 'trait_subject_cycle_extension_receiver_irrelevant'),('reject', 'trait_subject_cycle_extension_self'),('reject', 'trait_subject_cycle_extension_stacked'),('reject', 'trait_subject_cycle_extension_with_bare'),('reject', 'trait_subject_cycle_generic_active_view'),('reject', 'trait_subject_cycle_generic_bare'),('reject', 'trait_subject_cycle_generic_duplicate_binder'),('reject', 'trait_subject_cycle_generic_edge_reuse'),('reject', 'trait_subject_cycle_generic_growth'),('reject', 'trait_subject_cycle_generic_nested_bare'),('reject', 'trait_subject_cycle_generic_nested_type_view'),('reject', 'trait_subject_cycle_generic_record_binder_duplicate'),('reject', 'trait_subject_cycle_generic_specialized_bare'),('reject', 'trait_subject_cycle_generic_tuple_growth'),('reject', 'trait_subject_cycle_indirect_bare'),('reject', 'trait_subject_cycle_projection_argument_growth'),('reject', 'trait_subject_cycle_projection_binder_duplicate'),('reject', 'trait_subject_cycle_projection_receiver_generic_exact'),('reject', 'trait_subject_cycle_source_set_type_view'),('partreject', 'trait_subject_cycle_extension_crossmodule/Main')]:
 source=c/f'tests/fixtures/{kind}/{name}.pw'; expected=0 if kind=='run' else 1
 flags=['--gen'] if kind=='genreject' else []
 result=subprocess.run([*watch,str(out/'check'),*flags,str(source)],cwd=c,capture_output=True)
 assert result.returncode==expected,(name,result.stderr)
 if expected:
  reference=subprocess.run([*watch,str(carrier),*flags,str(source)],cwd=c,capture_output=True)
  assert result.stderr==reference.stderr,(name,result.stderr,reference.stderr)
 else:assert result.stdout==b'prepared\n',result.stdout
 if expected:
  returning=subprocess.run([*watch,str(out/'check'),'--return-gen-failure' if kind=='genreject' else '--return-failure',str(source)],cwd=c,capture_output=True)
  assert returning.returncode==0,(name,returning.returncode,returning.stderr)
  assert returning.stdout==b'returned\n',returning.stdout
  assert returning.stderr==reference.stderr,(name,returning.stderr,reference.stderr)
 results.append({'case':name,'exit':result.returncode});print('PASS',name,flush=True)
deps=subprocess.check_output(['/usr/bin/otool','-L',str(out/'check')],text=True)
assert 'LLVM' not in deps,deps

# Explicit requests must ignore the CLI environment and remain independent.
with (out/'inputs-compile.stderr').open('wb') as log:
 subprocess.run([sys.executable,'-B',str(c/'scripts/support/trace-command.py'),str(out/'inputs-compile.log'),'--',str(carrier),'--emit-object',str(out/'inputs.o'),'--trace-phases',str(Path(__file__).with_name('FrontendInputs.pw'))],cwd=c,stderr=log,check=True)
subprocess.run([*watch,'/usr/bin/clang','-O2',str(out/'inputs.o'),str(out/'runtime.c'),'-o',str(out/'inputs')],check=True)
result=subprocess.run([*watch,str(out/'inputs'),'/nonexistent/ignored.pw'],input=b'invalid source input',capture_output=True)
assert result.returncode==0,(result.returncode,result.stderr)
assert result.stdout==Path(__file__).with_name('FrontendInputs.out').read_bytes(),result.stdout
input_deps=subprocess.check_output(['/usr/bin/otool','-L',str(out/'inputs')],text=True)
assert 'LLVM' not in input_deps,input_deps
print('PASS explicit frontend inputs',flush=True)
(out/'inputs-results.json').write_text(json.dumps({'status':'passed','dependencies':input_deps},indent=2))
# Rendering a structured diagnostic must not exit the host process.
with (out/'diagnostic-compile.stderr').open('wb') as log:
 subprocess.run([sys.executable,'-B',str(c/'scripts/support/trace-command.py'),str(out/'diagnostic-compile.log'),'--',str(carrier),'--emit-object',str(out/'diagnostic.o'),'--trace-phases',str(Path(__file__).with_name('DiagnosticValues.pw'))],cwd=c,stderr=log,check=True)
subprocess.run([*watch,'/usr/bin/clang','-O2',str(out/'diagnostic.o'),str(out/'runtime.c'),'-o',str(out/'diagnostic')],check=True)
result=subprocess.run([*watch,str(out/'diagnostic')],capture_output=True)
assert result.returncode==0,(result.returncode,result.stderr)
assert result.stdout==Path(__file__).with_name('DiagnosticValues.out').read_bytes(),result.stdout
assert result.stderr==Path(__file__).with_name('DiagnosticValues.err').read_bytes(),result.stderr
print('PASS returning diagnostic rendering',flush=True)
# Literal decoding reports semantic failures without terminating its caller.
subprocess.run([*watch,str(carrier),'--emit-object',str(out/'literal.o'),str(Path(__file__).with_name('StringLiteralValues.pw'))],cwd=c,check=True)
subprocess.run([*watch,'/usr/bin/clang','-O2',str(out/'literal.o'),str(out/'runtime.c'),'-o',str(out/'literal')],check=True)
result=subprocess.run([*watch,str(out/'literal')],capture_output=True)
assert result.returncode==0,(result.returncode,result.stderr)
assert result.stdout==Path(__file__).with_name('StringLiteralValues.out').read_bytes(),result.stdout
assert result.stderr==b'',result.stderr
print('PASS returning string literal decoding',flush=True)
(out/'results.json').write_text(json.dumps({'status':'passed','cases':results,'dependencies':deps},indent=2))
