#ifndef SALTOPICDCPS_IMPL_H_
#define SALTOPICDCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_SALTopic.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


namespace org {

    namespace lsst {

        namespace sal {

            class  SALTopicTypeTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
            {
            public:
                SALTopicTypeTypeSupportFactory() {}
                virtual ~SALTopicTypeTypeSupportFactory() {}
            private:
                ::DDS::DataWriter_ptr
                create_datawriter (gapi_dataWriter handle);
            
                ::DDS::DataReader_ptr
                create_datareader (gapi_dataReader handle);
            
                ::DDS::DataReaderView_ptr
                create_view (gapi_dataReaderView handle);
            };
            
            class  SALTopicTypeTypeSupport : public virtual SALTopicTypeTypeSupportInterface,
                                           public ::DDS::TypeSupport_impl
            {
            public:
                virtual ::DDS::ReturnCode_t register_type(
                    ::DDS::DomainParticipant_ptr participant,
                    const char * type_name) THROW_ORB_EXCEPTIONS;
            
                virtual char * get_type_name() THROW_ORB_EXCEPTIONS;
            
                SALTopicTypeTypeSupport (void);
                virtual ~SALTopicTypeTypeSupport (void);
            
            private:
                SALTopicTypeTypeSupport (const SALTopicTypeTypeSupport &);
                void operator= (const SALTopicTypeTypeSupport &);
            
                static const char *metaDescriptor[];
                static const CORBA::ULong metaDescriptorArrLength;
            };
            
            typedef SALTopicTypeTypeSupportInterface_var SALTopicTypeTypeSupport_var;
            typedef SALTopicTypeTypeSupportInterface_ptr SALTopicTypeTypeSupport_ptr;
            
            class  SALTopicTypeDataWriter_impl : public virtual SALTopicTypeDataWriter,
                                                public ::DDS::DataWriter_impl
            {
            public:
            
                virtual ::DDS::InstanceHandle_t register_instance(
                    const SALTopicType & instance_data) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
                    const SALTopicType & instance_data,
                    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t unregister_instance(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle,
                    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t write(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t write_w_timestamp(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle,
                    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t dispose(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t dispose_w_timestamp(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle,
                    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t writedispose(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
                    const SALTopicType & instance_data,
                    ::DDS::InstanceHandle_t handle,
                    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t get_key_value(
                    SALTopicType & key_holder,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::InstanceHandle_t lookup_instance(
                    const SALTopicType & instance_data) THROW_ORB_EXCEPTIONS;
            
            
                SALTopicTypeDataWriter_impl (
                    gapi_dataWriter handle
                );
            
                virtual ~SALTopicTypeDataWriter_impl (void);
            
            private:
                SALTopicTypeDataWriter_impl(const SALTopicTypeDataWriter_impl &);
                void operator= (const SALTopicTypeDataWriter &);
            };
            
            class  SALTopicTypeDataReader_impl : public virtual SALTopicTypeDataReader,
                                                public ::DDS::DataReader_impl
            {
                friend class SALTopicTypeDataReaderView_impl;
            public:
                virtual ::DDS::ReturnCode_t read(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_sample(
                    SALTopicType & received_data,
                    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_sample(
                    SALTopicType & received_data,
                    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t return_loan(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t get_key_value(
                    SALTopicType & key_holder,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::InstanceHandle_t lookup_instance(
                    const SALTopicType & instance) THROW_ORB_EXCEPTIONS;
            
                SALTopicTypeDataReader_impl (
                    gapi_dataReader handle
                );
            
                virtual ~SALTopicTypeDataReader_impl(void);
            
            private:
                SALTopicTypeDataReader_impl(const SALTopicTypeDataReader &);
                void operator= (const SALTopicTypeDataReader &);
            
                static ::DDS::ReturnCode_t check_preconditions(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples
                );
            };
            
            class  SALTopicTypeDataReaderView_impl : public virtual SALTopicTypeDataReaderView,
                                                public ::DDS::DataReaderView_impl
            {
            public:
                virtual ::DDS::ReturnCode_t read(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_sample(
                    SALTopicType & received_data,
                    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_sample(
                    SALTopicType & received_data,
                    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_instance(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::SampleStateMask sample_states,
                    ::DDS::ViewStateMask view_states,
                    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq,
                    CORBA::Long max_samples,
                    ::DDS::InstanceHandle_t a_handle,
                    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t return_loan(
                    SALTopicTypeSeq & received_data,
                    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::ReturnCode_t get_key_value(
                    SALTopicType & key_holder,
                    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
            
                virtual ::DDS::InstanceHandle_t lookup_instance(
                    const SALTopicType & instance) THROW_ORB_EXCEPTIONS;
            
                SALTopicTypeDataReaderView_impl (
                    gapi_dataReader handle
                );
            
                virtual ~SALTopicTypeDataReaderView_impl(void);
            
            private:
                SALTopicTypeDataReaderView_impl(const SALTopicTypeDataReaderView &);
                void operator= (const SALTopicTypeDataReaderView &);
            };
            
        }

    }

}

#endif
