#ifndef PLEW_LLVM_PIPELINE_H
#define PLEW_LLVM_PIPELINE_H

// Shared by the embedded backend and scripts/support/llvm_link.py. Keep the
// literal on one line; the build helper rejects an unrecognized definition.
#define PLEW_LLVM_PIPELINE "function(sroa,early-cse,instcombine<verify-fixpoint;max-iterations=8>),cgscc(argpromotion),default<O1>"

#endif
