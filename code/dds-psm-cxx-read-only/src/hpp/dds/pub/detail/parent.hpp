#ifndef OMG_DDS_PUB_DETAIL_PARENT_HPP_
#define OMG_DDS_PUB_DETAIL_PARENT_HPP_

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
#include <dds/pub/detail/PublisherHolder.hpp>
#include <dds/pub/Publisher.hpp>
#include <dds/domain/DomainParticipant.hpp>


namespace dds { namespace pub { namespace detail {

    template <typename T>
    dds::pub::Publisher parent(const dds::pub::DataWriter<T>& writer) {
        return writer->parent()->get();
    }

    dds::pub::Publisher parent(const dds::pub::AnyDataWriter& writer);

    dds::domain::DomainParticipant parent(const dds::pub::Publisher& pub);

} } }


#endif /* OMG_DDS_PUB_DETAIL_PARENT_HPP_ */
