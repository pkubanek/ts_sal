// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   EventManager.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#ifndef WIN32
#  include <sys/time.h> 
#endif 
#include "StandardHeader.h"
#include "SubsysRepository.h"
#include "DataAdapter.h"
#include "EventManager.h"
#include "ErrorStack.h"

#if !defined (_LV_INLINE_)
  #include "EventManager.i"
#endif 


//=============================================================================
// STATIC MEMBERS
//=============================================================================
EventManager* EventManager::instance_ = 0;
std::vector<std::string> EventManager::default_periodic_filter;

//*****************************************************************************
//*****************************************************************************
// CLASS: EventCallback
//*****************************************************************************
//*****************************************************************************
//=============================================================================
// EventCallback::EventCallback
//=============================================================================
EventCallback::EventCallback (const std::string& _dev, 
                              const std::string& _attr,
                              LVUserEventRef _lv_evt_refnum)
  : SALLV::CallBack(),
    dev_(_dev),
    attr_(_attr),
    lv_evt_refnum_(_lv_evt_refnum),
    SALLV_evt_refnum_(0)
{
  //- noop
}

//=============================================================================
// EventCallback::EventCallback
//=============================================================================  
EventCallback::~EventCallback (void) 
{
  //- noop
}

//=============================================================================
// EventCallback::push_event
//=============================================================================  
void EventCallback::push_event (SALLV::EventData* _evt_data) 
{
  try
  {
    if (_evt_data)
    {
      this->push_lv_event(_evt_data);
    }
  }
  catch (...)
  {
    //- can't do anything here!
  }
}

//=============================================================================
// EventCallback::push_lv_event
//=============================================================================
void EventCallback::push_lv_event (SALLV::EventData* _ea)
  throw (SALLV::DevFailed)
{
  //- alllocate the event data structure
  UPtr up = ::DSNewPClr(sizeof(LvAttributeValue));
  if (up == 0) {
      SALLV::Except::throw_exception(_CPTC("out of memory error"),
                                     _CPTC("binding error: memory allocation failed"),
                                     _CPTC("EventCallback::push_lv_event"));
  }

  LvAttributeValuePtr lvav = reinterpret_cast<LvAttributeValuePtr>(up);

  //- set Subsys name
  long err = ::NumericArrayResize(iB, 1L, (UHandle*)&(lvav->dev_name), this->dev_.size());
  if (err != noErr) {
    SALLV::Except::throw_exception(_CPTC("out of memory error"),
                                   _CPTC("binding error: memory allocation failed"),
                                   _CPTC("EventCallback::push_lv_event"));
  }
  LvStringHdl sh = reinterpret_cast<LvStringHdl>(lvav->dev_name);
  (*sh)->length = this->dev_.size();
  ::memcpy((*sh)->data, this->dev_.c_str(), this->dev_.size());

  //- set attr. name
  err = ::NumericArrayResize(iB, 1L, (UHandle*)&(lvav->attr_name), this->attr_.size());
  if (err != noErr) {
    SALLV::Except::throw_exception(_CPTC("out of memory error"),
                                   _CPTC("binding error: memory allocation failed"),
                                   _CPTC("EventCallback::push_lv_event"));
  }
  sh = reinterpret_cast<LvStringHdl>(lvav->attr_name);
  (*sh)->length = this->attr_.size();
  ::memcpy((*sh)->data, this->attr_.c_str(), this->attr_.size());

  //- access the SALLV::SubsysAttribute
  SALLV::SubsysAttribute *da = _ea->attr_value;

  //- in case of error: just set error code and stack then return
  if (_ea->err) 
  {
    lvav->error_code = -1;
    SALLV::DevFailed df(_ea->errors);
    ERROR_STACK->devfailed(df, lvav->error_stack);
    ::PostLVUserEvent(this->lv_evt_refnum_, lvav);
    return;
  }

  //- set attribute quality (both value and string)
  std::string s;
  switch (da->quality) 
  {
    case SALLV::ATTR_VALID:
	    lvav->quality_val = 0;
      s = "VALID";
	    break;
    case SALLV::ATTR_INVALID:
	    lvav->quality_val = 1;
      s = "INVALID";
	    break;
    case SALLV::ATTR_ALARM:
	    lvav->quality_val = 2;
      s = "ALARM";
	    break;
    default:
	    lvav->quality_val = -1;
      s = "UNKNOWN";
	    break;
  };
  err = ::NumericArrayResize(iB, 1L, (UHandle*)&(lvav->quality_str), s.size());
  if (err != noErr) {
    SALLV::Except::throw_exception(_CPTC("out of memory error"),
                                   _CPTC("binding error: memory allocation failed"),
                                   _CPTC("EventCallback::push_lv_event"));
  }
  sh = reinterpret_cast<LvStringHdl>(lvav->quality_str);
  (*sh)->length = s.size();
  ::memcpy((*sh)->data, s.c_str(), s.size());

  //- set timestamp
  lvav->timestamp = kTIME_OFFSET +
                    (double)da->time.tv_sec +
                    1.E-6 * (double)da->time.tv_usec + 
                    1.E-9 * (double)da->time.tv_nsec;
  //- set dims
  SALLV::AttributeDimension r_dim = da->get_r_dimension();
  lvav->dim_x = r_dim.dim_x;
  lvav->dim_y = r_dim.dim_y;

  //- reset error code
  lvav->error_code = 0;
  ERROR_STACK->no_error("SALLVBinding::EventManager", lvav->error_stack);
  //- decode data
  try 
  {
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(this->dev_);
    int attr_id = ddesc->attr_exists(this->attr_);
    DATA_ADAPTER->decode_attr(ddesc, attr_id, *da, lvav->data);
  }
  catch (const SALLV::DevFailed& e) 
  {
    //- set error code 
    lvav->error_code = -1;
    //- set error stack
    ERROR_STACK->devfailed(e, lvav->error_stack); 
  }
  catch (...) 
  {
    //- set error code 
    lvav->error_code = -1;
    //- set error stack 
    ERROR_STACK->unknown("EventManager::push_lv_event", lvav->error_stack);
  }

  ::PostLVUserEvent(this->lv_evt_refnum_, lvav);
}

//*****************************************************************************
//*****************************************************************************
// CLASS: EventManager
//*****************************************************************************
//*****************************************************************************

//=============================================================================
// EventManager::init
//=============================================================================
int EventManager::init (void)
{
  if (EventManager::instance_ != 0)
    return 0;

  EventManager::instance_ = new EventManager;

  return (EventManager::instance_) ? 0 : -1; 
}

//=============================================================================
// EventManager::cleanup
//=============================================================================
void EventManager::cleanup (void)
{
  if (EventManager::instance_) {
    delete EventManager::instance_;
    EventManager::instance_ = 0;
  }
}

//=============================================================================
// EventManager::EventManager 
//=============================================================================
EventManager::EventManager (void) : events_have_been_used_(false)
{
  //- default event filter: all periodic events
  EventManager::default_periodic_filter.push_back(std::string("$counter % 1 == 0"));
}

//=============================================================================
// EventManager::~EventManager 
//=============================================================================
EventManager::~EventManager (void)
{
  this->clear();
}

//=============================================================================
// EventManager::subscribe
//=============================================================================
void EventManager::subscribe (const std::string& dev, 
                              const std::string& attr,
                              LVUserEventRef lv_evt_refnum,
                              SALLV::EventType evt_type,
                              const std::vector<std::string>& filters)
  throw (SALLV::DevFailed)
{ 
  omni_mutex_lock guard(this->lock_);

  if (this->subscription_exists(lv_evt_refnum)) 
  {
    return;
  }


  SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(dev);
  if (ddesc == 0) {
    std::string d = "failed to subscribe to " + dev + "/" + attr;
    SALLV::Except::throw_exception(_CPTC("could not obtain a valid Subsys reference"),
                                   d.c_str(),
			                             _CPTC("EventManager::subscribe"));
  }
   
  EventCallback * cb = new EventCallback(dev, attr, lv_evt_refnum);
  if (cb == 0) {
    std::string d = "failed to subscribe to " + dev + "/" + attr;
    SALLV::Except::throw_exception(_CPTC("out of memory error"),
                                   d.c_str(),
			                             _CPTC("EventManager::subscribe"));
  }

  try 
  {
    cb->SALLV_evt_refnum_ = ddesc->proxy()->subscribe_event(attr, evt_type, cb, filters);
  }
  catch (const SALLV::DevFailed& e)
  {
    delete cb;
    std::string d = "failed to subscribe to " + dev + "/" + attr;
    SALLV::Except::re_throw_exception(const_cast<SALLV::DevFailed&>(e),
                                      _CPTC("SALLV event subscription failed [SALLV exception caught]"),
                                      d.c_str(),
			                                _CPTC("EventManager::subscribe"));
  }
  catch (...) 
  {
    delete cb;
    std::string d = "failed to subscribe to " + dev + "/" + attr;
    SALLV::Except::throw_exception(_CPTC("SALLV event subscription failed [unknown error]"),
                                   d.c_str(),
			                             _CPTC("EventManager::subscribe"));
  }

  events_have_been_used_ = true;

  std::pair<EventCallbackMapIterator, bool> result;
  result = this->evt_cb_map_.insert(EventCallbackMap::value_type(lv_evt_refnum, cb));
  if (result.second == 0) {
     deletenager.cpp cb;
     std::string d = "failed to subscribe to " + dev + "/" + attr;
     SALLV::Except::throw_exception(_CPTC("internal error"),
			                              d.c_str(),
			                              _CPTC("EventManager::subscribe"));
  }
 
} 

//=============================================================================
// EventManager::unsubscribe
//=============================================================================
void EventManager::unsubscribe (LVUserEventRef lv_evt_refnum)
  throw (SALLV::DevFailed)
{ 
  omni_mutex_lock guard(this->lock_);

  if (this->subscription_exists(lv_evt_refnum) == false) 
  {
     SALLV::Except::throw_exception(_CPTC("no such subscription"),
			                              _CPTC("could not find any event subscription with the specified refnum"),
			                              _CPTC("EventManager::unsubscribe"));
  }

  EventCallbackMapIterator it = this->evt_cb_map_.find(lv_evt_refnum);
  if (it->second == 0) 
  {
    SALLV::Except::throw_exception(_CPTC("internal error [unexpected null CallBack]"),
			                             _CPTC("failed to unsubscribe to SALLV::event"),
			                             _CPTC("EventManager::unsubscribe"));
  }

  SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(it->second->Subsys_name());
  if (ddesc == 0) 
  {
    SALLV::Except::throw_exception(_CPTC("internal error [unexpected null SubsysDescriptor]"),
			                             _CPTC("failed to unsubscribe to SALLV::event"),
			                             _CPTC("EventManager::unsubscribe"));
  }

  try 
  {
    ddesc->proxy()->unsubscribe_event(it->second->SALLV_evt_refnum_);
  }
  catch (const SALLV::DevFailed& e)
  {
    std::string d = "failed to unsubscribe to " + it->second->Subsys_name() 
                  + "/" + it->second->attribute_name();
    SALLV::Except::re_throw_exception(const_cast<SALLV::DevFailed&>(e),
                                      _CPTC("SALLV exception caught"),
                                      d.c_str(),
			                                _CPTC("EventManager::unsubscribe"));
  }
  catch (...) 
  {
    std::string d = "failed to unsubscribe to " + it->second->Subsys_name() 
                  + "/" + it->second->attribute_name();
    SALLV::Except::throw_exception(_CPTC("unknown error"),
                                    d.c_str(),
			                             _CPTC("EventManager::unsubscribe"));
  }

  delete it->second;

  this->evt_cb_map_.erase(it); 
}


//=============================================================================
// EventManager::clear
//=============================================================================
void EventManager::clear (void)
{
  omni_mutex_lock guard(this->lock_);

  SubsysDescriptor * ddesc = 0;
  EventCallbackMapIterator cur = this->evt_cb_map_.begin();
  EventCallbackMapIterator end = this->evt_cb_map_.end();

  for (; cur != end; cur++) 
  {
    if (cur->second) 
    {
      ddesc = DEV_REP->Subsys_desc(cur->second->Subsys_name());
      if (ddesc) 
      {
        try 
        {
          ddesc->proxy()->unsubscribe_event(cur->second->SALLV_evt_refnum_);
        }
        catch (...) 
        {
          //- ignore exception
        }
      }
      delete cur->second;
      cur->second = 0;
    }
  } 

  this->evt_cb_map_.clear();
}

//=============================================================================
// EventManager::subscription_exists
//=============================================================================
bool EventManager::subscription_exists (LVUserEventRef _lv_evt_refnum)
{ 
  EventCallbackMapIterator it = this->evt_cb_map_.find(_lv_evt_refnum);
  return (it != this->evt_cb_map_.end()) ? true : false;
}

