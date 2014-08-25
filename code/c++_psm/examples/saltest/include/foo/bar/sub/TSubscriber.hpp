/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2012 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */
#ifndef OSPL_DDS_SUB_TSUBSCRIBER_HPP_
#define OSPL_DDS_SUB_TSUBSCRIBER_HPP_

/**
 * @file dds/sub/TSubscriber.hpp
 */

/*
 * OMG PSM class declaration
 */
#include <spec/dds/sub/TSubscriber.hpp>

// Implementation
namespace dds
{
namespace sub
{

template <typename DELEGATE>
TSubscriber<DELEGATE>::TSubscriber(const ::dds::domain::DomainParticipant& dp, bool builtin)
    : dds::core::TEntity<DELEGATE>(builtin ? new DELEGATE(dp) : new DELEGATE(dp, dp.default_subscriber_qos(), 0, dds::core::status::StatusMask::all()))
    {

    }

template <typename DELEGATE>
TSubscriber<DELEGATE>::TSubscriber(const ::dds::domain::DomainParticipant& dp,
                                   const dds::sub::qos::SubscriberQos& qos,
                                   dds::sub::SubscriberListener* listener,
                                   const dds::core::status::StatusMask& mask)
    : dds::core::TEntity<DELEGATE>(new DELEGATE(dp,qos, listener, mask)) { }

template <typename DELEGATE>
TSubscriber<DELEGATE>::TSubscriber(const DELEGATE& delegate)
    : dds::core::TEntity<DELEGATE>(new DELEGATE(delegate.participant(), delegate.sub_)) { }

template <typename DELEGATE>
TSubscriber<DELEGATE>::~TSubscriber() {}

template <typename DELEGATE>
void TSubscriber<DELEGATE>::notify_datareaders()
{
    this->delegate()->notify_datareaders();
}

/** @todo OSPL-1944 add implementation **/
template <typename DELEGATE>
void TSubscriber<DELEGATE>::listener(Listener*,
                                     const dds::core::status::StatusMask& event_mask) { }

/** @todo OSPL-1944 add implementation **/
template <typename DELEGATE>
typename TSubscriber<DELEGATE>::Listener* TSubscriber<DELEGATE>::listener() const
{
    return dds::core::null;
}


template <typename DELEGATE>
const dds::sub::qos::SubscriberQos& TSubscriber<DELEGATE>::qos() const
{
    return this->delegate()->qos();
}

template <typename DELEGATE>
void TSubscriber<DELEGATE>::qos(const dds::sub::qos::SubscriberQos& sqos)
{
    this->delegate()->qos(sqos);
}

template <typename DELEGATE>
dds::sub::qos::DataReaderQos TSubscriber<DELEGATE>::default_datareader_qos() const
{
    return this->delegate()->default_datareader_qos();
}

template <typename DELEGATE>
TSubscriber<DELEGATE> & TSubscriber<DELEGATE>::default_datareader_qos(
    const dds::sub::qos::DataReaderQos &qos) const
{
    this->delegate()->default_datareader_qos(qos);
    return *this;
}

template <typename DELEGATE>
const dds::domain::DomainParticipant& TSubscriber<DELEGATE>::participant() const
{
    return this->delegate()->participant();
}

}
}
// End of implementation

#endif /* OSPL_DDS_SUB_TSUBSCRIBER_HPP_ */
