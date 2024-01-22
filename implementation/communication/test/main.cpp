#include <signal.h>

#include <glog/logging.h>

#include "common/log.h"
#include "communication/server/server_impl.h"


int main(int , char const *argv[]) {
  // Initialize glog
  google::InitGoogleLogging(argv[0]);
  FLAGS_minloglevel = google::INFO;
  FLAGS_logtostdout = true;
  FLAGS_colorlogtostdout = true;

  // register signal for exit
  auto signal_handler = [](int signal) {
    AINFO << "Signal: " << signal << " received, exiting...";
    sm::communication::server::ServerImpl::Instance()->Stop();
  };
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);


  sm::communication::server::ServerImpl::Instance()->Init();
  // Running
  AINFO << "Starting test app ...";
  sm::communication::server::ServerImpl::Instance()->Start();



  // Shutdown test app
  AINFO << "Shutting down test app...";

  google::ShutdownGoogleLogging();
  return 0;
}
