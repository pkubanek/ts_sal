#ifndef OMG_DDS_SUB_PARENT_HPP_
#define OMG_DDS_SUB_PARENT_HPP_

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
#include <dds/sub/detail/parent.hpp>
#include <dds/sub/detail/DataReaderHolder.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/domain/DomainParticipant.hpp>


namespace dds { namespace sub {

    inline dds::domain::DomainParticipant parent(const Subscriber& sub) {
        return ::dds::sub::detail::parent(sub);
    }


    inline Subscriber parent(const AnyDataReader& reader) {
        return ::dds::sub::detail::parent(reader);
    }


    template <typename T>
    Subscriber parent(const DataReader<T>& reader) {
        return ::dds::sub::detail::parent<T>(reader);
    }


    // Also works with QueryCondition, which extends ReadCondition
    template <typename READER, typename T>
    READER parent(const ::dds::sub::cond::ReadCondition<T>& cond) {
        return ::dds::sub::detail::parent<READER, T>(cond);
    }

} }


#endif /* OMG_DDS_SUB_PARENT_HPP_ */
