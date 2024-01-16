#include "configuration/configuration.h"

#include <fstream>

#include "common/log.h"

namespace sm {
namespace config {

Configuration::Configuration() {}

bool Configuration::Init(const std::string& path) {
  std::ifstream file(path, std::ios::in);
  nlohmann::json root = nlohmann::json::parse(file, nullptr, true, true);
  file.close();
  if (root.is_discarded()) {
    AWARN << "state config [" << path << "] invalid, parse file failed";
    return false;
  }

  for (const std::string& state : root["states"]) {
    state_config_.states.push_back(state);
  }

  state_config_.initial_state = root["initial_state"];

  for (const auto& trans_element : root["transitions"]) {
    Transition transit {
      trans_element["trigger"],
      trans_element["source"],
      trans_element["dest"]
    };
    state_config_.transitions.emplace_back(transit);
  }
  init_ = true;
  return true;
}

}  // namespace config
}  // namespace sm