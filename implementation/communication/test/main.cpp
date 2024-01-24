#include <signal.h>
#include <mutex>
#include <condition_variable>

#include <glog/logging.h>

#include "common/log.h"
#include "communication/server/server_impl.h"

std::mutex g_app_mutex;
std::condition_variable g_app_cv;

int main(int , char const *argv[]) {
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


  sm::communication::server::ServerImpl::Instance()->Init();
  sm::Message message;
  message.id(0);
  message.msg_type(sm::MsgType::kS2S);
  message.content("something");
  sm::communication::server::ServerImpl::Instance()->Publish(message);




  // Running
  AINFO << "Starting test app ...";
  std::unique_lock<std::mutex> lock(g_app_mutex);
  g_app_cv.wait(lock);



  // Shutdown test app
  AINFO << "Shutting down test app...";
  sm::communication::server::ServerImpl::Instance()->CleanUp();
  google::ShutdownGoogleLogging();
  return 0;
}
