#ifndef OMG_TDDS_PUB_PUBLISHER_HPP_
#define OMG_TDDS_PUB_PUBLISHER_HPP_

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
#include <tdds/core/Entity.hpp>
#include <dds/core/cond/StatusCondition.hpp>
#include <dds/pub/pubfwd.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>
#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/domain/domainfwd.hpp>


namespace tdds { namespace pub {

/**
 * The Publisher acts on the behalf of one or several DataWriter objects
 * that belong to it. When it is informed of a change to the data associated
 * with one of its DataWriter objects, it decides when it is appropriate
 * to actually send the data-update message. In making this decision, it
 * considers any extra information that goes with the data (timestamp,
 * writer, etc.) as well as the QoS of the Publisher and the DataWriter.
 */
template <typename DELEGATE>
class Publisher : public tdds::core::Entity<DELEGATE> {
public:
    typedef dds::pub::PublisherListener                 Listener;
    typedef dds::core::cond::StatusCondition<Publisher> StatusCondition;
public:
	OMG_DDS_REF_TYPE(Publisher, tdds::core::Entity, DELEGATE)

	~Publisher() { }

    using tdds::core::Entity<DELEGATE>::qos;

	const dds::pub::qos::PublisherQos qos() const {
		return this->delegate()->qos();
	}


	void qos(const dds::pub::qos::PublisherQos& the_qos) {
		this->delegate()->qos(the_qos);
	}

	Publisher& operator <<(const dds::pub::qos::PublisherQos& the_qos) {
		this->delegate()->qos(the_qos);
		return *this;
	}

	Publisher& operator >> (dds::pub::qos::PublisherQos& the_qos) {
		the_qos = this->delegate()->qos();
		return *this;
	}

    void listener(Listener* the_listener,
                  const dds::core::status::StatusMask& event_mask);

    Listener* listener() const;

public:
    /**
     * This operation allows access to the StatusCondition
     * (Section 7.1.2.1.9, “StatusCondition Class) associated with the Entity.
     * The returned condition can then be added to a WaitSet (Section 7.1.2.1.6,
     * WaitSet Class) so that the application can wait for specific status changes
     * that affect the Entity.
     *
     * @return the status condition
     */
    StatusCondition status_condition() const{
        return this->delegate()->template status_condition<Publisher>(*this);
    }

public:
	/**
	 * This operation blocks the calling thread until either all data written
	 * by the reliable DataWriter entities is acknowledged by all matched
	 * reliable DataReader entities, or else the duration specified by the
	 * max_wait parameter elapses, whichever happens first.
	 * A normal return indicates that all the samples written have been
	 * acknowledged by all reliable matched data readers; A TimeoutError
	 * indicates that max_wait elapsed before all the data was acknowledged.
	 */
	void wait_for_acknowledgments(const dds::core::Duration& timeout) {
		this->delegate()->wait_for_acknowledgments(timeout);
	}
public:
	/**
	 * This operation sets a default value of the <code>DataWriterQos<\code>
	 * which will be used for newly created <core>DataWriter<code>entities
	 * for which no <code>DataWriterQos</code> is provided in the constructor.
	 * This operation will check that the resulting policies are self consistent;
	 * if they are not, the operation will have no effect and raise an
	 * InconsistentPolicyError.
	 */
	void default_data_writer_qos(const dds::pub::qos::DataWriterQos& dwqos) {
		this->delegate()->default_data_writer_qos(dwqos);
	}

	/**
	 * This operation retrieves the default value of the <code>DataWriterQos<\code>,
	 * that is, the QoS policies which will be used for newly created DataWriter
	 * that don't provide a QoS parameter in the constructor.
	 */
	const dds::pub::qos::DataWriterQos default_data_writer_qos() const {
		return this->delegate()->default_data_writer_qos();
	}

    template <typename T>
    dds::pub::DataWriter<T> create_datawriter(
            const dds::topic::Topic<T>& a_topic);

    template <typename T>
    dds::pub::DataWriter<T> create_datawriter(
            const dds::topic::Topic<T>& a_topic,
            const dds::pub::qos::DataWriterQos& a_qos,
            dds::pub::DataWriterListener<T>* a_listener = NULL,
            const dds::core::status::StatusMask& a_mask =
                    dds::core::status::StatusMask::all());

    template <typename T>
    dds::pub::DataWriter<T> create_datawriter(
            const dds::topic::Topic<T>& a_topic,
            const std::string& qos_library_name,
            const std::string& qos_profile_name,
            dds::pub::DataWriterListener<T>* a_listener = NULL,
            const dds::core::status::StatusMask& a_mask =
                    dds::core::status::StatusMask::all());
};

} } /* namespace dds / pub */

#endif /* OMG_TDDS_PUB_PUBLISHER_HPP_ */
