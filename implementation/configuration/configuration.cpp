#include "configuration/configuration.h"

#include <fstream>

#include "common/log.h"
#include "common/environment.h"
#include "common/file.h"

namespace sm {
namespace config {

Configuration::Configuration() {}

bool Configuration::Init(int argc, char const *argv[]) {
  // try to get SM_ROOT_PATH
  std::string root_path;
  if (argc < 2 && sm::common::GetEnv("SM_ROOT_PATH").empty()) {
    root_path = sm::common::GetCurrentPath();
  }else if (argc >= 2) {
    root_path = argv[1];
  } else {
    root_path = sm::common::GetEnv("SM_ROOT_PATH");
  }
  setenv("SM_ROOT_PATH", root_path.c_str(), 1);
  AINFO << "current work path is [SM_ROOT_PATH]: " << root_path;

  // try to find and load sm_config.json
  std::vector<std::string> path_list;
  size_t count = sm::common::FindPathByPattern(
      root_path, "sm_config.json", DT_REG, true, &path_list);
  if (count <= 0) {
    AERROR << "state config [sm_config.json] not found in " << root_path;
  } else if (count > 1) {
    AWARN << "find too many state config [sm_config.json] in " << root_path
          << ", use the first one: " << path_list[0];
  }
  AINFO << "state config [" << path_list[0] << "] will be load!";
  std::ifstream file(path_list[0], std::ios::in);
  nlohmann::json root = nlohmann::json::parse(file, nullptr, true, true);
  file.close();
  if (root.is_discarded()) {
    AWARN << "state config [" << path_list[0] << "] invalid, parse file failed";
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