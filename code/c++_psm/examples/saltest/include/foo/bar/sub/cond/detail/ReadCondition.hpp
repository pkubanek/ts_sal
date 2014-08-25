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
#ifndef OSPL_DDS_SUB_COND_DETAIL_READCONDITION_HPP_
#define OSPL_DDS_SUB_COND_DETAIL_READCONDITION_HPP_

/**
 * @file dds/sub/cond/detail/ReadCondition.hpp
 */

// Implementation

#include <dds/core/ref_traits.hpp>
#include <org/opensplice/core/ConditionImpl.hpp>
#include <dds/sub/cond/detail/Executor.hpp>
#include <dds/sub/AnyDataReader.hpp>

namespace dds
{
namespace sub
{
namespace cond
{
namespace detail
{

class ReadCondition: public org::opensplice::core::ConditionImpl
{

public:
    ReadCondition(const dds::sub::AnyDataReader& adr,
                  const dds::sub::status::DataState& status) :
        adr_(adr), executor_(new TrivialExecutor()), status_(status)
    {
    }

    template<typename T, typename FUN>
    ReadCondition(const dds::sub::DataReader<T>& dr,
                  const dds::sub::status::DataState& status,
                  const FUN& functor) :
        adr_(dr), executor_(
            new ParametrizedExecutor<FUN, dds::sub::DataReader<T> >(
                functor, dr)), status_(status)
    {
    }

    ~ReadCondition()
    {
        delete executor_;
    }

    virtual void dispatch()
    {
        executor_->exec();
    }


    const dds::sub::status::DataState state_filter() const
    {
        return status_;
    }

    const AnyDataReader& data_reader() const
    {
        return adr_;
    }

private:
    dds::sub::AnyDataReader adr_;
    dds::sub::cond::detail::Executor* executor_;
    dds::sub::status::DataState status_;
};

}
}
}
}

// End of implementation

#endif /* OSPL_DDS_SUB_COND_DETAIL_READCONDITION_HPP_ */
