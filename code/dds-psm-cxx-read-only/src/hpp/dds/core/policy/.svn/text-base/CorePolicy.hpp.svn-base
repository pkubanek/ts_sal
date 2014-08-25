#ifndef OMG_DDS_CORE_POLICY_CORE_POLICY_HPP_
#define OMG_DDS_CORE_POLICY_CORE_POLICY_HPP_

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

#include <dds/core/corefwd.hpp>
#include <dds/core/policy/detail/CorePolicy.hpp>
#include <dds/core/policy/PolicyKind.hpp>


//==============================================================================
// MACROS
//
#define OMG_DDS_POLICY_TRAITS(POLICY, ID) \
        template <> \
        class policy_id<POLICY> { \
        public: \
            static const dds::core::policy::QosPolicyId value = ID; \
        }; \
        template <> \
        class policy_name<POLICY> { \
            static const std::string& name(); \
        };

#define OMG_DDS_DEFINE_POLICY_TRAITS(POLICY, NAME) \
        const std::string& dds::core::policy::policy_name<POLICY>::name() { \
            static std::string the_name = #NAME; \
            return the_name; \
        }


//==============================================================================
// Policy Trait Classes

template <typename Policy>
class dds::core::policy::policy_id { };

template <typename Policy>
class dds::core::policy::policy_name { };


namespace dds { namespace core { namespace policy  {

OMG_DDS_POLICY_TRAITS(UserData,             1)
OMG_DDS_POLICY_TRAITS(Durability,           2)
OMG_DDS_POLICY_TRAITS(Presentation,         3)
OMG_DDS_POLICY_TRAITS(Deadline,             4)
OMG_DDS_POLICY_TRAITS(LatencyBudget,        5)
OMG_DDS_POLICY_TRAITS(Ownership,            6)

#ifdef OMG_DDS_OWNERSHIP_SUPPORT
OMG_DDS_POLICY_TRAITS(OwnershipStrength,    7)
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

OMG_DDS_POLICY_TRAITS(Liveliness,           8)
OMG_DDS_POLICY_TRAITS(TimeBasedFilter,      9)
OMG_DDS_POLICY_TRAITS(Partition,            10)
OMG_DDS_POLICY_TRAITS(Reliability,          11)
OMG_DDS_POLICY_TRAITS(DestinationOrder,     12)
OMG_DDS_POLICY_TRAITS(History,              13)
OMG_DDS_POLICY_TRAITS(ResourceLimits,       14)
OMG_DDS_POLICY_TRAITS(EntityFactory,        15)
OMG_DDS_POLICY_TRAITS(WriterDataLifecycle,  16)
OMG_DDS_POLICY_TRAITS(ReaderDataLifecycle,  17)
OMG_DDS_POLICY_TRAITS(TopicData,            18)
OMG_DDS_POLICY_TRAITS(GroupData,            19)
OMG_DDS_POLICY_TRAITS(TransportPriority,    20)
OMG_DDS_POLICY_TRAITS(Lifespan,             21)

#ifdef  OMG_DDS_PERSISTENCE_SUPPORT
OMG_DDS_POLICY_TRAITS(DurabilityService,    22)
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

} } }


#endif /* OMG_DDS_CORE_POLICY_CORE_POLICY_HPP_ */
