#pragma once

#include "common/macros.h"

#include <string>
#include <vector>
#include <atomic>

#include <nlohmann/json.hpp>

namespace sm {
namespace config {

struct Transition {
  std::string trigger;
  std::string source;
  std::string dest;
};

struct StateConfig {
  std::vector<std::string> states;
  std::string initial_state;
  std::vector<Transition> transitions;
};

class Configuration {
DECLARE_SINGLETON(Configuration);

 public:
  ~Configuration() = default;
  bool Init(const std::string& path);
  bool IsInitialized() const { return init_; }
  const StateConfig &GetStateConfig() const {
    return state_config_;
  }

 private:
  nlohmann::json config_;
  StateConfig state_config_;
  std::atomic_bool init_{false};
};

}  // namespace config
}  // namespace sm