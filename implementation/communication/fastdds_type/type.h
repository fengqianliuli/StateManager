#pragma once

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "communication/fastdds_type/messagePubSubTypes.h"

using eprosima::fastdds::dds::DomainParticipant;
using eprosima::fastdds::dds::DomainParticipantQos;
using eprosima::fastdds::dds::DomainParticipantFactory;
using eprosima::fastdds::dds::TypeSupport;
using eprosima::fastdds::dds::Topic;
using eprosima::fastdds::dds::Publisher;
using eprosima::fastdds::dds::Subscriber;
using eprosima::fastdds::dds::DataWriter;
using eprosima::fastdds::dds::DataReader;
using eprosima::fastdds::dds::DataReaderListener;
using eprosima::fastdds::dds::SampleInfo;

using eprosima::fastdds::dds::TOPIC_QOS_DEFAULT;
using eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT;
using eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT;
using eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT;
using eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;

using eprosima::fastrtps::rtps::GUID_t;

namespace sm {
namespace communication {

constexpr char kTopicName[] = "sm_message_topic";
constexpr char kTypeName[] = "sm::Message";

}  // namespace communication
}  // namespace sm