// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SubsysRepository.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

#ifndef _Subsys_REPOSITORY_CPP_
#define _Subsys_REPOSITORY_CPP_

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "SubsysRepository.h"

#if !defined (_LV_INLINE_)
# include "SubsysRepository.i"
#endif 

//=============================================================================
// STATIC MEMBERS
//=============================================================================
SubsysRepository * SubsysRepository::instance_ = 0;

//=============================================================================
// SubsysRepository::cleanup
//=============================================================================
void SubsysRepository::init (void)
    throw (SALLV::DevFailed)
{
  if (SubsysRepository::instance_ != 0)
    return;

  try
  {
    SubsysRepository::instance_ = new SubsysRepository;
    if (SubsysRepository::instance_ == 0) 
      throw std::bad_alloc();
  }
  catch (const std::bad_alloc&)
  {
    SALLV::Except::throw_exception(_CPTC("out of memory"),
			                             _CPTC("binding error: SubsysRepository instanciation failed"),
			                             _CPTC("SubsysRepository::init_Subsys_repository"));
  }
  catch (SALLV::DevFailed& df)
  {
    SALLV::Except::re_throw_exception(df,
                                      _CPTC("software error"),
			                                _CPTC("binding error: SubsysRepository instanciation failed [SALLV exception caught]"),
			                                _CPTC("SubsysRepository::init_Subsys_repository"));
  }
  catch (...)
  {
    SALLV::Except::throw_exception(_CPTC("software error"),
			                             _CPTC("binding error: SubsysRepository instanciation failed [unknown exception caught]"),
			                             _CPTC("SubsysRepository::init_Subsys_repository"));
  }
}

//=============================================================================
// SubsysRepository::cleanup
//=============================================================================
void SubsysRepository::cleanup (void)
    throw (SALLV::DevFailed)
{
  if (SubsysRepository::instance_) 
  {
    delete SubsysRepository::instance_;
    SubsysRepository::instance_ = 0;
  }
}

//=============================================================================
// SubsysRepository::SubsysRepository 
//=============================================================================
SubsysRepository::SubsysRepository (void)
{
  //- noop
}

//=============================================================================
// SubsysRepository::~SubsysRepository 
//=============================================================================
SubsysRepository::~SubsysRepository (void)
{
  //- critical section
  omni_mutex_lock guard(this->lock_);

  this->remove_Subsys_i("*");
}

//=============================================================================
// SubsysRepository::Subsys_desc
//=============================================================================
SubsysDescriptor * SubsysRepository::Subsys_desc (const std::string& _Subsys_name)
    throw (SALLV::DevFailed)
{
  //- critical section
  omni_mutex_lock guard(this->lock_);

  //- convert to lower case
  std::string dev_name(_Subsys_name);
  std::transform(dev_name.begin(), dev_name.end(), dev_name.begin(), ::tolower);

  //- search for <Subsys_name> in the repository
  SubsysDescriptorMapIterator it = this->dev_map_.find(dev_name);
  if (it != this->dev_map_.end() && it->second) 
    return it->second;

  SubsysDescriptor * ddesc = 0;

  try
  {
    //- search failed, create the descriptor
    ddesc = new SubsysDescriptor(dev_name);
    if (ddesc == 0) 
      throw std::bad_alloc();
  }
  catch (const std::bad_alloc &)
  {
    SALLV::Except::throw_exception(_CPTC("out of memory"),
			                             _CPTC("binding error: memory allocation failed"),
			                             _CPTC("SubsysRepository::Subsys_desc"));
  }
  catch (SALLV::DevFailed & df)
  {
    SALLV::Except::re_throw_exception(df,
                                      _CPTC("object instanciation failed"),
			                                _CPTC("SubsysDescriptor instanciation failed [SALLV exception caught]"),
			                                _CPTC("SubsysRepository::Subsys_desc"));
  }
  catch (...)
  {
    SALLV::Except::throw_exception(_CPTC("object instanciation failed"),
			                             _CPTC("SubsysDescriptor instanciation failed [unknown error]"),
			                             _CPTC("SubsysRepository::Subsys_desc"));
  }

  //- store the Subsys descriptor into the repository
  std::pair<SubsysDescriptorMapIterator, bool> result;
  result = this->dev_map_.insert(SubsysDescriptorMap::value_type(dev_name, ddesc));
  if (result.second == 0) 
  {
    delete ddesc;
    SALLV::Except::throw_exception(_CPTC("internal error"),
			                             _CPTC("binding error: could not insert Subsys into the local repository"),
                                   _CPTC("SubsysRepository::Subsys_desc"));
  }

  //- return the Subsys descriptor
  return ddesc;
}

//=============================================================================
// SubsysRepository::Subsys_desc
//=============================================================================
SubsysDescriptor * SubsysRepository::Subsys_desc (SALLV::SubsysProxy * _dp, bool _ownership)
    throw (SALLV::DevFailed)
{
  //- critical section
  omni_mutex_lock guard(this->lock_);

  if (! _dp)
  {
    SALLV::Except::throw_exception(_CPTC("invalid argument"),
			                             _CPTC("unexpected NULL argument"),
			                             _CPTC("SubsysRepository::Subsys_desc"));
  }

  //- convert to lower case
  std::string dev_name(_dp->dev_name());
  std::transform(dev_name.begin(), dev_name.end(), dev_name.begin(), ::tolower);

  //- search for <Subsys_name> in the repository
  SubsysDescriptorMapIterator it = this->dev_map_.find(dev_name);
  if (it != this->dev_map_.end() && it->second) 
    return it->second;

  //- search failed, create the descriptor
  SubsysDescriptor * ddesc = new SubsysDescriptor(_dp, _ownership);
  if (ddesc == 0) 
  {
    SALLV::Except::throw_exception(_CPTC("out of memory"),
			                             _CPTC("binding error: memory allocation failed"),
			                             _CPTC("SubsysRepository::Subsys_desc"));
  }

  //- store the Subsys descriptor into the repository
  std::pair<SubsysDescriptorMapIterator, bool> result;
  result = this->dev_map_.insert(SubsysDescriptorMap::value_type(dev_name, ddesc));
  if (result.second == 0) 
  {
    delete ddesc;
    SALLV::Except::throw_exception(_CPTC("internal error"),
			                             _CPTC("binding error: could not insert Subsys into the local repository"),
			                             _CPTC("SubsysRepository::Subsys_desc"));
  }

  //- return the Subsys descriptor
  return ddesc;
}

//=============================================================================
// SubsysRepository::remove_Subsys
//=============================================================================
void SubsysRepository::remove_Subsys (const std::string& _Subsys_name)
{
  //- critical section
  omni_mutex_lock guard(this->lock_);

  this->remove_Subsys_i(_Subsys_name);
}

//=============================================================================
// SubsysRepository::remove_Subsys_i
//=============================================================================
void SubsysRepository::remove_Subsys_i(const std::string& _Subsys_name)
{
  if (_Subsys_name == "*") 
  {
    SubsysDescriptorMapIterator cur = this->dev_map_.begin();
    SubsysDescriptorMapIterator end = this->dev_map_.end();
    for (; cur != end; cur++) 
    {
      if (cur->second)
	      delete cur->second;
    } 
    this->dev_map_.clear();
  }
  else 
  {
    std::string dev_name(_Subsys_name);
    std::transform(dev_name.begin(), dev_name.end(), dev_name.begin(), ::tolower);
    SubsysDescriptorMapIterator it = this->dev_map_.find(dev_name);
    if (it != this->dev_map_.end()) 
    {
      if (it->second)
        delete it->second;
      this->dev_map_.erase(dev_name);
    }
  }
}

#endif // _Subsys_REPOSITORY_CPP_
