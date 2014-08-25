// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   GroupRepository.cpp
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DEPENDENCIES
//=============================================================================
#include "StandardHeader.h"
#include "SubsysRepository.h"
#include "GroupRepository.h"

#if !defined (_LV_INLINE_)
# include "GroupRepository.i"
#endif 

//=============================================================================
// STATIC MEMBERS
//=============================================================================
GroupRepository* GroupRepository::instance_ = 0;
//-----------------------------------------------------------------------------
long GroupRepository::group_cnt = 0;

//=============================================================================
// CONSTs
//=============================================================================
#define kALL_GROUPS 0

//=============================================================================
// GroupRepository::init
//=============================================================================
void GroupRepository::init (void)
    throw (SALLV::DevFailed)
{
  if (GroupRepository::instance_ != 0)
    return;

  try
  {
    GroupRepository::instance_ = new GroupRepository;
    if (GroupRepository::instance_ == 0) 
      throw std::bad_alloc();
  }
  catch (const std::bad_alloc&)
  {
    SALLV::Except::throw_exception("out of memory",
			                             "binding error: SALLV::GroupRepository instanciation failed"),
			                             "GroupRepository::init");
  }
  catch (SALLV::DevFailed& df)
  {
    SALLV::Except::re_throw_exception(df,
                                      "software error"),
			                                "binding error: SALLV::GroupRepository instanciation failed [SALLV exception caught]"),
			                                "GroupRepository::init");
  }
  catch (...)
  {
    SALLV::Except::throw_exception("software error"),
			                             "binding error: SALLV::GroupRepository instanciation failed [unknown exception caught]"),
			                             "GroupRepository::init");
  }
}

//=============================================================================
// GroupRepository::cleanup
//=============================================================================
void GroupRepository::cleanup (void)
    throw (SALLV::DevFailed)
{
  if (GroupRepository::instance_) 
  {
    delete GroupRepository::instance_;
    GroupRepository::instance_ = 0;
  }
}

//=============================================================================
// GroupRepository::GroupRepository 
//=============================================================================
GroupRepository::GroupRepository (void)
{
  //- noop
}

//=============================================================================
// GroupRepository::~GroupRepository 
//=============================================================================
GroupRepository::~GroupRepository (void)
{
  //- critical section
  omni_mutex_lock guard(this->lock_);

  this->remove_group_i(kALL_GROUPS);
}

//=============================================================================
// GroupRepository::add
//=============================================================================
long GroupRepository::add (const std::string& _name, 
                           const SubsysList & _Subsyss_to_add,
                           const SubsysList & _Subsyss_to_remove)
    throw (SALLV::DevFailed)
{ 
  SALLV::Group * g = 0;

  if (! _Subsyss_to_add.size())
  {
    SALLV::Except::throw_exception("invalid argument"),
			                             "can't create empty SALLV::Group [empty managed Subsys list]"),
                                   "GroupRepository::add");
  }

  try
  {
    g = new SALLV::Group(_name);
    if (g == 0) 
      throw std::bad_alloc();
    
    g->add(_Subsyss_to_add);

    if (_Subsyss_to_remove.size())
      g->remove(_Subsyss_to_remove);
  }
  catch (const std::bad_alloc&)
  {
    SALLV::Except::throw_exception("out of memory"),
			                             "binding error: SALLV::Group initialization failed"),
			                             "GroupRepository::add");
  }
  catch (SALLV::DevFailed& df)
  {
    SALLV::Except::re_throw_exception(df,
                                      "software error"),
			                                "binding error: SALLV::Group initialization failed [SALLV exception caught]"),
			                                "GroupRepository::add");
  }
  catch (...)
  {
    SALLV::Except::throw_exception("software error"),
			                             "binding error: SALLV::Group initialization failed [unknown exception caught]"),
			                             "GroupRepository::add");
  }

  GroupDescriptor * gdesc = 0;

  try
  {
    gdesc = new GroupDescriptor(g);
    if (gdesc == 0) 
      throw std::bad_alloc();
  }
  catch (const std::bad_alloc &)
  {
    SALLV::Except::throw_exception("out of memory"),
			                             "GroupDescriptor instanciation failed"),
			                             "GroupRepository::add");
  }
  catch (...)
  {
    SALLV::Except::throw_exception("unknown error"),
			                             "GroupDescriptor instanciation failed [unknown error]"),
			                             "GroupRepository::add");
  }

  {
    //- critical section on repository
    omni_mutex_lock guard(this->lock_);

    //- increment group cnt (i.e.group id)
    ++GroupRepository::group_cnt;

    //- store the group into the repository
    std::pair<GroupMapIterator, bool> result;
    result = this->group_map_.insert(GroupMap::value_type(GroupRepository::group_cnt, gdesc));
    if (result.second == 0) 
    {
      delete gdesc;
      SALLV::Except::throw_exception("software error"),
			                               "could insert SALLV group into the repository [std::map::insert failed]"),
			                               "GroupRepository::add");
    }

    //- push group Subsyss into the dev. repository
    long num_Subsys = g->get_size();
    for (long d = 1; d <= num_Subsys; d++)
    {
      DEV_REP->Subsys_desc(g->get_Subsys(d), false);
    }
  }

  return GroupRepository::group_cnt;
}

//=============================================================================
// GroupRepository::remove
//=============================================================================
void GroupRepository::remove (long _group_id)
    throw (SALLV::DevFailed)
{ 
  //- critical section
  omni_mutex_lock guard(this->lock_);

  this->remove_group_i(_group_id);
}

//=============================================================================
// GroupRepository::remove_group_i
//=============================================================================
void GroupRepository::remove_group_i (long _group_id)
{
  if (_group_id == kALL_GROUPS) 
  {
    GroupMapIterator cur = this->group_map_.begin();
    GroupMapIterator end = this->group_map_.end();
    for (; cur != end; cur++) 
    {
      GroupDescriptor * gd = cur->second; 
      if (gd)
      {
        //- remove Subsyss from repository
        const SubsysList& dl = gd->Subsys_list();
	      for (size_t d = 0; d < dl.size(); d++)
          DEV_REP->remove_Subsys(dl[d]);
        //- delete group descriptor
        delete gd;
      }
    } 
    this->group_map_.clear();
  }
  else 
  {
    GroupMapIterator it = this->group_map_.find(_group_id);
    if (it != this->group_map_.end()) 
    {
      GroupDescriptor * gd = it->second; 
      if (gd)
      {
        //- remove Subsys from repository
        const SubsysList& dl = gd->Subsys_list();
	      for (size_t d = 0; d < dl.size(); d++)
          DEV_REP->remove_Subsys(dl[d]);
        this->group_map_.erase(_group_id);
        //- delete group descriptor
        delete gd;
      }
    }
  }
}




