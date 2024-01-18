
#include <iostream>
#include <memory>

#include "sm/plugin/sm_plugin_interface.h"
#include "sm/state/state_manager.h"

class OtaPlugin : public SmPluginInterface {
 public:
  virtual void Run() {
    std::cout << "I am OtaPlugin" << std::endl;
    auto sp = std::make_shared<sm::state_manager::StateManager>();
    std::cout << "OtaPlugin Current state: " << sp->GetCurrentState() << std::endl;
  }
};

class CalibrationPlugin : public SmPluginInterface {
 public:
  virtual void Run() {
    std::cout << "I am CalibrationPlugin" << std::endl;
    auto sp = std::make_shared<sm::state_manager::StateManager>();
    std::cout << "CalibrationPlugin Current state: " << sp->GetCurrentState() << std::endl;
  }
  ~CalibrationPlugin() {}
};

// also useful
// CLASS_LOADER_REGISTER_CLASS(OtaPlugin, SmPluginInterface);

SM_PLUGIN_MANAGER_REGISTER_PLUGIN(OtaPlugin, SmPluginInterface);
SM_PLUGIN_MANAGER_REGISTER_PLUGIN(CalibrationPlugin, SmPluginInterface);

