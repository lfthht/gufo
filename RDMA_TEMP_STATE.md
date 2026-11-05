# RDMA port state — 5 November 2026

The 0.30.0 port is qualified on the user's two Strix Halo servers with two
USB4 cables. See [the port and validation record](docs/models/qwen3.8-flash-next/USB4-V030.md)
and its compact JSON evidence for exact revisions, runtime identity and limits.

The port combines upstream 0.30.0 with maintained RDMA revision `f070a179`.
Source revision `098d43f0` built the installed candidate. Fifteen focused CPU
tests and six GPU suites pass, followed by 51 live generation checks and two
cancelled-stream recovery checks. Native zero-copy traffic completed on both
cables in AR and MTP. Continued MTP with RAM and disk caching disabled and
disk-cache reuse after a process restart both pass.

The earlier November 1 checkpoint and its unfinished work are retained in Git
history. Its RAM-cache-off failure is not the state of this tested port.

The default branch of the user's fork follows current upstream main. This
optional RDMA port remains on `codex/usb4-rdma-v0.30.0`. The dedicated text and
image services use the official 0.30.0 runtime; the saved dual-host preset uses
the qualified custom runtime. Old images and private host configuration
backups remain available for rollback.

Filled 262K-context, physical reboot/cable recovery, Windows, other model
artifacts and matched performance comparisons were not qualified in this run.
