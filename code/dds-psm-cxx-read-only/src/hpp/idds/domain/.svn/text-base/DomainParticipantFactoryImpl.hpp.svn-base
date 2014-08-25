#ifndef OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_IMPL_HPP_
#define OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_IMPL_HPP_

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

#include <dds/domain/domainfwd.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/domain/qos/DomainParticipantQos.hpp>


namespace idds { namespace domain {

class DomainParticipantFactoryImpl {
public:
    DomainParticipantFactoryImpl() { }

    ~DomainParticipantFactoryImpl() {
        OMG_DDS_LOG("MM", "~DomainParticipantFactoryImpl()");
    }

public:
    dds::domain::DomainParticipant create_participant(
        dds::domain::DomainId                           domain_id = 0);
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

#endif // !defined(OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_IMPL_HPP_)
