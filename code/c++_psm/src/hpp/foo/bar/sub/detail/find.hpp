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
#ifndef OSPL_DDS_SUB_DETAIL_FIND_HPP_
#define OSPL_DDS_SUB_DETAIL_FIND_HPP_

/**
 * @file
 */

// Implementation
#include <string>
#include <vector>

#include <dds/sub/Subscriber.hpp>
#include <dds/sub/status/DataState.hpp>
#include <dds/topic/TopicDescription.hpp>

namespace dds
{
namespace sub
{
namespace detail
{

template <typename READER, typename FwdIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const std::string& topic_name,
     FwdIterator begin, uint32_t max_size)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}

template <typename READER, typename BinIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const std::string& topic_name,
     BinIterator begin)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}
template <typename READER, typename T, typename FwdIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const dds::topic::TopicDescription<T>& topic_description,
     FwdIterator begin, uint32_t max_size)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}

template <typename READER, typename T, typename BinIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const dds::topic::TopicDescription<T>& topic_description,
     BinIterator begin)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}


template <typename READER, typename FwdIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const dds::sub::status::DataState& rs,
     FwdIterator begin, uint32_t max_size)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}

template <typename READER, typename BinIterator>
uint32_t
find(const dds::sub::Subscriber& sub,
     const dds::sub::status::DataState& rs,
     BinIterator begin)
{
    /** @todo OSPL-1743 */
    throw dds::core::UnsupportedError("not implemented");
    return 0;
}


}
}
}

#endif /* OSPL_DDS_SUB_DETAIL_FIND_HPP_ */
