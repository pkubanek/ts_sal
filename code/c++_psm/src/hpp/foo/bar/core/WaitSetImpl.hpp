#ifndef ORG_OPENSPLICE_CORE_WAITSETIMPL_HPP_
#define ORG_OPENSPLICE_CORE_WAITSETIMPL_HPP_

#include <vector>
#include <iostream>

#include <dds/core/Duration.hpp>
#include <dds/core/cond/Condition.hpp>


namespace org { namespace opensplice { namespace core {

    class WaitSetImpl {
     /**
     * @todo OSPL-1739 Implement
     */
    public:
        typedef std::vector<dds::core::cond::Condition> ConditionSeqType;

    public:
        WaitSetImpl() { }
        ~WaitSetImpl() { }
        void close();

    public:
        const ConditionSeqType wait(const dds::core::Duration& timeout) {
            return ConditionSeqType();
        }

        const ConditionSeqType wait() {
            return ConditionSeqType();
        }

        ConditionSeqType& wait(ConditionSeqType& triggered,
                               const dds::core::Duration& timeout) {
            return triggered;
        }

        ConditionSeqType& wait(ConditionSeqType& triggered) {
            return triggered;
        }

    public:
        void dispatch() {

        }

        void dispatch(const dds::core::Duration& timeout) {

        }

    public:
        WaitSetImpl& attach_condition(const dds::core::cond::Condition& cond) {
            return *this;
        }

        bool detach_condition(const dds::core::cond::Condition& cond) {
            return false;
        }

        const ConditionSeqType conditions() {
            return ConditionSeqType();
        }

        ConditionSeqType& conditions(ConditionSeqType& conds) const {
            return conds;
        }
    };

} } }

#endif /* ORG_OPENSPLICE_CORE_WAITSETIMPL_HPP_ */
