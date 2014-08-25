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
#ifndef OSPL_DDS_SUB_DETAIL_DATAREADER_HPP_
#define OSPL_DDS_SUB_DETAIL_DATAREADER_HPP_

/**
 * @file dds/sub/detail/DataReader.hpp
 */

// Implementation

#include <org/opensplice/core/config.hpp>
#include <org/opensplice/topic/TopicTraits.hpp>
#include <org/opensplice/core/memory.hpp>
#include <org/opensplice/sub/qos/QosConverter.hpp>
#include <dds/sub/LoanedSamples.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/topic/TopicInstance.hpp>
#include <dds/topic/ContentFilteredTopic.hpp>
#include <dds/core/status/Status.hpp>
#include <org/opensplice/core/exception_helper.hpp>


namespace org
{
namespace opensplice
{
namespace topic
{
template<> struct topic_data_seq<dds::sub::SampleInfo>
{
    typedef DDS::SampleInfoSeq type;
    typedef DDS::SampleInfoSeq_uniq_ utype;
};
}
}
}


namespace dds
{
namespace sub
{
class Query;
}
}
namespace dds
{
namespace sub
{
namespace functors
{
namespace detail
{
//////////////////////////////////////////////////////////////////////
// Manipulators
//////////////////////////////////////////////////////////////////////
class MaxSamplesManipulatorFunctor
{
public:
    MaxSamplesManipulatorFunctor(uint32_t n) :
        n_(n)
    {
    }

    template<typename S>
    void operator()(S& s)
    {
        s.max_samples(n_);
    }
private:
    uint32_t n_;
};

class ContentFilterManipulatorFunctor
{
public:
    ContentFilterManipulatorFunctor(const dds::sub::Query& q) :
        query_(q)
    {
    }

    template<typename S>
    void operator()(S& s)
    {
        s.filter_content(query_);
    }
private:
    const dds::sub::Query& query_;
};

class StateFilterManipulatorFunctor
{
public:
    StateFilterManipulatorFunctor(
        const dds::sub::status::DataState& s) :
        state_(s)
    {
    }

    template<typename S>
    void operator()(S& s)
    {
        s.state(state_);
    }
private:
    dds::sub::status::DataState state_;
};

class InstanceManipulatorFunctor
{
public:
    InstanceManipulatorFunctor(const dds::core::InstanceHandle& h) :
        handle_(h)
    {
    }

    template<typename S>
    void operator()(S& s)
    {
        s.instance(handle_);
    }
private:
    dds::core::InstanceHandle handle_;
};

class NextInstanceManipulatorFunctor
{
public:
    NextInstanceManipulatorFunctor(
        const dds::core::InstanceHandle& h) :
        handle_(h)
    {
    }

    template<typename S>
    void operator()(S& s)
    {
        s.next_instance(handle_);
    }
private:
    dds::core::InstanceHandle handle_;
};
}
}
}
}

namespace dds
{
namespace sub
{
template<typename T>
class DataReaderListener;
}
}

namespace dds
{
namespace sub
{
namespace detail
{
//////////////////////////////////////////////////////////////////////
// Listener
//////////////////////////////////////////////////////////////////////
template <typename T>
class DataReaderListener;

template <typename T>
class DataReaderEventHandler
{
public:
    virtual ~DataReaderEventHandler() { }

public:
    virtual void
    on_requested_deadline_missed(const dds::core::status::RequestedDeadlineMissedStatus& status) = 0;

    virtual void
    on_requested_incompatible_qos(const dds::core::status::RequestedIncompatibleQosStatus& status) = 0;

    virtual void
    on_sample_rejected(const dds::core::status::SampleRejectedStatus& status) = 0;

    virtual void
    on_liveliness_changed(const dds::core::status::LivelinessChangedStatus& status) = 0;

    virtual void
    on_data_available() = 0;

    virtual void
    on_subscription_matched(const dds::core::status::SubscriptionMatchedStatus& status) = 0;

    virtual void
    on_sample_lost(const dds::core::status::SampleLostStatus& status) = 0;

    virtual dds::sub::DataReaderListener<T>* listener() = 0;
    virtual void listener(dds::sub::DataReaderListener<T>* l) = 0;
};

template<typename T>
class DataReaderEventForwarder: public DDS::DataReaderListener
{
public:
    DataReaderEventForwarder(
        dds::sub::detail::DataReaderEventHandler<T>* handler) :
        handler_(handler)
    {
    }
    virtual ~DataReaderEventForwarder()
    {
        delete handler_;
    }
public:
    virtual void on_requested_deadline_missed(
        DDS::DataReader_ptr reader,
        const DDS::RequestedDeadlineMissedStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_requested_deadline_missed");
        handler_->on_requested_deadline_missed(
            dds::core::status::RequestedDeadlineMissedStatus());
    }
    virtual void on_requested_incompatible_qos(
        DDS::DataReader_ptr reader,
        const DDS::RequestedIncompatibleQosStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_requested_incompatible_qos");
        handler_->on_requested_incompatible_qos(
            dds::core::status::RequestedIncompatibleQosStatus());
    }
    virtual void on_sample_rejected(DDS::DataReader_ptr reader,
                                    const DDS::SampleRejectedStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_sample_rejected");
        handler_->on_sample_rejected(
            dds::core::status::SampleRejectedStatus());
    }
    virtual void on_liveliness_changed(DDS::DataReader_ptr reader,
                                       const DDS::LivelinessChangedStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_liveliness_changed");
        handler_->on_liveliness_changed(
            dds::core::status::LivelinessChangedStatus());
    }
    virtual void on_data_available(DDS::DataReader_ptr reader)
    {
        OMG_DDS_LOG("EVT", "on_data_available");
        handler_->on_data_available();
    }
    virtual void on_subscription_matched(DDS::DataReader_ptr reader,
                                         const DDS::SubscriptionMatchedStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_subscription_matched");
        handler_->on_subscription_matched(
            dds::core::status::SubscriptionMatchedStatus());
    }
    virtual void on_sample_lost(DDS::DataReader_ptr reader,
                                const DDS::SampleLostStatus& status)
    {
        OMG_DDS_LOG("EVT", "on_sample_lost");
        handler_->on_sample_lost(dds::core::status::SampleLostStatus());
    }

    dds::sub::detail::DataReaderEventHandler<T>* handler_;
};

template<typename T>
class DataReader;

template <typename DR, typename T>
class EventHandler : public dds::sub::detail::DataReaderEventHandler<T>
{
public:
    EventHandler(const DR& dr,
                    dds::sub::DataReaderListener<T>* l)
        : dr_(dr),
            listener_(l)
    { }
public:
    virtual void
    on_requested_deadline_missed(const dds::core::status::RequestedDeadlineMissedStatus& status)
    {
        if (listener_ != 0)
            listener_->on_requested_deadline_missed(dr_, status);
    }

    virtual void
    on_requested_incompatible_qos(const dds::core::status::RequestedIncompatibleQosStatus& status)
    {
        if (listener_ != 0)
            listener_->on_requested_incompatible_qos(dr_, status);
    }

    virtual void
    on_sample_rejected(const dds::core::status::SampleRejectedStatus& status)
    {
        if (listener_ != 0)
            listener_->on_sample_rejected(dr_, status);
    }

    virtual void
    on_liveliness_changed(const dds::core::status::LivelinessChangedStatus& status)
    {
        if (listener_ != 0)
            listener_->on_liveliness_changed(dr_, status);
    }

    virtual void
    on_data_available()
    {
        if (listener_ != 0)
            listener_->on_data_available(dr_);
    }

    virtual void
    on_subscription_matched(const dds::core::status::SubscriptionMatchedStatus& status)
    {
        if (listener_ != 0)
            listener_->on_subscription_matched(dr_, status);
    }

    virtual void
    on_sample_lost(const dds::core::status::SampleLostStatus& status)
    {
        if (listener_ != 0)
            listener_->on_sample_lost(dr_, status);
    }

    dds::sub::DataReaderListener<T>*
    listener()
    {
        return listener_;
    }

    void listener(dds::sub::DataReaderListener<T>* l)
    {
        listener_ = l;
    }


private:
    DR dr_;
    dds::sub::DataReaderListener<T>* listener_;
};

}
}
}

// using namespace org::opensplice::core;

//////////////////////////////////////////////////////////////////////////////
// DataReader
//////////////////////////////////////////////////////////////////////////////
template <typename T>
class dds::sub::detail::DataReader : public org::opensplice::core::EntityDelegate
{
public:

    ////////////////////////////////////////////////////////////////////////////
    // -- CTORS

    DataReader(const dds::sub::Subscriber& sub,
               const ::dds::topic::Topic<T>& topic) :
        sub_(sub), topic_(topic), cf_topic_(dds::core::null), event_forwarder_(0)
    {
        DDS::DataReaderQos drqos =
            *(DDS::DomainParticipantFactory::datareader_qos_default());
        DDS::DataReader_var r = sub_->sub_->create_datareader(topic_->t_,
                                drqos,
                                0,
                                DDS::ANY_STATUS);

        if (r.in() == 0) throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader. "
                            "Nil return from ::create_datareader")));

        raw_reader_ = DR::_narrow(r.in());
        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;
    }

    DataReader(const dds::sub::Subscriber& sub,
               const ::dds::topic::Topic<T>& topic,
               const dds::sub::qos::DataReaderQos& qos) :
        sub_(sub), topic_(topic), cf_topic_(dds::core::null), raw_reader_(0), qos_(qos), event_forwarder_(0)
    {
        DDS::DataReaderQos drqos = convertQos(qos);
        DDS::DataReader_var r = sub_->sub_->create_datareader(topic_->t_, drqos,
                                event_forwarder_, DDS::ANY_STATUS);

        if (r == 0)
        {
            throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader. "
                            "Nil return from ::create_datareader")));
        }

        raw_reader_ = DR::_narrow(r);
        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;

    }

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

    DataReader(const dds::sub::Subscriber& sub,
               const ::dds::topic::ContentFilteredTopic<T>& cftopic)
        : sub_(sub),
          topic_(cftopic.topic()),
          cf_topic_(cftopic),
          raw_reader_(0),
          event_forwarder_(0)
    {
        DDS::DataReaderQos drqos = *(DDS::DomainParticipantFactory::datareader_qos_default());
        DDS::DataReader_var r = sub_->sub_->create_datareader(cftopic->t_, drqos,
                                event_forwarder_, DDS::ANY_STATUS);

        if (r == 0)
        {
            throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader. "
                            "Nil return from ::create_datareader")));
        }

        raw_reader_ = DR::_narrow(r);
        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;
    }


    DataReader(const dds::sub::Subscriber& sub,
               const ::dds::topic::ContentFilteredTopic<T>& cftopic,
               const dds::sub::qos::DataReaderQos& qos)
        : sub_(sub),
          topic_(cftopic.topic()),
          cf_topic_(cftopic),
          raw_reader_(0),
          event_forwarder_(0)
    {
        DDS::DataReaderQos drqos = convertQos(qos);
        DDS::DataReader_var r = sub_->sub_->create_datareader(cftopic->idl_cftopic_.in(),
                                                              drqos,
                                                              event_forwarder_,
                                                              DDS::ANY_STATUS);
        if (CORBA::is_nil(r.in()))
        {
            throw dds::core::NullReferenceError(
                    org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader for ContentFilteredTopic. "
                            "Nil return from ::create_datareader")));
        }

        raw_reader_ = DR::_narrow(r);

        if (CORBA::is_nil(raw_reader_))
        {
            throw dds::core::NullReferenceError(
                    org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Failure narrowing ContentFilteredTopic DataReader to typed interface")));
        }

        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;
    }
#endif /* OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT */

#ifdef OMG_DDS_MULTI_TOPIC_SUPPORT

    DataReader(const dds::sub::Subscriber& pub,
               const ::dds::topic::MultiTopic<T>& topic)
    {
        DDS::DataReaderQos drqos = *(DDS::DomainParticipantFactory::datareader_qos_default());
        DDS::DataReader_var r = sub_->sub_->create_datareader(topic->t_, drqos,
                                event_forwarder_, DDS::ANY_STATUS);

        if (r == 0)
        {
            throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader. "
                            "Nil return from ::create_datareader")));
        }

        raw_reader_ = DR::_narrow(r);
        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;
    }

    DataReader(const dds::sub::Subscriber& pub,
               const ::dds::topic::MultiTopic<T>& topic,
               const dds::sub::qos::DataReaderQos& qos,
               dds::sub::detail::DataReaderEventHandler<T>* handler,
               const dds::core::status::StatusMask& mask)
    {
        event_handler(handler, mask);

        DDS::DataReaderQos drqos = convertQos(qos);
        DDS::DataReader_var r = sub_->sub_->create_datareader(topic->t_, drqos,
                                event_forwarder_, mask.to_ulong());

        if (r == 0)
        {
            throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataReader. "
                            "Nil return from ::create_datareader")));
        }

        raw_reader_ = DR::_narrow(r);
        org::opensplice::core::DDS_DR_REF tmp = org::opensplice::core::DDS_DR_REF(raw_reader_,
                                                org::opensplice::core::DRDeleter(sub_->sub_));
        reader_ = tmp;
    }
#endif /* OMG_DDS_MULTI_TOPIC_SUPPORT */

public:
    // -- Dtor
    ~DataReader()
    {
        if (event_forwarder_ != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->set_listener(0, DDS::STATUS_MASK_NONE);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::set_listener"));
            delete event_forwarder_;
        }
    }
    // -- SELECTORS --
    class Selector
    {
    public:
        Selector(DataReader<T>* dr) :
            dr_(dr), status_(dr_->default_status_filter()), next_instance_(
                false), handle_(dds::core::null), has_query_(false), query_(
                    "")
        {
        }

        Selector& instance(const dds::core::InstanceHandle& h)
        {
            next_instance_ = false;
            handle_ = h;
            return *this;
        }

        Selector& next_instance(const dds::core::InstanceHandle& h)
        {
            next_instance_ = true;
            handle_ = h;
            return *this;
        }

        Selector& filter_state(const dds::sub::status::DataState& s)
        {
            status_ = s;
            return *this;
        }

        template<typename QUERY>
        Selector& filter_content(const QUERY& query)
        {
            query_ = query.expression();
            /** @todo OSPL-1770 Get also params */
            return *this;
        }

        dds::sub::LoanedSamples<T> read()
        {
            return dr_->read(*this);
        }

        dds::sub::LoanedSamples<T> take()
        {
            return dr_->take(*this);
        }

        // --- Forward Iterators: --- //

        template<typename SamplesFWIterator>
        uint32_t read(SamplesFWIterator sfit, uint32_t max_samples)
        {
            return dr_->read(sfit, max_samples, *this);
        }

        template<typename SamplesFWIterator>
        uint32_t take(SamplesFWIterator sfit, uint32_t max_samples)
        {
            return dr_->take(sfit, max_samples, *this);
        }

        // --- Back-Inserting Iterators: --- //

        template<typename SamplesBIIterator>
        uint32_t read(SamplesBIIterator sbit)
        {
            return dr_->read(sbit, *this);
        }

        template<typename SamplesBIIterator>
        uint32_t take(SamplesBIIterator sbit)
        {
            return dr_->take(sbit, *this);
        }

    private:
        friend class DataReader;
        DataReader<T>* dr_;
        dds::sub::status::DataState status_;
        bool next_instance_;
        dds::core::InstanceHandle handle_;
        bool has_query_;
        std::string query_;
        std::vector<std::string> query_params_;
    };

    // -- MANIPULATORS SELECTORS --

    class ManipulatorSelector: public Selector
    {
    public:

        ManipulatorSelector(DataReader<T>* dr) :
            Selector(dr), read_mode_(true)
        {
        }

        bool read_mode()
        {
            return read_mode_;
        }

        void read_mode(bool b)
        {
            read_mode_ = b;
        }

        ManipulatorSelector&
        operator >>(dds::sub::LoanedSamples<T>& samples)
        {
            if (read_mode_) samples = this->Selector::read();
            else samples = this->Selector::take();
            return *this;
        }
    private:
        bool read_mode_;
    };
public:
    typedef typename org::opensplice::topic::topic_data_reader<T>::type DR;
    typedef typename org::opensplice::topic::topic_data_seq<T>::type TSeq;

public:
    void event_handler(dds::sub::detail::DataReaderEventHandler<T>* handler,
                       const dds::core::status::StatusMask& mask)
    {
        if (event_forwarder_ == 0) event_forwarder_ =
                new DataReaderEventForwarder<T>(handler);
        else event_forwarder_->handler_ = handler;
        DDS::ReturnCode_t result = raw_reader_->set_listener(event_forwarder_, mask.to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::set_listener"));
    }

public:

    const dds::sub::status::DataState& default_status_filter()
    {
        return status_filter_;
    }

    DataReader& default_status_filter(
        const dds::sub::status::DataState& status)
    {
        status_filter_ = status;
        return *this;
    }

public:
    // -- Read/Take API
    dds::sub::LoanedSamples<T> take()
    {
        dds::sub::LoanedSamples<T> ls;
        typename org::opensplice::topic::topic_data_seq<T>::type data;
        typename org::opensplice::topic::topic_data_seq<dds::sub::SampleInfo>::type info;
        DDS::ReturnCode_t result = raw_reader_->take(data,
                                                     info,
                                                     DDS::LENGTH_UNLIMITED,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));

        ls.delegate()->resize(data.length());
        typename dds::sub::LoanedSamples<T>::iterator it = ls.delegate()->mbegin();
        for (unsigned int i = 0; i < data.length(); ++i)
        {
            it->data(data[i]);
            it->info(*reinterpret_cast<dds::sub::SampleInfo*>(&info[0]));
            ++it;
        }
        if (data.length() != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return ls;
    }

    dds::sub::LoanedSamples<T> read()
    {
        dds::sub::LoanedSamples<T> ls;
        typename org::opensplice::topic::topic_data_seq<T>::type data;
        typename org::opensplice::topic::topic_data_seq<dds::sub::SampleInfo>::type info;
        DDS::ReturnCode_t result = raw_reader_->read(data,
                                                     info,
                                                     DDS::LENGTH_UNLIMITED,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));

        ls.delegate()->resize(data.length());
        typename dds::sub::LoanedSamples<T>::iterator it = ls.delegate()->mbegin();
        for (unsigned int i = 0; i < data.length(); ++i)
        {
            it->data(data[i]);
            it->info(*reinterpret_cast<dds::sub::SampleInfo*>(&info[0]));
            ++it;
        }
        if (data.length() != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }

        return ls;
    }

    // --- Forward Iterators: --- //

    template<typename SamplesFWIterator>
    uint32_t read(SamplesFWIterator samples,  uint32_t max_samples)
    {
        TSeq data;
        DDS::SampleInfoSeq info;
        DDS::ReturnCode_t result = raw_reader_->read(data,
                                                     info,
                                                     max_samples,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return size;
    }

    template<typename SamplesFWIterator>
    uint32_t take(SamplesFWIterator samples, uint32_t max_samples)
    {
        TSeq data;
        DDS::SampleInfoSeq info;
        DDS::ReturnCode_t result = raw_reader_->take(data,
                                                     info,
                                                     max_samples,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return size;
    }

    // --- Back-Inserting Iterators: --- //
    template<typename SamplesBIIterator>
    uint32_t read(SamplesBIIterator samples)
    {
        TSeq data;
        DDS::SampleInfoSeq info;
        DDS::ReturnCode_t result = raw_reader_->read(data,
                                                     info,
                                                     DDS::LENGTH_UNLIMITED,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return size;
    }

    template<typename SamplesBIIterator>
    uint32_t take(SamplesBIIterator samples)
    {
        TSeq data;
        DDS::SampleInfoSeq info;
        DDS::ReturnCode_t result = raw_reader_->take(data,
                                                     info,
                                                     DDS::LENGTH_UNLIMITED,
                                                     status_filter_.sample_state().to_ulong(),
                                                     status_filter_.view_state().to_ulong(),
                                                     status_filter_.instance_state().to_ulong());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return size;
    }
    //========================================================================
    //== Instance Management
    dds::topic::TopicInstance<T> key_value(const dds::core::InstanceHandle& h)
    {
        T key_holder;
        DDS::ReturnCode_t result = raw_reader_->get_key_value(key_holder, h.delegate().handle());
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::get_key_value"));
        return dds::topic::TopicInstance<T>(key_holder, h);
    }

    const dds::core::InstanceHandle lookup_instance(const T& key) const
    {
        DDS::InstanceHandle_t h = raw_reader_->lookup_instance(key);
        if (h == DDS::HANDLE_NIL) return dds::core::InstanceHandle::nil();
        return dds::core::InstanceHandle(h);
    }

    //========================================================================
    //== Status API

    const dds::core::status::LivelinessChangedStatus&
    liveliness_changed_status() const
    {
        return liveliness_status_;
    }

    const dds::core::status::SampleRejectedStatus&
    sample_rejected_status() const
    {
        return sample_rejected_status_;
    }

    const dds::core::status::SampleLostStatus&
    sample_lost_status() const
    {
        return sample_lost_status_;
    }

    const dds::core::status::RequestedDeadlineMissedStatus&
    requested_deadline_missed_status()
    {
        return deadline_missed_status_;

    }

    const dds::core::status::RequestedIncompatibleQosStatus&
    requested_incompatible_qos_status() const
    {
        return incompatible_qos_status_;
    }

    const dds::core::status::SubscriptionMatchedStatus&
    subscription_matched_status() const
    {
        return subscription_matched_status_;
    }

    //========================================================================
    // -- Entity Navigation
    dds::topic::TopicDescription<T> topic_description() const
    {
        return this->topic_;
    }
    const dds::sub::Subscriber& subscriber() const
    {
        return sub_;
    }

    //========================================================================
    // -- QoS
public:
    const dds::sub::qos::DataReaderQos& qos() const
    {
        return qos_;
    }

    void qos(const dds::sub::qos::DataReaderQos& qos)
    {
        DDS::ReturnCode_t result = raw_reader_->set_qos(org::opensplice::sub::qos::convertQos(qos));
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::set_qos"));
        qos_ = qos;
    }

    // ==============================================================
    // == Resource Management
    void close()
    {
        /** @todo OSPL-1770 Properly implement close by releasing the DR resources.
        // as well as keeping track of its status.
        // Notice that a trivial implementation  close () (like this) is
        // also compliant with the spec since resources will be collected
        // once the DR reference count drops to zero. */
    }
private:
    // ==============================================================
    // == Selector Read/Take API

    dds::sub::LoanedSamples<T> take(const Selector& cmd)
    {
        dds::sub::LoanedSamples<T> ls;
        typename org::opensplice::topic::topic_data_seq<T>::type data;
        typename org::opensplice::topic::topic_data_seq<dds::sub::SampleInfo>::type info;
        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->take(data, info,
                              DDS::LENGTH_UNLIMITED,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->take_instance(data, info,
                                           DDS::LENGTH_UNLIMITED,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->take_next_instance(data, info,
                                                DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }
        ls.delegate()->resize(data.length());
        typename dds::sub::LoanedSamples<T>::iterator it = ls.delegate()->mbegin();
        for (unsigned int i = 0; i < data.length(); ++i)
        {
            it->data(data[i]);
            it->info(*reinterpret_cast<dds::sub::SampleInfo*>(&info[0]));
            ++it;
        }
        if (data.length() != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return ls;
    }

    dds::sub::LoanedSamples<T> read(const Selector& cmd)
    {
        dds::sub::LoanedSamples<T> ls;
        typename org::opensplice::topic::topic_data_seq<T>::type data;
        typename org::opensplice::topic::topic_data_seq<dds::sub::SampleInfo>::type info;

        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->read(data, info,
                              DDS::LENGTH_UNLIMITED,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->read_instance(data, info,
                                           DDS::LENGTH_UNLIMITED,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->read_next_instance(data, info,
                                                DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }
        uint32_t size = data.length();
        ls.delegate()->resize(size);
        typename dds::sub::LoanedSamples<T>::iterator it = ls.delegate()->mbegin();
        for (unsigned int i = 0; i < size; ++i)
        {
            it->data(data[i]);
            it->info(*reinterpret_cast<dds::sub::SampleInfo*>(&info[0]));
            ++it;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return ls;
    }

    // --- Forward Iterators: --- //

    template<typename SamplesFWIterator>
    uint32_t read(SamplesFWIterator samples,
                  uint32_t max_samples, const Selector& cmd)
    {
        TSeq data;
        DDS::SampleInfoSeq info;

        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->read(data, info, max_samples,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->read_instance(data, info, max_samples,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->read_next_instance(data, info, DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }
        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }
        return size;
    }

    template<typename SamplesFWIterator>
    uint32_t take(SamplesFWIterator samples,
                  uint32_t max_samples, const Selector& cmd)
    {
        TSeq data;
        DDS::SampleInfoSeq info;

        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->take(data, info, max_samples,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->take_instance(data, info, max_samples,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->take_next_instance(data, info, DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }
        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }

        return size;
    }

    // --- Back-Inserting Iterators: --- //

    template<typename SamplesBIIterator>
    uint32_t read(SamplesBIIterator samples,
                  const Selector& cmd)
    {
        TSeq data;
        DDS::SampleInfoSeq info;

        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->read(data, info, DDS::LENGTH_UNLIMITED,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->read_instance(data, info, DDS::LENGTH_UNLIMITED,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->read_next_instance(data, info, DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::read_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }

        return size;
    }

    template<typename SamplesBIIterator>
    uint32_t take(SamplesBIIterator samples,
                  const Selector& cmd)
    {
        TSeq data;
        DDS::SampleInfoSeq info;
        if (cmd.has_query_ == false && cmd.handle_.is_nil())
        {
            DDS::ReturnCode_t result = raw_reader_->take(data, info, DDS::LENGTH_UNLIMITED,
                              cmd.status_.sample_state().to_ulong(),
                              cmd.status_.view_state().to_ulong(),
                              cmd.status_.instance_state().to_ulong());
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take"));
        }
        else if (cmd.has_query_ == false && cmd.handle_ != dds::core::null)
        {
            if (cmd.next_instance_ == false)
            {
                DDS::ReturnCode_t result = raw_reader_->take_instance(data, info, DDS::LENGTH_UNLIMITED,
                                           cmd.handle_.delegate().handle(),
                                           cmd.status_.sample_state().to_ulong(),
                                           cmd.status_.view_state().to_ulong(),
                                           cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_instance"));
            }
            else
            {
                DDS::ReturnCode_t result = raw_reader_->take_next_instance(data, info, DDS::LENGTH_UNLIMITED,
                                                cmd.handle_.delegate().handle(),
                                                cmd.status_.sample_state().to_ulong(),
                                                cmd.status_.view_state().to_ulong(),
                                                cmd.status_.instance_state().to_ulong());
                org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::take_next_instance"));
            }
        }
        else
        {
            OMG_DDS_LOG("WARNING", "Queries are not supported yet!");
            throw dds::core::UnsupportedError(org::opensplice::core::exception_helper(
                                                OSPL_CONTEXT_LITERAL(
                            "dds::core::UnsupportedError : Queries are not supported yet")));
        }

        uint32_t size = data.length();
        for (uint32_t i = 0; i < size; ++i)
        {
            samples->data(data[i]);
            samples->info(*(reinterpret_cast<dds::sub::SampleInfo*>(&info[i])));
            ++samples;
        }
        if (size != 0)
        {
            DDS::ReturnCode_t result = raw_reader_->return_loan(data, info);
            org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::return_loan"));
        }

        return size;
    }

private:
    dds::sub::Subscriber sub_;
    dds::topic::Topic<T> topic_;
    dds::topic::ContentFilteredTopic<T> cf_topic_;
    org::opensplice::core::DDS_DR_REF reader_;
    DR* raw_reader_;
    dds::sub::qos::DataReaderQos qos_;
    dds::core::status::StatusMask mask_;
    dds::sub::status::DataState status_filter_;
    dds::core::status::LivelinessChangedStatus liveliness_status_;
    dds::core::status::SampleRejectedStatus sample_rejected_status_;
    dds::core::status::SampleLostStatus sample_lost_status_;
    dds::core::status::RequestedDeadlineMissedStatus deadline_missed_status_;
    dds::core::status::RequestedIncompatibleQosStatus incompatible_qos_status_;
    dds::core::status::SubscriptionMatchedStatus subscription_matched_status_;
    DataReaderEventForwarder<T>* event_forwarder_;
};

// End of implementation

#endif /* OSPL_DDS_SUB_DETAIL_DATAREADER_HPP_ */
