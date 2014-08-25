#ifndef OMG_DDS_PUB_DETAIL_PUB_FWD_HPP_
#define OMG_DDS_PUB_DETAIL_PUB_FWD_HPP_

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

#include <tdds/core/corefwd.hpp>
#include <tdds/pub/pubfwd.hpp>
#include <idds/pub/pubfwd.hpp>


namespace dds { namespace pub {

namespace detail {
    typedef ::tdds::pub::CoherentSet<idds::pub::CoherentSetImpl>
    CoherentSet;

    template <typename T>
    class DataWriter;

    typedef ::tdds::pub::Publisher<idds::pub::PublisherImpl>
    Publisher;

    class PublisherHolder;

    typedef ::tdds::pub::SuspendedPublication<idds::pub::SuspendedPublicationImpl>
    SuspendedPublication;
}   // namespace dds::pub::detail


namespace qos { namespace detail {
    typedef tdds::core::qos::EntityQos< idds::qos::DataWriterQosImpl >
    DataWriterQos;

    typedef tdds::core::qos::EntityQos< idds::qos::PublisherQosImpl >
    PublisherQos;
} } // namespace dds::pub::qos::detail

} }

#endif /* OMG_DDS_PUB_DETAIL_PUB_FWD_HPP_ */
