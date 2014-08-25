package SALData;

public interface SALEventDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            SALData.SALEvent instance_data);

    long register_instance_w_timestamp(
            SALData.SALEvent instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            SALData.SALEvent instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            SALData.SALEvent instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            SALData.SALEvent instance_data, 
            long handle);

    int write_w_timestamp(
            SALData.SALEvent instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            SALData.SALEvent instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            SALData.SALEvent instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            SALData.SALEvent instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            SALData.SALEvent instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            SALData.SALEventHolder key_holder, 
            long handle);
    
    long lookup_instance(
            SALData.SALEvent instance_data);

}
