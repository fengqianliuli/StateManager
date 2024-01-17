/******************************************************************************
 * Copyright 2023 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "plugin_manager/plugin_manager.h"

#include <dirent.h>
#include <unistd.h>

#include <memory>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>

#include "common/environment.h"
#include "common/file.h"
#include "common/log.h"
#include "plugin_manager/plugin_description.h"

namespace sm {
namespace plugin_manager {

PluginManager::PluginManager() {}

PluginManager::~PluginManager() {}

bool PluginManager::ProcessPluginDescriptionFile(const std::string& file_path,
                                                 std::string* library_path) {
  std::ifstream file(file_path, std::ios::in);
  nlohmann::json root = nlohmann::json::parse(file, nullptr, true, true);
  file.close();
  if (root.is_discarded()) {
    AWARN << "fail to process file " << file_path;
    return false;
  }

  // TODO(liangjinping): parse as struct
  *library_path = root["path"];

  // TODO(liangjinping): parse description file and do something more

  return true;
}

bool PluginManager::LoadPlugin(
    const std::string& plugin_description_file_path) {
  AINFO << "loading plugin from description[" << plugin_description_file_path
        << "]";

  auto description =
      std::make_shared<sm::plugin_manager::PluginDescription>();
  if (!description->ParseFromDescriptionFile(plugin_description_file_path)) {
    return false;
  }

  if (plugin_description_map_.find(description->name_) !=
      plugin_description_map_.end()) {
    AWARN << "plugin [" << description->name_ << "] already loaded";
    return true;
  }

  if (!LoadLibrary(description->actual_library_path_)) {
    AWARN << "plugin description[" << plugin_description_file_path << "] name["
          << description->name_ << "] load failed, library["
          << description->actual_library_path_ << "] invalid";
    return false;
  }

  plugin_loaded_map_[description->name_] = true;
  plugin_description_map_[description->name_] = description;
  for (auto& class_name_pair : description->class_name_base_class_name_map_) {
    plugin_class_plugin_name_map_[class_name_pair] = description->name_;
  }
  AINFO << "plugin description[" << plugin_description_file_path << "] name["
        << description->name_ << "] load success";
  return true;
}

/**
 * @brief find sm_plugin_index directory
 * @param base_path search root
 * @param path_list vector for storing result
 * @return true if at least one is found
 */
bool FindPlunginIndexPath(const std::string& base_path,
                          std::vector<std::string>* path_list) {
  // TODO(liangjinping): change to configurable
  size_t count = sm::common::FindPathByPattern(
      base_path, "sm_plugin_index", DT_DIR, true, path_list);
  return count > 0;
}

bool PluginManager::FindPluginIndexAndLoad(
    const std::string& plugin_index_path) {
  std::vector<std::string> plugin_index_list;
  sm::common::FindPathByPattern(plugin_index_path, "", DT_REG, false,
                                           &plugin_index_list);
  bool success = true;
  for (auto plugin_index : plugin_index_list) {
    std::string plugin_name = sm::common::GetFileName(plugin_index);
    AINFO << "plugin index[" << plugin_index << "] name[" << plugin_name
          << "] found";
    if (plugin_description_map_.find(plugin_name) !=
        plugin_description_map_.end()) {
      AWARN << "plugin [" << plugin_name << "] already loaded";
      continue;
    }

    auto description = std::make_shared<PluginDescription>(plugin_name);
    if (!description->ParseFromIndexFile(plugin_index)) {
      success = false;
      // invalid index file
      continue;
    }

    // load now
    // if (!class_loader_manager_.LoadLibrary(actual_library_path)) {
    //   success = false;
    //   AWARN << "plugin index[" << plugin_index << "] name[" << plugin_name
    //         << "] load failed, library[" << actual_library_path << "]
    //         invalid";
    //   continue;
    // }

    // lazy load
    plugin_loaded_map_[description->name_] = false;
    plugin_description_map_[description->name_] = description;
    for (auto& class_name_pair : description->class_name_base_class_name_map_) {
      plugin_class_plugin_name_map_[class_name_pair] = description->name_;
    }
    AINFO << "plugin index[" << plugin_index << "] name[" << description->name_
          << "] lazy load success";
  }
  return success;
}

bool PluginManager::LoadInstalledPlugins() {
  if (!sm::common::GetEnv("SM_ROOT_PATH").empty()) {
    AWARN << "search plugin index path under SM_ROOT_PATH, it may take "
             "longer time to load plugins";
    // enable scanning sm_plugin_index path under SM_ROOT_PATH
    const std::string sm_root_path =
        sm::common::GetEnv("SM_ROOT_PATH");
    // TODO(infra): make it configurable or detect automatically
    std::vector<std::string> user_plugin_index_path_list;
    AINFO << "scanning plugin index path under " << sm_root_path;
    FindPlunginIndexPath(sm_root_path, &user_plugin_index_path_list);
    // load user plugin with higher priority
    for (auto dir : user_plugin_index_path_list) {
      AINFO << "loading user plugins from path[" << dir << "]";
      FindPluginIndexAndLoad(dir);
    }
  }
  return true;
}

bool PluginManager::LoadLibrary(const std::string& library_path) {
  if (!class_loader_manager_.LoadLibrary(library_path)) {
    AWARN << "plugin library[" << library_path << "] load failed";
    return false;
  }
  return true;
}

}  // namespace plugin_manager
}  // namespace sm
