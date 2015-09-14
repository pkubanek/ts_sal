// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeDeviceProxy.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// ThreadSafeDeviceProxy::state
//=============================================================================
LV_INLINE const std::string
ThreadSafeDeviceProxy::status (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->status();
}

//=============================================================================
// ThreadSafeDeviceProxy::state
//=============================================================================
LV_INLINE SALLV::DevState
ThreadSafeDeviceProxy::state (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->state();
}

//=============================================================================
// ThreadSafeDeviceProxy::ping
//=============================================================================
LV_INLINE int 
ThreadSafeDeviceProxy::ping (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->ping();
}

//=============================================================================
// ThreadSafeDeviceProxy::command_list_query
//=============================================================================
LV_INLINE SALLV::CommandInfoList* 
ThreadSafeDeviceProxy::command_list_query (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_list_query();
}

//=============================================================================
// ThreadSafeDeviceProxy::attribute_list
//=============================================================================
LV_INLINE std::vector<std::string>* 
ThreadSafeDeviceProxy::get_attribute_list (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->get_attribute_list();
}

//=============================================================================
// ThreadSafeDeviceProxy::attribute_list_query
//=============================================================================
LV_INLINE SALLV::AttributeInfoList* 
ThreadSafeDeviceProxy::attribute_list_query (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->attribute_list_query();
}

//=============================================================================
// ThreadSafeDeviceProxy::read_attribute
//=============================================================================
LV_INLINE SALLV::DeviceAttribute
ThreadSafeDeviceProxy::read_attribute (const std::string& attr_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attribute(const_cast<std::string&>(attr_name));
}

//=============================================================================
// ThreadSafeDeviceProxy::read_attribute
//=============================================================================
LV_INLINE SALLV::DeviceAttribute
ThreadSafeDeviceProxy::read_attribute (const char *attr_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attribute(attr_name);
}

  SALLV::DeviceAttribute read_attributes(const std::vector<std::string>& attr_names) 
    throw (SALLV::DevFailed);

//=============================================================================
// ThreadSafeDeviceProxy:read_attributes
//=============================================================================
LV_INLINE std::vector<SALLV::DeviceAttribute>*
ThreadSafeDeviceProxy::read_attributes (const std::vector<std::string>& attr_names) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attributes(const_cast<std::vector<std::string>&>(attr_names));
}

//=============================================================================
// ThreadSafeDeviceProxy::write_attribute
//=============================================================================
LV_INLINE void
ThreadSafeDeviceProxy::write_attribute (const SALLV::DeviceAttribute& attr_value) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->write_attribute(const_cast<SALLV::DeviceAttribute&>(attr_value));
}

//=============================================================================
// ThreadSafeDeviceProxy::write_attributes
//=============================================================================
LV_INLINE void
ThreadSafeDeviceProxy::write_attributes (const std::vector<SALLV::DeviceAttribute>& attr_values) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->write_attributes(const_cast<std::vector<SALLV::DeviceAttribute>&>(attr_values));
}

//=============================================================================
// ThreadSafeDeviceProxy::command_inout
//=============================================================================
LV_INLINE SALLV::DeviceData
ThreadSafeDeviceProxy::command_inout (const std::string& cmd_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(const_cast<std::string&>(cmd_name));
}

//=============================================================================
// ThreadSafeDeviceProxy::attribute_history
//=============================================================================
LV_INLINE std::vector<SALLV::DeviceAttributeHistory> * 
ThreadSafeDeviceProxy::attribute_history (const std::string & attr_name, int history_len) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->attribute_history(const_cast<std::string&>(attr_name), history_len);
}
 
//=============================================================================
// ThreadSafeDeviceProxy::attribute_history
//=============================================================================
LV_INLINE std::vector<SALLV::DeviceAttributeHistory> * 
ThreadSafeDeviceProxy::attribute_history (const char * attr_name, int history_len) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->attribute_history(attr_name, history_len);
}
    
//=============================================================================
// ThreadSafeDeviceProxy::command_inout
//=============================================================================
LV_INLINE SALLV::DeviceData
ThreadSafeDeviceProxy::command_inout (const char * cmd_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(cmd_name);
}

//=============================================================================
// ThreadSafeDeviceProxy::command_inout
//=============================================================================
LV_INLINE SALLV::DeviceData
ThreadSafeDeviceProxy::command_inout (const std::string& cmd_name, 
                                      const SALLV::DeviceData &d) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(const_cast<std::string&>(cmd_name),
                                  const_cast<SALLV::DeviceData &>(d));
}

//=============================================================================
// ThreadSafeDeviceProxy::command_inout
//=============================================================================
LV_INLINE SALLV::DeviceData
ThreadSafeDeviceProxy::command_inout (const char * cmd_name, 
                                      const SALLV::DeviceData &d) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(cmd_name,
                                  const_cast<SALLV::DeviceData &>(d));
}

//=============================================================================
// ThreadSafeDeviceProxy::command_inout
//=============================================================================
LV_INLINE int
ThreadSafeDeviceProxy::subscribe_event(const std::string &attr_name, 
                                       SALLV::EventType event, 
                                       SALLV::CallBack *cb, 
                                       const std::vector<std::string> &filters) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->subscribe_event(attr_name, event, cb, filters);
}


//=============================================================================
// ThreadSafeDeviceProxy::unsubscribe_event
//=============================================================================
LV_INLINE void
ThreadSafeDeviceProxy::unsubscribe_event (int event_id)
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->unsubscribe_event(event_id);
}

//=============================================================================
// ThreadSafeDeviceProxy::unsafe_proxy
//=============================================================================
LV_INLINE SALLV::DeviceProxy&
ThreadSafeDeviceProxy::unsafe_proxy (void)
{
  return *this->dp_;
}

//=============================================================================
// ThreadSafeDeviceProxy::proxy
//=============================================================================
LV_INLINE const std::string&
ThreadSafeDeviceProxy::dev_name (void) const
{
  return this->name_;
}

//=============================================================================
// ThreadSafeDeviceProxy::set_timeout
//=============================================================================
LV_INLINE void
ThreadSafeDeviceProxy::set_timeout (size_t tmo_msecs)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->set_timeout_millis(static_cast<int>(tmo_msecs));
}
