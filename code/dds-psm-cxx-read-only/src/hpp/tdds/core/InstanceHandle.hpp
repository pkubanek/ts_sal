#ifndef OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_
#define OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_

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
#include <dds/core/Value.hpp>


namespace tdds { namespace core {

template <typename DELEGATE>
class InstanceHandle : public dds::core::Value<DELEGATE> {
public:
    InstanceHandle() { }

    InstanceHandle(const dds::core::null_type& src)
    : dds::core::Value<DELEGATE>(src) { }

    ~InstanceHandle() { }

public:
    static const InstanceHandle nil() {
        return InstanceHandle();
    }

    bool operator==(const InstanceHandle& other) const {
    	return this->delegate().operator==(other);
    }

    InstanceHandle& operator=(const dds::core::null_type& src) {
    	this->delegate()->operator=(src);
    }

    bool operator==(const dds::core::null_type& other) const {
    	return this->is_nil();
    }

    bool is_nil() const {
    	return this->delegate()->is_nil();
    }
};

} }

#endif // !defined(OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_)
