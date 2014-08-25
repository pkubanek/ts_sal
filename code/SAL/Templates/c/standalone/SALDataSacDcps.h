#ifndef SALDATASACDCPS_H
#define SALDATASACDCPS_H

#include "SALDataDcps.h"

#ifndef DDS_API
#define DDS_API
#endif


#define SALData_SALTopicTypeSupport DDS_TypeSupport

 SALData_SALTopicTypeSupport
SALData_SALTopicTypeSupport__alloc (
    void
    );

 DDS_ReturnCode_t
SALData_SALTopicTypeSupport_register_type (
    SALData_SALTopicTypeSupport _this,
    const DDS_DomainParticipant domain,
    const DDS_string name
    );

 DDS_string
SALData_SALTopicTypeSupport_get_type_name (
    SALData_SALTopicTypeSupport _this
    );

#ifndef _DDS_sequence_SALData_SALTopic_defined
#define _DDS_sequence_SALData_SALTopic_defined
typedef struct {
    DDS_unsigned_long _maximum;
    DDS_unsigned_long _length;
    SALData_SALTopic *_buffer;
    DDS_boolean _release;
} DDS_sequence_SALData_SALTopic;

 DDS_sequence_SALData_SALTopic *DDS_sequence_SALData_SALTopic__alloc (void);
 SALData_SALTopic *DDS_sequence_SALData_SALTopic_allocbuf (DDS_unsigned_long len);
#endif /* _DDS_sequence_SALData_SALTopic_defined */

#define SALData_SALTopicDataWriter DDS_DataWriter

#define SALData_SALTopicDataWriter_enable DDS_Entity_enable

#define SALData_SALTopicDataWriter_get_status_changes DDS_Entity_get_status_changes

#define SALData_SALTopicDataWriter_get_statuscondition DDS_Entity_get_statuscondition

#define SALData_SALTopicDataWriter_get_instance_handle DDS_Entity_get_instance_handle

#define SALData_SALTopicDataWriter_assert_liveliness DDS_DataWriter_assert_liveliness

#define SALData_SALTopicDataWriter_get_listener DDS_DataWriter_get_listener

#define SALData_SALTopicDataWriter_get_liveliness_lost_status DDS_DataWriter_get_liveliness_lost_status

#define SALData_SALTopicDataWriter_get_matched_subscription_data DDS_DataWriter_get_matched_subscription_data

#define SALData_SALTopicDataWriter_get_matched_subscriptions DDS_DataWriter_get_matched_subscriptions

#define SALData_SALTopicDataWriter_get_offered_deadline_missed_status DDS_DataWriter_get_offered_deadline_missed_status

#define SALData_SALTopicDataWriter_get_offered_incompatible_qos_status DDS_DataWriter_get_offered_incompatible_qos_status

#define SALData_SALTopicDataWriter_get_publication_match_status DDS_DataWriter_get_publication_match_status

#define SALData_SALTopicDataWriter_get_publisher DDS_DataWriter_get_publisher

#define SALData_SALTopicDataWriter_get_qos DDS_DataWriter_get_qos

#define SALData_SALTopicDataWriter_get_topic DDS_DataWriter_get_topic

#define SALData_SALTopicDataWriter_set_listener DDS_DataWriter_set_listener

#define SALData_SALTopicDataWriter_set_qos DDS_DataWriter_set_qos

 DDS_InstanceHandle_t
SALData_SALTopicDataWriter_register_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data
    );

 DDS_InstanceHandle_t
SALData_SALTopicDataWriter_register_instance_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_Time_t *source_timestamp
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_unregister_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_unregister_instance_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle,
    const DDS_Time_t *source_timestamp
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_write (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_write_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t handle,
    const DDS_Time_t *source_timestamp
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_dispose (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_dispose_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle,
    const DDS_Time_t *source_timestamp
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_writedispose (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_writedispose_w_timestamp (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *instance_data,
    const DDS_InstanceHandle_t instance_handle,
    const DDS_Time_t *source_timestamp
    );

 DDS_ReturnCode_t
SALData_SALTopicDataWriter_get_key_value (
    SALData_SALTopicDataWriter _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    );

 DDS_InstanceHandle_t
SALData_SALTopicDataWriter_lookup_instance (
    SALData_SALTopicDataWriter _this,
    const SALData_SALTopic *key_holder
    );

#define SALData_SALTopicDataReader DDS_DataReader

#define SALData_SALTopicDataReader_enable DDS_Entity_enable

#define SALData_SALTopicDataReader_get_status_changes DDS_Entity_get_status_changes

#define SALData_SALTopicDataReader_get_statuscondition DDS_Entity_get_statuscondition

#define SALData_SALTopicDataReader_get_instance_handle DDS_Entity_get_instance_handle

#define SALData_SALTopicDataReader_create_querycondition DDS_DataReader_create_querycondition

#define SALData_SALTopicDataReader_create_readcondition DDS_DataReader_create_readcondition

#define SALData_SALTopicDataReader_delete_contained_entities DDS_DataReader_delete_contained_entities

#define SALData_SALTopicDataReader_delete_readcondition DDS_DataReader_delete_readcondition

#define SALData_SALTopicDataReader_get_listener DDS_DataReader_get_listener

#define SALData_SALTopicDataReader_get_liveliness_changed_status DDS_DataReader_get_liveliness_changed_status

#define SALData_SALTopicDataReader_get_matched_publication_data DDS_DataReader_get_matched_publication_data

#define SALData_SALTopicDataReader_get_matched_publications DDS_DataReader_get_matched_publications

#define SALData_SALTopicDataReader_get_qos DDS_DataReader_get_qos

#define SALData_SALTopicDataReader_get_requested_deadline_missed_status DDS_DataReader_get_requested_deadline_missed_status

#define SALData_SALTopicDataReader_get_requested_incompatible_qos_status DDS_DataReader_get_requested_incompatible_qos_status

#define SALData_SALTopicDataReader_get_sample_lost_status DDS_DataReader_get_sample_lost_status

#define SALData_SALTopicDataReader_get_sample_rejected_status DDS_DataReader_get_sample_rejected_status

#define SALData_SALTopicDataReader_get_subscriber DDS_DataReader_get_subscriber

#define SALData_SALTopicDataReader_get_subscription_match_status DDS_DataReader_get_subscription_match_status

#define SALData_SALTopicDataReader_get_topicdescription DDS_DataReader_get_topicdescription

#define SALData_SALTopicDataReader_set_listener DDS_DataReader_set_listener

#define SALData_SALTopicDataReader_set_qos DDS_DataReader_set_qos

#define SALData_SALTopicDataReader_wait_for_historical_data DDS_DataReader_wait_for_historical_data

 DDS_ReturnCode_t
SALData_SALTopicDataReader_read (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_take (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_read_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_take_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_read_next_sample (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_take_next_sample (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    );

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
    );

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
    );

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
    );

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
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_read_next_instance_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_take_next_instance_w_condition (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_return_loan (
    SALData_SALTopicDataReader _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReader_get_key_value (
    SALData_SALTopicDataReader _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    );

 DDS_InstanceHandle_t
SALData_SALTopicDataReader_lookup_instance (
    SALData_SALTopicDataReader _this,
    const SALData_SALTopic *key_holder
    );

#define SALData_SALTopicDataReaderView DDS_DataReaderView

#define SALData_SALTopicDataReaderView_enable DDS_Entity_enable

#define SALData_SALTopicDataReaderView_get_instance_handle DDS_Entity_get_instance_handle

#define SALData_SALTopicDataReaderView_get_qos DDS_DataReaderView_get_qos

#define SALData_SALTopicDataReaderView_get_datareader DDS_DataReaderView_get_datareader

#define SALData_SALTopicDataReaderView_set_qos DDS_DataReaderView_set_qos

#define SALData_SALTopicDataReaderView_create_readcondition DDS_DataReaderView_create_readcondition

#define SALData_SALTopicDataReaderView_create_querycondition DDS_DataReaderView_create_querycondition

#define SALData_SALTopicDataReaderView_delete_readcondition DDS_DataReaderView_delete_readcondition

#define SALData_SALTopicDataReaderView_delete_contained_entities DDS_DataReaderView_delete_contained_entities

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_SampleStateMask sample_states,
    const DDS_ViewStateMask view_states,
    const DDS_InstanceStateMask instance_states
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_next_sample (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_next_sample (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *received_data,
    DDS_SampleInfo *sample_info
    );

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
    );

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
    );

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
    );

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
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_return_loan (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_read_next_instance_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_take_next_instance_w_condition (
    SALData_SALTopicDataReaderView _this,
    DDS_sequence_SALData_SALTopic *received_data,
    DDS_SampleInfoSeq *info_seq,
    const DDS_long max_samples,
    const DDS_InstanceHandle_t a_handle,
    const DDS_ReadCondition a_condition
    );

 DDS_ReturnCode_t
SALData_SALTopicDataReaderView_get_key_value (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *key_holder,
    const DDS_InstanceHandle_t handle
    );

 DDS_InstanceHandle_t
SALData_SALTopicDataReaderView_lookup_instance (
    SALData_SALTopicDataReaderView _this,
    SALData_SALTopic *key_holder
    );

#endif
