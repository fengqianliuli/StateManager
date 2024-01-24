#include "communication/client/client_impl.h"

#include "common/log.h"

namespace sm {
namespace communication {
namespace client {

ClientImpl::ClientImpl()
    : type_(new MessagePubSubType()) {

}

ClientImpl::~ClientImpl() {
  if (writer_ != nullptr) {
    publisher_->delete_datawriter(writer_);
  }
  if (reader_ != nullptr) {
    subscriber_->delete_datareader(reader_);
  }
  if (publisher_ != nullptr) {
    participant_->delete_publisher(publisher_);
  }
  if (subscriber_ != nullptr) {
    participant_->delete_subscriber(subscriber_);
  }
  if (topic_ != nullptr) {
    participant_->delete_topic(topic_);
  }
  DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool ClientImpl::Init() {
  // init participant_
  DomainParticipantQos participantQos;
  participantQos.name("sm_client");
  participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
  if (participant_ == nullptr) {
    AERROR << "create participant failed!";
    return false;
  }

  // Register the Type
  type_.register_type(participant_);
  // Create the publications Topic
  topic_ = participant_->create_topic(kTopicName, kTypeName, TOPIC_QOS_DEFAULT);
  if (topic_ == nullptr) {
    AERROR << "create topic failed!";
    return false;
  }

  // Create the Publisher
  publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
  if (publisher_ == nullptr) {
    AERROR << "create publisher failed!";
    return false;
  }

  // Create the DataWriter
  writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT);
  local_writer_guid_ = writer_->guid();
  if (writer_ == nullptr) {
    AERROR << "create data_writer failed!";
    return false;
  }

  // Create the Subscriber
  subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
  if (subscriber_ == nullptr) {
    AERROR << "create subscriber failed!";
    return false;
  }

  // Create the DataReader
  reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, this);
  if (reader_ == nullptr) {
    AERROR << "create data_reader failed!";
    return false;
  }

  return true;
}

void ClientImpl::Publish(Message& message) {
  if (writer_ != nullptr) {
    writer_->write(&message);
  }
}

void ClientImpl::on_data_available(DataReader* reader) {
  if (reader->take_next_sample(&message_, &info_) == ReturnCode_t::RETCODE_OK) {
    if (info_.valid_data) {
      if (local_writer_guid_ == info_.sample_identity.writer_guid()) {
        AINFO << "ignore message from myself.";
        return;
      }
      this->msg_handler();
    }
  }
}

void ClientImpl::msg_handler() {
  AINFO <<
    "Received message: id[" << message_.id() << "]"
    " msg_type[" << message_.msg_type() << "]"
    " content[" << message_.content() << "]";
}

}  // namespace client
}  // namespace communication
}  // namespace sm
