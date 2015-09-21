// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SALLVBinding.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL 
///  SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "ErrorStack.h"

#ifdef SAL_SUPPORT_REPOSITORY
#include "SubsysRepository.h"
#endif

#include "DataAdapter.h"
#include "EventManager.h"
#include "ObjectManager.h" 

//=============================================================================
// SHARED LIB EXPORTED SYMBOLS
//=============================================================================
#if defined(WIN32)
# define LVB_EXPORT extern "C" __declspec (dllexport)
# define LVB_CALLING_CONV __cdecl 
#else
# define LVB_EXPORT extern "C"    
# define LVB_CALLING_CONV
#endif

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW
//=============================================================================
//- SALLV ping support --------------------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV ping (const char*, void*, void*);
//- SALLV Subsys state/status support  ----------------------------------------
LVB_EXPORT long LVB_CALLING_CONV state (const char*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV status (const char*, void*, void*);
//- SALLV commands support  ---------------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV command_inout (const char*, const char*, void*, void*, void*);
//- SALLV read/write attributes support ---------------------------------------
LVB_EXPORT long LVB_CALLING_CONV read_attributes (const char*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV write_attributes (const char*, void*, void*);
//- SALLV events support ------------------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV subscribe_event (const char*,const char*, LVRefNum*, short, const char*, void*);
LVB_EXPORT long LVB_CALLING_CONV unsubscribe_event (LVRefNum *, void*);

#ifdef SAL_SUPPORT_GROUP
//- SALLV groups support ------------------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV group_create (const char*, void*, void*, long*, void*);
LVB_EXPORT long LVB_CALLING_CONV group_kill (long, void*);
LVB_EXPORT long LVB_CALLING_CONV group_size (long, long*, void*);
LVB_EXPORT long LVB_CALLING_CONV group_command_inout (long, const char*, void*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV group_read_attributes (long, void*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV group_write_attribute (long, const char *, void*, void*); 
#endif

#ifdef SAL_SUPPORT_ARCHIVE
//- SALLV archiving support ---------------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV extract_archived_data (const char*, const char*, unsigned long, void*, void*); 
#endif


//- SALLV Subsys timeout support ----------------------------------------------
LVB_EXPORT long LVB_CALLING_CONV set_timeout (const char*, unsigned long, void*);
//- SALLV Subsys interface (dyn. attrs) ---------------------------------------
LVB_EXPORT long LVB_CALLING_CONV reload_Subsys_interface (const char*, void*);
LVB_EXPORT long LVB_CALLING_CONV Subsys_commands_list (const char*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV Subsys_commands_info (const char*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV Subsys_attributes_list (const char*, void*, void*);
LVB_EXPORT long LVB_CALLING_CONV Subsys_attributes_info (const char*, void*, void*);
//-----------------------------------------------------------------------------
#if defined(_TBFL_HAS_OPEN_CLOSE_SESSION_INTERFACE_)
//- open/lose session routines (may be removed in a near future)
  LVB_EXPORT long LVB_CALLING_CONV open_lvb_session (void* error_stack_);
  LVB_EXPORT long LVB_CALLING_CONV close_lvb_session (void* error_stack_);
#endif

//=============================================================================
// CONSTS
//=============================================================================
const int kNoError =  0;
const int kError   = -1;

//=============================================================================
// MACROS
//=============================================================================
#define _TO_LV_ERR_STACK(X) reinterpret_cast<LvStringArrayHdl&>(X)

//=============================================================================
// EVENT TYPES
//=============================================================================
enum SALLVEventTypes
{
  LV_CONFIG_EVENT=0,
  LV_QOS_EVENT,
  LV_INFO_EVENT,
  LV_WARN_EVENT,
  LV_ALARM_EVENT
};

#if (_TBFL_HAS_STATIC_OBJ_MANAGER_ == 0) && defined(_TBFL_HAS_OPEN_CLOSE_SESSION_INTERFACE_)
//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: open_lvb_session
//=============================================================================
long open_lvb_session (void* error_stack_)
{
  try 
  {
    ObjectManager::init();
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("open_lvb_session", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("open_lvb_session", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: close_lvb_session
//=============================================================================
long close_lvb_session (void* error_stack_)
{
  try 
  {
    ObjectManager::fini();
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("close_lvb_session", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("close_lvb_session", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}
#endif

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: ping
//=============================================================================
long LVB_CALLING_CONV ping (const char* _dev_name, void* argout_, void* error_stack_)
{
  try
  {
    //- get local descriptor
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    //- ping the Subsys
    int rtt = ddesc->proxy()->ping();

    //- be sure argout_ is valid
    if (argout_ == 0) 
    {
      SALLV::Except::throw_exception("internal error",
                                     "unexpected null pointer",
                                     "ping");
    }

    //- push result into argout_
    *(reinterpret_cast<long*>(argout_)) = rtt;
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("ping", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("ping", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: state
//=============================================================================
long LVB_CALLING_CONV state (const char* _dev_name, void* argout_, void* error_stack_)
{
  try
  {
    //- get local descriptor
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    short lv_state = 0;

    //- convert from DevState to i16 (Labview calls to DLL don't like enum values)
    switch (ddesc->proxy()->state()) 
    {
      case SALLV::OFFLINE:
        lv_state = 0;
        break;
      case SALLV::ACTIVE:
        lv_state = 1;
        break;
      case SALLV::CMDERROR:
        lv_state = 2;
        break;
      case SALLV::ERROR:
        lv_state = 3;
        break;
      case SALLV::HALT:
        lv_state = 4;
        break;
      case SALLV::FAULT:
        lv_state = 5;
        break;
      case SALLV::DONE:
        lv_state = 6;
        break;
    }

    //- push result into argout_
    *(reinterpret_cast<short*>(argout_)) = lv_state;

  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("state", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("state", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: status
//=============================================================================
long LVB_CALLING_CONV status (const char* _dev_name, void* argout_, void* error_stack_)
{
  try
  {
    SALLV::DevFailed df;
    bool has_error = false;
    bool has_SALLV_error = false;

    SALLV::DevState state = SALLV::UNKNOWN;
    std::string lv_status = "unknown (failed to get state/status from Subsys)";

    try 
    {
      //- get local descriptor
      SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name); 

      //- get both state and status from Subsys
      state = ddesc->proxy()->state();
      lv_status = ddesc->proxy()->status();
    }
    catch (const SALLV::DevFailed& e) 
    {
      df = e;
      has_error = true;
      has_SALLV_error = true;
    }
    catch (...) 
    {
      has_error = true;
      has_SALLV_error = false;
    }

    //- convert from DevState to i16 (Labview calls to DLL don't like enum values)
    std::string lv_state_val;
    std::string lv_state_str;
    switch (state) 
    {
      case SALLV::OFFLINE:
        lv_state_val = "0"; 
        lv_state_str = "OFFLINE";
        break;
      case SALLV::ACTIVE:
        lv_state_val = "1"; 
        lv_state_str = "ACTIVE";
        break;
      case SALLV::CMDERROR:
        lv_state_val = "2"; 
        lv_state_str = "CMDERROR";
        break;
      case SALLV::ERROR:
        lv_state_val = "3"; 
        lv_state_str = "ERROR";
        break;
      case SALLV::HALT:
        lv_state_val = "4"; 
        lv_state_str = "HALT";
        break;
      case SALLV::FAULT:
        lv_state_val = "5"; 
        lv_state_str = "FAULT";
        break;
      case SALLV::DONE:
        lv_state_val = "6"; 
        lv_state_str = "DONE";
        break;
    }

    long err = ::NumericArrayResize(LvMemoryAddress, 
                                    1L, 
                                    reinterpret_cast<UHandle*>(&argout_), 
                                    3);
    if (err != noErr) {
      SALLV::Except::throw_exception("out of memory",
                                     "binding error: memory allocation failed",
                                     "status");
    }

    LvStringArrayHdl lvh = _TO_LV_ERR_STACK(argout_);
    (*lvh)->length = 3;
    ::memset((*lvh)->data, 0, (*lvh)->length * sizeof(long));
    size_t l = 0;
    LvStringHdl sh;

    sh = 0;
    l = lv_state_val.size();
    err = ::NumericArrayResize(iB, 1L, reinterpret_cast<UHandle*>(&sh), l);
    if (err != noErr) {
      SALLV::Except::throw_exception("out of memory",
                                     "binding error: memory allocation failed",
                                     "status");
    }
    (*sh)->length = l;
    ::memcpy((*sh)->data, lv_state_val.c_str(), l);
    (*lvh)->data[0] = sh;

    sh = 0;
    l = lv_state_str.size();
    err = ::NumericArrayResize(iB, 1L, reinterpret_cast<UHandle*>(&sh), l);
    if (err != noErr) {
      SALLV::Except::throw_exception("out of memory",
                                     "binding error: memory allocation failed",
                                     "status");
    }
    (*sh)->length = l;
    ::memcpy((*sh)->data, lv_state_str.c_str(), l);
    (*lvh)->data[1] = sh;

    sh = 0;
    l = lv_status.size();
    err = ::NumericArrayResize(iB, 1L, reinterpret_cast<UHandle*>(&sh), l);
    if (err != noErr) {
      SALLV::Except::throw_exception("out of memory",
                                     "binding error: memory allocation failed",
                                     "status");
    }
    (*sh)->length = l;
    ::memcpy((*sh)->data, lv_status.c_str(), l);
    (*lvh)->data[2] = sh;

    if (has_error) 
    {
      if (has_SALLV_error)
        throw df;
      else
        throw;
    }
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("status", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("status", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: command_inout
//=============================================================================
long LVB_CALLING_CONV command_inout (const char* _dev_name,
                                     const char* _cmd_name,
                                     void* _argin, 
                                     void* argout_,
                                     void* error_stack_)
{
  try
  {
    //- cast to actual type
    LvArgIOPtr ai = reinterpret_cast<LvArgIOPtr>(_argin);
    if (! ai)
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvArgIO cluster [check your Vi inputs)",
                                     "SALLVBinding::command_inout");
    }

    //- cast to actual type
    LvArgIOPtr ao = reinterpret_cast<LvArgIOPtr>(argout_);
    if (! ao)
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvArgIO cluster [check your Vi inputs)",
                                     "SALLVBinding::command_inout");
    }

    //- get local descriptor
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    //- is <cmd_name> a valid command for <dev_name>
    int cmd_id = ddesc->cmd_exists(_cmd_name);

    //- get <argin> type for <cmd_name>
    int ai_type = (ddesc->cmd_list())[cmd_id].in_type;

    //- get <argout> type for <cmd_name>
    int ao_type = (ddesc->cmd_list())[cmd_id].out_type;

    //- get <cmd_name> result in a SALLV::SubsysData 
    SALLV::SubsysData dd_out;

    //- encode <argin> then exec the command 
    if (ai_type != NULL) 
    {
      SALLV::SubsysData dd_in;
      DATA_ADAPTER->encode_argin(ddesc, cmd_id, ai, dd_in);
      dd_out = ddesc->proxy()->command_inout(_cmd_name, dd_in);
    }
    //- just exec the command 
    else 
    {
      dd_out = ddesc->proxy()->command_inout(_cmd_name);
    }

    //- decode <argout>
    if (ao_type != NULL) 
    {
      DATA_ADAPTER->decode_argout(ddesc, cmd_id, dd_out, ao);
    }
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("command_inout", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("command_inout", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: read_attributes
//=============================================================================
long LVB_CALLING_CONV read_attributes (const char* _dev_name,
                                       void* values_inout_,
                                       void* error_stack_)
{
  std::vector<SALLV::SubsysAttribute>* attr_values = 0;

  try 
  {
    //- get local descriptor
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    //- values_inout_ is a handle to an LvAttributeValueArray (i.e. an array of clusters)
    LvAttributeValueArrayHdl avah = reinterpret_cast<LvAttributeValueArrayHdl>(values_inout_);
    if (! avah || ! (*avah))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvAttributeValue array [check your Vi inputs)",
                                     "SALLVBinding::read_attributes");
    }

    //- how many entries do we have in this array?
    long n = (*avah)->length;

    std::vector<std::string> attr_names;
    attr_names.resize(n);

    //- for each entry in the LvAttributeValueArray...
		long i;
    for (i = 0; i < n; i++)
    {
      //- point to the i-th LvAttributeValue in the array
      LvAttributeValuePtr av = (*avah)->attr_values + i;
      //- get attribute name 
      LvStringHdl sh = reinterpret_cast<LvStringHdl>(av->attr_name);
      attr_names[i].assign(reinterpret_cast<char*>((*sh)->data), 
                           reinterpret_cast<char*>((*sh)->data) + (*sh)->length);
    }

    //- read attributes
    attr_values = ddesc->proxy()->read_attributes(attr_names);

    //- populate each LvAttributeValue
    for (i = 0; i < n; i++)
    {
      //- point to the i-th LvAttributeValue in the array
      LvAttributeValuePtr av = (*avah)->attr_values + i;
      //- decode attribute value
      DATA_ADAPTER->SALLV_to_lv_attribute_value(ddesc, attr_names[i], (*attr_values)[i], av); 
    }

    //- release memory 
    if (attr_values) delete attr_values;
  }
  catch (const SALLV::DevFailed& e)
  {
    if (attr_values) delete attr_values;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    if (attr_values) delete attr_values;
    ERROR_STACK->unknown("read_attributes", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("read_attributes", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: write_attributes
//=============================================================================
long LVB_CALLING_CONV write_attributes (const char* _dev_name,
                                        void* values_inout_,
                                        void* error_stack_)
{
  try 
  {
    //- get local descriptor
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    //- values_inout_ is a handle to an LvAttributeValueArray (i.e. an array of clusters)
    LvAttributeValueArrayHdl avah = reinterpret_cast<LvAttributeValueArrayHdl>(values_inout_);
    if (! avah || ! (*avah))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvAttributeValue array [check your Vi inputs)",
                                     "SALLVBinding::write_attributes");
    }

    //- how many entries do we have in this array?
    long n = (*avah)->length;

    //- some locals
    std::string attr_name;

    //- create and resize a vector of SALLV::SubsysAttribute 
    std::vector<SALLV::SubsysAttribute> da_list;
    da_list.resize(n);

    //- Get attr/val for each entry in the array
    for (long i = 0; i < n; i++) 
    {
      //- point to the i-th LvAttributeValue in the array
      LvAttributeValuePtr av = (*avah)->attr_values + i;
      //- get attr name
      LvStringHdl sh = reinterpret_cast<LvStringHdl>(av->attr_name);
      attr_name.assign(reinterpret_cast<char*>((*sh)->data), 
                       reinterpret_cast<char*>((*sh)->data) + (*sh)->length);
      //- get <_attr_name> id
      int attr_id = ddesc->attr_exists(attr_name);

      //- encode data (may throw an exception)
      try 
      {
        DATA_ADAPTER->encode_attr(ddesc, attr_id, av, da_list[i]);
      }
      catch (const SALLV::DevFailed& e) 
      {
        ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
        return kError;
      }
      catch (...) 
      {
        ERROR_STACK->unknown("write_attributes", _TO_LV_ERR_STACK(error_stack_));
        return kError;
      }
    }

    //- write attributes 
    ddesc->proxy()->write_attributes(da_list);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("write_attributes", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("write_attributes", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}


//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: subscribe_event
//=============================================================================
long LVB_CALLING_CONV subscribe_event (const char* _dev_name,
                                       const char* _attr_name,
                                       LVRefNum *_evt_refnum,
                                       short lv_evt_type,
                                       const char* lv_evt_filters,
                                       void *error_stack_)
{
  try
  {
    SALLV::EventType evt_type = SALLV::PERIODIC_EVENT;
    std::vector<std::string> filters;

    switch (lv_evt_type)
    {
      case LV_CONFIG_EVENT:
        evt_type = SALLV::CONFIG_EVENT;
        if (::strlen(lv_evt_filters) == 0)
        {
          SALLV::Except::throw_exception("invalid event filters",
                                         "valid event filter string required for CONFIG_EVENT",
                                         "subscribe_event");
        }
        filters.push_back(std::string(lv_evt_filters));
        break;
      case LV_QOS_EVENT:
        evt_type = SALLV::QOS_EVENT;
        if (::strlen(lv_evt_filters) == 0)
        {
          SALLV::Except::throw_exception("invalid event filters",
                                         "valid event filter string required for QOS_EVENT",
                                         "subscribe_event");
        }
        filters.push_back(std::string(lv_evt_filters));
        break;
      case LV_INFO_EVENT:
        evt_type = SALLV::INFO_EVENT;
        if (::strlen(lv_evt_filters) == 0)
        {
          SALLV::Except::throw_exception("invalid event filters",
                                         "valid event filter string required for INFO_EVENT",
                                         "subscribe_event");
        }
        filters.push_back(std::string(lv_evt_filters));
        break;
      case LV_WARN_EVENT:
        evt_type = SALLV::WARN_EVENT;
        if (::strlen(lv_evt_filters) == 0)
        {
          SALLV::Except::throw_exception("invalid event filters",
                                         "valid event filter string required for WARN_EVENT",
                                         "subscribe_event");
        }
        filters.push_back(std::string(lv_evt_filters));
        break;
      case LV_ALARM_EVENT:
        evt_type = SALLV::ALARM_EVENT;
        if (::strlen(lv_evt_filters) == 0)
        {
          SALLV::Except::throw_exception("invalid event filters",
                                         "valid event filter string required for ALARM_EVENT",
                                         "subscribe_event");
        }
        filters.push_back(std::string(lv_evt_filters));
        break;
      default:
        SALLV::Except::throw_exception("invalid event type specified",
                                       "invalid or unsupported SALLV event type",
                                       "subscribe_event");
        break;
    }

    EVT_MANAGER->subscribe(_dev_name, _attr_name, *_evt_refnum, evt_type, filters);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("subscribe_event", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("subscribe_event", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: unsubscribe_event
//=============================================================================
long LVB_CALLING_CONV unsubscribe_event (LVRefNum *_evt_refnum, void* error_stack_)
{
  try
  {
    EVT_MANAGER->unsubscribe(*_evt_refnum);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("unsubscribe_event", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("unsubscribe_event", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}



#ifdef SAL_SUPPORT_GROUP

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_create
//=============================================================================
long LVB_CALLING_CONV group_create (const char* _group_name,
                                    void* _managed_Subsyss,
                                    void* _ignored_Subsyss,
                                    long* group_id_,
                                    void* error_stack_)
{
  try
  {
    //- build vector of <managed Subsys> names
    LvStringArrayHdl h = reinterpret_cast<LvStringArrayHdl>(_managed_Subsyss);
    if (! h || ! (*h))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvString array [check your Vi inputs)",
                                     "SALLVBinding::group_create");
    }

    LvStringHdl sh = 0;
    SubsysList managed_Subsyss((*h)->length);
		long i;
    for (i = 0; i < (*h)->length; i++) 
    {
      sh = (*h)->data[i]; 
      managed_Subsyss[i].assign(reinterpret_cast<char*>((*sh)->data), 
                                reinterpret_cast<char*>((*sh)->data) + (*sh)->length);
    }

    //- build vector of <ignored Subsys> names
    SubsysList ignored_Subsyss(0);
    h = reinterpret_cast<LvStringArrayHdl>(_ignored_Subsyss);
    if (h && *h)
      ignored_Subsyss.resize((*h)->length);

    for (i = 0; i < (*h)->length; i++) 
    {
      sh = (*h)->data[i]; 
      ignored_Subsyss[i].assign(reinterpret_cast<char*>((*sh)->data), 
                                reinterpret_cast<char*>((*sh)->data) + (*sh)->length);
    }

    //- create the group and return its id to the caller
    *group_id_ = GRP_REP->add(_group_name, managed_Subsyss, ignored_Subsyss); 
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_create", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_create", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_kill
//=============================================================================
long LVB_CALLING_CONV group_kill (long _group_id, void* error_stack_)
{
  try
  {
    //- remove group from repository
    GRP_REP->remove(_group_id);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_kill", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_kill", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_size
//=============================================================================
long LVB_CALLING_CONV group_size (long _group_id,
                                  long* group_size_,
                                  void* error_stack_)
{
  try
  {
    //- get group from repository
    GroupDescriptor * gdesc = GRP_REP->get(_group_id);
    
    //- check returned reference
    if (! gdesc || ! gdesc->group())
    {
      SALLV::Except::throw_exception("invalid group identifier",
                                     "invalid group identifier specified [no such group]",
                                     "group_size");
    } 

    //- return group size to caller
    *group_size_ = static_cast<long>(gdesc->group()->get_size(false));
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_size", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_size", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_command_inout
//=============================================================================
long LVB_CALLING_CONV group_command_inout (long _group_id,
                                           const char * _command_name,
                                           void* _args_in,
                                           void* args_out_,
                                           void* error_stack_)
{
  try
  {
    //- get group from repository
    GroupDescriptor * gdesc = GRP_REP->get(_group_id);
  
    //- check returned reference
    if (! gdesc || ! gdesc->group())
    {
      SALLV::Except::throw_exception("invalid group identifier",
                                     "invalid group identifier specified [no such group]",
                                     "group_command_inout");
    } 

    //- get group size
    size_t grp_size = gdesc->group()->get_size(false);

    //- check input array size
    if (! grp_size)
    {
      SALLV::Except::throw_exception("empty group",
                                     "can't execute a command on an empty group",
                                     "group_command_inout");
    } 

    //- get Subsys descriptor of the first Subsys in the group (arbitrary choice)
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(gdesc->Subsys_list()[0]);

    //- is <cmd_name> a valid command for <dev_name>
    int cmd_id = ddesc->cmd_exists(_command_name);

    //- get <argin> type for <cmd_name>
    int ai_type = (ddesc->cmd_list())[cmd_id].in_type;
    bool ai_type_is_not_void = ai_type != SALLV::NULL;

    //- get <argout> type for <cmd_name>
    int ao_type = (ddesc->cmd_list())[cmd_id].out_type;
    bool ao_type_is_not_void = ao_type != SALLV::NULL;

    //- _args_in is a handle to an LvArgIOArray (i.e. an array of clusters)
    LvArgIOArrayHdl args_in = reinterpret_cast<LvArgIOArrayHdl>(_args_in);
    if (ai_type_is_not_void && (! args_in || ! (*args_in)))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvArgIO array [check your Vi inputs)",
                                     "SALLVBinding::group_command_inout");
    }

    //- args_out_ is a handle to an LvArgIOArray (i.e. an array of clusters)
    LvArgIOArrayHdl args_out = reinterpret_cast<LvArgIOArrayHdl>(args_out_);
    if (ao_type_is_not_void && (! args_out || ! (*args_out)))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvArgIO array [check your Vi inputs)",
                                     "SALLVBinding::group_command_inout");
    }

    //- how many entries do we have in args_in array?
    long n_in = (ai_type_is_not_void) ? (*args_in)->length : 0;

    //- how many entries do we have in args_out array?
    long n_out = (ao_type_is_not_void) ? (*args_out)->length : 0;

    //- check input array size
    if (ai_type_is_not_void && (n_in != grp_size))
    {
      SALLV::Except::throw_exception("invalid array",
                                     "the size of the arg-in array must equal the number of Subsyss in the group",
                                     "group_command_inout");
    } 

    //- check output array size
    if (ao_type_is_not_void && (n_out != grp_size))
    {
      SALLV::Except::throw_exception("invalid array",
                                     "the size of the arg-out array must equal the number of Subsyss in the group",
                                     "group_command_inout");
    } 

    //- cmd replies
    SALLV::GroupCmdReplyList cmd_args_out;

    if (ai_type_is_not_void) 
    {
      //- create and resize a vector of SALLV::SubsysAttribute 
      std::vector<SALLV::SubsysData> dd_list;

      //- Get attr/val for each entry in the array
      for (long i = 0; i < n_in; i++) 
      {
        //- get Subsys descriptor of the first Subsys in the group (arbitrary choice)
        ddesc = DEV_REP->Subsys_desc(gdesc->Subsys_list()[i]);

        //- is <cmd_name> a valid command for <dev_name>
        cmd_id = ddesc->cmd_exists(_command_name);

        //- point to associated LvAttributeValue 
        LvArgIOPtr arg_io = (*args_in)->arg_io + i;

        //- encode <argin> 
        SALLV::SubsysData dd;
        DATA_ADAPTER->encode_argin(ddesc, cmd_id, arg_io, dd);
        dd_list.push_back(dd);
      }
      //- exec ncmd 
      cmd_args_out = gdesc->group()->command_inout(_command_name, dd_list, false);
    }
    else
    {
      //- exec cmd 
      cmd_args_out = gdesc->group()->command_inout(_command_name, false);
    }

    //- decode <argout>
    if (ao_type_is_not_void) 
    {
      for (unsigned long i = 0; i < grp_size; i++) 
      {
        //- point to the i-th LvAttributeValue in the array
        LvArgIOPtr arg_out = (*args_out)->arg_io + i;
        //- decode <argout> 
        DATA_ADAPTER->decode_argout(ddesc, cmd_id, cmd_args_out[i].get_data(), arg_out);
      }
    }
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_command_inout", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_command_inout", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_read_attributes
//=============================================================================
long LVB_CALLING_CONV group_read_attributes (long _group_id,
                                             void* _attributes_names,
                                             void* values_inout_,
                                             void* error_stack_)
{
  try
  {
    //- get group from repository
    GroupDescriptor * gdesc = GRP_REP->get(_group_id);
  
    //- check returned reference
    if (! gdesc || ! gdesc->group())
    {
      SALLV::Except::throw_exception("invalid group identifier",
                                     "invalid group identifier specified [no such group]",
                                     "group_read_attributes");
    } 

    //- get attribute names from 2nd argument
    LvStringArrayHdl h = reinterpret_cast<LvStringArrayHdl>(_attributes_names);
    if (h == 0) 
    {
      SALLV::Except::throw_exception("invalid argument",
                                     "binding internal error: unexpected null argument",
                                     "group_read_attributes");
    }

    //- vector of attribute names: the attributes to be read
    std::vector<std::string> attributes_names((*h)->length);
    for (size_t i = 0; i < attributes_names.size(); i++)
    {
      LvStringHdl sh = (*h)->data[i]; 
      attributes_names[i].assign(reinterpret_cast<char*>((*sh)->data), 
                                 reinterpret_cast<char*>((*sh)->data) + (*sh)->length);
    }

    //- read attributes on each Subsys in the group (may throw an exception)
    SALLV::GroupAttrReplyList arl = gdesc->group()->read_attributes(attributes_names, false);

    //- the number of Subsys in the group
    long grp_size = gdesc->group()->get_size(false);

    //- check input array size
    if (! grp_size)
    {
      SALLV::Except::throw_exception("empty group",
                                     "can't read attributes on an empty group",
                                     "group_read_attributes");
    } 

    //- the number of read attributes
    long nattrs = attributes_names.size();

    //- values_inout_ is a handle to an LvAttributeValueArray (i.e. an array of clusters)
    LvAttributeValueArrayHdl avah = reinterpret_cast<LvAttributeValueArrayHdl>(values_inout_);

    //- how many entries do we have in this array?
    long avah_size = (*avah)->length;

    //- be sure we have enough room to store results
    long required_avah_size = grp_size * nattrs;
    if (avah_size != required_avah_size)
    {
      SALLV::Except::throw_exception("invalid argument",
                                     "wrong size for input array of AttributeValues",
                                     "group_read_attributes");
    }
    
    //- for each Subsys in the group...
    for (long d = 0; d < grp_size; d++)
    {
      //- get local Subsys descriptor
      SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(gdesc->Subsys_list()[d]);
      //- for each read attribute 
      for (long a = 0; a < nattrs; a++)
      {
        //- compute current index in arl (GroupAttrReplyList) 
        long current_index = d * nattrs + a;
        //- point to associated LvAttributeValue 
        LvAttributeValuePtr av = (*avah)->attr_values + current_index;
        //- decode attribute value
        DATA_ADAPTER->SALLV_to_lv_attribute_value(ddesc, 
                                                  attributes_names[a], 
                                                  arl[current_index].get_data(), 
                                                  av);
      }
    }
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_read_attributes", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_read_attributes", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: group_write_attribute
//=============================================================================
long LVB_CALLING_CONV group_write_attribute (long _group_id,
                                             const char * _attribute_name,
                                             void* _values_in,
                                             void* error_stack_)
{
  try
  {
    //- get group from repository
    GroupDescriptor * gdesc = GRP_REP->get(_group_id);
  
    //- check returned reference
    if (! gdesc || ! gdesc->group())
    {
      SALLV::Except::throw_exception("invalid group identifier",
                                     "invalid group identifier specified [no such group]",
                                     "group_write_attribute");
    } 

    //- get group size
    size_t grp_size = gdesc->group()->get_size(false);

    //- check input array size
    if (! grp_size)
    {
      SALLV::Except::throw_exception("empty group",
                                     "can't write attribute on an empty group",
                                     "group_write_attribute");
    } 

    //- _values_in is a handle to an LvAttributeValueArray (i.e. an array of clusters)
    LvAttributeValueArrayHdl avah = reinterpret_cast<LvAttributeValueArrayHdl>(_values_in);
    
    //- how many entries do we have in this array?
    long n = (*avah)->length;

    //- check returned reference
    if (n != grp_size || n != gdesc->Subsys_list().size())
    {
      SALLV::Except::throw_exception("invalid array",
                                     "the size of the AttributeValue array must equal the number of Subsyss in the group",
                                     "group_write_attribute");
    } 

    //- some locals
    std::string attr_name;

    //- create and resize a vector of SALLV::SubsysAttribute 
    std::vector<SALLV::SubsysAttribute> da_list;
    da_list.resize(n);

    //- Get attr/val for each entry in the array
    for (long i = 0; i < n; i++) 
    {
      //- get local Subsys descriptor
      SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(gdesc->Subsys_list()[i]);

      //- point to the i-th LvAttributeValue in the array
      LvAttributeValuePtr av = (*avah)->attr_values + i;

      //- get <_attribute_name> id
      int attr_id = ddesc->attr_exists(_attribute_name);

      //- encode data (may throw an exception)
      DATA_ADAPTER->encode_attr(ddesc, attr_id, av, da_list[i]);
    }

    //- write attribute
    gdesc->group()->write_attribute(da_list, false);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("group_write_attribute", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("group_write_attribute", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}


#endif



//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: set_timeout
//=============================================================================
long LVB_CALLING_CONV set_timeout (const char* _dev_name, 
                                   unsigned long _tmo, 
                                   void* error_stack_)
{
  try
  {
    //- avoid too short tmo (min = 1 second)
    if (_tmo < 1000) _tmo = 1000;

    //- get local descriptor for <_dev_name>
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    //- change timeout on <_dev_name>
    ddesc->proxy()->set_timeout(_tmo);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("set_timeout", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("set_timeout", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

#ifdef SAL_SUPPORT_ARCHIVE

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: extract_archived_data
//=============================================================================
long LVB_CALLING_CONV extract_archived_data (const char* _db_extractor_dev_name,
                                             const char* _dynamic_attr_name,
                                             unsigned long _dynamic_attr_history_len,
                                             void* values_inout_,
                                             void* error_stack_)
{
  std::vector<SALLV::SubsysAttributeHistory>* archived_attr_values = 0;

  try
  {
    //- get local descriptor for <_db_extractor_dev_name>
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_db_extractor_dev_name);

    //- we now need to read <dynamic_attr_name> history on <db_extractor_dev_name> to get the archived data!
    archived_attr_values = ddesc->proxy()->attribute_history(_dynamic_attr_name, _dynamic_attr_history_len);

    //- dyn. attr. workaround: close/(re)open Subsys connection to get the <dynamic_attr_name> data type
    DEV_REP->remove_Subsys(_db_extractor_dev_name);
    ddesc = DEV_REP->Subsys_desc(_db_extractor_dev_name);
    
    //- reinterpret <values_inout_> as a <LvAttributeValueArrayHdl>
    LvAttributeValueArrayHdl avah = reinterpret_cast<LvAttributeValueArrayHdl>(values_inout_);
    if (! avah || ! (*avah))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvAttributeValue array [check your Vi inputs)",
                                     "SALLVBinding::extract_archived_data");
    }

    //- be sure the input array as correct size (can't resize it from a DLL!)
    if ((*avah)->length != static_cast<long>(_dynamic_attr_history_len))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected <destination array> size",
                                     "SALLVBinding::extract_archived_data");
    }

    //- populate each LvAttributeValue
    for (long i = 0; i < static_cast<long>(_dynamic_attr_history_len); i++)
    {
      //- point to the i-th LvAttributeValue in the array
      LvAttributeValuePtr av = (*avah)->attr_values + i;
      //- decode attribute value
      DATA_ADAPTER->SALLV_to_lv_attribute_value(ddesc, _dynamic_attr_name, (*archived_attr_values)[i], av); 
    }
    
    //- avoid memory leak...
    delete archived_attr_values;
  }
  catch (const SALLV::DevFailed& e)
  {
    if (archived_attr_values) delete archived_attr_values;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    if (archived_attr_values) delete archived_attr_values;
    ERROR_STACK->unknown("extract_archived_data", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("extract_archived_data", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

#endif

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: reload_Subsys_interface
//=============================================================================
long LVB_CALLING_CONV reload_Subsys_interface (const char* _dev_name, 
                                               void* error_stack_)
{
  try
  {
    //- close/(re)open Subsys connection to reload the Subsys interface
    DEV_REP->remove_Subsys(_dev_name);
    DEV_REP->Subsys_desc(_dev_name);
  }
  catch (const SALLV::DevFailed& e)
  {
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    ERROR_STACK->unknown("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: Subsys_commands_list
//=============================================================================
long LVB_CALLING_CONV Subsys_commands_list (const char* _dev_name, 
                                            void* commands_list, 
                                            void* error_stack_)
{
  SALLV::CommandInfoList * cil = 0;

  try
  {
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    cil = ddesc->proxy()->command_list_query();

    LvStringArrayHdl lvh = reinterpret_cast<LvStringArrayHdl&>(commands_list);
    if (! lvh || ! (*lvh))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvStringArray array [check your Vi inputs)",
                                     "SALLVBinding::Subsys_commands_list");
    }

    long err = ::NumericArrayResize(uL, 
                                    1L, 
                                    reinterpret_cast<UHandle*>(&lvh), 
                                    cil->size());
    if (err != noErr)
      SALLV::Except::throw_exception("internal error",
                                     "failed to resize a LabVIEW array",
                                     "SALLVBinding::Subsys_attributes_list");

    (*lvh)->length = cil->size();

    ::memset((*lvh)->data, 0, (*lvh)->length * sizeof(long));

    for (size_t i = 0; i < cil->size(); i++)
    {
      LvStringHdl sh = 0;
	    size_t l = (*cil)[i].cmd_name.length();
      err = ::NumericArrayResize(iB, 1L, reinterpret_cast<UHandle*>(&sh), l);
      if (err != noErr)
        SALLV::Except::throw_exception("internal error",
                                       "failed to resize a LabVIEW array",
                                       "SALLVBinding::Subsys_attributes_list");
	    (*sh)->length = l;
      ::memcpy((*sh)->data, (*cil)[i].cmd_name.c_str(), l);
      (*lvh)->data[i] = sh;
    }

    delete cil;
  }
  catch (const SALLV::DevFailed& e)
  {
    delete cil;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    delete cil;
    ERROR_STACK->unknown("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: Subsys_commands_info
//=============================================================================
long LVB_CALLING_CONV Subsys_commands_info (const char* _dev_name, 
                                            void* commands_info, 
                                            void* error_stack_)
{
  SALLV::CommandInfoList * cil = 0;

  try
  {
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    cil = ddesc->proxy()->command_list_query();

    LvCommandInfoArrayHdl lvh = reinterpret_cast<LvCommandInfoArrayHdl&>(commands_info);
    if (! lvh || ! (*lvh))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvCommandInfo array [check your Vi inputs)",
                                     "SALLVBinding::Subsys_commands_info");
    }

    //- be sure the input array as correct size (can't resize it from a DLL!)
    if ((*lvh)->length != static_cast<long>(cil->size()))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected <destination array> size",
                                     "SALLVBinding::Subsys_commands_info");
    }

    //- fill in each AttributeInfo
    for (size_t i = 0; i < cil->size(); i++)
    {
      //- point to the i-th LvAttributeInfo in the LvAttributeInfoArray
      LvCommandInfo & lci = (*lvh)->cmd_infos[i];
      //- point to the i-th SALLV::AttributeInfo in the SALLV::AttributeInfoList 
      SALLV::CommandInfo & tci = (*cil)[i];
      //- LvAttributeInfo.name
      LvStringHdl sh = lci.name;
      if (! sh || ! (*sh))
      {
        SALLV::Except::throw_exception("unexpected null handle",
                                       "invalid LvCommandInfo [seems to be uninitialized]",
                                       "DataAdapter::Subsys_commands_info");
      }
      if ((*sh)->length != static_cast<int32>(tci.cmd_name.size()))
      {
        long err = ::NumericArrayResize(uB, 1L, (UHandle*)&sh, tci.cmd_name.size());
        if (err != noErr) 
        {
          SALLV::Except::throw_exception("out of memory error",
                                         "binding error: memory allocation failed",
                                         "DataAdapter::Subsys_commands_info");
        }
        sh = lci.name;
        (*sh)->length = tci.cmd_name.length();
        ::memcpy((*sh)->data, tci.cmd_name.c_str(), tci.cmd_name.size());
      }
      //- LvAttributeInfo.in_type
      lci.in_type = static_cast<short int>(tci.in_type);
      //- LvAttributeInfo.out_type
      lci.out_type = static_cast<short int>(tci.out_type);
      //- LvAttributeInfo.level
      lci.level = static_cast<short int>(tci.disp_level);
    }

    delete cil;
  }
  catch (const SALLV::DevFailed& e)
  {
    delete cil;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    delete cil;
    ERROR_STACK->unknown("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("reload_Subsys_interface", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: Subsys_attributes_list
//=============================================================================
long LVB_CALLING_CONV Subsys_attributes_list (const char* _dev_name, 
                                              void * attributes_list, 
                                              void* error_stack_)
{
  std::vector<std::string> * al = 0;

  try
  {
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    al = ddesc->proxy()->get_attribute_list();

    LvStringArrayHdl lvh = reinterpret_cast<LvStringArrayHdl&>(attributes_list);
    if (! lvh || ! (*lvh))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvString array [check your Vi inputs)",
                                     "SALLVBinding::Subsys_commands_info");
    }

    long err = ::NumericArrayResize(uL, 
                                    1L, 
                                    reinterpret_cast<UHandle*>(&lvh), 
                                    al->size());
    if (err != noErr)
      SALLV::Except::throw_exception("internal error",
                                     "failed to resize a LabVIEW array",
                                     "SALLVBinding::Subsys_attributes_list");

    (*lvh)->length = al->size();

    ::memset((*lvh)->data, 0, (*lvh)->length * sizeof(long));

    for (size_t i = 0; i < al->size(); i++)
    {
      LvStringHdl sh = 0;
	    size_t l = (*al)[i].length();
      err = ::NumericArrayResize(iB, 1L, reinterpret_cast<UHandle*>(&sh), l);
      if (err != noErr)
        SALLV::Except::throw_exception("internal error",
                                       "failed to resize a LabVIEW array",
                                       "SALLVBinding::Subsys_attributes_list");
	    (*sh)->length = l;
      ::memcpy((*sh)->data, (*al)[i].c_str(), l);
      (*lvh)->data[i] = sh;
    }

    delete al;
  }
  catch (const SALLV::DevFailed& e)
  {
    delete al;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    delete al;
    ERROR_STACK->unknown("Subsys_attributes_list", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("Subsys_attributes_list", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

//=============================================================================
// BINDING C-INTERFACE TO LABVIEW: Subsys_attributes_info
//=============================================================================
long LVB_CALLING_CONV Subsys_attributes_info (const char* _dev_name, 
                                              void * attributes_info, 
                                              void* error_stack_)
{
  SALLV::AttributeInfoList * ail = 0;

  try
  {
    SubsysDescriptor * ddesc = DEV_REP->Subsys_desc(_dev_name);

    ail = ddesc->proxy()->attribute_list_query();

    LvAttributeInfoArrayHdl lvh = reinterpret_cast<LvAttributeInfoArrayHdl&>(attributes_info);
    if (! lvh || ! (*lvh))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected null pointer to LvAttributeInfo array [check your Vi inputs)",
                                     "SALLVBinding::Subsys_attributes_info");
    }

    //- be sure the input array as correct size (can't resize it from a DLL!)
    if ((*lvh)->length != static_cast<long>(ail->size()))
    {
      SALLV::Except::throw_exception("invalid parameter",
                                     "unexpected <destination array> size",
                                     "SALLVBinding::Subsys_attributes_info");
    }

    //- fill in each AttributeInfo
    for (size_t i = 0; i < ail->size(); i++)
    {
      //- point to the i-th LvAttributeInfo in the LvAttributeInfoArray
      LvAttributeInfo & lai = (*lvh)->attr_infos[i];
      //- point to the i-th SALLV::AttributeInfo in the SALLV::AttributeInfoList 
      SALLV::AttributeInfo & tai = (*ail)[i];
      //- LvAttributeInfo.name
      LvStringHdl sh = lai.name;
      if (! sh || ! (*sh))
      {
        SALLV::Except::throw_exception("unexpected null handle",
                                       "invalid LvAttributeInfo [seems to be uninitialized]",
                                       "DataAdapter::Subsys_attributes_info");
      }
      if ((*sh)->length != static_cast<int32>(tai.name.size()))
      {
        long err = ::NumericArrayResize(uB, 1L, (UHandle*)&sh, tai.name.size());
        if (err != noErr) 
        {
          SALLV::Except::throw_exception("out of memory error",
                                         "binding error: memory allocation failed",
                                         "DataAdapter::Subsys_attributes_info");
        }
        sh = lai.name;
        (*sh)->length = tai.name.length();
        ::memcpy((*sh)->data, tai.name.c_str(), tai.name.size());
      }
      //- LvAttributeInfo.access
      lai.access = static_cast<short int>(tai.writable);
      //- LvAttributeInfo.format
      lai.format = static_cast<short int>(tai.data_format);
      //- LvAttributeInfo.type
      lai.type = static_cast<short int>(tai.data_type);
      //- LvAttributeInfo.level
      lai.level = static_cast<short int>(tai.disp_level);
      //- LvAttributeInfo.disp_label
      sh = lai.disp_label;
      if (! sh || ! (*sh))
      {
        SALLV::Except::throw_exception("unexpected null handle",
                                       "invalid LvAttributeInfo [seems to be uninitialized]",
                                       "DataAdapter::Subsys_attributes_info");
      }
      if ((*sh)->length != static_cast<int32>(tai.label.size()))
      {
        long err = ::NumericArrayResize(uB, 1L, (UHandle*)&sh, tai.label.size());
        if (err != noErr) 
        {
          SALLV::Except::throw_exception("out of memory error",
                                         "binding error: memory allocation failed",
                                         "DataAdapter::Subsys_attributes_info");
        }
        sh = lai.disp_label;
        (*sh)->length = tai.label.length();
        ::memcpy((*sh)->data, tai.label.c_str(), tai.label.size());
      }
      //- LvAttributeInfo.disp_unit
      sh = lai.disp_unit;
      if (! sh || ! (*sh))
      {
        SALLV::Except::throw_exception("unexpected null handle",
                                       "invalid LvAttributeInfo [seems to be uninitialized]",
                                       "DataAdapter::Subsys_attributes_info");
      }
      if ((*sh)->length != static_cast<int32>(tai.unit.size()))
      {
        long err = ::NumericArrayResize(uB, 1L, (UHandle*)&sh, tai.unit.size());
        if (err != noErr) 
        {
          SALLV::Except::throw_exception("out of memory error",
                                         "binding error: memory allocation failed",
                                         "DataAdapter::Subsys_attributes_info");
        }
        sh = lai.disp_unit;
        (*sh)->length = tai.unit.size();
        ::memcpy((*sh)->data, tai.unit.c_str(), tai.unit.size());
      }
      //- LvAttributeInfo.format
      sh = lai.disp_format;
      if (! sh || ! (*sh))
      {
        SALLV::Except::throw_exception("unexpected null handle",
                                       "invalid LvAttributeInfo [seems to be uninitialized]",
                                       "DataAdapter::Subsys_attributes_info");
      }
      if ((*sh)->length != static_cast<int32>(tai.format.size()))
      {
        long err = ::NumericArrayResize(uB, 1L, (UHandle*)&sh, tai.format.size());
        if (err != noErr) 
        {
          SALLV::Except::throw_exception("out of memory error",
                                         "binding error: memory allocation failed",
                                         "DataAdapter::Subsys_attributes_info");
        }
        sh = lai.disp_format;
        (*sh)->length = tai.format.size();
        ::memcpy((*sh)->data, tai.format.c_str(), tai.format.size());
      }
    }
    delete ail;
  }
  catch (const SALLV::DevFailed& e)
  {
    delete ail;
    ERROR_STACK->devfailed(e, _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }
  catch (...) 
  {
    delete ail;
    ERROR_STACK->unknown("Subsys_attributes_info", _TO_LV_ERR_STACK(error_stack_));
    return kError;
  }

  ERROR_STACK->no_error("Subsys_attributes_info", _TO_LV_ERR_STACK(error_stack_));

  return kNoError;
}

