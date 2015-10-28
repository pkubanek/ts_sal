
proc addCallbackMethod { fout base name } {
   puts $fout "
int SAL_[set base]::registerCallback_[set name] ( int (*dataProcessor([set base]_[set name]C *data) )
\{
/* Create data reader listener */
	int actorIdx = SAL__[set base]_[set name]_ACTOR;
	sal\[actorIdx\].reader_listener = DDS_DataReaderListener__alloc();
	sal\[actorIdx\].reader_listener->listener_data = NULL;
	sal\[actorIdx\].reader_listener->on_data_available = (void (*)(void *, DDS_DataReader))on_[set name]Data_available;
	sal\[actorIdx\].reader_listener->on_requested_deadline_missed = NULL;
	sal\[actorIdx\].reader_listener->on_requested_incompatible_qos = NULL;
	sal\[actorIdx\].reader_listener->on_sample_rejected = NULL;
	sal\[actorIdx\].reader_listener->on_liveliness_changed = NULL;
	sal\[actorIdx\].reader_listener->on_subscription_matched = NULL;
	sal\[actorIdx\].reader_listener->on_sample_lost = NULL;
	sal\[actorIdx\].dataProcessor = dataProcessor;
	sal\[actorIdx\].reader = DDS_Subscriber_create_datareader(sal\[actorIdx\].subscriber, 
								sal\[actorIdx\].topic, 
								DDS_DATAREADER_QOS_DEFAULT,
								sal\[actorIdx\].reader_listener,
								DDS_DATA_AVAILABLE_STATUS); 
\}

void on_[set name]Data_available (void *listener_data, DDS_DataReader reader )
\{
	int status;
	[set base].[set name]C data;
	int actorIdx = SAL__[set base]_[set name]_ACTOR;
	[set name]DataReader [set name]_reader = NULL;
	DDS_sequence_[set name] *Instances = NULL;
	DDS_SampleInfoSeq *info_seq = NULL;

	[set name]_reader = reader;
	data_seq = DDS_sequence_[set name]__alloc();
	info_seq = DDS_SampleInfoSeq__alloc();
	retcode = [set name]DataReader_take([set name]_reader,
					  Instances, 
					  info_seq,
					  DDS_LENGTH_UNLIMITED,
					  DDS_ANY_SAMPLE_STATE,
					  DDS_ANY_VIEW_STATE,
					  DDS_ANY_INSTANCE_STATE);

	for (j = 0; j <Instances->_length; ++j) \{
  	   if (info_seq->_buffer\[j\].valid_data) \{
               if (sal\[actorIdx\].dataProcessor != NULL) \{"

// copy Instances[j] into data (include/SAL_[set base]_[set name].Cget.tmp)

    puts $fout " 		   status = *(sal\[actorIdx\].dataprocessor)(&data);
               \}
           \}
	\}
\}

int SAL_[set base]::print_[set name] ([set base]_[set name]C *data) 
\{"

// copy from include/SAL_[set base]_[set name].Cout.tmp

    puts $fout "
\}"
}




