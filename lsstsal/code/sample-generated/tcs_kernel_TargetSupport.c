
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef tcs_kernel_TargetSupport_h
#include "tcs_kernel_TargetSupport.h"
#endif

#ifndef tcs_kernel_TargetPlugin_h
#include "tcs_kernel_TargetPlugin.h"
#endif



#ifdef __cplusplus  
    #ifndef dds_c_log_impl_h              
         #include "dds_c/dds_c_log_impl.h"                                
    #endif        
#endif        




/* ========================================================================= */
/**
   <<IMPLEMENTATION>>

   Defines:   TData,
              TDataWriter,
	      TDataReader,
              TTypeSupport

   Configure and implement 'tcs_kernel_Target' support classes.

   Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   tcs_kernel_TargetTYPENAME

/* Defines */
#define TDataWriter tcs_kernel_TargetDataWriter
#define TData       tcs_kernel_Target


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "dds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   tcs_kernel_TargetTYPENAME

/* Defines */
#define TDataReader tcs_kernel_TargetDataReader
#define TDataSeq    tcs_kernel_TargetSeq
#define TData       tcs_kernel_Target


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "dds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

  <<IMPLEMENTATION >>

   Requires:  TTYPENAME,
              TPlugin_new
              TPlugin_delete
   Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    tcs_kernel_TargetTYPENAME
#define TPlugin_new  tcs_kernel_TargetPlugin_new
#define TPlugin_delete  tcs_kernel_TargetPlugin_delete

/* Defines */
#define TTypeSupport tcs_kernel_TargetTypeSupport
#define TData        tcs_kernel_Target
#define TDataReader  tcs_kernel_TargetDataReader
#define TDataWriter  tcs_kernel_TargetDataWriter
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"
#else
#include "dds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete


