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
#ifndef OSPL_DDS_SUB_ANYDATAREADER_HPP_
#define OSPL_DDS_SUB_ANYDATAREADER_HPP_

/**
 * @file dds/sub/AnyDataReader.hpp
 */

/*
 * OMG PSM class declaration
 */
#include <spec/dds/sub/AnyDataReader.hpp>

// Implementation
namespace dds
{
namespace sub
{

template <typename T>
AnyDataReader::AnyDataReader(const dds::sub::DataReader<T>& dr)
    : holder_ (new detail::DRHolder<T>(dr)) { }

inline const detail::DRHolderBase* AnyDataReader::operator->() const
{
    return holder_.get();
}

inline dds::sub::detail::DRHolderBase* AnyDataReader::operator->()
{
    return holder_.get();
}


inline AnyDataReader& AnyDataReader::swap(AnyDataReader& rhs)
{
    holder_.swap(holder_);
    return *this;
}

template <typename T>
AnyDataReader& AnyDataReader::operator =(const DataReader<T>& rhs)
{
    holder_.reset(new detail::DRHolder<T>(rhs));
    return *this;
}

inline AnyDataReader& AnyDataReader::operator =(AnyDataReader rhs)
{
    if (this != &rhs)
        holder_ = rhs.holder_;
    return *this;
}

template <typename T>
dds::sub::DataReader<T> AnyDataReader::get()
{
    OMG_DDS_STATIC_ASSERT(::dds::topic::is_topic_type<T>::value == 1);
    detail::DRHolder<T>* h = dynamic_cast<detail::DRHolder<T>* >(holder_.get());
    if (h == 0)
    {
        throw dds::core::InvalidDowncastError("invalid type");
    }
    return h->get();
}

}
}
// End of implementation

#endif /* OSPL_DDS_SUB_ANYDATAREADER_HPP_ */
