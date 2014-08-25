#ifndef ORG_OPENSPLICE_CORE_STATUSCONDITIONIMPL_HPP_
#define ORG_OPENSPLICE_CORE_STATUSCONDITIONIMPL_HPP_

#include <dds/core/status/State.hpp>
#include <dds/core/Entity.hpp>
#include <org/opensplice/core/ConditionImpl.hpp>

namespace org { namespace opensplice { namespace core {

    class StatusConditionImpl : public org::opensplice::core::ConditionImpl {
    public:
        StatusConditionImpl(const dds::core::Entity& entity) : entity_(entity) { }

        void enabled_statuses(const dds::core::status::StatusMask& status) {
            mask_ = status;
        }

        const dds::core::status::StatusMask enabled_statuses() const {
            return mask_;
        }

        dds::core::Entity entity() const {
            return entity_;
        }
    private:
        dds::core::Entity entity_;
        dds::core::status::StatusMask mask_;
    };

} } }

#endif  /* ORG_OPENSPLICE_CORE_STATUSCONDITIONIMPL_HPP_ */
