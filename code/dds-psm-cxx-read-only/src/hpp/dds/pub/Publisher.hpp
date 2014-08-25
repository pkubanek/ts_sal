#ifndef OMG_DDS_PUB_PUBLISHER_HPP_
#define OMG_DDS_PUB_PUBLISHER_HPP_

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

#include <dds/pub/pubfwd.hpp>
#include <dds/pub/detail/Publisher.hpp>
#include <dds/pub/detail/PublisherHolder.hpp>
#include <dds/core/ref_traits.hpp>

template <typename DELEGATE> template <typename T>
dds::pub::DataWriter<T>
tdds::pub::Publisher<DELEGATE>::create_datawriter(
        const dds::topic::Topic<T>& a_topic,
        const dds::pub::qos::DataWriterQos& a_qos,
        dds::pub::DataWriterListener<T>* a_listener,
        const dds::core::status::StatusMask& a_mask) {
    return dds::pub::DataWriter<T>(
        new dds::pub::detail::DataWriter<T>(
            a_topic,
            a_qos,
            dds::core::smart_ptr_traits<dds::pub::detail::PublisherHolder>::ref_type(new dds::pub::detail::PublisherHolder(*this))));
}

#endif /* OMG_DDS_PUB_PUBLISHER_HPP_ */
