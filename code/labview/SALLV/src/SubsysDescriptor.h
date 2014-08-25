// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SubsysDescriptorriptor.h
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

#ifndef _DEVICE_DESC_H_
#define _DEVICE_DESC_H_

//=============================================================================
// DEPENDENCIEs
//=============================================================================
#include "StandardHeader.h"
#include "ThreadSafeSubsysProxy.h"
#include <string>

//=============================================================================
// DEFINEs
//=============================================================================
#define NO_SUCH_ATTR (int)-1
#define NO_SUCH_CMD  (int)-1

//=============================================================================
// CLASS : SubsysDescriptor
//=============================================================================
class SubsysDescriptor 
{
  friend class SubsysRepository;

public:

  typedef struct 
  {
	  std::string name;
	  long in_type;
	  long out_type;
  } MinCmdInfo;
  // Used to store locally the mininum required cmd info.

  typedef std::vector<MinCmdInfo> MinCmdInfoList;
  // Define what is a list of <MinCmdInfo>;

  typedef struct 
  {
	  std::string name;
	  SALLV::AttrWriteType writable;
	  SALLV::AttrDataFormat data_format;
	  int data_type;
  } MinAttrInfo;
  // Used to store locally the mininum required attr info.

  typedef std::vector<MinAttrInfo> MinAttrInfoList;
  // Define what is a list of <MinAttrInfo>;

  const std::string& name (void) const;
  // Returns the subsys name.

  const MinCmdInfoList& cmd_list (void) const;
  // Returns the subsys commands list.

  const MinAttrInfoList& attr_list (void) const;
  // Returns the subsys attributes list.

  int cmd_exists (const std::string& cmd_name)
    throw (SALLV::DevFailed);
  // If <cmd_name> is supported by the subsys, returns its 
  // indice in <cmd_list>,NO_SUCH_CMD otherwise.

  int cmd_exists (const char* cmd_name)
    throw (SALLV::DevFailed);
  // If <cmd_name> is supported by the subsys, returns its 
  // indice in <cmd_list>, NO_SUCH_CMD otherwise.

  int attr_exists (const std::string& attr_name)
    throw (SALLV::DevFailed);
  // If <attr_name> is an attribute of the subsys, returns its 
  // indice in <attr_list>, NO_SUCH_ATTR otherwise.

  int attr_exists (const char* attr_name)
    throw (SALLV::DevFailed);
  // If <attr_name> is an attribute of the subsys, returns its 
  // indice in <attr_list>, NO_SUCH_ATTR otherwise.

  bool is_attr_writable (const std::string& _attr_name);
  // Returns <true> if the attribute named <_attr_name> is 
  // writable, <false> otherwise.

  bool is_attr_writable (int attr_id);
  // Returns <true> if the attribute named <_attr_name> is 
  // writable, <false> otherwise.

  bool is_attr_readable (const std::string& _attr_name);
  // Returns <true> if the attribute named <_attr_name> is 
  // readable, <false> otherwise.

  bool is_attr_readable (int attr_id);
  // Returns <true> if the attribute named <_attr_name> is 
  // readable, <false> otherwise.

  ThreadSafeSubsysProxy * operator-> (void) const;
  // Returns the underlying subsys proxy

  ThreadSafeSubsysProxy * proxy (void) const;
  // Returns the underlying subsys proxy

private:
  SubsysDescriptor (const std::string& _dev_name);
  // Ctor

  SubsysDescriptor (SALLV::SubsysProxy * dp, bool ownership);
  // Ctor

  void get_subsys_interface (void)
    throw (SALLV::DevFailed);
  // Request then store localy the subsys interface 

  void cmd_list (SALLV::CommandInfoList* cmd_list);
  // Set the subsys commands list

  void attr_list (SALLV::AttributeInfoList* attr_list);
  // Set the subsys attributes list

  virtual void disconnect (void);
  // Release the underlying proxy keeping only the attrs and cmds info 

  MinCmdInfoList dev_cmd_list_;
  // The subsys command list

  MinAttrInfoList dev_attr_list_;
  // The subsys attribute list

  ThreadSafeSubsysProxy * dev_proxy_;
  //- The underlying subsys proxy

  // = Disallow these operations (except for SubsysRepository).
  //-----------------------------------------------------------
  SubsysDescriptor (const SubsysDescriptor&);
  virtual ~SubsysDescriptor();
  void operator= (const SubsysDescriptor&); 
};

//=============================================================================
// INLINED CODE
//=============================================================================
#if defined (_LV_INLINE_)
  #include "SubsysDescriptor.i"
#endif 

#endif // _DEVICE_DESC_H_

   
   
