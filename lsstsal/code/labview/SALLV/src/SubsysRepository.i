// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for Matlab
//
// = FILENAME
//   DevRepository.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// SubsysDesc::name
//=============================================================================
MEX_INLINE const std::string& SubsysDesc::name (void) const
{
  return this->dev_name_;
}

//=============================================================================
// SubsysDesc::proxy
//=============================================================================
MEX_INLINE SALLV::SubsysProxy* SubsysDesc::proxy (void) const
{
  return this->dev_proxy_;
}

//=============================================================================
// SubsysDesc::cmd_list
//=============================================================================
MEX_INLINE const SubsysDesc::MinCmdInfoList& SubsysDesc::cmd_list (void) const
{
  return this->dev_cmd_list_;
}

//=============================================================================
// SubsysDesc::attr_list
//=============================================================================
MEX_INLINE const SubsysDesc::MinAttrInfoList& SubsysDesc::attr_list (void) const
{
  return this->dev_attr_list_;
}

//=============================================================================
// SubsysDesc::cmd_exists 
//=============================================================================
MEX_INLINE int SubsysDesc::cmd_exists (const char* _cmd_name)
{
  return this->cmd_exists(std::string(_cmd_name));
}

//=============================================================================
// SubsysDesc::attr_exists 
//=============================================================================
MEX_INLINE int SubsysDesc::attr_exists (const char* _attr_name)
{
  return this->attr_exists(std::string(_attr_name));
}

//=============================================================================
// DevRepository::instance
//=============================================================================
MEX_INLINE DevRepository* DevRepository::instance (void)
{
  return DevRepository::instance_;
}

//=============================================================================
// DevRepository::Subsys_desc
//=============================================================================
MEX_INLINE SubsysDesc* DevRepository::Subsys_desc (const char* Subsys_name)
{
  return this->Subsys_desc(std::string(Subsys_name));
}

