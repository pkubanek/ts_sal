#ifndef OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_IMPL_HPP_
#define OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_IMPL_HPP_

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

#include <idds/domain/domainfwd.hpp>
#include <dds/domain/domainfwd.hpp>
#include <idds/core/EntityImpl.hpp>


namespace idds { namespace domain {

class DomainParticipantImpl : public virtual  idds::core::EntityImpl {
public:
    explicit DomainParticipantImpl(dds::domain::DomainId id);

    DomainParticipantImpl(dds::domain::DomainId id,
            const dds::domain::qos::DomainParticipantQos& qos);

    virtual ~DomainParticipantImpl();

public:
    void listener(
            dds::domain::DomainParticipantListener* listener,
            const dds::core::status::StatusMask& event_mask);

    dds::domain::DomainParticipantListener* listener() const;

public:
    const dds::domain::qos::DomainParticipantQos qos() const;

    void qos(const dds::domain::qos::DomainParticipantQos& qos);

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

    dds::domain::DomainId domain_id();

    void assert_liveliness();

    bool contains_entity(const dds::core::InstanceHandle& handle);

    dds::core::Time current_time();

    void close();


private:

    dds::domain::qos::DomainParticipantQos qos_;
};

} }
#endif /* OMG_IDDS_DOMAIN_DOMAIN_PARTICIPANT_IMPL_HPP_ */
