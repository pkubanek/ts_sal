// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeDeviceProxy.h
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
// Class ThreadSafeDeviceProxy (SINGLETON)
//=============================================================================
class ThreadSafeDeviceProxy
{
public:
  ThreadSafeDeviceProxy (const std::string& dev_name) 
    throw (SALLV::DevFailed);

	ThreadSafeDeviceProxy (const char * dev_name) 
    throw (SALLV::DevFailed);

  ThreadSafeDeviceProxy (SALLV::DeviceProxy * dp, bool ownership = false) 
    throw (SALLV::DevFailed);

  virtual ~ThreadSafeDeviceProxy ();

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

  SALLV::DeviceAttribute read_attribute (const std::string& attr_name) 
    throw (SALLV::DevFailed);

	SALLV::DeviceAttribute read_attribute (const char * attr_name) 
    throw (SALLV::DevFailed);

  std::vector<SALLV::DeviceAttribute>* read_attributes (const std::vector<std::string>& attr_names) 
    throw (SALLV::DevFailed);

	void write_attribute (const SALLV::DeviceAttribute& attr_value) 
    throw (SALLV::DevFailed);

	void write_attributes (const std::vector<SALLV::DeviceAttribute>& attr_values) 
    throw (SALLV::DevFailed);

  std::vector<SALLV::DeviceAttributeHistory> * attribute_history (const std::string & attr_name, int history_len) 
    throw (SALLV::DevFailed);
 
  std::vector<SALLV::DeviceAttributeHistory> * attribute_history (const char * attr_name, int history_len) 
    throw (SALLV::DevFailed);
    
  SALLV::DeviceData command_inout (const std::string& cmd_name) 
    throw (SALLV::DevFailed);

	SALLV::DeviceData command_inout (const char * cmd_name) 
    throw (SALLV::DevFailed);

  SALLV::DeviceData command_inout (const std::string& cmd_name, const SALLV::DeviceData &d) 
    throw (SALLV::DevFailed);

	SALLV::DeviceData command_inout (const char *cmd_name, const SALLV::DeviceData &d) 
    throw (SALLV::DevFailed);

  int subscribe_event(const std::string &attr_name, 
                      SALLV::EventType event, 
                      SALLV::CallBack *cb, 
                      const std::vector<std::string> &filters) 
    throw (SALLV::DevFailed);

	void unsubscribe_event(int event_id) 
    throw (SALLV::DevFailed);

  SALLV::DeviceProxy& unsafe_proxy (void);

  const std::string& dev_name (void) const;

  void set_timeout (size_t tmo_msecs);

private:
  SALLV::DeviceProxy * dp_;

  bool ownership_;

  std::string name_;

  omni_mutex lock_;

  // = Disallow these operations (except for friends).
  //---------------------------------------------------------
  ThreadSafeDeviceProxy (const ThreadSafeDeviceProxy&);
  void operator= (const ThreadSafeDeviceProxy&); 
};

//=============================================================================
// INLINED CODE
//=============================================================================
#if defined (_LV_INLINE_)
  #include "ThreadSafeDeviceProxy.i"
#endif 

#endif // _TS_DEV_PROXY_H_
