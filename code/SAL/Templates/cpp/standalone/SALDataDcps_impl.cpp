#include "SALDataDcps_impl.h"
#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "SALDataSplDcps.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


extern c_bool
__SALData_SALTopic__copyIn(
    c_base base,
    struct SALData::SALTopic *from,
    struct _SALData_SALTopic *to);

extern void
__SALData_SALTopic__copyOut(
    void *_from,
    void *_to);

// DDS SALData::SALTopic TypeSupportFactory Object Body

::DDS::DataWriter_ptr
SALData::SALTopicTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new SALData::SALTopicDataWriter_impl(handle);
}

::DDS::DataReader_ptr
SALData::SALTopicTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new SALData::SALTopicDataReader_impl (handle);
}


::DDS::DataReaderView_ptr
SALData::SALTopicTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new SALData::SALTopicDataReaderView_impl (handle);
}

// DDS SALData::SALTopic TypeSupport Object Body

SALData::SALTopicTypeSupport::SALTopicTypeSupport(void) :
    TypeSupport_impl(
        __SALData_SALTopic__name(),
        __SALData_SALTopic__keys(),
        SALData::SALTopicTypeSupport::metaDescriptor,
        (gapi_copyIn) __SALData_SALTopic__copyIn,
        (gapi_copyOut) __SALData_SALTopic__copyOut,
        (gapi_readerCopy) ::DDS::ccpp_DataReaderCopy<SALData::SALTopicSeq, SALData::SALTopic>,
        new  SALData::SALTopicTypeSupportFactory(),
        SALData::SALTopicTypeSupport::metaDescriptorArrLength)
{
    // Parent constructor takes care of everything.
}

SALData::SALTopicTypeSupport::~SALTopicTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
SALData::SALTopicTypeSupport::register_type(
    ::DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

char *
SALData::SALTopicTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS SALData::SALTopic DataWriter_impl Object Body

SALData::SALTopicDataWriter_impl::SALTopicDataWriter_impl (
    gapi_dataWriter handle
) : ::DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALTopicDataWriter_impl::~SALTopicDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

::DDS::InstanceHandle_t
SALData::SALTopicDataWriter_impl::register_instance(
    const SALData::SALTopic & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
SALData::SALTopicDataWriter_impl::register_instance_w_timestamp(
    const SALTopic & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::unregister_instance(
    const SALData::SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::unregister_instance_w_timestamp(
    const SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::write(
    const SALData::SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::write_w_timestamp(
    const SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::dispose(
    const SALData::SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::dispose_w_timestamp(
    const SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::writedispose(
    const SALData::SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::writedispose_w_timestamp(
    const SALTopic & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALTopicDataWriter_impl::get_key_value(
    SALTopic & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALTopicDataWriter_impl::lookup_instance(
    const SALData::SALTopic & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS SALData::SALTopic DataReader_impl Object Body

SALData::SALTopicDataReader_impl::SALTopicDataReader_impl (
    gapi_dataReader handle
) : ::DDS::DataReader_impl(handle, ::DDS::ccpp_DataReaderParallelDemarshallingMain<SALData::SALTopicSeq>)
{
    // Parent constructor takes care of everything.
}

SALData::SALTopicDataReader_impl::~SALTopicDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALTopicDataReader_impl::read(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::take(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::read_w_condition(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::take_w_condition(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::read_next_sample(
    SALData::SALTopic & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALTopicDataReader_impl::take_next_sample(
    SALData::SALTopic & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALTopicDataReader_impl::read_instance(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::take_instance(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::read_next_instance(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::take_next_instance(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::read_next_instance_w_condition(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::take_next_instance_w_condition(
    SALData::SALTopicSeq & received_data,
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
SALData::SALTopicDataReader_impl::return_loan(
    SALData::SALTopicSeq & received_data,
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
                        SALData::SALTopicSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALTopicDataReader_impl::get_key_value(
    SALData::SALTopic & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALTopicDataReader_impl::lookup_instance(
    const SALData::SALTopic & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
SALData::SALTopicDataReader_impl::check_preconditions(
    SALData::SALTopicSeq & received_data,
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


// DDS SALData::SALTopic DataReaderView_impl Object Body

SALData::SALTopicDataReaderView_impl::SALTopicDataReaderView_impl (
    gapi_dataReaderView handle
) : ::DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALTopicDataReaderView_impl::~SALTopicDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read_w_condition(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take_w_condition(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read_next_sample(
    SALData::SALTopic & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take_next_sample(
    SALData::SALTopic & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read_instance(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take_instance(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read_next_instance(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take_next_instance(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::read_next_instance_w_condition(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::take_next_instance_w_condition(
    SALData::SALTopicSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALTopicDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALTopicDataReaderView_impl::return_loan(
    SALData::SALTopicSeq & received_data,
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
                        SALData::SALTopicSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALTopicDataReaderView_impl::get_key_value(
    SALData::SALTopic & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALTopicDataReaderView_impl::lookup_instance(
    const SALData::SALTopic & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



extern c_bool
__SALData_SALCommand__copyIn(
    c_base base,
    struct SALData::SALCommand *from,
    struct _SALData_SALCommand *to);

extern void
__SALData_SALCommand__copyOut(
    void *_from,
    void *_to);

// DDS SALData::SALCommand TypeSupportFactory Object Body

::DDS::DataWriter_ptr
SALData::SALCommandTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new SALData::SALCommandDataWriter_impl(handle);
}

::DDS::DataReader_ptr
SALData::SALCommandTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new SALData::SALCommandDataReader_impl (handle);
}


::DDS::DataReaderView_ptr
SALData::SALCommandTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new SALData::SALCommandDataReaderView_impl (handle);
}

// DDS SALData::SALCommand TypeSupport Object Body

SALData::SALCommandTypeSupport::SALCommandTypeSupport(void) :
    TypeSupport_impl(
        __SALData_SALCommand__name(),
        __SALData_SALCommand__keys(),
        SALData::SALCommandTypeSupport::metaDescriptor,
        (gapi_copyIn) __SALData_SALCommand__copyIn,
        (gapi_copyOut) __SALData_SALCommand__copyOut,
        (gapi_readerCopy) ::DDS::ccpp_DataReaderCopy<SALData::SALCommandSeq, SALData::SALCommand>,
        new  SALData::SALCommandTypeSupportFactory(),
        SALData::SALCommandTypeSupport::metaDescriptorArrLength)
{
    // Parent constructor takes care of everything.
}

SALData::SALCommandTypeSupport::~SALCommandTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
SALData::SALCommandTypeSupport::register_type(
    ::DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

char *
SALData::SALCommandTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS SALData::SALCommand DataWriter_impl Object Body

SALData::SALCommandDataWriter_impl::SALCommandDataWriter_impl (
    gapi_dataWriter handle
) : ::DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALCommandDataWriter_impl::~SALCommandDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

::DDS::InstanceHandle_t
SALData::SALCommandDataWriter_impl::register_instance(
    const SALData::SALCommand & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
SALData::SALCommandDataWriter_impl::register_instance_w_timestamp(
    const SALCommand & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::unregister_instance(
    const SALData::SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::unregister_instance_w_timestamp(
    const SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::write(
    const SALData::SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::write_w_timestamp(
    const SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::dispose(
    const SALData::SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::dispose_w_timestamp(
    const SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::writedispose(
    const SALData::SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::writedispose_w_timestamp(
    const SALCommand & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALCommandDataWriter_impl::get_key_value(
    SALCommand & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALCommandDataWriter_impl::lookup_instance(
    const SALData::SALCommand & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS SALData::SALCommand DataReader_impl Object Body

SALData::SALCommandDataReader_impl::SALCommandDataReader_impl (
    gapi_dataReader handle
) : ::DDS::DataReader_impl(handle, ::DDS::ccpp_DataReaderParallelDemarshallingMain<SALData::SALCommandSeq>)
{
    // Parent constructor takes care of everything.
}

SALData::SALCommandDataReader_impl::~SALCommandDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALCommandDataReader_impl::read(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::take(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::read_w_condition(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::take_w_condition(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::read_next_sample(
    SALData::SALCommand & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALCommandDataReader_impl::take_next_sample(
    SALData::SALCommand & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALCommandDataReader_impl::read_instance(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::take_instance(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::read_next_instance(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::take_next_instance(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::read_next_instance_w_condition(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::take_next_instance_w_condition(
    SALData::SALCommandSeq & received_data,
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
SALData::SALCommandDataReader_impl::return_loan(
    SALData::SALCommandSeq & received_data,
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
                        SALData::SALCommandSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALCommandDataReader_impl::get_key_value(
    SALData::SALCommand & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALCommandDataReader_impl::lookup_instance(
    const SALData::SALCommand & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
SALData::SALCommandDataReader_impl::check_preconditions(
    SALData::SALCommandSeq & received_data,
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


// DDS SALData::SALCommand DataReaderView_impl Object Body

SALData::SALCommandDataReaderView_impl::SALCommandDataReaderView_impl (
    gapi_dataReaderView handle
) : ::DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALCommandDataReaderView_impl::~SALCommandDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read_w_condition(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take_w_condition(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read_next_sample(
    SALData::SALCommand & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take_next_sample(
    SALData::SALCommand & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read_instance(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take_instance(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read_next_instance(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take_next_instance(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::read_next_instance_w_condition(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::take_next_instance_w_condition(
    SALData::SALCommandSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALCommandDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALCommandDataReaderView_impl::return_loan(
    SALData::SALCommandSeq & received_data,
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
                        SALData::SALCommandSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALCommandDataReaderView_impl::get_key_value(
    SALData::SALCommand & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALCommandDataReaderView_impl::lookup_instance(
    const SALData::SALCommand & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



extern c_bool
__SALData_SALResponse__copyIn(
    c_base base,
    struct SALData::SALResponse *from,
    struct _SALData_SALResponse *to);

extern void
__SALData_SALResponse__copyOut(
    void *_from,
    void *_to);

// DDS SALData::SALResponse TypeSupportFactory Object Body

::DDS::DataWriter_ptr
SALData::SALResponseTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new SALData::SALResponseDataWriter_impl(handle);
}

::DDS::DataReader_ptr
SALData::SALResponseTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new SALData::SALResponseDataReader_impl (handle);
}


::DDS::DataReaderView_ptr
SALData::SALResponseTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new SALData::SALResponseDataReaderView_impl (handle);
}

// DDS SALData::SALResponse TypeSupport Object Body

SALData::SALResponseTypeSupport::SALResponseTypeSupport(void) :
    TypeSupport_impl(
        __SALData_SALResponse__name(),
        __SALData_SALResponse__keys(),
        SALData::SALResponseTypeSupport::metaDescriptor,
        (gapi_copyIn) __SALData_SALResponse__copyIn,
        (gapi_copyOut) __SALData_SALResponse__copyOut,
        (gapi_readerCopy) ::DDS::ccpp_DataReaderCopy<SALData::SALResponseSeq, SALData::SALResponse>,
        new  SALData::SALResponseTypeSupportFactory(),
        SALData::SALResponseTypeSupport::metaDescriptorArrLength)
{
    // Parent constructor takes care of everything.
}

SALData::SALResponseTypeSupport::~SALResponseTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
SALData::SALResponseTypeSupport::register_type(
    ::DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

char *
SALData::SALResponseTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS SALData::SALResponse DataWriter_impl Object Body

SALData::SALResponseDataWriter_impl::SALResponseDataWriter_impl (
    gapi_dataWriter handle
) : ::DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALResponseDataWriter_impl::~SALResponseDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

::DDS::InstanceHandle_t
SALData::SALResponseDataWriter_impl::register_instance(
    const SALData::SALResponse & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
SALData::SALResponseDataWriter_impl::register_instance_w_timestamp(
    const SALResponse & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::unregister_instance(
    const SALData::SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::unregister_instance_w_timestamp(
    const SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::write(
    const SALData::SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::write_w_timestamp(
    const SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::dispose(
    const SALData::SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::dispose_w_timestamp(
    const SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::writedispose(
    const SALData::SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::writedispose_w_timestamp(
    const SALResponse & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALResponseDataWriter_impl::get_key_value(
    SALResponse & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALResponseDataWriter_impl::lookup_instance(
    const SALData::SALResponse & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS SALData::SALResponse DataReader_impl Object Body

SALData::SALResponseDataReader_impl::SALResponseDataReader_impl (
    gapi_dataReader handle
) : ::DDS::DataReader_impl(handle, ::DDS::ccpp_DataReaderParallelDemarshallingMain<SALData::SALResponseSeq>)
{
    // Parent constructor takes care of everything.
}

SALData::SALResponseDataReader_impl::~SALResponseDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALResponseDataReader_impl::read(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::take(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::read_w_condition(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::take_w_condition(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::read_next_sample(
    SALData::SALResponse & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALResponseDataReader_impl::take_next_sample(
    SALData::SALResponse & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALResponseDataReader_impl::read_instance(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::take_instance(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::read_next_instance(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::take_next_instance(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::read_next_instance_w_condition(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::take_next_instance_w_condition(
    SALData::SALResponseSeq & received_data,
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
SALData::SALResponseDataReader_impl::return_loan(
    SALData::SALResponseSeq & received_data,
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
                        SALData::SALResponseSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALResponseDataReader_impl::get_key_value(
    SALData::SALResponse & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALResponseDataReader_impl::lookup_instance(
    const SALData::SALResponse & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
SALData::SALResponseDataReader_impl::check_preconditions(
    SALData::SALResponseSeq & received_data,
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


// DDS SALData::SALResponse DataReaderView_impl Object Body

SALData::SALResponseDataReaderView_impl::SALResponseDataReaderView_impl (
    gapi_dataReaderView handle
) : ::DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALResponseDataReaderView_impl::~SALResponseDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read_w_condition(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take_w_condition(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read_next_sample(
    SALData::SALResponse & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take_next_sample(
    SALData::SALResponse & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read_instance(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take_instance(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read_next_instance(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take_next_instance(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::read_next_instance_w_condition(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::take_next_instance_w_condition(
    SALData::SALResponseSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALResponseDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALResponseDataReaderView_impl::return_loan(
    SALData::SALResponseSeq & received_data,
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
                        SALData::SALResponseSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALResponseDataReaderView_impl::get_key_value(
    SALData::SALResponse & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALResponseDataReaderView_impl::lookup_instance(
    const SALData::SALResponse & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



extern c_bool
__SALData_SALEvent__copyIn(
    c_base base,
    struct SALData::SALEvent *from,
    struct _SALData_SALEvent *to);

extern void
__SALData_SALEvent__copyOut(
    void *_from,
    void *_to);

// DDS SALData::SALEvent TypeSupportFactory Object Body

::DDS::DataWriter_ptr
SALData::SALEventTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new SALData::SALEventDataWriter_impl(handle);
}

::DDS::DataReader_ptr
SALData::SALEventTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new SALData::SALEventDataReader_impl (handle);
}


::DDS::DataReaderView_ptr
SALData::SALEventTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new SALData::SALEventDataReaderView_impl (handle);
}

// DDS SALData::SALEvent TypeSupport Object Body

SALData::SALEventTypeSupport::SALEventTypeSupport(void) :
    TypeSupport_impl(
        __SALData_SALEvent__name(),
        __SALData_SALEvent__keys(),
        SALData::SALEventTypeSupport::metaDescriptor,
        (gapi_copyIn) __SALData_SALEvent__copyIn,
        (gapi_copyOut) __SALData_SALEvent__copyOut,
        (gapi_readerCopy) ::DDS::ccpp_DataReaderCopy<SALData::SALEventSeq, SALData::SALEvent>,
        new  SALData::SALEventTypeSupportFactory(),
        SALData::SALEventTypeSupport::metaDescriptorArrLength)
{
    // Parent constructor takes care of everything.
}

SALData::SALEventTypeSupport::~SALEventTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
SALData::SALEventTypeSupport::register_type(
    ::DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

char *
SALData::SALEventTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS SALData::SALEvent DataWriter_impl Object Body

SALData::SALEventDataWriter_impl::SALEventDataWriter_impl (
    gapi_dataWriter handle
) : ::DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALEventDataWriter_impl::~SALEventDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

::DDS::InstanceHandle_t
SALData::SALEventDataWriter_impl::register_instance(
    const SALData::SALEvent & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
SALData::SALEventDataWriter_impl::register_instance_w_timestamp(
    const SALEvent & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::unregister_instance(
    const SALData::SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::unregister_instance_w_timestamp(
    const SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::write(
    const SALData::SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::write_w_timestamp(
    const SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::dispose(
    const SALData::SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::dispose_w_timestamp(
    const SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::writedispose(
    const SALData::SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::writedispose_w_timestamp(
    const SALEvent & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
SALData::SALEventDataWriter_impl::get_key_value(
    SALEvent & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALEventDataWriter_impl::lookup_instance(
    const SALData::SALEvent & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS SALData::SALEvent DataReader_impl Object Body

SALData::SALEventDataReader_impl::SALEventDataReader_impl (
    gapi_dataReader handle
) : ::DDS::DataReader_impl(handle, ::DDS::ccpp_DataReaderParallelDemarshallingMain<SALData::SALEventSeq>)
{
    // Parent constructor takes care of everything.
}

SALData::SALEventDataReader_impl::~SALEventDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALEventDataReader_impl::read(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::take(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::read_w_condition(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::take_w_condition(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::read_next_sample(
    SALData::SALEvent & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALEventDataReader_impl::take_next_sample(
    SALData::SALEvent & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALEventDataReader_impl::read_instance(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::take_instance(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::read_next_instance(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::take_next_instance(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::read_next_instance_w_condition(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::take_next_instance_w_condition(
    SALData::SALEventSeq & received_data,
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
SALData::SALEventDataReader_impl::return_loan(
    SALData::SALEventSeq & received_data,
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
                        SALData::SALEventSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALEventDataReader_impl::get_key_value(
    SALData::SALEvent & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALEventDataReader_impl::lookup_instance(
    const SALData::SALEvent & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
SALData::SALEventDataReader_impl::check_preconditions(
    SALData::SALEventSeq & received_data,
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


// DDS SALData::SALEvent DataReaderView_impl Object Body

SALData::SALEventDataReaderView_impl::SALEventDataReaderView_impl (
    gapi_dataReaderView handle
) : ::DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

SALData::SALEventDataReaderView_impl::~SALEventDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read_w_condition(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take_w_condition(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read_next_sample(
    SALData::SALEvent & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take_next_sample(
    SALData::SALEvent & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read_instance(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take_instance(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read_next_instance(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take_next_instance(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::read_next_instance_w_condition(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::take_next_instance_w_condition(
    SALData::SALEventSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = SALData::SALEventDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


::DDS::ReturnCode_t
SALData::SALEventDataReaderView_impl::return_loan(
    SALData::SALEventSeq & received_data,
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
                        SALData::SALEventSeq::freebuf( received_data.get_buffer(false) );
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
SALData::SALEventDataReaderView_impl::get_key_value(
    SALData::SALEvent & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
SALData::SALEventDataReaderView_impl::lookup_instance(
    const SALData::SALEvent & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



const char * ::SALData::SALTopicTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALTopic\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member></Struct></Module></MetaData>"};
const CORBA::ULong (::SALData::SALTopicTypeSupport::metaDescriptorArrLength) = 3;
const char * ::SALData::SALCommandTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALCommand\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member><Member name=\"private_seqNum\"><Long/>",
"</Member><Member name=\"device\"><String length=\"32\"/></Member><Member name=\"property\"><String length=\"32\"/>",
"</Member><Member name=\"action\"><String length=\"32\"/></Member><Member name=\"value\"><String length=\"32\"/>",
"</Member><Member name=\"modifiers\"><String length=\"128\"/></Member></Struct></Module></MetaData>"};
const CORBA::ULong (::SALData::SALCommandTypeSupport::metaDescriptorArrLength) = 6;
const char * ::SALData::SALResponseTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALResponse\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member><Member name=\"private_seqNum\"><Long/>",
"</Member><Member name=\"ack\"><Long/></Member><Member name=\"error\"><Long/></Member><Member name=\"result\">",
"<String length=\"32\"/></Member></Struct></Module></MetaData>"};
const CORBA::ULong (::SALData::SALResponseTypeSupport::metaDescriptorArrLength) = 5;
const char * ::SALData::SALEventTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALEvent\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member><Member name=\"message\"><String length=\"128\"/>",
"</Member></Struct></Module></MetaData>"};
const CORBA::ULong (::SALData::SALEventTypeSupport::metaDescriptorArrLength) = 4;
