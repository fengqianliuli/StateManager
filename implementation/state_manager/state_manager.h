#pragma once

#include "common/macros.h"

#include <unordered_map>
#include <string>

#include "fsm/fsm.hpp"

namespace sm {
namespace state_manager {

class StateManager {
DECLARE_SINGLETON(StateManager);

 public:
  ~StateManager() = default;
  std::string GetCurrentState();
  bool Trigger(const std::string& event);

 private:
  fsm::stack fsm_;
  std::unordered_map<int, std::string> state2str_;
};

}  // namespace state_manager
}  // namespace sm