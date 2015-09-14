
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/


#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



#ifndef tcs_kernel_Target_h
#include "tcs_kernel_Target.h"
#endif

/* ========================================================================= */
const char *tcs_kernel_TargetTYPENAME = "tcs_kernel_Target";

DDS_TypeCode* tcs_kernel_Target_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode tcs_kernel_Target_g_tc_site_string = DDS_INITIALIZE_STRING_TYPECODE(32);
    static DDS_TypeCode tcs_kernel_Target_g_tc_OffSys_string = DDS_INITIALIZE_STRING_TYPECODE(32);

    static DDS_TypeCode_Member tcs_kernel_Target_g_tc_members[22]=
    {
        {
            (char *)"private_revCode",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"private_sndStamp",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"private_rcvStamp",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"private_seqNum",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"private_origin",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"site",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"t0",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"az",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"el",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"azdot",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"eldot",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"Wavel",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"XOffset",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"YOffset",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"OffSys",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"focalplaneX",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"focalplaneY",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"Temp",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"Press",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"Humid",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"TLR",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        },
        {
            (char *)"Tai",/* Member name */
            DDS_BOOLEAN_FALSE,/* Is a pointer? */
            -1, /* Bitfield bits */
            NULL,/* Member type code is assigned later */
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER /* Ignored */
        }
    };

    static DDS_TypeCode tcs_kernel_Target_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"tcs_kernel_Target", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        22, /* Number of members */
        tcs_kernel_Target_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for tcs_kernel_Target*/

    if (is_initialized) {
        return &tcs_kernel_Target_g_tc;
    }


    tcs_kernel_Target_g_tc_members[0]._typeCode = (RTICdrTypeCode *)integer_get_typecode();
    tcs_kernel_Target_g_tc_members[1]._typeCode = (RTICdrTypeCode *)integer_get_typecode();
    tcs_kernel_Target_g_tc_members[2]._typeCode = (RTICdrTypeCode *)integer_get_typecode();
    tcs_kernel_Target_g_tc_members[3]._typeCode = (RTICdrTypeCode *)integer_get_typecode();
    tcs_kernel_Target_g_tc_members[4]._typeCode = (RTICdrTypeCode *)integer_get_typecode();
    tcs_kernel_Target_g_tc_members[5]._typeCode = (RTICdrTypeCode *)&tcs_kernel_Target_g_tc_site_string;
    tcs_kernel_Target_g_tc_members[6]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[7]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[8]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[9]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[10]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[11]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[12]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[13]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[14]._typeCode = (RTICdrTypeCode *)&tcs_kernel_Target_g_tc_OffSys_string;
    tcs_kernel_Target_g_tc_members[15]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[16]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[17]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[18]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[19]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[20]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    tcs_kernel_Target_g_tc_members[21]._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

    is_initialized = RTI_TRUE;

    return &tcs_kernel_Target_g_tc;
}


RTIBool tcs_kernel_Target_initialize(
    tcs_kernel_Target* sample) {
    return tcs_kernel_Target_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool tcs_kernel_Target_initialize_ex(
    tcs_kernel_Target* sample,RTIBool allocatePointers)
{

    if (!integer_initialize_ex(&sample->private_revCode,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!integer_initialize_ex(&sample->private_sndStamp,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!integer_initialize_ex(&sample->private_rcvStamp,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!integer_initialize_ex(&sample->private_seqNum,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!integer_initialize_ex(&sample->private_origin,allocatePointers)) {
        return RTI_FALSE;
    }
            
    sample->site = DDS_String_alloc((32));
    if (sample->site == NULL) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_initFloat(&sample->t0)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->az)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->el)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->azdot)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->eldot)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->Wavel)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->XOffset)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->YOffset)) {
        return RTI_FALSE;
    }                
            
    sample->OffSys = DDS_String_alloc((32));
    if (sample->OffSys == NULL) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_initFloat(&sample->focalplaneX)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->focalplaneY)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->Temp)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->Press)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->Humid)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->TLR)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initFloat(&sample->Tai)) {
        return RTI_FALSE;
    }                
            

    return RTI_TRUE;
}

void tcs_kernel_Target_finalize(
    tcs_kernel_Target* sample)
{
    tcs_kernel_Target_finalize_ex(sample,RTI_TRUE);
}
        
void tcs_kernel_Target_finalize_ex(
    tcs_kernel_Target* sample,RTIBool deletePointers)
{

    integer_finalize_ex(&sample->private_revCode,deletePointers);
            
    integer_finalize_ex(&sample->private_sndStamp,deletePointers);
            
    integer_finalize_ex(&sample->private_rcvStamp,deletePointers);
            
    integer_finalize_ex(&sample->private_seqNum,deletePointers);
            
    integer_finalize_ex(&sample->private_origin,deletePointers);
            
    DDS_String_free(sample->site);                
            
    DDS_String_free(sample->OffSys);                
            
}

RTIBool tcs_kernel_Target_copy(
    tcs_kernel_Target* dst,
    const tcs_kernel_Target* src)
{

    if (!integer_copy(
        &dst->private_revCode, &src->private_revCode)) {
        return RTI_FALSE;
    }
            
    if (!integer_copy(
        &dst->private_sndStamp, &src->private_sndStamp)) {
        return RTI_FALSE;
    }
            
    if (!integer_copy(
        &dst->private_rcvStamp, &src->private_rcvStamp)) {
        return RTI_FALSE;
    }
            
    if (!integer_copy(
        &dst->private_seqNum, &src->private_seqNum)) {
        return RTI_FALSE;
    }
            
    if (!integer_copy(
        &dst->private_origin, &src->private_origin)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyString(
        dst->site, src->site, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->t0, &src->t0)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->az, &src->az)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->el, &src->el)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->azdot, &src->azdot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->eldot, &src->eldot)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->Wavel, &src->Wavel)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->XOffset, &src->XOffset)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->YOffset, &src->YOffset)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyString(
        dst->OffSys, src->OffSys, (32) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->focalplaneX, &src->focalplaneX)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->focalplaneY, &src->focalplaneY)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->Temp, &src->Temp)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->Press, &src->Press)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->Humid, &src->Humid)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->TLR, &src->TLR)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->Tai, &src->Tai)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'tcs_kernel_Target' sequence class.
 */
#define T tcs_kernel_Target
#define TSeq tcs_kernel_TargetSeq
#define T_initialize_ex tcs_kernel_Target_initialize_ex
#define T_finalize_ex   tcs_kernel_Target_finalize_ex
#define T_copy       tcs_kernel_Target_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T

