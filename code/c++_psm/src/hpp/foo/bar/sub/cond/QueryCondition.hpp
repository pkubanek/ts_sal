/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2012 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */
#ifndef OSPL_DDS_SUB_COND_QUERYCONDITION_HPP_
#define OSPL_DDS_SUB_COND_QUERYCONDITION_HPP_

/**
 * @file dds/sub/cond/QueryCondition.hpp
 */

/*
 * OMG PSM class declaration
 */
#include <spec/dds/sub/cond/QueryCondition.hpp>

// Implementation

namespace dds
{
namespace sub
{
namespace cond
{

template<typename FWIterator>
void QueryCondition::parameters(const FWIterator& begin, const FWIterator end)
{
    this->delegate()->parameters(begin, end);
}

}
}
}

// End of implementation

#endif /* OSPL_DDS_SUB_COND_QUERYCONDITION_HPP_ */
