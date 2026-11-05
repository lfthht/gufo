#pragma once
#include <memory>

#include "gufo/ext/text.hpp"
namespace gufo::models::qwen38_flash_next {
namespace rocm {
class Communicator;
}
struct RdmaRunnerOptions {
  std::uint32_t rank{0};
  std::uint32_t world_size{2};
  int hip_device{0};
  std::shared_ptr<rocm::Communicator> communicator;
};
std::shared_ptr<ext::TextModelRunner> CreateQwenFlashNextRdmaTextRunner(
    const ext::TextRunnerOptions&, const RdmaRunnerOptions&,
    std::string* error);
}  // namespace gufo::models::qwen38_flash_next
