#ifndef OSPL_DDS_PUB_DETAIL_FIND_HPP_
#define OSPL_DDS_PUB_DETAIL_FIND_HPP_

#include <string>

#include <dds/pub/Publisher.hpp>

/** @todo OSPL-1743 This is a no-op. Should it in fact do something ? */

namespace dds
{
namespace pub
{
namespace detail
{

template <typename WRITER, typename FwdIterator>
uint32_t
find(const dds::pub::Publisher& pub, const std::string& topic_name,
     FwdIterator begin, int32_t max_size)
{
    return 0;
}


template <typename WRITER, typename BinIterator>
uint32_t
find(const dds::pub::Publisher& pub,
     const std::string& topic_name,
     BinIterator begin)
{
    return 0;
}

}
}
}

#endif /* OSPL_DDS_PUB_DETAIL_FIND_HPP_ */
