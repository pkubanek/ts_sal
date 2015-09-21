// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ThreadSafeDeviceProxy.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "ThreadSafeDeviceProxy.h"

#if !defined (_LV_INLINE_)
  #include "ThreadSafeDeviceProxy.i"
#endif 

//=============================================================================
// ThreadSafeDeviceProxy::ThreadSafeDeviceProxy 
//=============================================================================
ThreadSafeDeviceProxy::ThreadSafeDeviceProxy (const std::string& dev_name)
    throw (SALLV::DevFailed)
 : dp_(0), ownership_(true), name_(dev_name)  
{
  dp_ = new SALLV::DeviceProxy(const_cast<std::string&>(dev_name));
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("out of memory",
			                             "binding error: memory allocation failed" ,  "ThreadSafeDeviceProxy::ThreadSafeDeviceProxy");
  }
}

//=============================================================================
// ThreadSafeDeviceProxy::ThreadSafeDeviceProxy 
//=============================================================================
ThreadSafeDeviceProxy::ThreadSafeDeviceProxy (const char * dev_name)
    throw (SALLV::DevFailed)
 : dp_(0), ownership_(true), name_(dev_name)    
{
	std::string dev(dev_name);

  dp_ = new SALLV::DeviceProxy(dev);
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("out of memory",
			                             "binding error: memory allocation failed"),
			                             "ThreadSafeDeviceProxy::ThreadSafeDeviceProxy");
  }
}

//=============================================================================
// ThreadSafeDeviceProxy::ThreadSafeDeviceProxy 
//=============================================================================
ThreadSafeDeviceProxy::ThreadSafeDeviceProxy (SALLV::DeviceProxy * _dp, bool _ownership)
    throw (SALLV::DevFailed)
 : dp_(_dp), ownership_(_ownership)  
{
  if (dp_ == 0) 
  {
    SALLV::Except::throw_exception("invalid argument",
			                             "unexpected NULL DeviceProxy"),
			                             "ThreadSafeDeviceProxy::ThreadSafeDeviceProxy");
  }
  this->name_ = dp_->dev_name();
}

//=============================================================================
// ThreadSafeDeviceProxy::~ThreadSafeDeviceProxy 
//=============================================================================
ThreadSafeDeviceProxy::~ThreadSafeDeviceProxy (void)
{
  omni_mutex_lock guard(this->lock_);

  if (dp_ && ownership_)
    delete dp_;
}

