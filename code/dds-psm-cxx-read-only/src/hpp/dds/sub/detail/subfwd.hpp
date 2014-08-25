#ifndef OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_
#define OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_

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
#include <tdds/sub/subfwd.hpp>
#include <idds/sub/subfwd.hpp>

namespace dds { namespace sub {

namespace detail {
    typedef ::tdds::sub::CoherentAccess< ::idds::sub::CoherentAccessImpl >
    CoherentAccess;

    template <typename T>
    class DataReader;

    template <typename T>
    class DataReaderHolder;

    class GenerationCount;

    template <typename T>
    class LoanedSamples;

    class Rank;

    class SampleInfo;

    template <typename T>
    class Sample;

    class SampleInfo;

    typedef ::tdds::sub::Subscriber< ::idds::sub::SubscriberImpl >
    Subscriber;
}   // namespace dds::sub::detail


namespace cond { namespace detail {
    template <typename T>
    class ReadConditionImpl;

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
    template <typename T>
    class QueryCondition;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
} } // namespace dds::sub::cond::detail


namespace qos { namespace detail {
    typedef tdds::core::qos::EntityQos < idds::qos::DataReaderQosImpl >
    DataReaderQos;

    typedef tdds::core::qos::EntityQos< idds::qos::SubscriberQosImpl >
    SubscriberQos;
} } // namespace dds::sub::qos::detail

} }

#endif /* OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_ */
