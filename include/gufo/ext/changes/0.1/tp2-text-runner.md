# Paired text-runner execution

Add optional source contracts for serializing model-owned prompt context,
planning speculative steps identically on paired ranks, and rejecting reuse
of states or snapshots whose producing peer failed verification. Batched
decode members may carry an explicit draft count. Chat requests retain the
original structured-output schema so a paired rank can reconstruct the same
constraint. Defaults preserve existing single-process providers.
