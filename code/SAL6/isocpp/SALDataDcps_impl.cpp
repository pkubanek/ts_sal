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



const char * ::SALData::SALTopicTypeSupport::metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALTopic\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member></Struct></Module></MetaData>"};
const CORBA::ULong (::SALData::SALTopicTypeSupport::metaDescriptorArrLength) = 3;
