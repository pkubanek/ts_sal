#ifndef SALDATADCPS_IMPL_H_
#define SALDATADCPS_IMPL_H_

#include "ccpp.h"
#include "SALData_DCPS.hpp"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"

namespace SALData {

    class  SALTopicTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        SALTopicTypeSupportFactory() {}
        virtual ~SALTopicTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr
        create_view (gapi_dataReaderView handle);
    };
    
    class  SALTopicTypeSupport : public virtual SALTopicTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;
    
        SALTopicTypeSupport (void);
        virtual ~SALTopicTypeSupport (void);
    
    private:
        SALTopicTypeSupport (const SALTopicTypeSupport &);
        void operator= (const SALTopicTypeSupport &);
    
        static const char *metaDescriptor[];
        static const CORBA::ULong metaDescriptorArrLength;
    };
    
    typedef SALTopicTypeSupportInterface_var SALTopicTypeSupport_var;
    typedef SALTopicTypeSupportInterface_ptr SALTopicTypeSupport_ptr;
    
    class  SALTopicDataWriter_impl : public virtual SALTopicDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const SALTopic & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const SALTopic & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const SALTopic & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALTopic & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALTopic & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        SALTopicDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~SALTopicDataWriter_impl (void);
    
    private:
        SALTopicDataWriter_impl(const SALTopicDataWriter_impl &);
        void operator= (const SALTopicDataWriter &);
    };
    
    class  SALTopicDataReader_impl : public virtual SALTopicDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class SALTopicDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALTopic & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALTopic & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALTopic & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALTopic & instance) THROW_ORB_EXCEPTIONS;
    
        SALTopicDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALTopicDataReader_impl(void);
    
    private:
        SALTopicDataReader_impl(const SALTopicDataReader &);
        void operator= (const SALTopicDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  SALTopicDataReaderView_impl : public virtual SALTopicDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALTopic & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALTopic & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALTopicSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALTopic & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALTopic & instance) THROW_ORB_EXCEPTIONS;
    
        SALTopicDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALTopicDataReaderView_impl(void);
    
    private:
        SALTopicDataReaderView_impl(const SALTopicDataReaderView &);
        void operator= (const SALTopicDataReaderView &);
    };
    
}

#define SALDATA_DCPS_TYPESUPPORT_DEFINED
#endif
