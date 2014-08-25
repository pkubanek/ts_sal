// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SubsysDescriptorriptor.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// SubsysDescriptor::proxy
//=============================================================================
LV_INLINE ThreadSafeSubsysProxy * 
SubsysDescriptor::proxy (void) const
{
  return this->dev_proxy_;
}

//=============================================================================
// SubsysDescriptor::operator->
//=============================================================================
LV_INLINE ThreadSafeSubsysProxy * 
SubsysDescriptor::operator-> (void) const
{
  return this->dev_proxy_;
}

//=============================================================================
// SubsysDescriptor::name
//=============================================================================
LV_INLINE const std::string& 
SubsysDescriptor::name (void) const
{
  return this->dev_proxy_->dev_name();
}

//=============================================================================
// SubsysDescriptor::cmd_list
//=============================================================================
LV_INLINE const SubsysDescriptor::MinCmdInfoList& 
SubsysDescriptor::cmd_list (void) const
{
  return this->dev_cmd_list_;
}

//=============================================================================
// SubsysDescriptor::cmd_list
//=============================================================================
LV_INLINE const SubsysDescriptor::MinAttrInfoList& 
SubsysDescriptor::attr_list (void) const
{
  return this->dev_attr_list_;
}

//=============================================================================
// SubsysDescriptor::cmd_exists 
//=============================================================================
LV_INLINE int 
SubsysDescriptor::cmd_exists (const char* _cmd_name)
    throw (SALLV::DevFailed)
{
  return this->cmd_exists(std::string(_cmd_name));
}

//=============================================================================
// SubsysDescriptor::attr_exists 
//=============================================================================
LV_INLINE int 
SubsysDescriptor::attr_exists (const char* _attr_name)
    throw (SALLV::DevFailed)
{
  return this->attr_exists(std::string(_attr_name));
}

