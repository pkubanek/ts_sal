#ifndef OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_HPP_
#define OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_HPP_

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

#include <dds/core/corefwd.hpp>
#include <dds/core/Reference.hpp>
#include <dds/domain/domainfwd.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/domain/qos/DomainParticipantFactoryQos.hpp>
#include <dds/domain/qos/DomainParticipantQos.hpp>


namespace tdds { namespace domain {

template <typename DELEGATE>
class DomainParticipantFactory : public dds::core::Reference<DELEGATE> {
public:
    OMG_DDS_REF_TYPE(DomainParticipantFactory, dds::core::Reference, DELEGATE)

public:
    ~DomainParticipantFactory() {
        OMG_DDS_LOG("MM", "~DomainParticipantFactory()");
    }

public:
    /**
     * Create a new <code>DomainParticipant</code> object. 
     * The <code>DomainParticipant</code> signifies that the calling 
     * application intends to join the Domain identified by the domain_id 
     * argument.
     * The <code>DomainParticipant</code> will be created with 
     * <code>DomainParticipantQos</code> passed as argument.
     *
     * @param id the id of the domain joined by the new
     *           <code>DomainParticipant</code>.
     * @param qos the QoS settings for the new <code>DomainParticipant</code>
     */
    dds::domain::DomainParticipant create_participant(
        dds::domain::DomainId                           domain_id = 0);

    /**
     * Create a new <code>DomainParticipant</code> object.
     * The <code>DomainParticipant</code> signifies that the calling
     * application intends to join the Domain identified by the domain_id
     * argument.
     * The <code>DomainParticipant</code> will be created with
     * <code>DomainParticipantQos</code> passed as argument.
     *
     * @param id the id of the domain joined by this <code>DomainParticipant</code>.
     * @param qos the QoS settings for this <code>DomainParticipant</code>
     */
    dds::domain::DomainParticipant create_participant(
        dds::domain::DomainId                           domain_id,
        const dds::domain::qos::DomainParticipantQos&   a_qos,
        dds::domain::DomainParticipantListener*         a_listener = NULL,
        const dds::core::status::StatusMask&            mask =
                dds::core::status::StatusMask::all());

    dds::domain::DomainParticipant create_participant(
        dds::domain::DomainId                           domain_id,
        const std::string&                              qos_library_name,
        const std::string&                              qos_profile_name,
        dds::domain::DomainParticipantListener*         a_listener = NULL,
        const dds::core::status::StatusMask&            mask =
                dds::core::status::StatusMask::all());

    const dds::domain::qos::DomainParticipantQos
    default_participant_qos() const;

    void
    default_participant_qos(const dds::domain::qos::DomainParticipantQos& qos);

    void default_participant_qos(const std::string& qos_library_name,
                                 const std::string& qos_profile_name);

    const dds::domain::qos::DomainParticipantFactoryQos qos() const;

    void qos(const dds::domain::qos::DomainParticipantFactoryQos& qos);
};

}}

#endif // !defined(OMG_TDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_HPP_)
