#ifndef OMG_DDS_TOPIC_DETAIL_TOPIC_HPP_
#define OMG_DDS_TOPIC_DETAIL_TOPIC_HPP_

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

#include <dds/topic/detail/topicfwd.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <dds/core/status/Status.hpp>
#include <idds/topic/TopicDescription.hpp>
#include <dds/core/ref_traits.hpp>

namespace dds { namespace topic { namespace detail {

template <typename T>
class Topic : public idds::topic::TopicDescriptionImpl<T> {
public:
    Topic(const std::string& the_name,
          const std::string& the_type_name,
          const dds::topic::qos::TopicQos& the_qos,
          const dds::core::smart_ptr_traits<dds::domain::detail::DomainParticipantHolder>::ref_type& dp)
    : idds::topic::TopicDescriptionImpl<T>(the_name, the_type_name, dp),
	  qos_(the_qos)
	  { }

public:
    /**
     * Returns a <code>StatusCondition</code> instance associated with
     * this <code>Entity</code>.
     */
    template <typename SELF>
    ::dds::core::cond::StatusCondition<SELF>
    status_condition(const SELF& self) const {
        return ::dds::core::cond::StatusCondition<SELF>(
                new dds::core::cond::detail::StatusCondition<SELF>(self));
    }

public:
	const dds::topic::qos::TopicQos qos() const {
		return qos_;
	}

	void qos(const dds::topic::qos::TopicQos& the_qos) {
		qos_ = the_qos;
	}

	dds::core::status::InconsistentTopicStatus inconsistent_topic_status() {
		return dds::core::status::InconsistentTopicStatus();
	}

private:
	dds::topic::qos::TopicQos qos_;

};

} } }
#endif /* OMG_DDS_TOPIC_DETAIL_TOPIC_HPP_ */
