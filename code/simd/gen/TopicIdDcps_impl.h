#ifndef TOPICIDDCPS_IMPL_H_
#define TOPICIDDCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_TopicId.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


class  TopicIdTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
{
public:
    TopicIdTypeSupportFactory() {}
    virtual ~TopicIdTypeSupportFactory() {}
private:
    ::DDS::DataWriter_ptr 
    create_datawriter (gapi_dataWriter handle);

    ::DDS::DataReader_ptr 
    create_datareader (gapi_dataReader handle);

    ::DDS::DataReaderView_ptr 
    create_view (gapi_dataReaderView handle);
};

class  TopicIdTypeSupport : public virtual TopicIdTypeSupportInterface,
                               public ::DDS::TypeSupport_impl
{
public:
    virtual ::DDS::ReturnCode_t register_type(
        ::DDS::DomainParticipant_ptr participant,
        const char * type_name) THROW_ORB_EXCEPTIONS;

    virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    

    TopicIdTypeSupport (void);
    virtual ~TopicIdTypeSupport (void);

private:
    TopicIdTypeSupport (const TopicIdTypeSupport &);
    void operator= (const TopicIdTypeSupport &);

    static const char *metaDescriptor;
};

typedef TopicIdTypeSupportInterface_var TopicIdTypeSupport_var;
typedef TopicIdTypeSupportInterface_ptr TopicIdTypeSupport_ptr;

class  TopicIdDataWriter_impl : public virtual TopicIdDataWriter,
                                    public ::DDS::DataWriter_impl
{
public:

    virtual ::DDS::InstanceHandle_t register_instance(
        const TopicId & instance_data) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
        const TopicId & instance_data,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::ReturnCode_t unregister_instance(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write_w_timestamp(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose_w_timestamp(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
        const TopicId & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t get_key_value(
        TopicId & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::InstanceHandle_t lookup_instance(
        const TopicId & instance_data) THROW_ORB_EXCEPTIONS;


    TopicIdDataWriter_impl (
        gapi_dataWriter handle
    );

    virtual ~TopicIdDataWriter_impl (void);

private:
    TopicIdDataWriter_impl(const TopicIdDataWriter_impl &);
    void operator= (const TopicIdDataWriter &);
};

class  TopicIdDataReader_impl : public virtual TopicIdDataReader,
                                    public ::DDS::DataReader_impl
{
    friend class TopicIdDataReaderView_impl;
public:
    virtual ::DDS::ReturnCode_t read(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        TopicId & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        TopicId & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        TopicId & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const TopicId & instance) THROW_ORB_EXCEPTIONS;

    TopicIdDataReader_impl (
        gapi_dataReader handle
    );

    virtual ~TopicIdDataReader_impl(void);

private:
    TopicIdDataReader_impl(const TopicIdDataReader &);
    void operator= (const TopicIdDataReader &);

    static ::DDS::ReturnCode_t check_preconditions(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples
    );
};

class  TopicIdDataReaderView_impl : public virtual TopicIdDataReaderView,
                                    public ::DDS::DataReaderView_impl
{
public:
    virtual ::DDS::ReturnCode_t read(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        TopicId & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        TopicId & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        TopicIdSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        TopicId & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const TopicId & instance) THROW_ORB_EXCEPTIONS;

    TopicIdDataReaderView_impl (
        gapi_dataReader handle
    );

    virtual ~TopicIdDataReaderView_impl(void);

private:
    TopicIdDataReaderView_impl(const TopicIdDataReaderView &);
    void operator= (const TopicIdDataReaderView &);
};

#endif
