#include "communication/server/server_impl.h"

#include "common/log.h"
#include "communication/common_def.h"

namespace sm {
namespace communication {
namespace server {

ServerImpl::ServerImpl()
    : runtime_(vsomeip::runtime::get()),
      app_(runtime_->create_application("StateManager")) {

}

bool ServerImpl::Init() {
  // init vsomeip app and register
  std::lock_guard<std::mutex> its_lock(mutex_);

  if (!app_->init()) {
    AERROR << "failed to initialize vsomeip application.";
    return false;
  }
  app_->register_state_handler(
    std::bind(&ServerImpl::on_state, this, std::placeholders::_1));
  app_->register_message_handler(
    kSmServiceId, vsomeip::ANY_INSTANCE, kSmMethodId,
    std::bind(&ServerImpl::on_message, this, std::placeholders::_1)
  );
  return true;
}

void ServerImpl::Start() {
  app_->start();
}

void ServerImpl::Stop() {
  app_->clear_all_handler();
  app_->stop_offer_service(kSmServiceId, vsomeip::ANY_INSTANCE);
  app_->stop();
}

void ServerImpl::on_state(vsomeip::state_type_e _state) {
  AINFO << "application " << app_->get_name() << " is "
        << (_state == vsomeip::state_type_e::ST_REGISTERED ?
            "registered." : "deregistered.");
  if (_state == vsomeip::state_type_e::ST_REGISTERED) {
    app_->offer_service(kSmServiceId, vsomeip::ANY_INSTANCE);
  }
}

void ServerImpl::on_message(const std::shared_ptr<vsomeip::message>& _request) {
  AINFO << "Received a message: "
        << "client: " << _request->get_client() << "."
        << "session: " << _request->get_session() << "."
        << "service: " << _request->get_service() << "."
        << "instance: " << _request->get_instance() << "."
        << "method: " << _request->get_method() << ".";
}


}  // namespace server
}  // namespace communication
}  // namespace sm
