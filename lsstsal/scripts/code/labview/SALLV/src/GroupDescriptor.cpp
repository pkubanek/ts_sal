// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   GroupDescriptor.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "GroupDescriptor.h"

#if !defined (_LV_INLINE_)
# include "GroupDescriptor.i"
#endif 
 
//=============================================================================
// GroupDescriptor::GroupDescriptor
//=============================================================================
GroupDescriptor::GroupDescriptor (SALLV::Group* _g)
    : g(_g), dl(0)
{
  if (g) 
    dl = g->get_device_list(false);
}

//=============================================================================
// GroupDescriptor::~GroupDescriptor
//=============================================================================
GroupDescriptor::~GroupDescriptor ()
{
  dl.clear();
  if (g) delete g;
}


