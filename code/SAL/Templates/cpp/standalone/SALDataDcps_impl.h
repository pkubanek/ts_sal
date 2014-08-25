#ifndef SALDATADCPS_IMPL_H_
#define SALDATADCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_SALData.h"
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
    
    class  SALCommandTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        SALCommandTypeSupportFactory() {}
        virtual ~SALCommandTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr
        create_view (gapi_dataReaderView handle);
    };
    
    class  SALCommandTypeSupport : public virtual SALCommandTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;
    
        SALCommandTypeSupport (void);
        virtual ~SALCommandTypeSupport (void);
    
    private:
        SALCommandTypeSupport (const SALCommandTypeSupport &);
        void operator= (const SALCommandTypeSupport &);
    
        static const char *metaDescriptor[];
        static const CORBA::ULong metaDescriptorArrLength;
    };
    
    typedef SALCommandTypeSupportInterface_var SALCommandTypeSupport_var;
    typedef SALCommandTypeSupportInterface_ptr SALCommandTypeSupport_ptr;
    
    class  SALCommandDataWriter_impl : public virtual SALCommandDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const SALCommand & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const SALCommand & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const SALCommand & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALCommand & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALCommand & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        SALCommandDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~SALCommandDataWriter_impl (void);
    
    private:
        SALCommandDataWriter_impl(const SALCommandDataWriter_impl &);
        void operator= (const SALCommandDataWriter &);
    };
    
    class  SALCommandDataReader_impl : public virtual SALCommandDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class SALCommandDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALCommand & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALCommand & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALCommand & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALCommand & instance) THROW_ORB_EXCEPTIONS;
    
        SALCommandDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALCommandDataReader_impl(void);
    
    private:
        SALCommandDataReader_impl(const SALCommandDataReader &);
        void operator= (const SALCommandDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  SALCommandDataReaderView_impl : public virtual SALCommandDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALCommand & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALCommand & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALCommandSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALCommand & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALCommand & instance) THROW_ORB_EXCEPTIONS;
    
        SALCommandDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALCommandDataReaderView_impl(void);
    
    private:
        SALCommandDataReaderView_impl(const SALCommandDataReaderView &);
        void operator= (const SALCommandDataReaderView &);
    };
    
    class  SALResponseTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        SALResponseTypeSupportFactory() {}
        virtual ~SALResponseTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr
        create_view (gapi_dataReaderView handle);
    };
    
    class  SALResponseTypeSupport : public virtual SALResponseTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;
    
        SALResponseTypeSupport (void);
        virtual ~SALResponseTypeSupport (void);
    
    private:
        SALResponseTypeSupport (const SALResponseTypeSupport &);
        void operator= (const SALResponseTypeSupport &);
    
        static const char *metaDescriptor[];
        static const CORBA::ULong metaDescriptorArrLength;
    };
    
    typedef SALResponseTypeSupportInterface_var SALResponseTypeSupport_var;
    typedef SALResponseTypeSupportInterface_ptr SALResponseTypeSupport_ptr;
    
    class  SALResponseDataWriter_impl : public virtual SALResponseDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const SALResponse & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const SALResponse & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const SALResponse & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALResponse & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALResponse & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        SALResponseDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~SALResponseDataWriter_impl (void);
    
    private:
        SALResponseDataWriter_impl(const SALResponseDataWriter_impl &);
        void operator= (const SALResponseDataWriter &);
    };
    
    class  SALResponseDataReader_impl : public virtual SALResponseDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class SALResponseDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALResponse & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALResponse & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALResponse & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALResponse & instance) THROW_ORB_EXCEPTIONS;
    
        SALResponseDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALResponseDataReader_impl(void);
    
    private:
        SALResponseDataReader_impl(const SALResponseDataReader &);
        void operator= (const SALResponseDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  SALResponseDataReaderView_impl : public virtual SALResponseDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALResponse & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALResponse & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALResponseSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALResponse & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALResponse & instance) THROW_ORB_EXCEPTIONS;
    
        SALResponseDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALResponseDataReaderView_impl(void);
    
    private:
        SALResponseDataReaderView_impl(const SALResponseDataReaderView &);
        void operator= (const SALResponseDataReaderView &);
    };
    
    class  SALEventTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        SALEventTypeSupportFactory() {}
        virtual ~SALEventTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr
        create_view (gapi_dataReaderView handle);
    };
    
    class  SALEventTypeSupport : public virtual SALEventTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;
    
        SALEventTypeSupport (void);
        virtual ~SALEventTypeSupport (void);
    
    private:
        SALEventTypeSupport (const SALEventTypeSupport &);
        void operator= (const SALEventTypeSupport &);
    
        static const char *metaDescriptor[];
        static const CORBA::ULong metaDescriptorArrLength;
    };
    
    typedef SALEventTypeSupportInterface_var SALEventTypeSupport_var;
    typedef SALEventTypeSupportInterface_ptr SALEventTypeSupport_ptr;
    
    class  SALEventDataWriter_impl : public virtual SALEventDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const SALEvent & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const SALEvent & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const SALEvent & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALEvent & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALEvent & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        SALEventDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~SALEventDataWriter_impl (void);
    
    private:
        SALEventDataWriter_impl(const SALEventDataWriter_impl &);
        void operator= (const SALEventDataWriter &);
    };
    
    class  SALEventDataReader_impl : public virtual SALEventDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class SALEventDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALEvent & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALEvent & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALEvent & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALEvent & instance) THROW_ORB_EXCEPTIONS;
    
        SALEventDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALEventDataReader_impl(void);
    
    private:
        SALEventDataReader_impl(const SALEventDataReader &);
        void operator= (const SALEventDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  SALEventDataReaderView_impl : public virtual SALEventDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            SALEvent & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            SALEvent & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            SALEventSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            SALEvent & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const SALEvent & instance) THROW_ORB_EXCEPTIONS;
    
        SALEventDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~SALEventDataReaderView_impl(void);
    
    private:
        SALEventDataReaderView_impl(const SALEventDataReaderView &);
        void operator= (const SALEventDataReaderView &);
    };
    
}

#endif
