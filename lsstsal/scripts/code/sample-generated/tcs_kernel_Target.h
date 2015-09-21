
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef tcs_kernel_Target_h
#define tcs_kernel_Target_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *tcs_kernel_TargetTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct tcs_kernel_Target
{
    integer  private_revCode;
    integer  private_sndStamp;
    integer  private_rcvStamp;
    integer  private_seqNum;
    integer  private_origin;
    char*  site; /* maximum length = (32) */
    DDS_Float  t0;
    DDS_Float  az;
    DDS_Float  el;
    DDS_Float  azdot;
    DDS_Float  eldot;
    DDS_Float  Wavel;
    DDS_Float  XOffset;
    DDS_Float  YOffset;
    char*  OffSys; /* maximum length = (32) */
    DDS_Float  focalplaneX;
    DDS_Float  focalplaneY;
    DDS_Float  Temp;
    DDS_Float  Press;
    DDS_Float  Humid;
    DDS_Float  TLR;
    DDS_Float  Tai;

} tcs_kernel_Target;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* tcs_kernel_Target_get_typecode(); /* Type code */
    

DDS_SEQUENCE(tcs_kernel_TargetSeq, tcs_kernel_Target);
        
NDDSUSERDllExport
RTIBool tcs_kernel_Target_initialize(
        tcs_kernel_Target* self);
        
NDDSUSERDllExport
RTIBool tcs_kernel_Target_initialize_ex(
        tcs_kernel_Target* self,RTIBool allocatePointers);

NDDSUSERDllExport
void tcs_kernel_Target_finalize(
        tcs_kernel_Target* self);
                        
NDDSUSERDllExport
void tcs_kernel_Target_finalize_ex(
        tcs_kernel_Target* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool tcs_kernel_Target_copy(
        tcs_kernel_Target* dst,
        const tcs_kernel_Target* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* tcs_kernel_Target_h */
