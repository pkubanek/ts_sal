#include "SALTopicDcps_impl.h"
#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "SALTopicSplDcps.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


extern c_bool
__org_lsst_sal_SALTopicType__copyIn(
    c_base base,
    struct org::lsst::sal::SALTopicType *from,
    struct _org_lsst_sal_SALTopicType *to);

extern void
__org_lsst_sal_SALTopicType__copyOut(
    void *_from,
    void *_to);

// DDS org::lsst::sal::SALTopicType TypeSupportFactory Object Body

::DDS::DataWriter_ptr
org::lsst::sal::SALTopicTypeTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new org::lsst::sal::SALTopicTypeDataWriter_impl(handle);
}

::DDS::DataReader_ptr
org::lsst::sal::SALTopicTypeTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new org::lsst::sal::SALTopicTypeDataReader_impl (handle);
}


::DDS::DataReaderView_ptr
org::lsst::sal::SALTopicTypeTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new org::lsst::sal::SALTopicTypeDataReaderView_impl (handle);
}

// DDS org::lsst::sal::SALTopicType TypeSupport Object Body

org::lsst::sal::SALTopicTypeTypeSupport::SALTopicTypeTypeSupport(void) :
    TypeSupport_impl(
        __org_lsst_sal_SALTopicType__name(),
        __org_lsst_sal_SALTopicType__keys(),
        org::lsst::sal::SALTopicTypeTypeSupport::metaDescriptor,
        (gapi_copyIn) __org_lsst_sal_SALTopicType__copyIn,
        (gapi_copyOut) __org_lsst_sal_SALTopicType__copyOut,
        (gapi_readerCopy) ::DDS::ccpp_DataReaderCopy<org::lsst::sal::SALTopicTypeSeq, org::lsst::sal::SALTopicType>,
        new  org::lsst::sal::SALTopicTypeTypeSupportFactory(),
        org::lsst::sal::SALTopicTypeTypeSupport::metaDescriptorArrLength)
{
    // Parent constructor takes care of everything.
}

org::lsst::sal::SALTopicTypeTypeSupport::~SALTopicTypeTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeTypeSupport::register_type(
    ::DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

char *
org::lsst::sal::SALTopicTypeTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS org::lsst::sal::SALTopicType DataWriter_impl Object Body

org::lsst::sal::SALTopicTypeDataWriter_impl::SALTopicTypeDataWriter_impl (
    gapi_dataWriter handle
) : ::DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

org::lsst::sal::SALTopicTypeDataWriter_impl::~SALTopicTypeDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

::DDS::InstanceHandle_t
org::lsst::sal::SALTopicTypeDataWriter_impl::register_instance(
    const org::lsst::sal::SALTopicType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
org::lsst::sal::SALTopicTypeDataWriter_impl::register_instance_w_timestamp(
    const SALTopicType & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::unregister_instance(
    const org::lsst::sal::SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::unregister_instance_w_timestamp(
    const SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::write(
    const org::lsst::sal::SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::write_w_timestamp(
    const SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::dispose(
    const org::lsst::sal::SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::dispose_w_timestamp(
    const SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::writedispose(
    const org::lsst::sal::SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::writedispose_w_timestamp(
    const SALTopicType & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataWriter_impl::get_key_value(
    SALTopicType & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
org::lsst::sal::SALTopicTypeDataWriter_impl::lookup_instance(
    const org::lsst::sal::SALTopicType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS org::lsst::sal::SALTopicType DataReader_impl Object Body

org::lsst::sal::SALTopicTypeDataReader_impl::SALTopicTypeDataReader_impl (
    gapi_dataReader handle
) : ::DDS::DataReader_impl(handle, ::DDS::ccpp_DataReaderParallelDemarshallingMain<org::lsst::sal::SALTopicTypeSeq>)
{
    // Parent constructor takes care of everything.
}

org::lsst::sal::SALTopicTypeDataReader_impl::~SALTopicTypeDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read_next_sample(
    org::lsst::sal::SALTopicType & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take_next_sample(
    org::lsst::sal::SALTopicType & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read_next_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take_next_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::read_next_instance_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::take_next_instance_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::return_loan(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = ::DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() &&
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == ::DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        org::lsst::sal::SALTopicTypeSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == ::DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = ::DDS::RETCODE_OK;
                    } else {
                        status = ::DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = ::DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::get_key_value(
    org::lsst::sal::SALTopicType & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
org::lsst::sal::SALTopicTypeDataReader_impl::lookup_instance(
    const org::lsst::sal::SALTopicType & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples)
{
    ::DDS::ReturnCode_t status = ::DDS::RETCODE_PRECONDITION_NOT_MET;

    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
                max_samples <= static_cast<CORBA::Long>(received_data.maximum()) ||
                max_samples == ::DDS::LENGTH_UNLIMITED ) {
                status = ::DDS::RETCODE_OK;
            }
        }
    }
    return status;
}


// DDS org::lsst::sal::SALTopicType DataReaderView_impl Object Body

org::lsst::sal::SALTopicTypeDataReaderView_impl::SALTopicTypeDataReaderView_impl (
    gapi_dataReaderView handle
) : ::DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

org::lsst::sal::SALTopicTypeDataReaderView_impl::~SALTopicTypeDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read_next_sample(
    org::lsst::sal::SALTopicType & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take_next_sample(
    org::lsst::sal::SALTopicType & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read_next_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take_next_instance(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::read_next_instance_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::take_next_instance_w_condition(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = org::lsst::sal::SALTopicTypeDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::return_loan(
    org::lsst::sal::SALTopicTypeSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = ::DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() &&
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReaderView_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == ::DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        org::lsst::sal::SALTopicTypeSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == ::DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = ::DDS::RETCODE_OK;
                    } else {
                        status = ::DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = ::DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


::DDS::ReturnCode_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::get_key_value(
    org::lsst::sal::SALTopicType & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
org::lsst::sal::SALTopicTypeDataReaderView_impl::lookup_instance(
    const org::lsst::sal::SALTopicType & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



const char * ::org::lsst::sal::SALTopicTypeTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"org\"><Module name=\"lsst\"><Module name=\"sal\"><Struct name=\"SALTopicType\">",
"<Member name=\"private_revCode\"><String/></Member></Struct></Module></Module></Module></MetaData>"};
const CORBA::ULong (::org::lsst::sal::SALTopicTypeTypeSupport::metaDescriptorArrLength) = 2;
