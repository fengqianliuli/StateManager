#pragma once

#include "common/macros.h"

#include <string>
#include <memory>
#include <mutex>

#include <vsomeip/vsomeip.hpp>

namespace sm {
namespace communication {
namespace server {

class ServerImpl {
DECLARE_SINGLETON(ServerImpl);

 public:
  ~ServerImpl() = default;
  bool Init();
  void Start();
  void Stop();

 private:
  void on_state(vsomeip::state_type_e _state);
  void on_message(const std::shared_ptr<vsomeip::message> &_request);

 private:
  std::shared_ptr<vsomeip::runtime> runtime_;
  std::shared_ptr<vsomeip::application> app_;
  std::mutex mutex_;
};

}  // namespace server
}  // namespace communication
}  // namespace sm
