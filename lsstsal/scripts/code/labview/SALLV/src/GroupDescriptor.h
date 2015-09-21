// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   GroupRepository.h
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

#ifndef _GROUP_DESC_H_
#define _GROUP_DESC_H_

//=============================================================================
// DEPENDENCIEs
//=============================================================================
#include <map>

//=============================================================================
// TYPEDEFs
//=============================================================================
typedef std::vector<std::string> DeviceList;

//=============================================================================
// CLASS : GroupDescriptor
//=============================================================================
class GroupDescriptor
{
  friend class GroupRepository;

public:
  //- ctor
  GroupDescriptor (SALLV::Group * _g);

  //- underlying group access
  SALLV::Group * operator-> ();

  //- underlying group access
  SALLV::Group * group ();

  //- list of devices belonging to group
  const DeviceList & device_list ();

  //- default ctor
  bool operator< (const GroupDescriptor & _src) const;

private:
  //- ref to group
  SALLV::Group * g;

  //- list of devices belonging to group
  DeviceList dl;

  //- private/hidden/forbidden methods
  GroupDescriptor (const GroupDescriptor&);
  virtual ~GroupDescriptor ();
  GroupDescriptor & operator= (const GroupDescriptor&);
};

//=============================================================================
// INLINED CODE
//=============================================================================
#if defined (_LV_INLINE_)
  #include "GroupDescriptor.i"
#endif 

#endif // _GROUP_DESC_H_

   
   
