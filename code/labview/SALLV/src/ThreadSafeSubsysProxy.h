// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeSubsysProxy.h
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

#ifndef _TS_DEV_PROXY_H_
#define _TS_DEV_PROXY_H_

#include <string>
#include <vector>

//=============================================================================
// Class ThreadSafeSubsysProxy (SINGLETON)
//=============================================================================
class ThreadSafeSubsysProxy
{
public:
  ThreadSafeSubsysProxy (const std::string& dev_name) 
    throw (SALLV::DevFailed);

	ThreadSafeSubsysProxy (const char * dev_name) 
    throw (SALLV::DevFailed);

  ThreadSafeSubsysProxy (SALLV::SubsysProxy * dp, bool ownership = false) 
    throw (SALLV::DevFailed);

  virtual ~ThreadSafeSubsysProxy ();

  const std::string status (void) 
    throw (SALLV::DevFailed);

	SALLV::DevState state (void) 
    throw (SALLV::DevFailed);

  int ping (void) 
    throw (SALLV::DevFailed);

  SALLV::CommandInfoList* command_list_query (void) 
    throw (SALLV::DevFailed);

  std::vector<std::string>* get_attribute_list (void) 
    throw (SALLV::DevFailed);

  SALLV::AttributeInfoList* attribute_list_query (void) 
    throw (SALLV::DevFailed);

  SALLV::SubsysAttribute read_attribute (const std::string& attr_name) 
    throw (SALLV::DevFailed);

	SALLV::SubsysAttribute read_attribute (const char * attr_name) 
    throw (SALLV::DevFailed);

  std::vector<SALLV::SubsysAttribute>* read_attributes (const std::vector<std::string>& attr_names) 
    throw (SALLV::DevFailed);

	void write_attribute (const SALLV::SubsysAttribute& attr_value) 
    throw (SALLV::DevFailed);

	void write_attributes (const std::vector<SALLV::SubsysAttribute>& attr_values) 
    throw (SALLV::DevFailed);

  SALLV::SubsysData command_inout (const std::string& cmd_name) 
    throw (SALLV::DevFailed);

	SALLV::SubsysData command_inout (const char * cmd_name) 
    throw (SALLV::DevFailed);

  SALLV::SubsysData command_inout (const std::string& cmd_name, const SALLV::SubsysData &d) 
    throw (SALLV::DevFailed);

	SALLV::SubsysData command_inout (const char *cmd_name, const SALLV::SubsysData &d) 
    throw (SALLV::DevFailed);

  int subscribe_event(const std::string &attr_name, 
                      SALLV::EventType event, 
                      SALLV::CallBack *cb, 
                      const std::vector<std::string> &filters) 
    throw (SALLV::DevFailed);

	void unsubscribe_event(int event_id) 
    throw (SALLV::DevFailed);

  SALLV::SubsysProxy& unsafe_proxy (void);

  const std::string& dev_name (void) const;

  void set_timeout (size_t tmo_msecs);

private:
  SALLV::SubsysProxy * dp_;

  bool ownership_;

  std::string name_;

  omni_mutex lock_;

  // = Disallow these operations (except for friends).
  //---------------------------------------------------------
  ThreadSafeSubsysProxy (const ThreadSafeSubsysProxy&);
  void operator= (const ThreadSafeSubsysProxy&); 
};

//=============================================================================
// INLINED CODE
//=============================================================================
#if defined (_LV_INLINE_)
  #include "ThreadSafeSubsysProxy.i"
#endif 

#endif // _TS_DEV_PROXY_H_
