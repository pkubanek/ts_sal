package SALData;

public interface SALCommandDataWriterOperations extends
    DDS.DataWriterOperations
{

    long register_instance(
            SALData.SALCommand instance_data);

    long register_instance_w_timestamp(
            SALData.SALCommand instance_data, 
            DDS.Time_t source_timestamp);

    int unregister_instance(
            SALData.SALCommand instance_data, 
            long handle);

    int unregister_instance_w_timestamp(
            SALData.SALCommand instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int write(
            SALData.SALCommand instance_data, 
            long handle);

    int write_w_timestamp(
            SALData.SALCommand instance_data, 
            long handle, 
            DDS.Time_t source_timestamp);

    int dispose(
            SALData.SALCommand instance_data, 
            long instance_handle);

    int dispose_w_timestamp(
            SALData.SALCommand instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);
    
    int writedispose(
            SALData.SALCommand instance_data, 
            long instance_handle);

    int writedispose_w_timestamp(
            SALData.SALCommand instance_data, 
            long instance_handle, 
            DDS.Time_t source_timestamp);

    int get_key_value(
            SALData.SALCommandHolder key_holder, 
            long handle);
    
    long lookup_instance(
            SALData.SALCommand instance_data);

}
