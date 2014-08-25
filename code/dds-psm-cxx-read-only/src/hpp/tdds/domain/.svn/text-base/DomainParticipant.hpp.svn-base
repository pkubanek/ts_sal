#ifndef OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_HPP_
#define OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_HPP_

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

#include <string>

#include <dds/core/detail/conformance.hpp>
#include <tdds/core/Entity.hpp>
#include <dds/core/cond/StatusCondition.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/topic/ContentFilteredTopic.hpp>
#include <dds/topic/MultiTopic.hpp>
#include <dds/pub/pubfwd.hpp>
#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/pub/Publisher.hpp>
#include <dds/sub/qos/SubscriberQos.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/domain/domainfwd.hpp>
#include <dds/domain/qos/DomainParticipantQos.hpp>
#include <dds/core/macros.hpp>

namespace tdds { namespace domain {


/**
 * The <code>DomainParticipant</code> object plays several roles:
 * <ul>
 *   <li>
 *     It represents the participation of the application on a communication
 *     plane that isolates applications running on the same set of physical
 *     computers from each other. A domain establishes a virtual network
 *     linking all applications that share the same domainId and isolating
 *     them from applications running on different domains. In this way,
 *     several independent distributed applications can coexist in the same
 *     physical network without interfering, or even being aware of each
 *     other.
 *   </li>
 * </ul>
 */
template <typename DELEGATE>
class DomainParticipant : public tdds::core::Entity<DELEGATE> {
public:
    typedef dds::domain::DomainParticipantListener Listener;

    typedef dds::core::cond::StatusCondition<DomainParticipant>
    StatusCondition;

public:
    OMG_DDS_REF_TYPE(DomainParticipant, tdds::core::Entity, DELEGATE)

public:
    ~DomainParticipant() {
        OMG_DDS_LOG("MM", "~DomainParticipant()");
    }

public:
    /**
     * This operation allows access to the StatusCondition
     * (Section 7.1.2.1.9, "StatusCondition Class") associated with the Entity.
     * The returned condition can then be added to a WaitSet (Section 7.1.2.1.6,
     * WaitSet Class) so that the application can wait for specific status changes
     * that affect the Entity.
     *
     * @return the status condition
     */
    StatusCondition status_condition() const{
        return this->delegate()->template status_condition<DomainParticipant>(*this);
    }

    /**
     * Register a listener with the <core>DomainParticipant</code>.
     * The notifications received by the listener depend on the
     * status mask with which it was registered.
     *
     * @param listener the listener
     * @param event_mask the mask defining the events for which the listener
     *  will be notified.
     */
    void listener(
            Listener* the_listener,
            const dds::core::status::StatusMask& event_mask) {
        this->delegate()->listener(the_listener, event_mask);
    }

    /**
     * Get the listener of this <code>DomainParticipant</code>
     */
    Listener* listener() const {
        return this->delegate()->listener();
    }

    using tdds::core::Entity<DELEGATE>::qos;

    /**
     * Return the <code>DomainParticipantQos</code> setting for this instance.
     *
     * @return the qos setting.
     */
    const dds::domain::qos::DomainParticipantQos
    qos() const {
        return this->delegate()->qos();
    }

    void qos(const dds::domain::qos::DomainParticipantQos& the_qos) {
        this->delegate()->qos(the_qos);
    }

    /**
     * This operation retrieves the domain_id used to create the
     * <code>DomainParticipant</code>. The domain_id identifies the DDS domain
     * to which the <code>DomainParticipant</code> belongs.
     * As described in the introduction to Section 7.1.2.2.1,
     * DomainParticipant Class, on page 22 each DDS domain represents a
     * separate data communication plane isolated from other domains.
     *
     * @return the domain id
     */
    dds::domain::DomainId domain_id() const {
        return this->delegate()->domain_id();
    }


    /**
     * This operation manually asserts the liveliness of the DataWriter.
     * This is used in combination with the LIVELINESS QoS policy
     * (see Section 7.1.3, Supported QoS, on page 96) to indicate to the
     * Service that the entity remains active.
     * This operation need only be used if the LIVELINESS setting is either
     * MANUAL_BY_PARTICIPANT or MANUAL_BY_TOPIC. Otherwise, it has no effect.
     *
     * <b>Note</b> Writing data via the write operation on a DataWriter
     * asserts liveliness on the DataWriter itself and its DomainParticipant.
     * Consequently the use of assert_liveliness is only needed if the
     * application is not writing data regularly.
     */
    void
    assert_liveliness() {
        this->delegate()->assert_liveliness();
    }


    /**
     * This operation checks whether or not the given a_handle represents
     * an Entity that was created from the DomainParticipant.
     * The containment applies recursively. That is, it applies both to
     * entities (TopicDescription, Publisher, or Subscriber) created directly
     * using the DomainParticipant as well as entities created using a
     * contained Publisher, or Subscriber as the factory, and so forth.
     *
     * @param handle the instance handle for which the containement
     *               relationship has to be checked.
     *
     * @return true if the handle belongs to an <code>Entity</code> belonging
     *              to this <code>DomainParticipant</code>
     */
    bool
    contains_entity(const dds::core::InstanceHandle& handle) {
        return this->delegate()->contains_entity();
    }

    /**
     * This operation returns the current value of the time that the service
     * uses to time-stamp data writes and to set the reception timestamp
     * for the data updates it receives.
     */
    const dds::core::Time
    current_time() {
        return this->delegate()->current_time();
    }

    // --- Publisher Factory Methods: --- //
public:
    /**
     * This operation creates a Publisher with default QoS.
     */
    dds::pub::Publisher create_publisher();

    /**
     * This operation creates a Publisher with the desired QoS policies
     * and attaches to it the specified PublisherListener.
     * If the specified QoS policies are not consistent, the operation
     * will fail and an exception will be thrown.
     */
    dds::pub::Publisher create_publisher(
            const dds::pub::qos::PublisherQos& pub_qos,
            dds::pub::PublisherListener* pub_listener = NULL,
            const dds::core::status::StatusMask& event_mask =
                    dds::core::status::StatusMask::all());

    /**
     * This operation creates a Publisher with the desired QoS policies
     * and attaches to it the specified PublisherListener.
     * If the specified QoS policies are not consistent, the operation
     * will fail and an exception will be thrown.
     */
    dds::pub::Publisher create_publisher(
            const std::string& qos_library_name,
            const std::string& qos_profile_name,
            const dds::pub::PublisherListener* a_listener = NULL,
            const dds::core::status::StatusMask& mask =
                    dds::core::status::StatusMask::all());

    const dds::pub::qos::PublisherQos default_publisher_qos() const;
    void default_publisher_qos(const dds::pub::qos::PublisherQos& qos);
    void default_publisher_qos(const std::string& qos_library_name,
                               const std::string& qos_profile_name);

    // --- Subscriber Factory Methods: --- //
public:
    dds::sub::Subscriber create_subscriber();

    dds::sub::Subscriber create_subscriber(
            const dds::sub::qos::SubscriberQos& qos,
            dds::sub::SubscriberListener* a_listener = NULL,
            const dds::core::status::StatusMask& a_mask =
                    dds::core::status::StatusMask::all());

    dds::sub::Subscriber create_subscriber(
            const std::string& qos_library_name,
            const std::string& qos_profile_name,
            dds::sub::SubscriberListener* a_listener = NULL,
            const dds::core::status::StatusMask& a_mask =
                    dds::core::status::StatusMask::all());

    const dds::sub::qos::SubscriberQos default_subscriber_qos() const;
    void default_subscriber_qos(const dds::sub::qos::SubscriberQos& qos);
    void default_subscriber_qos(const std::string& qos_library_name,
                                const std::string& qos_profile_name);

    // --- Topic Factory Methods: --- //
public:
    template <typename T>
    dds::topic::Topic<T> create_topic(
            const std::string& topic_name);

    template <typename T>
    dds::topic::Topic<T> create_topic(
            const std::string& topic_name,
            const std::string& type_name_name);

    template <typename T>
    dds::topic::Topic<T> create_topic(
            const std::string& topic_name,
            const std::string& type_name, 
            const dds::topic::qos::TopicQos& topic_qos,
            dds::topic::TopicListener<T>* a_listener = NULL,
            const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all());

    template <typename T>
    dds::topic::Topic<T> create_topic(
            const std::string& topic_name,
            const std::string& type_name_name, 
            const std::string& qos_library_name,
            const std::string& qos_profile_name,
            dds::topic::TopicListener<T>* a_listener = NULL,
            const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all());
                                    

    const dds::topic::qos::TopicQos default_topic_qos() const;
    void default_topic_qos(const dds::topic::qos::TopicQos& topic_qos);
    void default_topic_qos(const std::string& qos_library_name,
                           const std::string& qos_profile_name);

    // --- ContentFilteredTopic Factory Methods: --- //
public:
#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
    template <typename T>
    dds::topic::ContentFilteredTopic<T> create_contentfilteredtopic(
        const std::string& name,
        const dds::topic::Topic<T>& related_topic,
        const std::string& filter_expression,
        const dds::core::StringSeq& expression_parameters);
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

     // --- MultiTopic Factory Methods: --- //
public:
#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
    template <typename T>
    dds::topic::MultiTopic<T> create_multitopic(
        const std::string& name,
        const std::string& type_name, 
        const std::string& subscription_expression,
        const dds::core::StringSeq& expression_parameters);
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
};

} } /* namespace tdds / namespace domain */

#endif /* OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_HPP_ */
