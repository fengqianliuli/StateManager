#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <signal.h>

#include <glog/logging.h>

#include "common/log.h"
#include "configuration/configuration.h"
#include "state_manager/state_manager_impl.h"
#include "plugin_manager/plugin_manager.h"
#include "sm/plugin/sm_plugin_interface.h"

std::mutex g_app_mutex;
std::condition_variable g_app_cv;

int main(int argc, char const *argv[]) {
  // Initialize glog
  google::InitGoogleLogging(argv[0]);
  FLAGS_minloglevel = google::INFO;
  FLAGS_logtostdout = true;
  FLAGS_colorlogtostdout = true;

  // register signal for exit
  auto signal_handler = [](int signal) {
    AINFO << "Signal: " << signal << " received, exiting...";
    std::unique_lock<std::mutex> lock(g_app_mutex);
    g_app_cv.notify_all();
  };
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  // Initialize configuration
  if (!sm::config::Configuration::Instance()->Init(argc, argv)) {
      AERROR << "Failed to initialize configuration.";
      return -1;
  }

  // Initialize plugin manager
  sm::plugin_manager::PluginManager::Instance()->LoadInstalledPlugins();

  // Initialize state manager impl
  sm::state_manager::StateManagerImpl::Instance();

  // Test plugin running func
  auto sp = sm::plugin_manager::PluginManager::Instance()->
    CreateInstance<SmPluginInterface>("OtaPlugin");
  sp->Running();
  auto sp1 = sm::plugin_manager::PluginManager::Instance()->
    CreateInstance<SmPluginInterface>("CalibrationPlugin");
  sp1->Running();

  // Running
  AINFO << "Starting state manager app ...";
  std::unique_lock<std::mutex> lock(g_app_mutex);
  g_app_cv.wait(lock);



  // Shutdown state manager app
  sm::state_manager::StateManagerImpl::Instance()->CleanUp();
  sm::plugin_manager::PluginManager::Instance()->CleanUp();
  sm::config::Configuration::Instance()->CleanUp();
  AINFO << "Shutting down state manager app...";

  google::ShutdownGoogleLogging();
  return 0;
}
