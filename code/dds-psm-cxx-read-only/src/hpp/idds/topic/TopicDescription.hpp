#ifndef OMG_IDDS_TOPIC_TOPICDESCRIPTION_HPP_
#define OMG_IDDS_TOPIC_TOPICDESCRIPTION_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
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

#include <string>

#include <idds/core/EntityImpl.hpp>
#include <idds/topic/topicfwd.hpp>
#include <dds/core/ref_traits.hpp>

namespace dds { namespace domain { namespace detail {
    class DomainParticipantHolder;
} } }


namespace idds { namespace topic {

template <typename T>
class TopicDescriptionImpl : public idds::core::EntityImpl {
public:
    typedef dds::core::smart_ptr_traits<dds::domain::detail::DomainParticipantHolder>::ref_type
    DPHolder;

public:
    TopicDescriptionImpl(
            const std::string& the_name,
            const std::string& the_type_name,
            const DPHolder& dp)
    : name_(the_name),
      type_name_(the_type_name),
      dp_(dp) { }

public:
	/**
	 * Get the name used to create the TopicDescription.
	 */
	const std::string& name() const {
		return name_;
	}

	/**
	 * The type_name used to create the TopicDescription.
	 */
	const std::string& type_name() const {
		return type_name_;
	}

    /**
     * This operation returns the DomainParticipant to which the
     * TopicDescription belongs.
     */
    dds::domain::detail::DomainParticipantHolder* parent() const {
        return dp_.get();
    }

protected:
	std::string name_;
	std::string type_name_;
    DPHolder dp_;
};
} }
#endif /* OMG_IDDS_TOPIC_TOPICDESCRIPTION_HPP_ */
