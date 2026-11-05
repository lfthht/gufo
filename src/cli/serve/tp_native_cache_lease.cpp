#include "src/cli/serve/tp_native_cache_lease.hpp"
namespace gufo::server {
std::optional<ComponentCacheMetrics> ServingCacheLease::Metrics() const {
  return component_ ? std::optional(component_->Metrics()) : std::nullopt;
}
std::vector<std::size_t> ServingCacheLease::PlannedCaptures(
    std::size_t stable) const {
  return component_ ? component_->PlannedCaptures(stable)
                    : std::vector<std::size_t>{};
}
#define FORWARD_RESULT(type, name, qualifiers, args, call)         \
  type ServingCacheLease::name args qualifiers {                   \
    return component_ ? component_->name call : legacy_.name call; \
  }
FORWARD_RESULT(ContinuationState&, state, const, (), ())
FORWARD_RESULT(bool, cache_hit, const noexcept, (), ())
FORWARD_RESULT(std::size_t, cached_tokens, const noexcept, (), ())
FORWARD_RESULT(std::size_t, restored_snapshot_bytes, const noexcept, (), ())
FORWARD_RESULT(double, restore_ms, const noexcept, (), ())
FORWARD_RESULT(bool, restored_from_disk, const noexcept, (), ())
FORWARD_RESULT(ContinuationLookup, lookup, const noexcept, (), ())
FORWARD_RESULT(bool, HasSnapshotFor, const,
               (std::span<const ContinuationToken> tokens), (tokens))
FORWARD_RESULT(bool, TryReserveSnapshot, ,
               (std::size_t bytes, std::size_t boundary, bool preserve,
                SnapshotPurpose purpose,
                std::span<const ContinuationToken> tokens),
               (bytes, boundary, preserve, purpose, tokens))
FORWARD_RESULT(void, SkipSnapshot, noexcept,
               (SnapshotEventReason reason, std::size_t bytes,
                std::size_t boundary),
               (reason, bytes, boundary))
FORWARD_RESULT(std::size_t, PublishSnapshot, ,
               (std::vector<ContinuationToken> tokens,
                std::shared_ptr<const ContinuationSnapshot> snapshot,
                bool preserve),
               (std::move(tokens), std::move(snapshot), preserve))
FORWARD_RESULT(std::size_t, Commit, ,
               (std::vector<ContinuationToken> tokens,
                std::shared_ptr<const ContinuationSnapshot> snapshot,
                std::vector<ContinuationToken> live),
               (std::move(tokens), std::move(snapshot), std::move(live)))
FORWARD_RESULT(void, Invalidate, noexcept, (), ())
#undef FORWARD_RESULT
void ServingCacheLease::AdoptRestoredPrefix(std::size_t tokens,
                                            std::size_t bytes, double ms) {
  if (component_)
    throw std::logic_error("component restore is owned by the component cache");
  legacy_.AdoptRestoredPrefix(tokens, bytes, ms);
}
bool ServingCacheLease::retains_snapshots() const noexcept {
  // The component cache keeps its own commit semantics.
  return component_ != nullptr || legacy_.retains_snapshots();
}
void ServingCacheLease::PreparePrefill(std::size_t tokens) {
  if (component_)
    component_->PreparePrefill(tokens);
}

std::size_t ServingCacheLease::CaptureBytes() const {
  return component_->CaptureBytes();
}
std::size_t ServingCacheLease::CaptureBytes(std::size_t boundary) const {
  return component_->CaptureBytes(boundary);
}
std::unique_ptr<TextRunnerSnapshot> ServingCacheLease::Capture() {
  return component_->Capture();
}
}  // namespace gufo::server
