#pragma once

#include <string>

namespace sm {
namespace state_manager {

class StateManagerImpl;

class StateManager {
 public:
  StateManager();
  ~StateManager() = default;
  std::string GetCurrentState();
  bool Trigger(const std::string& event);

 private:
  StateManagerImpl* impl_;
};

}  // namespace state_manager
}  // namespace sm