#ifndef OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_
#define OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/core/detail/inttypes.hpp>
#include <tdds/core/corefwd.hpp>
#include <idds/core/corefwd.hpp>


namespace dds { namespace core {

namespace detail {
    typedef tdds::core::Entity<idds::core::EntityImpl> Entity;

    typedef ::tdds::core::InstanceHandle< idds::core::InstanceHandleImpl >
    InstanceHandle;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    template <typename T>
    class optional;

#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

}   // namespace dds::core::detail


namespace cond { namespace detail {

    typedef ::tdds::core::cond::Condition<idds::core::ConditionImpl> Condition;

    typedef ::tdds::core::cond::GuardCondition<idds::core::GuardConditionImpl>
    GuardCondition;

    template <typename ENTITY> class StatusCondition;

    class WaitSet;

} } // namespace dds::core::cond::detail


namespace policy { namespace detail {
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    typedef tdds::core::policy::DataRepresentation<idds::core::policy::DataRepresentation>
    DataRepresentation;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    typedef tdds::core::policy::Deadline<idds::core::policy::Deadline>
    Deadline;

    typedef tdds::core::policy::DestinationOrder<idds::core::policy::DestinationOrder>
    DestinationOrder;

    typedef tdds::core::policy::Durability<idds::core::policy::Durability>
    Durability;

#ifdef  OMG_DDS_PERSISTENCE_SUPPORT
    typedef tdds::core::policy::DurabilityService<idds::core::policy::DurabilityService>
    DurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    typedef tdds::core::policy::EntityFactory<idds::core::policy::EntityFactory>
    EntityFactory;

    typedef tdds::core::policy::GroupData<idds::core::policy::GroupData>
    GroupData;

    typedef tdds::core::policy::History<idds::core::policy::History>
    History;

    typedef tdds::core::policy::LatencyBudget<idds::core::policy::LatencyBudget>
    LatencyBudget;

    typedef tdds::core::policy::Lifespan<idds::core::policy::Lifespan>
    Lifespan;

    typedef tdds::core::policy::Liveliness<idds::core::policy::Liveliness>
    Liveliness;

    typedef tdds::core::policy::Ownership<idds::core::policy::Ownership>
    Ownership;

#ifdef  OMG_DDS_OWNERSHIP_SUPPORT
    typedef tdds::core::policy::OwnershipStrength<idds::core::policy::OwnershipStrength>
    OwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    typedef tdds::core::policy::Partition<idds::core::policy::Partition>
    Partition;

    typedef tdds::core::policy::Presentation<idds::core::policy::Presentation>
    Presentation;

    typedef ::tdds::core::policy::QosPolicyCount< idds::core::policy::QosPolicyCountImpl >
    QosPolicyCount;

    typedef tdds::core::policy::ReaderDataLifecycle<idds::core::policy::ReaderDataLifecycle>
    ReaderDataLifecycle;

    typedef tdds::core::policy::Reliability<idds::core::policy::Reliability>
    Reliability;

    typedef tdds::core::policy::ResourceLimits<idds::core::policy::ResourceLimits>
    ResourceLimits;

    typedef tdds::core::policy::TimeBasedFilter<idds::core::policy::TimeBasedFilter>
    TimeBasedFilter;

    typedef tdds::core::policy::TopicData<idds::core::policy::TopicData>
    TopicData;

    typedef tdds::core::policy::TransportPriority<idds::core::policy::TransportPriority>
    TransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    typedef tdds::core::policy::TypeConsistencyEnforcement<idds::core::policy::TypeConsistencyEnforcement>
    TypeConsistencyEnforcement;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    typedef tdds::core::policy::UserData<idds::core::policy::UserData>
    UserData;

    typedef tdds::core::policy::WriterDataLifecycle<idds::core::policy::WriterDataLifecycle>
    WriterDataLifecycle;
} } // namespace dds::core::policy::detail


namespace status { namespace detail {
    typedef tdds::core::status::InconsistentTopicStatus< idds::core::InconsistentTopicStatusImpl >
    InconsistentTopicStatus;

    typedef tdds::core::status::LivelinessChangedStatus <idds::core::LivelinessChangedStatusImpl>
    LivelinessChangedStatus;

    typedef tdds::core::status::LivelinessLostStatus<idds::core::LivelinessLostStatusImpl>
    LivelinessLostStatus;

    typedef tdds::core::status::OfferedDeadlineMissedStatus<idds::core::OfferedDeadlineMissedStatusImpl>
    OfferedDeadlineMissedStatus;

    typedef tdds::core::status::OfferedIncompatibleQosStatus<idds::core::OfferedIncompatibleQosStatusImpl>
    OfferedIncompatibleQosStatus;

    typedef tdds::core::status::PublicationMatchedStatus<idds::core::PublicationMatchedStatusImpl>
    PublicationMatchedStatus;

    typedef tdds::core::status::SampleRejectedStatus< idds::core::SampleRejectedStatusImpl >
    SampleRejectedStatus;

    typedef tdds::core::status::RequestedDeadlineMissedStatus<idds::core::RequestedDeadlineMissedStatusImpl>
    RequestedDeadlineMissedStatus;

    typedef tdds::core::status::RequestedIncompatibleQosStatus<idds::core::RequestedIncompatibleQosStatusImpl>
    RequestedIncompatibleQosStatus;

    typedef tdds::core::status::SampleLostStatus<idds::core::SampleLostStatusImpl>
    SampleLostStatus;

    typedef tdds::core::status::SubscriptionMatchedStatus<idds::core::SubscriptionMatchedStatusImpl>
    SubscriptionMatchedStatus;
} } // namespace dds::core::status::detail

} }

#endif /* OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_ */
