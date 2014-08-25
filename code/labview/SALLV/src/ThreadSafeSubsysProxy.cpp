// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeSubsysProxy.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "ThreadSafeSubsysProxy.h"

#if !defined (_LV_INLINE_)
  #include "ThreadSafeSubsysProxy.i"
#endif 

//=============================================================================
// ThreadSafeSubsysProxy::ThreadSafeSubsysProxy 
//=============================================================================
ThreadSafeSubsysProxy::ThreadSafeSubsysProxy (const std::string& dev_name)
    throw (SALLV::DevFailed)
 : dp_(0), ownership_(true), name_(dev_name)  
{
  dp_ = new SALLV::SubsysProxy(const_cast<std::string&>(dev_name));
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("out of memory",
			                             "binding error: memory allocation failed" ,  "ThreadSafeSubsysProxy::ThreadSafeSubsysProxy");
  }
}

//=============================================================================
// ThreadSafeSubsysProxy::ThreadSafeSubsysProxy 
//=============================================================================
ThreadSafeSubsysProxy::ThreadSafeSubsysProxy (const char * dev_name)
    throw (SALLV::DevFailed)
 : dp_(0), ownership_(true), name_(dev_name)    
{
	std::string dev(dev_name);

  dp_ = new SALLV::SubsysProxy(dev);
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("out of memory",
			                             "binding error: memory allocation failed"),
			                             "ThreadSafeSubsysProxy::ThreadSafeSubsysProxy");
  }
}

//=============================================================================
// ThreadSafeSubsysProxy::ThreadSafeSubsysProxy 
//=============================================================================
ThreadSafeSubsysProxy::ThreadSafeSubsysProxy (SALLV::SubsysProxy * _dp, bool _ownership)
    throw (SALLV::DevFailed)
 : dp_(_dp), ownership_(_ownership)  
{
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("invalid argument",
			                             "unexpected NULL SubsysProxy"),
			                             "ThreadSafeSubsysProxy::ThreadSafeSubsysProxy");
  }
  this->name_ = dp_->dev_name();
}

//=============================================================================
// ThreadSafeSubsysProxy::~ThreadSafeSubsysProxy 
//=============================================================================
ThreadSafeSubsysProxy::~ThreadSafeSubsysProxy (void)
{
  omni_mutex_lock guard(this->lock_);

  if (dp_ && ownership_)
    delete dp_;
}

