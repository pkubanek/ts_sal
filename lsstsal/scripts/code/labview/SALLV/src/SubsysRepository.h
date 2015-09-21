// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   SubsysRepository.h
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

#ifndef _DEVICE_REPOSITORY_H_
#define _DEVICE_REPOSITORY_H_

//=============================================================================
// DEPENDENCIEs
//=============================================================================
#include <map>
#include "StandardHeader.h"
#include "SubsysDescriptor.h"

//=============================================================================
// SHORTCUT
//=============================================================================
#define DEV_REP (SubsysRepository::instance())

//=============================================================================
// CLASS : SubsysRepository 
//=============================================================================
class SubsysRepository 
{
  friend class ObjectManager;

  typedef std::map<std::string, SubsysDescriptor*> SubsysDescriptorMap;
  // SubsysMap : a STL map of <SubsysDescriptor*> indexed by subsys name

  typedef SubsysDescriptorMap::iterator SubsysDescriptorMapIterator;
  // SubsysMapIterator : a SubsysMap iterator

public:

  static SubsysRepository * instance (void);
  //- Returns the unique instance of <SubsysRepository>.

  SubsysDescriptor * subsys_desc (const char* subsys_name)
    throw (SALLV::DevFailed);
  // Providing a subsys name, returns its subsys descriptor.

  SubsysDescriptor * subsys_desc (const std::string& subsys_name)
    throw (SALLV::DevFailed);
  // Providing a subsys name, returns its subsys descriptor

  SubsysDescriptor * subsys_desc (SALLV::SubsysProxy * subsys_proxy, bool ownership = false)
    throw (SALLV::DevFailed);
  // Providing a subsys proxy, returns its subsys descriptor

  void remove_subsys (const std::string& subsys_name);
  //- Providing a subsys name, returns removes it from the repository.

private:
  static void init (void)
    throw (SALLV::DevFailed);
  //- Instanciates the singleton.
  
  static void cleanup (void)
    throw (SALLV::DevFailed);
  //- Releases the singleton.

  static SubsysRepository * instance_;
  //- The unique instance of <SubsysRepository>.

  void remove_subsys_i (const std::string& subsys_name);
  //- Providing a subsys name, returns removes it from the repository.

  SubsysDescriptorMap dev_map_;
  //- The actual repository (see typedef above).

  omni_mutex lock_;
  //- Use a lock in order to make the repository thread-safe.

  // = Disallow these operations (except for ObjectManager).
  //-------------------------------------------------------
  SubsysRepository();
  SubsysRepository (const SubsysRepository&);
  virtual ~SubsysRepository();
  void operator= (const SubsysRepository&); 
};

#if defined (_LV_INLINE_)
#  include "SubsysRepository.i"
#endif 

#endif // _DEVICE_REPOSITORY_H_

   
   
