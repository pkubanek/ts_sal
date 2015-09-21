// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SubsysDescriptorriptor.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "SubsysDescriptor.h"

#if !defined (_LV_INLINE_)
# include "SubsysDescriptor.i"
#endif 

//=============================================================================
// SubsysDescriptor::SubsysDescriptor
//=============================================================================
SubsysDescriptor::SubsysDescriptor (const std::string& _dev_name) 
  : dev_cmd_list_(0), 
    dev_attr_list_(0),
    dev_proxy_ (0)
{
  //- instanciate the Subsys proxy
  try 
  {
    this->dev_proxy_ = new ThreadSafeSubsysProxy(_dev_name);
    if (this->dev_proxy_ == 0) 
    {
      SALLV::Except::throw_exception(_CPTC("out of memory"),
			                               _CPTC("binding error: memory allocation failed"),
			                               _CPTC("SubsysDescriptor::SubsysDescriptor"));
    }
	}
	catch (SALLV::DevFailed &e) 
  {
    std::string d = "binding error: failed to create proxy for Subsys " + _dev_name;
    SALLV::Except::re_throw_exception(e,
                                      _CPTC("SALLV::SubsysProxy instanciation failed"),
			                                _CPTC(d.c_str()),
			                                _CPTC("SubsysDescriptor::SubsysDescriptor"));
	}
  catch (...) 
  {
    SALLV::Except::throw_exception(_CPTC("unknown error"),
			                             _CPTC("binding error: unknown exception caught"),
			                             _CPTC("SubsysDescriptor::SubsysDescriptor"));
  }

  //- enable transparent reconnection
  this->dev_proxy_->unsafe_proxy().set_transparency_reconnection(true);

  //- get Subsys attributes and commands info
  this->get_Subsys_interface();
}

//=============================================================================
// SubsysDescriptor::SubsysDescriptor 
//=============================================================================
SubsysDescriptor::SubsysDescriptor (SALLV::SubsysProxy * _dp, bool _ownership)
  : dev_cmd_list_(0), 
    dev_attr_list_(0),
    dev_proxy_ (0)
{
  //- instanciate the Subsys proxy
  try 
  {
    this->dev_proxy_ = new ThreadSafeSubsysProxy(_dp, _ownership);
    if (this->dev_proxy_ == 0) 
    {
      SALLV::Except::throw_exception(_CPTC("out of memory"),
			                               _CPTC("binding error: memory allocation failed"),
			                               _CPTC("SubsysDescriptor::SubsysDescriptor"));
    }
	}
	catch (SALLV::DevFailed &e) 
  {
    std::string d = "binding error: failed to create proxy for Subsys " + _dp->dev_name();
    SALLV::Except::re_throw_exception(e,
                                      _CPTC("SALLV::SubsysProxy instanciation failed"),
			                                _CPTC(d.c_str()),
			                                _CPTC("SubsysDescriptor::SubsysDescriptor"));
	}
  catch (...) 
  {
    SALLV::Except::throw_exception(_CPTC("unknown error"),
			                             _CPTC("binding error: unknown exception caught"),
			                             _CPTC("SubsysDescriptor::SubsysDescriptor"));
  }

  //- enable transparent reconnection
  //- _dp->set_transparency_reconnection(true);

  //- get Subsys attributes and commands info
  this->get_Subsys_interface();
}

//=============================================================================
// SubsysDescriptor::~SubsysDescriptor 
//=============================================================================
SubsysDescriptor::~SubsysDescriptor (void)
{
  this->dev_cmd_list_.clear();
  this->dev_attr_list_.clear();
  this->disconnect();
}

//=============================================================================
// SubsysDescriptor::disconnect
//=============================================================================
void SubsysDescriptor::disconnect (void)
{
  if (this->dev_proxy_) 
  {
    delete this->dev_proxy_;
    this->dev_proxy_ = 0;
  }
}

//=============================================================================
// SubsysDescriptor::get_Subsys_interface
//=============================================================================
void SubsysDescriptor::get_Subsys_interface (void)
  throw (SALLV::DevFailed) 
{
  if (! this->dev_proxy_)
  {
    SALLV::Except::throw_exception(_CPTC("binding error"),
                                   _CPTC("unexpected NULL Subsys proxy"),
			                             _CPTC("SubsysDescriptor::get_Subsys_interface"));
  }

  //- get Subsys commands list & info
  try 
  {
    this->cmd_list(this->dev_proxy_->command_list_query());
  }
  catch (SALLV::DevFailed &e) 
  {
    SALLV::Except::re_throw_exception(e,
                                      _CPTC("command_list_query failed"),
			                                _CPTC("binding error: failed to get Subsys commands list"),
			                                _CPTC("SubsysDescriptor::get_Subsys_interface"));
  }
  catch (...) 
  {
    SALLV::Except::throw_exception(_CPTC("unknown error"),
			                             _CPTC("binding error: unknown exception caught"),
			                             _CPTC("SubsysDescriptor::get_Subsys_interface"));
  }

  //- get Subsys attributes list 
  try 
  {
    this->attr_list(this->dev_proxy_->attribute_list_query());  
  }
  catch (SALLV::DevFailed &e) 
  {
    //--TODO::C++ and Java servers have different behavior!!! 
    //--a C++ server return an empty list if it has no attributes
    //--whereas a Java server throw an exception. Both should 
    //--return an empty list. A quick and dirty workaround...
    std::string reason("API_AttrNotFound");
    if (reason != std::string(e.errors[0].reason)) 
    {  
      SALLV::Except::re_throw_exception(e,
                                        _CPTC("attribute_list_query failed"),
			                                  _CPTC("binding error: failed to get Subsys attributes list"),
			                                  _CPTC("SubsysDescriptor::get_Subsys_interface"));
    }
    else 
    {
      this->attr_list(0);
    }
  }
  catch (...) 
  {
    SALLV::Except::throw_exception(_CPTC("unknown error"),
			                             _CPTC("binding error: failed to get Subsys attributes list"),
			                             _CPTC("SubsysDescriptor::get_Subsys_interface"));
  }
}

//=============================================================================
// SubsysDescriptor::cmd_exists 
//=============================================================================
int SubsysDescriptor::cmd_exists (const std::string& _cmd_name)
  throw (SALLV::DevFailed)
{
  int indx = 0;
  SubsysDescriptor::MinCmdInfoList::iterator cur = this->dev_cmd_list_.begin();
  SubsysDescriptor::MinCmdInfoList::iterator end = this->dev_cmd_list_.end();
  while (cur != end) 
  {
    if ((*cur).name == _cmd_name)
      return indx;
    cur++; 
    indx++;
  }
  SALLV::Except::throw_exception(_CPTC("command not found"),
			                           _CPTC("command could not be found in local command list"),
			                           _CPTC("SubsysDescriptor::cmd_exists"));
  return NO_SUCH_CMD;
}

//=============================================================================
// SubsysDescriptor::attr_exists 
//=============================================================================
int SubsysDescriptor::attr_exists (const std::string& _attr_name)
  throw (SALLV::DevFailed)
{
  int indx = 0;
  SubsysDescriptor::MinAttrInfoList::iterator cur = this->dev_attr_list_.begin();
  SubsysDescriptor::MinAttrInfoList::iterator end = this->dev_attr_list_.end();
  while (cur != end) 
  {
    if ((*cur).name == _attr_name)
      return indx;
    cur++; 
    indx++;
  }
  SALLV::Except::throw_exception(_CPTC("attribute not found"),
			                           _CPTC("attribute could not be found in local attribute list"),
			                           _CPTC("SubsysDescriptor::attr_exists"));
  return NO_SUCH_ATTR;
}

//=============================================================================
// SubsysDescriptor::is_attr_writable
//=============================================================================
bool SubsysDescriptor::is_attr_writable (const std::string& _attr_name)
{ 
  return this->is_attr_writable(this->attr_exists(_attr_name));
}

//=============================================================================
// SubsysDescriptor::is_attr_writable
//=============================================================================
bool SubsysDescriptor::is_attr_writable (int _attr_id)
{
  if (_attr_id < 0 || static_cast<size_t>(_attr_id) >= this->dev_attr_list_.size())	
    return false;

  switch (this->dev_attr_list_[_attr_id].writable) 
  {
    case SALLV::READ:
    case SALLV::READ_WITH_WRITE:
      return false;
    default:
      break;
  }

  return true;
}

//=============================================================================
// SubsysDescriptor::is_attr_readable
//=============================================================================
bool SubsysDescriptor::is_attr_readable (const std::string& _attr_name)
{ 
  return this->is_attr_writable(this->attr_exists(_attr_name));
}

//=============================================================================
// SubsysDescriptor::is_attr_readable
//=============================================================================
bool SubsysDescriptor::is_attr_readable (int _attr_id)
{
  if (_attr_id < 0 ||static_cast<size_t>(_attr_id) >= this->dev_attr_list_.size())
    return false;
 
  switch (this->dev_attr_list_[_attr_id].writable) 
  {
    case SALLV::WRITE:
      return false;
      break;
    default:
      break;
  }

  return true; 
}

//=============================================================================
// SubsysDescriptor::cmd_list
//=============================================================================
void SubsysDescriptor::cmd_list (SALLV::CommandInfoList* _cmd_list)
{
  this->dev_cmd_list_.clear();

  if (_cmd_list == 0)
    return;

  SubsysDescriptor::MinCmdInfoList::size_type s = _cmd_list->size();

  this->dev_cmd_list_.resize(s);

  for (SubsysDescriptor::MinCmdInfoList::size_type i = 0; i < s; i++) 
  {
    this->dev_cmd_list_[i].name = (*_cmd_list)[i].cmd_name;
    this->dev_cmd_list_[i].in_type = (*_cmd_list)[i].in_type;
    this->dev_cmd_list_[i].out_type = (*_cmd_list)[i].out_type;
  }

  delete _cmd_list;
}

//=============================================================================
// SubsysDescriptor::attr_list
//=============================================================================
void SubsysDescriptor::attr_list (SALLV::AttributeInfoList* _attr_list)
{
  this->dev_attr_list_.clear();

  if (_attr_list == 0)
    return;

  SubsysDescriptor::MinAttrInfoList::size_type s = _attr_list->size();

  this->dev_attr_list_.resize(s);

  for (SubsysDescriptor::MinAttrInfoList::size_type i = 0; i < s; i++) 
  {
    this->dev_attr_list_[i].name = (*_attr_list)[i].name;
    this->dev_attr_list_[i].writable = (*_attr_list)[i].writable;
    this->dev_attr_list_[i].data_format = (*_attr_list)[i].data_format;
    this->dev_attr_list_[i].data_type = (*_attr_list)[i].data_type;
  }

  delete _attr_list;
}

