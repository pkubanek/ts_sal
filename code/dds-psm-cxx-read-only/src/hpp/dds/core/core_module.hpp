#ifndef OMG_DDS_CORE_CORE_MODULE_HPP_
#define OMG_DDS_CORE_CORE_MODULE_HPP_

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

// This file is an omnibus header for the core module of the DDS API.

// --- Simple Value Types: --- //
#include <dds/core/LengthUnlimited.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/Duration.hpp>
#include <dds/core/Time.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/core/types.hpp>
#include <dds/core/Exception.hpp>

// --- QoS Policies & Related Classes: --- //
#include <dds/core/policy/PolicyKind.hpp>
#include <dds/core/policy/QosPolicyCount.hpp>
#include <dds/core/policy/CorePolicy.hpp>

// --- Reference Types: --- //
#include <dds/core/Reference.hpp>
#include <dds/core/WeakReference.hpp>

// --- Conditions & WaitSet: --- //
#include <dds/core/cond/Condition.hpp>
#include <dds/core/cond/GuardCondition.hpp>
#include <dds/core/cond/StatusCondition.hpp>
#include <dds/core/cond/WaitSet.hpp>
#include <dds/core/cond/parent.hpp>

// --- Entity: --- //
#include <dds/core/Entity.hpp>

// --- Entity Status & Related Classes: --- //
#include <dds/core/status/State.hpp>
#include <dds/core/status/Status.hpp>


#endif /* OMG_DDS_CORE_CORE_MODULE_HPP_ */
