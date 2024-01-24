#pragma once

#include "common/macros.h"

#include <string>

#include "communication/fastdds_type/type.h"

namespace sm {
namespace communication {
namespace server {

class ServerImpl : public DataReaderListener {
DECLARE_SINGLETON(ServerImpl);

 public:
  virtual ~ServerImpl();
  bool Init();
  void Publish(Message& message);

 private:
  void on_data_available(DataReader* reader) override;
  void msg_handler();

 private:
  DomainParticipant* participant_{nullptr};
  Publisher* publisher_{nullptr};
  Subscriber* subscriber_{nullptr};
  Topic* topic_{nullptr};
  DataWriter* writer_{nullptr};
  DataReader* reader_{nullptr};
  TypeSupport type_;
  Message message_;
  SampleInfo info_;

  GUID_t local_writer_guid_;
};

}  // namespace server
}  // namespace communication
}  // namespace sm
