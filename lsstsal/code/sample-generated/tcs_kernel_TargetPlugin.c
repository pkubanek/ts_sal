
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/


#include <string.h>

#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

#ifndef osapi_type_h
  #include "osapi/osapi_type.h"
#endif
#ifndef osapi_heap_h
  #include "osapi/osapi_heap.h"
#endif

#ifndef osapi_utility_h
  #include "osapi/osapi_utility.h"
#endif

#ifndef cdr_type_h
  #include "cdr/cdr_type.h"
#endif

#ifndef cdr_type_h
  #include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
  #include "cdr/cdr_stream.h"
#endif

#ifndef pres_typePlugin_h
  #include "pres/pres_typePlugin.h"
#endif



#ifndef tcs_kernel_TargetPlugin_h
#include "tcs_kernel_TargetPlugin.h"
#endif


/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


RTIBool tcs_kernel_TargetPlugin_serialize_data(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option)
{

    if (!integerPlugin_serialize_data(
        stream, &sample->private_revCode, serialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_serialize_data(
        stream, &sample->private_sndStamp, serialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_serialize_data(
        stream, &sample->private_rcvStamp, serialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_serialize_data(
        stream, &sample->private_seqNum, serialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_serialize_data(
        stream, &sample->private_origin, serialize_option)) {
        return RTI_FALSE;
    }
            
    if (sample->site == NULL) {
        return RTI_FALSE;
    }
    if (!RTICdrStream_serializeString(
        stream, sample->site, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->t0)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->az)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->el)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->azdot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->eldot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->Wavel)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->XOffset)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->YOffset)) {
        return RTI_FALSE;
    }
            
    if (sample->OffSys == NULL) {
        return RTI_FALSE;
    }
    if (!RTICdrStream_serializeString(
        stream, sample->OffSys, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->focalplaneX)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->focalplaneY)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->Temp)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->Press)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->Humid)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->TLR)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeFloat(
        stream, &sample->Tai)) {
        return RTI_FALSE;
    }
            
    return RTI_TRUE;
}



RTIBool tcs_kernel_TargetPlugin_serialize(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option)
{
    if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
        return RTI_FALSE;
    }
    return tcs_kernel_TargetPlugin_serialize_data(
        stream, sample, serialize_option); 
} 





RTIBool tcs_kernel_TargetPlugin_deserialize_data(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option)
{

    if (!integerPlugin_deserialize_data(
        stream, &sample->private_revCode, deserialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_deserialize_data(
        stream, &sample->private_sndStamp, deserialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_deserialize_data(
        stream, &sample->private_rcvStamp, deserialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_deserialize_data(
        stream, &sample->private_seqNum, deserialize_option)) {
        return RTI_FALSE;
    }
            
    if (!integerPlugin_deserialize_data(
        stream, &sample->private_origin, deserialize_option)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeString(
        stream, sample->site, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->t0)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->az)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->el)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->azdot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->eldot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->Wavel)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->XOffset)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->YOffset)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeString(
        stream, sample->OffSys, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->focalplaneX)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->focalplaneY)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->Temp)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->Press)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->Humid)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->TLR)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeFloat(
        stream, &sample->Tai)) {
        return RTI_FALSE;
    }
            
    return RTI_TRUE;
}


RTIBool tcs_kernel_TargetPlugin_deserialize(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option)
{
    if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
        return RTI_FALSE;
    }
    return tcs_kernel_TargetPlugin_deserialize_data(
        stream, sample, deserialize_option); 
}





unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized_data(
    unsigned int current_alignment)
{
        
    unsigned int initial_alignment = current_alignment;
        

    current_alignment +=  integerPlugin_get_max_size_serialized_data(
        current_alignment);
            
    current_alignment +=  integerPlugin_get_max_size_serialized_data(
        current_alignment);
            
    current_alignment +=  integerPlugin_get_max_size_serialized_data(
        current_alignment);
            
    current_alignment +=  integerPlugin_get_max_size_serialized_data(
        current_alignment);
            
    current_alignment +=  integerPlugin_get_max_size_serialized_data(
        current_alignment);
            
    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, (32) + 1);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, (32) + 1);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    return current_alignment - initial_alignment;
}



RTIBool tcs_kernel_TargetPlugin_serialize_key(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option)
{


    return RTI_TRUE;
}


RTIBool tcs_kernel_TargetPlugin_deserialize_key(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option)
{

    return RTI_TRUE;
}


unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized_key(
    unsigned int current_alignment)
{
        
    unsigned int initial_alignment = current_alignment;
        

    return current_alignment - initial_alignment;
}



unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized(
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += RTICdrType_getUnsignedShortMaxSizeSerialized(current_alignment);
    current_alignment += RTICdrType_getUnsignedShortMaxSizeSerialized(current_alignment);
    
    return (current_alignment - initial_alignment) + 
           tcs_kernel_TargetPlugin_get_max_size_serialized_data(
               current_alignment);
}

/* ------------------------------------------------------------------------
 * Utility Methods
 * ------------------------------------------------------------------------ */


void tcs_kernel_TargetPlugin_print(
    const tcs_kernel_Target *sample,
    const char* description, int indent_level)
{

    if (description != NULL) {
        RTICdrType_printIndent(indent_level);
        RTILog_debug("%s:\n", description);
    }

    if (sample == NULL) {
        RTICdrType_printIndent(indent_level + 1);
        RTILog_debug("NULL\n");
        return;
    }
        

    integerPlugin_print(
        &sample->private_revCode, "private_revCode", indent_level + 1);
            
    integerPlugin_print(
        &sample->private_sndStamp, "private_sndStamp", indent_level + 1);
            
    integerPlugin_print(
        &sample->private_rcvStamp, "private_rcvStamp", indent_level + 1);
            
    integerPlugin_print(
        &sample->private_seqNum, "private_seqNum", indent_level + 1);
            
    integerPlugin_print(
        &sample->private_origin, "private_origin", indent_level + 1);
            
    if (&sample->site==NULL) {
        RTICdrType_printString(
            NULL, "site", indent_level + 1);                
    } else {
        RTICdrType_printString(
            sample->site, "site", indent_level + 1);                
    }
            
    RTICdrType_printFloat(
        &sample->t0, "t0", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->az, "az", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->el, "el", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->azdot, "azdot", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->eldot, "eldot", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->Wavel, "Wavel", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->XOffset, "XOffset", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->YOffset, "YOffset", indent_level + 1);
            
    if (&sample->OffSys==NULL) {
        RTICdrType_printString(
            NULL, "OffSys", indent_level + 1);                
    } else {
        RTICdrType_printString(
            sample->OffSys, "OffSys", indent_level + 1);                
    }
            
    RTICdrType_printFloat(
        &sample->focalplaneX, "focalplaneX", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->focalplaneY, "focalplaneY", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->Temp, "Temp", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->Press, "Press", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->Humid, "Humid", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->TLR, "TLR", indent_level + 1);
            
    RTICdrType_printFloat(
        &sample->Tai, "Tai", indent_level + 1);
            
}

/* ------------------------------------------------------------------------
 * Lifecycle Methods
 * ------------------------------------------------------------------------ */


tcs_kernel_Target *tcs_kernel_TargetPlugin_create_sample()
{
    return tcs_kernel_TargetPlugin_create_sample_ex(RTI_TRUE);
}
        

tcs_kernel_Target *tcs_kernel_TargetPlugin_create_sample_ex(RTIBool allocatePointers)
{

    tcs_kernel_Target *sample = NULL;

    RTIOsapiHeap_allocateStructure(&sample, tcs_kernel_Target);
                
    if (sample != NULL) {
        if (!tcs_kernel_Target_initialize_ex(sample,allocatePointers)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }

    return sample;
}


void tcs_kernel_TargetPlugin_delete_sample(
    tcs_kernel_Target *sample)
{
    tcs_kernel_TargetPlugin_delete_sample_ex(sample,RTI_TRUE);
}
        

void tcs_kernel_TargetPlugin_delete_sample_ex(
    tcs_kernel_Target *sample,RTIBool deletePointers)
{
    tcs_kernel_Target_finalize_ex(sample,deletePointers);
    RTIOsapiHeap_freeStructure(sample);
}

 


/* ------------------------------------------------------------------------
 * Key Manipulation Methods
 * ------------------------------------------------------------------------ */


PRESTypePluginKeyKind tcs_kernel_TargetPlugin_get_key_kind()
{
        

    return PRES_TYPEPLUGIN_NO_KEY;
    
}


tcs_kernel_TargetKeyHolder *tcs_kernel_TargetPlugin_create_key()
{
    /* Note: If the definition of tcs_kernel_TargetKeyHolder
     * changes, the implementation of this method will need to change
     * accordingly.
     */
    return tcs_kernel_TargetPlugin_create_sample();
}


void tcs_kernel_TargetPlugin_delete_key(
    tcs_kernel_TargetKeyHolder *key)
{
    /* Note: If the definition of tcs_kernel_TargetKeyHolder
     * changes, the implementation of this method will need to change
     * accordingly.
     */
    tcs_kernel_TargetPlugin_delete_sample(key);
}


RTIBool tcs_kernel_TargetPlugin_instance_to_key(
    tcs_kernel_TargetKeyHolder *dst, const tcs_kernel_Target *src)
{

    return RTI_TRUE;
}


RTIBool tcs_kernel_TargetPlugin_key_to_instance(
    tcs_kernel_Target *dst, const tcs_kernel_TargetKeyHolder *src)
{

    return RTI_TRUE;
}


/* Fill in the fields of the given instance ID based on the key field(s)
 * of the given instance sample.
 *
 * Important: The fields of the instance ID cannot all be set to zero!
 */
RTIBool tcs_kernel_TargetPlugin_instance_to_id(
    DDS_InstanceId_t *id, RTIBool *is_unique,
    const tcs_kernel_Target *instance)
{
    int idIndex;

    idIndex = 3;

    id->value[3] = 0;
    id->value[2] = 0;
    id->value[1] = 0;
    id->value[0] = 0;


    /* By default, NDDSGen assumes that the key specified in the type
     * fully identifies instances of that type. If you would like to
     * further discriminate among instances based on the participant
     * from which they originate, set this out parameter to RTI_FALSE. In
     * that case, only set the value at the last index of the instance ID;
     * the first three values will be set automatically to the RTPS host ID and
     * application ID of the writer's domain participant. (See the
     * documentation for DDS_WireProtocolQosPolicy for a description of
     * the host ID and app ID.)
     */
    *is_unique = RTI_TRUE;
    return RTI_TRUE;
}












/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */

struct PRESTypePlugin *tcs_kernel_TargetPlugin_new()
{
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_1_1;
    
    RTIOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);

    plugin->version = PLUGIN_VERSION;

    plugin->data.serializeFnc =
        (RTICdrStreamSerializeFunction)
        tcs_kernel_TargetPlugin_serialize;

    plugin->data.serializeDataFnc =
        (RTICdrStreamSerializeFunction)
        tcs_kernel_TargetPlugin_serialize_data;  
    plugin->data.deserializeFnc =
        (RTICdrStreamDeserializeFunction)
        tcs_kernel_TargetPlugin_deserialize;

    plugin->data.deserializeDataFnc =
        (RTICdrStreamDeserializeFunction)
        tcs_kernel_TargetPlugin_deserialize_data;
    plugin->data.copyFnc =
        (PRESTypePluginDataCopyFunction)
        tcs_kernel_Target_copy;
    plugin->data.getKeyKindFnc =
        (PRESTypePluginDataGetKeyKindFunction)
        tcs_kernel_TargetPlugin_get_key_kind;
    plugin->data.printFnc =
        (RTICdrTypePrintFunction)
        tcs_kernel_TargetPlugin_print;
    plugin->data.getMaxSizeSerializedFnc =
        (RTICdrTypeGetMaxSizeSerializedFunction)
        tcs_kernel_TargetPlugin_get_max_size_serialized;
    plugin->data.getMaxSizeSerializedDataFnc =
        (RTICdrTypeGetMaxSizeSerializedFunction)
        tcs_kernel_TargetPlugin_get_max_size_serialized_data;
    plugin->data.createSampleExFnc =
        (PRESTypePluginDataCreateSampleExFunction)
        tcs_kernel_TargetPlugin_create_sample_ex;
    plugin->data.createSampleFnc =
        (PRESTypePluginDataCreateSampleFunction)
        tcs_kernel_TargetPlugin_create_sample;        
    plugin->data.destroySampleExFnc =
        (PRESTypePluginDataDestroySampleExFunction)
        tcs_kernel_TargetPlugin_delete_sample_ex;
    plugin->data.destroySampleFnc =
        (PRESTypePluginDataDestroySampleFunction)
        tcs_kernel_TargetPlugin_delete_sample;        
    plugin->data.initializeExFnc =
        (PRESTypePluginDataInitializeExFunction)
        tcs_kernel_Target_initialize_ex;
    plugin->data.initializeFnc =
        (PRESTypePluginDataInitializeFunction)
        tcs_kernel_Target_initialize;        
    plugin->data.finalizeExFnc =
        (PRESTypePluginDataFinalizeExFunction)
        tcs_kernel_Target_finalize_ex;
    plugin->data.finalizeFnc =
        (PRESTypePluginDataFinalizeFunction)
        tcs_kernel_Target_finalize;
        
    plugin->data.instanceToKeyFnc =
        (PRESTypePluginDataInstanceToKeyFunction)
        tcs_kernel_TargetPlugin_instance_to_key;
    plugin->data.keyToInstanceFnc =
        (PRESTypePluginDataKeyToInstanceFunction)
        tcs_kernel_TargetPlugin_key_to_instance;
    plugin->data.instanceToGuidFnc =
        (PRESTypePluginDataInstanceToGuidFunction)
        tcs_kernel_TargetPlugin_instance_to_id;


    plugin->data.createKeyFnc =
        (PRESTypePluginDataCreateKeyFunction)
        tcs_kernel_TargetPlugin_create_key;
    plugin->data.destroyKeyFnc =
        (PRESTypePluginDataDestroyKeyFunction)
        tcs_kernel_TargetPlugin_delete_key;

    
    plugin->data.serializeKeyFnc =
        (RTICdrStreamSerializeFunction)
        tcs_kernel_TargetPlugin_serialize_key;
    plugin->data.deserializeKeyFnc =
        (RTICdrStreamDeserializeFunction)
        tcs_kernel_TargetPlugin_deserialize_key;
    plugin->data.getMaxSizeSerializedKeyFnc =
        (RTICdrTypeGetMaxSizeSerializedFunction)
        tcs_kernel_TargetPlugin_get_max_size_serialized_key;
        
       

    plugin->dataPoolFactory = PRES_TYPEPLUGIN_DEFAULT_DATA_POOL_FACTORY;

    
    plugin->typeCode = (struct RTICdrTypeCode *)tcs_kernel_Target_get_typecode();
    

    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE;
    
    return plugin;
}


void tcs_kernel_TargetPlugin_delete(struct PRESTypePlugin *self)
{
    RTIOsapiHeap_freeStructure(self);
}

