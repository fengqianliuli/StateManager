#include "sm/state/state_manager.h"

#include "state_manager/state_manager_impl.h"

namespace sm {
namespace state_manager {

StateManager::StateManager() {
  impl_ = StateManagerImpl::Instance();
}

std::string StateManager::GetCurrentState() {
  return impl_->GetCurrentState();
}

bool StateManager::Trigger(const std::string &trigger) {
  return impl_->Trigger(trigger);
}

}  // namespace state_manager
}  // namespace sm
