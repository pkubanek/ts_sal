#ifndef OMG_DDS_SUB_DETAIL_PARENT_HPP_
#define OMG_DDS_SUB_DETAIL_PARENT_HPP_

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

#include <dds/core/ref_traits.hpp>
#include <dds/core/macros.hpp>
#include <dds/sub/subfwd.hpp>
#include <dds/sub/cond/ReadCondition.hpp>
#include <dds/sub/DataReader.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/domain/DomainParticipant.hpp>


namespace dds { namespace sub { namespace detail {

    dds::domain::DomainParticipant parent(const dds::sub::Subscriber& sub);


    dds::sub::Subscriber parent(const dds::sub::AnyDataReader& reader);


    // Also works with QueryCondition, which extends ReadCondition
    template <typename READER, typename T>
    READER parent(const ::dds::sub::cond::ReadCondition<T>& c) {
        OMG_DDS_STATIC_ASSERT((::dds::core::is_same<T, typename READER::DataType>::value));
        return c->parent()->get();
    }
    
} } }


#endif /* OMG_DDS_SUB_DETAIL_PARENT_HPP_ */
