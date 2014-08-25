#ifndef OMG_DDS_SUB_SUB_MODULE_HPP_
#define OMG_DDS_SUB_SUB_MODULE_HPP_

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


// This file is an omnibus header for the sub module of the DDS API.

// --- Data: --- //
#include <dds/sub/status/ReaderState.hpp>
#include <dds/sub/Sample.hpp>

// --- DataReader: --- //
#include <dds/sub/ReaderQuery.hpp>
#include <dds/sub/qos/DataReaderQos.hpp>
#include <dds/sub/DataReaderListener.hpp>
#include <dds/sub/AnyDataReaderListener.hpp>
#include <dds/sub/DataReader.hpp>
#include <dds/sub/AnyDataReader.hpp>

// --- ReadCondition & QueryCondition: --- //
#include <dds/sub/cond/ReadCondition.hpp>
#include <dds/sub/cond/QueryCondition.hpp>

// --- Subscriber: --- //
#include <dds/sub/qos/SubscriberQos.hpp>
#include <dds/sub/SubscriberListener.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/sub/CoherentAccess.hpp>

// --- Search Functions: --- //
#include <dds/sub/discovery.hpp>
#include <dds/sub/find.hpp>
#include <dds/sub/parent.hpp>


#endif /* OMG_DDS_SUB_SUB_MODULE_HPP_ */
