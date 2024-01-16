#include <thread>
#include <chrono>

#include <glog/logging.h>

#include "common/log.h"
#include "state_manager/state_manager.h"
#include "configuration/configuration.h"


int main(int argc, char const *argv[]) {
    // Initialize glog
    google::InitGoogleLogging(argv[0]);
    FLAGS_minloglevel = google::INFO;
    FLAGS_logtostdout = true;
    FLAGS_colorlogtostdout = true;

    if (argc < 2) {
        AERROR << "Please provide the config file.";
        return -1;
    }

    // Initialize configuration
    if (!sm::config::Configuration::Instance()->Init(argv[1])) {
        AERROR << "Failed to initialize configuration.";
        return -1;
    }

    // Initialize state manager
    auto sm_instance = sm::state_manager::StateManager::Instance();
    AINFO << "Starting state manager...";


    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Shutdown state manager
    sm_instance->CleanUp();
    AINFO << "Shutting down state manager...";

    google::ShutdownGoogleLogging();
    return 0;
}
