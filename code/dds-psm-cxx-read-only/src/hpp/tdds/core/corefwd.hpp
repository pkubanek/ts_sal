#ifndef OMG_TDDS_CORE_CORE_FWD_HPP_
#define OMG_TDDS_CORE_CORE_FWD_HPP_

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


namespace tdds { namespace core {

template <typename DELEGATE>
class Entity;


template <typename DELEGATE>
class InstanceHandle;


namespace cond {
    template <typename DELEGATE>
    class Condition;

    template <typename DELEGATE>
    class GuardCondition;

    template <typename DELEGATE>
    class WaitSet;
}


namespace policy {
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    template <typename DELEGATE>
    class DataRepresentation;
#endif  // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    template <typename DELEGATE>
    class Deadline;

    template <typename DELEGATE>
    class DestinationOrder;

    template <typename DELEGATE>
    class Durability;

#ifdef OMG_DDS_PERSISTENCE_SUPPORT
    template <typename DELEGATE>
    class DurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    template <typename DELEGATE>
    class EntityFactory;

    template <typename DELEGATE>
    class GroupData;

    template <typename DELEGATE>
    class History;

    template <typename DELEGATE>
    class LatencyBudget;

    template <typename DELEGATE>
    class Lifespan;

    template <typename DELEGATE>
    class Liveliness;

    template <typename DELEGATE>
    class Ownership;

#ifdef OMG_DDS_OWNERSHIP_SUPPORT
    template <typename DELEGATE>
    class OwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    template <typename DELEGATE>
    class Partition;

    template <typename DELEGATE>
    class Presentation;

    template <typename DELEGATE>
    class ResourceLimits;

    template <typename DELEGATE>
    class QosPolicyCount;

    template <typename DELEGATE>
    class ReaderDataLifecycle;

    template <typename DELEGATE>
    class Reliability;

    template <typename DELEGATE>
    class TimeBasedFilter;

    template <typename DELEGATE>
    class TopicData;

    template <typename DELEGATE>
    class TransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    template <typename DELEGATE>
    class TypeConsistencyEnforcement;
#endif  // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    template <typename DELEGATE>
    class UserData;

    template <typename DELEGATE>
    class WriterDataLifecycle;
}


namespace qos {
    template <typename DELEGATE>
    class EntityQos;
}


namespace status {
    template <typename D>
    class InconsistentTopicStatus;

    template <typename D>
    class SampleLostStatus;

    template <typename D>
    class SampleRejectedStatus;

    template <typename D>
    class LivelinessLostStatus;

    template <typename D>
    class LivelinessChangedStatus;

    template <typename D>
    class OfferedDeadlineMissedStatus;

    template <typename D>
    class RequestedDeadlineMissedStatus;

    template <typename D>
    class OfferedIncompatibleQosStatus;

    template <typename D>
    class RequestedIncompatibleQosStatus;

    template <typename D>
    class PublicationMatchedStatus;

    template <typename D>
    class SubscriptionMatchedStatus;
}

} }

#endif /* OMG_TDDS_CORE_CORE_FWD_HPP_ */
