// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   DataAdapter.h
//
// = AUTHOR
//   Nicolas Leclercq
//
// ============================================================================

#ifndef _DATA_ADAPTER_H_
#define _DATA_ADAPTER_H_

//=============================================================================
// FORWARD DECL
//=============================================================================
class SubsysDescriptor;

//=============================================================================
// #DEFINEs
//=============================================================================
#define DATA_ADAPTER (DataAdapter::instance())

//=============================================================================
// CLASS : DataAdapter 
//=============================================================================
class DataAdapter 
{
  friend class ObjectManager;

public:

  static DataAdapter* instance (void);
  //- Returns the unique instance of <DataAdapter>.
  
  int encode_argin (SubsysDescriptor* ddesc, 
                    int cmd_id,
                    LvArgIOPtr argin,
                    SALLV::SubsysData& dd_in) 
    throw (SALLV::DevFailed);
  //- Converts <argin> from Labview type to SALLV type

  int decode_argout (SubsysDescriptor* ddesc, 
                     int cmd_id,
                     SALLV::SubsysData& dd_out,
                     LvArgIOPtr argout) 
    throw (SALLV::DevFailed);
  //- Converts <dd_out> from SALLV type to Labview type
  
  int encode_attr (SubsysDescriptor* ddesc, 
                   int attr_id,
                   LvAttributeValuePtr attr_value,
                   SALLV::SubsysAttribute& attr_in) 
    throw (SALLV::DevFailed);
  //- Converts <argin> from Labview type to SALLV type

  int decode_attr (SubsysDescriptor* ddesc, 
                   int attr_id,
                   SALLV::SubsysAttribute& attr_out, 
                   void*& argout) 
    throw (SALLV::DevFailed);
  //- Low level converter for <attr_value>

  void SALLV_to_lv_attribute_value (SubsysDescriptor* _ddesc, 
                                    const std::string& attr_name,
                                    SALLV::SubsysAttribute& _tav, 
                                    LvAttributeValuePtr lvav_)
    throw (SALLV::DevFailed);
  //- High level converter for <attr_value>

private:

  static int init (void);
  //- Instanciates the singleton.
  
  static void cleanup (void);
  //- Releases the singleton.

  static DataAdapter* instance_;
  //- The unique instance of <DataAdapter>.

  // = Disallow these operations (except for ObjectManager).
  //-------------------------------------------------------
  DataAdapter();
  DataAdapter (const DataAdapter&);
  virtual ~DataAdapter();
  void operator= (const DataAdapter&); 
};

//=============================================================================
// INLINED CODE
//=============================================================================
#if defined (_LV_INLINE_)
  #include "DataAdapter.i"
#endif 

#endif // _DATA_ADAPTER_H_

   
   
