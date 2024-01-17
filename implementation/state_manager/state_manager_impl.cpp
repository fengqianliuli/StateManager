#include "state_manager/state_manager_impl.h"

#include "common/util.h"
#include "configuration/configuration.h"

namespace sm {
namespace state_manager {

StateManagerImpl::StateManagerImpl() {
  auto&& config = config::Configuration::Instance()->GetStateConfig();
  // set initial state
  auto initial_state_num = common::Hash(config.initial_state);
  state2str_[initial_state_num] = config.initial_state;
  fsm_.set(fsm::state(initial_state_num));

  // set transit
  for (auto&& transit : config.transitions) {
    auto source_num = common::Hash(transit.source);
    auto trigger_num = common::Hash(transit.trigger);
    auto dest_num = common::Hash(transit.dest);
    state2str_[source_num] = transit.source;
    state2str_[trigger_num] = transit.trigger;
    state2str_[dest_num] = transit.dest;

    fsm_.on(fsm::state(source_num),
            fsm::state(trigger_num))
    = [&](const fsm::args &) {
          fsm_.set(fsm::state(dest_num));
      };
  }
}

std::string StateManagerImpl::GetCurrentState() {
  return state2str_[fsm_.get_state().name];
}

bool StateManagerImpl::Trigger(const std::string &trigger) {
  return fsm_.command(fsm::state(common::Hash(trigger)));
}


}  // namespace state_manager
}  // namespace sm