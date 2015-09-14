package SALData;

public interface SALResponseDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            SALData.SALResponse instance_data);

    long register_instance_w_timestamp(
            SALData.SALResponse instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            SALData.SALResponse instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            SALData.SALResponse instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            SALData.SALResponse instance_data, 
            long handle);

    int write_w_timestamp(
            SALData.SALResponse instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            SALData.SALResponse instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            SALData.SALResponse instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            SALData.SALResponse instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            SALData.SALResponse instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            SALData.SALResponseHolder key_holder, 
            long handle);
    
    long lookup_instance(
            SALData.SALResponse instance_data);

}
