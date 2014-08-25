#ifndef OMG_DDS_SUB_SUB_FWD_HPP_
#define OMG_DDS_SUB_SUB_FWD_HPP_

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
#include <dds/sub/detail/subfwd.hpp>


namespace dds { namespace sub {

class AnyDataReader;

class AnyDataReaderListener;

typedef ::dds::sub::detail::CoherentAccess CoherentAccess;

template <typename T,
          template <typename Q> class DELEGATE = ::dds::sub::detail::DataReader>
class DataReader;

template <typename T>
class DataReaderListener;

typedef ::dds::sub::detail::GenerationCount GenerationCount;

template <typename T, typename DELEGATE = dds::sub::detail::LoanedSamples<T> >
class LoanedSamples;

class NoOpAnyDataReaderListener;

template <typename T>
class NoOpDataReaderListener;

class NoOpSubscriberListener;

typedef ::dds::sub::detail::Rank Rank;

template <typename T>
class ReaderQuery;

template <typename T, typename DELEGATE=dds::sub::detail::Sample<T> >
class Sample;

typedef tdds::sub::SampleInfo<dds::sub::detail::SampleInfo> SampleInfo;

typedef dds::sub::detail::Subscriber Subscriber;

class SubscriberListener;


namespace cond {
	template <typename T,
	          template <typename Q> class DELEGATE = ::dds::sub::cond::detail::ReadConditionImpl>
	class ReadCondition;

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
	template <typename T,
	          template <typename Q> class DELEGATE = ::dds::sub::cond::detail::QueryCondition>
	class QueryCondition;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
}


namespace qos {
    typedef ::dds::sub::qos::detail::DataReaderQos DataReaderQos;

    typedef ::dds::sub::qos::detail::SubscriberQos SubscriberQos;
}


namespace status {
    class ReaderState;
}

} }

#endif /* OMG_DDS_SUB_SUB_FWD_HPP_ */
