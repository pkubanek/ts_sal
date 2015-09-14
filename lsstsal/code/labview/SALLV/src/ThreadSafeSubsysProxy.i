// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeSubsysProxy.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// ThreadSafeSubsysProxy::state
//=============================================================================
LV_INLINE const std::string
ThreadSafeSubsysProxy::status (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->status();
}

//=============================================================================
// ThreadSafeSubsysProxy::state
//=============================================================================
LV_INLINE SALLV::DevState
ThreadSafeSubsysProxy::state (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->state();
}

//=============================================================================
// ThreadSafeSubsysProxy::ping
//=============================================================================
LV_INLINE int 
ThreadSafeSubsysProxy::ping (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->ping();
}

//=============================================================================
// ThreadSafeSubsysProxy::command_list_query
//=============================================================================
LV_INLINE SALLV::CommandInfoList* 
ThreadSafeSubsysProxy::command_list_query (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_list_query();
}

//=============================================================================
// ThreadSafeSubsysProxy::attribute_list
//=============================================================================
LV_INLINE std::vector<std::string>* 
ThreadSafeSubsysProxy::get_attribute_list (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->get_attribute_list();
}

//=============================================================================
// ThreadSafeSubsysProxy::attribute_list_query
//=============================================================================
LV_INLINE SALLV::AttributeInfoList* 
ThreadSafeSubsysProxy::attribute_list_query (void) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->attribute_list_query();
}

//=============================================================================
// ThreadSafeSubsysProxy::read_attribute
//=============================================================================
LV_INLINE SALLV::SubsysAttribute
ThreadSafeSubsysProxy::read_attribute (const std::string& attr_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attribute(const_cast<std::string&>(attr_name));
}

//=============================================================================
// ThreadSafeSubsysProxy::read_attribute
//=============================================================================
LV_INLINE SALLV::SubsysAttribute
ThreadSafeSubsysProxy::read_attribute (const char *attr_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attribute(attr_name);
}

  SALLV::SubsysAttribute read_attributes(const std::vector<std::string>& attr_names) 
    throw (SALLV::DevFailed);

//=============================================================================
// ThreadSafeSubsysProxy:read_attributes
//=============================================================================
LV_INLINE std::vector<SALLV::SubsysAttribute>*
ThreadSafeSubsysProxy::read_attributes (const std::vector<std::string>& attr_names) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->read_attributes(const_cast<std::vector<std::string>&>(attr_names));
}

//=============================================================================
// ThreadSafeSubsysProxy::write_attribute
//=============================================================================
LV_INLINE void
ThreadSafeSubsysProxy::write_attribute (const SALLV::SubsysAttribute& attr_value) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->write_attribute(const_cast<SALLV::SubsysAttribute&>(attr_value));
}

//=============================================================================
// ThreadSafeSubsysProxy::write_attributes
//=============================================================================
LV_INLINE void
ThreadSafeSubsysProxy::write_attributes (const std::vector<SALLV::SubsysAttribute>& attr_values) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->write_attributes(const_cast<std::vector<SALLV::SubsysAttribute>&>(attr_values));
}

//=============================================================================
// ThreadSafeSubsysProxy::command_inout
//=============================================================================
LV_INLINE SALLV::SubsysData
ThreadSafeSubsysProxy::command_inout (const std::string& cmd_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(const_cast<std::string&>(cmd_name));
}

    
//=============================================================================
// ThreadSafeSubsysProxy::command_inout
//=============================================================================
LV_INLINE SALLV::SubsysData
ThreadSafeSubsysProxy::command_inout (const char * cmd_name) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(cmd_name);
}

//=============================================================================
// ThreadSafeSubsysProxy::command_inout
//=============================================================================
LV_INLINE SALLV::SubsysData
ThreadSafeSubsysProxy::command_inout (const std::string& cmd_name, 
                                      const SALLV::SubsysData &d) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(const_cast<std::string&>(cmd_name),
                                  const_cast<SALLV::SubsysData &>(d));
}

//=============================================================================
// ThreadSafeSubsysProxy::command_inout
//=============================================================================
LV_INLINE SALLV::SubsysData
ThreadSafeSubsysProxy::command_inout (const char * cmd_name, 
                                      const SALLV::SubsysData &d) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->command_inout(cmd_name,
                                  const_cast<SALLV::SubsysData &>(d));
}

//=============================================================================
// ThreadSafeSubsysProxy::command_inout
//=============================================================================
LV_INLINE int
ThreadSafeSubsysProxy::subscribe_event(const std::string &attr_name, 
                                       SALLV::EventType event, 
                                       SALLV::CallBack *cb, 
                                       const std::vector<std::string> &filters) 
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  return this->dp_->subscribe_event(attr_name, event, cb, filters);
}


//=============================================================================
// ThreadSafeSubsysProxy::unsubscribe_event
//=============================================================================
LV_INLINE void
ThreadSafeSubsysProxy::unsubscribe_event (int event_id)
  throw (SALLV::DevFailed)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->unsubscribe_event(event_id);
}

//=============================================================================
// ThreadSafeSubsysProxy::unsafe_proxy
//=============================================================================
LV_INLINE SALLV::SubsysProxy&
ThreadSafeSubsysProxy::unsafe_proxy (void)
{
  return *this->dp_;
}

//=============================================================================
// ThreadSafeSubsysProxy::proxy
//=============================================================================
LV_INLINE const std::string&
ThreadSafeSubsysProxy::dev_name (void) const
{
  return this->name_;
}

//=============================================================================
// ThreadSafeSubsysProxy::set_timeout
//=============================================================================
LV_INLINE void
ThreadSafeSubsysProxy::set_timeout (size_t tmo_msecs)
{
  omni_mutex_lock guard(this->lock_);
  this->dp_->set_timeout_millis(static_cast<int>(tmo_msecs));
}
