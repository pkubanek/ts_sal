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
#ifndef OSPL_DDS_SUB_COND_DETAIL_QUERYCONDITION_HPP_
#define OSPL_DDS_SUB_COND_DETAIL_QUERYCONDITION_HPP_

/**
 * @file dds/sub/cond/detail/QueryCondition.hpp
 */

// Implementation

#include <dds/sub/cond/detail/ReadCondition.hpp>
#include <dds/sub/Query.hpp>

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

namespace dds
{
namespace sub
{
namespace cond
{
namespace detail
{
class QueryCondition;
// For Implementor to fills in

}
}
}
}

class dds::sub::cond::detail::QueryCondition: public ReadCondition
{
public:
    typedef std::vector<std::string>::iterator iterator;
    typedef std::vector<std::string>::const_iterator const_iterator;
public:
    QueryCondition(
        const dds::sub::Query& query,
        const dds::sub::status::DataState& data_state)
        : ReadCondition(query.data_reader(), data_state),
          query_(query)
    { }

    virtual ~QueryCondition() { }

    void expression(const std::string& expr)
    {
        query_.expression(expr);
    }

    const std::string& expression()
    {
        return query_.expression();
    }


    /**
     * Provides the begin iterator to the parameter list.
     */
    iterator begin()
    {
        return query_.begin();
    }

    /**
     * The end iterator to the parameter list.
     */
    iterator end()
    {
        return query_.end();
    }

    const_iterator begin() const
    {
        return query_.begin();
    }

    /**
     * The end iterator to the parameter list.
     */
    const_iterator end() const
    {
        return query_.end();
    }

    template<typename FWIterator>
    void parameters(const FWIterator& begin, const FWIterator end)
    {
        query_.parameters(begin, end);
    }

    void add_parameter(const std::string& param)
    {
        query_.add_parameter(param);
    }

    dds::core::size_type parameters_length() const
    {
        return query_.parameters_length();
    }

    const AnyDataReader& data_reader()
    {
        return query_.data_reader();
    }

private:
    dds::sub::Query query_;
};

#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

// End of implementation

#endif /* OSPL_DDS_SUB_COND_DETAIL_QUERYCONDITION_HPP_ */
