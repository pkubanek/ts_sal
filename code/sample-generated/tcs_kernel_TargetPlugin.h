
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef tcs_kernel_TargetPlugin_h
#define tcs_kernel_TargetPlugin_h

#ifndef tcs_kernel_Target_h
#include "tcs_kernel_Target.h"
#endif




struct RTICdrStream;
struct MIGRtpsGuid;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


/* The type used to store keys for instances of type struct
 * tcs_kernel_Target.
 *
 * By default, this type is struct tcs_kernel_Target
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct tcs_kernel_Target)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct tcs_kernel_Target, the
 * following restriction applies: the key of struct
 * tcs_kernel_Target must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct tcs_kernel_Target.
 */
typedef tcs_kernel_Target tcs_kernel_TargetKeyHolder;


extern RTIBool tcs_kernel_TargetPlugin_serialize(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option);

extern RTIBool tcs_kernel_TargetPlugin_serialize_data(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option);



extern RTIBool tcs_kernel_TargetPlugin_deserialize(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option);

extern RTIBool tcs_kernel_TargetPlugin_deserialize_data(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option);



extern unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized(
    unsigned int current_alignment);

extern unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized_data(
    unsigned int current_alignment);

extern void tcs_kernel_TargetPlugin_print(
    const tcs_kernel_Target *sample,
    const char *description, int indent_level);

extern tcs_kernel_Target *tcs_kernel_TargetPlugin_create_sample();

extern tcs_kernel_Target *tcs_kernel_TargetPlugin_create_sample_ex(RTIBool allocatePointers);        

extern void tcs_kernel_TargetPlugin_delete_sample(
    tcs_kernel_Target *sample);        

extern void tcs_kernel_TargetPlugin_delete_sample_ex(
    tcs_kernel_Target *sample,RTIBool deletePointers);

extern PRESTypePluginKeyKind tcs_kernel_TargetPlugin_get_key_kind();

extern struct PRESTypePlugin *tcs_kernel_TargetPlugin_new();

extern void tcs_kernel_TargetPlugin_delete(struct PRESTypePlugin *plugin);

/* The following are used if your key kind is USER_KEY */

extern tcs_kernel_TargetKeyHolder *tcs_kernel_TargetPlugin_create_key();

extern void tcs_kernel_TargetPlugin_delete_key(
    tcs_kernel_TargetKeyHolder *key);

extern RTIBool tcs_kernel_TargetPlugin_instance_to_key(
    tcs_kernel_TargetKeyHolder *key, const tcs_kernel_Target *instance);

extern RTIBool tcs_kernel_TargetPlugin_key_to_instance(
    tcs_kernel_Target *instance, const tcs_kernel_TargetKeyHolder *key);

extern RTIBool tcs_kernel_TargetPlugin_instance_to_id(
    DDS_InstanceId_t *id, RTIBool *is_unique,
    const tcs_kernel_Target *instance);




extern RTIBool tcs_kernel_TargetPlugin_serialize_key(
    struct RTICdrStream *stream, const tcs_kernel_Target *sample,
    void *serialize_option);

extern RTIBool tcs_kernel_TargetPlugin_deserialize_key(
    struct RTICdrStream *stream, tcs_kernel_Target *sample,
    void *deserialize_option);

extern unsigned int tcs_kernel_TargetPlugin_get_max_size_serialized_key(
    unsigned int current_alignment);

#ifdef __cplusplus
}
#endif
        

#endif /* tcs_kernel_TargetPlugin_h */
