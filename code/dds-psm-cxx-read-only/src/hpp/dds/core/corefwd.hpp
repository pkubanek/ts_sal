#ifndef OMG_DDS_CORE_CORE_FWD_HPP_
#define OMG_DDS_CORE_CORE_FWD_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include <vector>

#include <dds/core/detail/corefwd.hpp>
#include <tdds/core/corefwd.hpp>

namespace dds { namespace core {

class AlreadyClosedError;

typedef std::vector<uint8_t> ByteSeq;

class Duration;

typedef ::dds::core::detail::Entity Entity;

class Error;

class Exception;

class IllegalOperationError;

class ImmutablePolicyError;

class InconsistentPolicyError;

typedef ::dds::core::detail::InstanceHandle InstanceHandle;

typedef std::vector<InstanceHandle> InstanceHandleSeq;

class InvalidArgumentError;

class InvalidDataError;

class InvalidDowncastError;

template <typename T1, typename T2>
struct is_base_of;

template <typename T1, typename T2>
struct is_same;

class NotEnabledError;

class NullReferenceError;

class null_type;

class OutOfResourcesError;

template <typename TO, typename FROM>
TO polymorphic_cast(FROM& from);

class PreconditionNotMetError;

template <typename DELEGATE>
class Reference;

template <typename T>
struct smart_ptr_traits;

typedef std::vector<std::string> StringSeq;

class Time;

class TimeoutError;

class UnsupportedError;

template <typename DELEGATE>
class Value;

template <typename T>
class WeakReference;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

template <typename T, template <typename Q> class DELEGATE = dds::core::detail::optional >
class optional;

#endif

namespace cond {
    typedef ::dds::core::cond::detail::Condition Condition;

    typedef ::dds::core::cond::detail::GuardCondition GuardCondition;

    template <typename ENTITY,
              typename DELEGATE = dds::core::cond::detail::StatusCondition<ENTITY> >
    class StatusCondition;

    typedef ::tdds::core::cond::WaitSet< ::dds::core::cond::detail::WaitSet >
    WaitSet;
}


namespace policy {
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
	typedef uint16_t DataRepresentationId;

	typedef std::vector<DataRepresentationId> DataRepresentationIdSeq;
#endif

    typedef dds::core::policy::detail::Deadline
    Deadline;

    typedef dds::core::policy::detail::DestinationOrder
    DestinationOrder;

    typedef dds::core::policy::detail::Durability
    Durability;

    typedef dds::core::policy::detail::EntityFactory
    EntityFactory;

    typedef dds::core::policy::detail::GroupData
    GroupData;

    typedef dds::core::policy::detail::History
    History;

    typedef dds::core::policy::detail::LatencyBudget
    LatencyBudget;

    typedef dds::core::policy::detail::Lifespan
    Lifespan;

    typedef dds::core::policy::detail::Liveliness
    Liveliness;

    typedef dds::core::policy::detail::Ownership
    Ownership;

#ifdef  OMG_DDS_OWNERSHIP_SUPPORT
    typedef dds::core::policy::detail::OwnershipStrength
    OwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    typedef dds::core::policy::detail::Partition
    Partition;

    template <typename Policy>
    class policy_id;

    template <typename Policy>
    class policy_name;

    typedef dds::core::policy::detail::Presentation
    Presentation;

    typedef ::dds::core::policy::detail::QosPolicyCount QosPolicyCount;

    typedef std::vector<QosPolicyCount> QosPolicyCountSeq;

    typedef uint32_t QosPolicyId;

    typedef dds::core::policy::detail::ReaderDataLifecycle
    ReaderDataLifecycle;

    typedef dds::core::policy::detail::Reliability
    Reliability;

    typedef dds::core::policy::detail::ResourceLimits
    ResourceLimits;

    typedef dds::core::policy::detail::TimeBasedFilter
    TimeBasedFilter;

    typedef dds::core::policy::detail::TopicData
    TopicData;

    typedef dds::core::policy::detail::TransportPriority
    TransportPriority;

    typedef dds::core::policy::detail::UserData
    UserData;

    typedef dds::core::policy::detail::WriterDataLifecycle
    WriterDataLifecycle;

#ifdef  OMG_DDS_PERSISTENCE_SUPPORT
    typedef ::dds::core::policy::detail::DurabilityService
    DurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    // TODO
#endif
}


namespace status {
    class DataAvailableStatus;

    class DataOnReadersStatus;

    typedef ::dds::core::status::detail::InconsistentTopicStatus
    InconsistentTopicStatus;

    typedef ::dds::core::status::detail::LivelinessChangedStatus
    LivelinessChangedStatus;

    typedef ::dds::core::status::detail::LivelinessLostStatus
    LivelinessLostStatus;

    typedef ::dds::core::status::detail::OfferedDeadlineMissedStatus
 	OfferedDeadlineMissedStatus;

    typedef ::dds::core::status::detail::OfferedIncompatibleQosStatus
 	OfferedIncompatibleQosStatus;

    typedef ::dds::core::status::detail::PublicationMatchedStatus
    PublicationMatchedStatus;

    class SampleRejectedState;

    typedef ::dds::core::status::detail::SampleRejectedStatus
    SampleRejectedStatus;

    typedef ::dds::core::status::detail::RequestedDeadlineMissedStatus
 	RequestedDeadlineMissedStatus;

    typedef ::dds::core::status::detail::RequestedIncompatibleQosStatus
    RequestedIncompatibleQosStatus;

    typedef ::dds::core::status::detail::SampleLostStatus
    SampleLostStatus;

    class StatusMask;

    typedef ::dds::core::status::detail::SubscriptionMatchedStatus
    SubscriptionMatchedStatus;
}

} }

#endif /* OMG_DDS_CORE_CORE_FWD_HPP_ */
