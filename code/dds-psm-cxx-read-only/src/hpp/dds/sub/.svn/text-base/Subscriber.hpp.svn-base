#ifndef OMG_DDS_SUB_SUBSCRIBER_HPP_
#define OMG_DDS_SUB_SUBSCRIBER_HPP_

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

#include <dds/sub/subfwd.hpp>
#include <dds/sub/detail/Subscriber.hpp>


template <typename DELEGATE> template <typename T>
dds::sub::DataReader<T>
tdds::sub::Subscriber<DELEGATE>::create_datareader(
        const dds::topic::TopicDescription<T>&  a_topic,
        const dds::sub::qos::DataReaderQos&     a_qos,
        dds::sub::DataReaderListener<T>*        a_listener,
        const dds::core::status::StatusMask&    a_mask) {
    return dds::sub::DataReader<T>(
        new dds::sub::detail::DataReader<T>());
}

#endif /* OMG_DDS_SUB_SUBSCRIBER_HPP_ */
