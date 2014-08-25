#if defined (__cplusplus)
extern "C" {
#endif

#include "SALDataSacDcps.h"
#include "SALDataSplDcps.h"

#include <dds_dcps.h>
#include <dds_dcps_private.h>

DDS_sequence_SALData_SALTopic *DDS_sequence_SALData_SALTopic__alloc (void)
{
    return (DDS_sequence_SALData_SALTopic *)DDS__malloc (DDS_sequence_free, 0, sizeof(DDS_sequence_SALData_SALTopic));
}

SALData_SALTopic *DDS_sequence_SALData_SALTopic_allocbuf (DDS_unsigned_long len)
{
    DDS_boolean DDS_sequence_SALData_SALTopic_freebuf (void *buffer);

    return (SALData_SALTopic *)DDS_sequence_allocbuf (DDS_sequence_SALData_SALTopic_freebuf, sizeof (SALData_SALTopic), len);
}

DDS_boolean DDS_sequence_SALData_SALTopic_freebuf (void *buffer)
{
    DDS_unsigned_long *count = (DDS_unsigned_long *)DDS__header (buffer);
    SALData_SALTopic *b = (SALData_SALTopic *)buffer;
    DDS_unsigned_long i;
    void SALData_SALTopic__free (void *object);

    for (i = 0; i < *count; i++) {
        SALData_SALTopic__free (&b[i]);
    }
    return TRUE;
}

SALData_SALTopicTypeSupport
SALData_SALTopicTypeSupport__alloc (
    void
    )
{
    extern c_bool __SALData_SALTopic__copyIn(c_base base, void *from, void *to);
    extern void __SALData_SALTopic__copyOut(void *from, void *to);
    extern const char *SALData_SALTopic_metaDescriptor[];
    extern c_ulong SALData_SALTopic_metaDescriptorArrLength;
    
    c_ulong i;
    c_ulong strlength =0;
    char * metaDescriptor;
    SALData_SALTopicTypeSupport result;
    for (i = 0; i < SALData_SALTopic_metaDescriptorArrLength; i++) {
        strlength +=strlen(SALData_SALTopic_metaDescriptor[i]);
    }
    
    metaDescriptor = malloc(strlength+1);
    metaDescriptor[0] = '\0';
    for (i = 0; i < SALData_SALTopic_metaDescriptorArrLength; i++) {
        strcat(metaDescriptor,SALData_SALTopic_metaDescriptor[i]);
    }
	result = DDS__FooTypeSupport__alloc (
	    __SALData_SALTopic__name(),
            __SALData_SALTopic__keys(),
            metaDescriptor,
            NULL,
            (DDS_copyIn)__SALData_SALTopic__copyIn,
            (DDS_copyOut)__SALData_SALTopic__copyOut,
            (DDS_unsigned_long)(sizeof(SALData_SALTopic)),
            (DDS_typeSupportAllocBuffer)DDS_sequence_SALData_SALTopic_allocbuf
        );
    free(metaDescriptor);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicTypeSupport_register_type (
    SALData_SALTopicTypeSupport _this,
    const DDS_DomainParticipant domain,
    const DDS_string name
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooTypeSupport_register_type (
	    (DDS_TypeSupport)_this,
	    domain,
	    name
	);
    return result;
}

DDS_string
SALData_SALTopicTypeSupport_get_type_name (
    SALData_SALTopicTypeSupport _this
    )
{
    DDS_string result = (DDS_string)
        DDS__FooTypeSupport_get_type_name (
	    (DDS_TypeSupport)_this
	);
    return result;
}

DDS_InstanceHandle_t
SALData_SALTopicDataWriter_register_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data
    )
{
    DDS_InstanceHandle_t result = (DDS_InstanceHandle_t)
        DDS__FooDataWriter_register_instance (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data
	);
    return result;
}

DDS_InstanceHandle_t
SALData_SALTopicDataWriter_register_instance_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_Time_t *source_timestamp
    )
{
    DDS_InstanceHandle_t result = (DDS_InstanceHandle_t)
        DDS__FooDataWriter_register_instance_w_timestamp (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    source_timestamp
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_unregister_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_unregister_instance (
	    (const DDS_DataWriter)_this,
	    (DDS_sample)instance_data,
	    handle
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_unregister_instance_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle,
    const DDS_Time_t *source_timestamp
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_unregister_instance_w_timestamp (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    handle,
	    source_timestamp
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_write (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_write (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    handle
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_write_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle,
    const DDS_Time_t *source_timestamp
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_write_w_timestamp (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    handle,
	    source_timestamp
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_dispose (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_dispose (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    instance_handle
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_dispose_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle,
    const DDS_Time_t *source_timestamp
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_dispose_w_timestamp (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    instance_handle,
	    source_timestamp
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_writedispose (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_writedispose (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    instance_handle
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_writedispose_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle,
    const DDS_Time_t *source_timestamp
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_writedispose_w_timestamp (
	    (DDS_DataWriter)_this,
	    (const DDS_sample)instance_data,
	    instance_handle,
	    source_timestamp
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataWriter_get_key_value (
    SALData_SALTopicDataWriter _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataWriter_get_key_value (
	    (DDS_DataWriter)_this,
	    (DDS_sample)key_holder,
	    handle
	);
    return result;
}

DDS_InstanceHandle_t
SALData_SALTopicDataWriter_lookup_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *key_holder
    )
{
    DDS_InstanceHandle_t result = (DDS_InstanceHandle_t)
        DDS__FooDataWriter_lookup_instance (
        (DDS_DataWriter)_this,
        (DDS_sample)key_holder
    );
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read_w_condition (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_condition
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take_w_condition (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_condition
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read_next_sample (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read_next_sample (
	    (DDS_DataReader)_this,
	    (DDS_sample)received_data,
	    sample_info
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take_next_sample (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take_next_sample (
	    (DDS_DataReader)_this,
	    (DDS_sample)received_data,
	    sample_info
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read_instance (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read_instance (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take_instance (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take_instance (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read_next_instance (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read_next_instance (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take_next_instance (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take_next_instance (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_read_next_instance_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_read_next_instance_w_condition (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    a_condition
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_take_next_instance_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_take_next_instance_w_condition (
	    (DDS_DataReader)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    a_condition
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_return_loan (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_return_loan (
            (DDS_DataReader)_this,
            (DDS_sequence)received_data,
            info_seq
    );
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReader_get_key_value (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReader_get_key_value (
	    (DDS_DataReader)_this,
	    (DDS_sample)key_holder,
	    handle
	);
    return result;
}

DDS_InstanceHandle_t
SALData_SALTopicDataReader_lookup_instance (
    SALData_SALTopicDataReader _this,
    const SALData_SALTopic *key_holder
    )
{
    DDS_InstanceHandle_t result = (DDS_InstanceHandle_t)
        DDS__FooDataReader_lookup_instance (
	    (DDS_DataReader)_this,
	    (DDS_sample)key_holder
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_next_sample (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read_next_sample (
	    (DDS_DataReaderView)_this,
	    (DDS_sample)received_data,
	    sample_info
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_next_sample (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take_next_sample (
	    (DDS_DataReaderView)_this,
	    (DDS_sample)received_data,
	    sample_info
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_instance (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read_instance (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_instance (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take_instance (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_next_instance (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read_next_instance (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_next_instance (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take_next_instance (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
	    sample_states,
	    view_states,
	    instance_states
	);
    return result;
}

DDS_ReturnCode_t
SALData_SALTopicDataReaderView_return_loan (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_return_loan (
            (DDS_DataReaderView)_this,
            (DDS_sequence)received_data,
            info_seq
    );
    
    if ( result == DDS_RETCODE_OK ) {
        DDS__free(received_data->_buffer);
        received_data->_length  = 0;
        received_data->_maximum = 0;
        received_data->_buffer  = NULL;
        
        DDS__free(info_seq->_buffer);
        info_seq->_length  = 0;
        info_seq->_maximum = 0;
        info_seq->_buffer  = NULL;
    }
        
    return result;
}


DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read_w_condition (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
            a_condition
	);
    return result;
}


DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take_w_condition (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
            a_condition
	);
    return result;
}


DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_next_instance_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
   )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_read_next_instance_w_condition (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
            a_condition
	);
    return result;
}


DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_next_instance_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
   )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_take_next_instance_w_condition (
	    (DDS_DataReaderView)_this,
	    (DDS_sequence)received_data,
	    info_seq,
	    max_samples,
	    a_handle,
            a_condition
	);
    return result;
}


DDS_ReturnCode_t
SALData_SALTopicDataReaderView_get_key_value (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    )
{
    DDS_ReturnCode_t result = (DDS_ReturnCode_t)
        DDS__FooDataReaderView_get_key_value (
	    (DDS_DataReaderView)_this,
	    (DDS_sample)key_holder,
	    handle
	);
    return result;
}


DDS_InstanceHandle_t
SALData_SALTopicDataReaderView_lookup_instance (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *key_holder
    )
{
    DDS_InstanceHandle_t result = (DDS_InstanceHandle_t)
        DDS__FooDataReaderView_lookup_instance (
	    (DDS_DataReaderView)_this,
	    (DDS_sample)key_holder
	);
    return result;
}

#if defined (__cplusplus)
}
#endif
