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
#ifndef OSPL_DDS_SUB_QUERY_HPP_
#define OSPL_DDS_SUB_QUERY_HPP_

/**
 * @file dds/sub/Query.hpp
 */

/*
 * OMG PSM class declaration
 */
#include <spec/dds/sub/Query.hpp>

// Implementation

namespace dds
{
namespace sub
{

template<typename T>
Query::Query(const dds::sub::DataReader<T>& dr, const std::string& query_expression) :
    dds::core::Value<DELEGATE>(dr, query_expression)
{
}

template<typename T, typename FWIterator>
Query::Query(const dds::sub::DataReader<T>& dr, const std::string& query_expression,
             const FWIterator& params_begin, const FWIterator& params_end) :
    dds::core::Value<DELEGATE>(dr, query_expression, params_begin,
                               params_end)
{
}

template<typename T>
Query::Query(const dds::sub::DataReader<T>& dr, const std::string& query_expression,
             const std::vector<std::string>& params) :
    dds::core::Value<DELEGATE>(dr, query_expression, params.begin(),
                               params.end())
{
}

template<typename FWIterator>
void Query::parameters(const FWIterator& begin, const FWIterator end)
{
    this->delegate().parameters(begin, end);
}

}
}

// End of implementation

#endif /* OSPL_DDS_SUB_QUERY_HPP_ */
