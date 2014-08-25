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
#ifndef OSPL_DDS_PUB_DETAIL_DATAWRITER_HPP_
#define OSPL_DDS_PUB_DETAIL_DATAWRITER_HPP_

/**
 * @file dds/pub/detail/DataWriter.hpp
 */

// Implementation

#include <dds/topic/Topic.hpp>
#include <org/opensplice/core/EntityDelegate.hpp>
#include <org/opensplice/topic/TopicTraits.hpp>
#include <org/opensplice/core/memory.hpp>
#include <org/opensplice/pub/qos/QosConverter.hpp>
#include <org/opensplice/core/exception_helper.hpp>

namespace dds
{
namespace pub
{
template <typename T>
class DataWriterListener;

namespace detail
{
template <typename T>
class DataWriter;
}
}
}

//using namespace org::opensplice::core;

template <typename T>
class dds::pub::detail::DataWriter : public  org::opensplice::core::EntityDelegate
{
public:
    typedef typename org::opensplice::topic::topic_data_writer<T>::type DW;

public:
    DataWriter(const ::dds::pub::Publisher& pub,
               const dds::topic::Topic<T>& topic,
               const ::dds::pub::qos::DataWriterQos& qos,
               DataWriterListener<T>* listener,
               const dds::core::status::StatusMask& mask)
        :   pub_(pub),
            topic_(topic),
            qos_(qos),
            listener_(listener),
            mask_(mask)
    {
        /** @todo OSPL-1944 implement listeners */
        DDS::DataWriterQos dwqos = convertQos(qos);
        DDS::DataWriter_var w =
            pub_->pub_->create_datawriter(topic_->t_,
                                          dwqos,
                                          0,
                                          mask.to_ulong());
        if (w.in() == 0)
            throw dds::core::NullReferenceError(org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create DataWriter. "
                            "Nil return from ::create_datawriter")));

        raw_writer_ = DW::_narrow(w.in());

        org::opensplice::core::DDS_DW_REF tmp = org::opensplice::core::DDS_DW_REF(raw_writer_, org::opensplice::core::DWDeleter(pub_->pub_));
        writer_ = tmp;
    }


    virtual ~DataWriter() { }


public:
    void write(const T& sample)
    {
        DDS::ReturnCode_t result = raw_writer_->write(sample, DDS::HANDLE_NIL);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write"));
    }

    void write(const T& sample, const dds::core::Time& timestamp)
    {
        DDS::ReturnCode_t result = raw_writer_->write_w_timestamp(sample, DDS::HANDLE_NIL, timestamp);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write_w_timestamp"));
    }

    void write(const T& sample, const ::dds::core::InstanceHandle& instance)
    {
        DDS::ReturnCode_t result = raw_writer_->write(sample, instance);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write"));
    }

    void write(const T& sample,
               const ::dds::core::InstanceHandle& instance,
               const dds::core::Time& timestamp)
    {
        DDS::ReturnCode_t result = raw_writer_->write_w_timestamp(sample, instance, timestamp);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write_w_timestamp"));
    }

    void write(const dds::topic::TopicInstance<T>& i)
    {
        DDS::ReturnCode_t result = raw_writer_->write(i, DDS::HANDLE_NIL);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write"));
    }

    void write(const dds::topic::TopicInstance<T>& i,
               const dds::core::Time& timestamp)
    {
        DDS::ReturnCode_t result = raw_writer_->write_w_timestamp(i, DDS::HANDLE_NIL, timestamp);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::write_w_timestamp"));
    }

    const ::dds::core::InstanceHandle register_instance(const T& key)
    {
        return dds::topic::TopicInstance<T>(dds::core::InstanceHandle(raw_writer_->register_instance(key->t_)));
    }

    const ::dds::core::InstanceHandle register_instance(const T& key, const dds::core::Time& ts)
    {
        DDS::Time_t ddsTime;
        ddsTime.sec = ts.sec();
        ddsTime.nanosec = ts.nanosec();

        return dds::topic::TopicInstance<T>(dds::core::InstanceHandle(raw_writer_->register_instance(key->t_, ddsTime)));
    }

    const ::dds::pub::qos::DataWriterQos& qos() const
    {
        return qos_;
    }

    void qos(const dds::pub::qos::DataWriterQos& qos)
    {
        DDS::ReturnCode_t result = raw_writer_->set_qos(org::opensplice::pub::qos::convertQos(qos));
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::set_qos"));

        qos_ = qos;
    }

    const dds::topic::Topic<T>& topic() const
    {
        return topic_;
    }

    const dds::pub::Publisher& publisher() const
    {
        return pub_;
    }

    void wait_for_acknowledgments(const ::dds::core::Duration& timeout)
    {
        DDS::Duration_t ddsTimeout;
        ddsTimeout.sec = timeout.sec();
        ddsTimeout.nanosec = timeout.nanosec();

        DDS::ReturnCode_t result = raw_writer_->wait_for_acknowledgments(ddsTimeout);
        org::opensplice::core::check_and_throw(result, OSPL_CONTEXT_LITERAL("Calling ::wait_for_acknowledgments"));
    }

private:
    ::dds::pub::Publisher             pub_;
    dds::topic::Topic<T>            topic_;
    ::dds::pub::qos::DataWriterQos    qos_;
    DataWriterListener<T>*            listener_;
    dds::core::status::StatusMask     mask_;

    org::opensplice::core::DDS_DW_REF writer_;
    DW* raw_writer_;

};

// End of implementation

#endif /* OSPL_DDS_PUB_DETAIL_DATAWRITER_HPP_ */
