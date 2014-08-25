#ifndef OMG_TDDS_CORE_STATUS_STATUS_HPP_
#define OMG_TDDS_CORE_STATUS_STATUS_HPP_

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

#include <tdds/core/corefwd.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/core/policy/QosPolicyCount.hpp>
#include <dds/core/status/State.hpp>

namespace tdds { namespace core { namespace status {

template <typename D>
class InconsistentTopicStatus : public dds::core::Value<D> {
public:
    InconsistentTopicStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }
};

template <typename D>
class SampleLostStatus : public dds::core::Value<D> {
public:
    SampleLostStatus() : dds::core::Value<D>() {}

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }
};


template <typename D>
class SampleRejectedStatus : public dds::core::Value<D> {
public:
	SampleRejectedStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    const dds::core::status::SampleRejectedState last_reason() const {
        return this->delegate().last_reason();
    }

    const dds::core::InstanceHandle last_instance_handle() const {
        return this->delegate().last_instance_handle();
    }
};

template <typename D>
class LivelinessLostStatus : public dds::core::Value<D> {
public:
    LivelinessLostStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }
};

template <typename D>
class LivelinessChangedStatus : public dds::core::Value<D> {
public:
    LivelinessChangedStatus() : dds::core::Value<D>() { }

public:
    int32_t alive_count() const {
        return this->delegate().alive_count();
    }

    int32_t not_alive_count() const {
        return this->delegate().not_alive_count();
    }

    int32_t alive_count_change() const {
        return this->delegate().alive_count();
    }

    int32_t not_alive_count_change() const {
        return this->delegate().not_alive_count();
    }

    const dds::core::InstanceHandle last_publication_handle() const {
        return this->delegate().last_instance_handle();
    }
};

template <typename D>
class OfferedDeadlineMissedStatus : public dds::core::Value<D> {
public:
    OfferedDeadlineMissedStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    const dds::core::InstanceHandle last_instance_handle() const {
        return this->delegate().last_instance_handle();
    }
};

template <typename D>
class RequestedDeadlineMissedStatus : public dds::core::Value<D> {
public:
    RequestedDeadlineMissedStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    const dds::core::InstanceHandle last_instance_handle() const {
        return this->delegate().last_instance_handle();
    }
};



template <typename D>
class OfferedIncompatibleQosStatus : public dds::core::Value<D>{
public:
    OfferedIncompatibleQosStatus()
    : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    dds::core::policy::QosPolicyId last_policy_id() const {
        return this->delegate().last_policy_id();
    }

    const dds::core::policy::QosPolicyCountSeq policies() const;

    dds::core::policy::QosPolicyCountSeq&
    policies(dds::core::policy::QosPolicyCountSeq& dst) const;
};

template <typename D>
class RequestedIncompatibleQosStatus : public dds::core::Value<D> {
public:
    RequestedIncompatibleQosStatus()
    : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    dds::core::policy::QosPolicyId last_policy_id() const {
        return this->delegate().last_policy_id();
    }

    const dds::core::policy::QosPolicyCountSeq policies() const {
        return this->delegate().policies();
    }

    dds::core::policy::QosPolicyCountSeq&
    policies(dds::core::policy::QosPolicyCountSeq& dst) const;
};

template <typename D>
class PublicationMatchedStatus : public dds::core::Value<D> {
public:
    PublicationMatchedStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    int32_t current_count() const {
        return this->delegate().current_count();
    }

    int32_t current_count_change() const {
        return this->delegate().current_count_change();
    }

    const dds::core::InstanceHandle last_subscription_handle() const {
        return this->delegate().last_subscription_handle();
    }
};

template <typename D>
class SubscriptionMatchedStatus : public dds::core::Value<D> {
public:
    SubscriptionMatchedStatus() : dds::core::Value<D>() { }

public:
    int32_t total_count() const {
        return this->delegate().total_count();
    }

    int32_t total_count_change() const {
        return this->delegate().total_count_change();
    }

    int32_t current_count() const {
        return this->delegate().current_count();
    }

    int32_t current_count_change() const {
        return this->delegate().current_count_change();
    }

    const dds::core::InstanceHandle last_publication_handle() const {
        return this->delegate().last_publication_handle();
    }
};

} } }/* namespace tdds::core::status */

#endif /* OMG_TDDS_CORE_STATUS_STATUS_HPP_ */
