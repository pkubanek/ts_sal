#ifndef ORG_OPENSPLICE_SUB_QOS_SUBSCRIBER_QOS_IMPL_HPP_
#define ORG_OPENSPLICE_SUB_QOS_SUBSCRIBER_QOS_IMPL_HPP_

#include <dds/core/policy/CorePolicy.hpp>
#include <org/opensplice/core/config.hpp>

namespace org
{
namespace opensplice
{
namespace sub
{
namespace qos
{

class OSPL_ISOCPP_IMPL_API SubscriberQosImpl
{
public:
    SubscriberQosImpl();

    SubscriberQosImpl(
        dds::core::policy::Presentation presentation,
        dds::core::policy::Partition partition,
        dds::core::policy::GroupData group_data,
        dds::core::policy::EntityFactory entity_factory);

    ~SubscriberQosImpl();

    void policy(const dds::core::policy::Presentation& presentation);
    void policy(const dds::core::policy::Partition& partition);
    void policy(const dds::core::policy::GroupData& grout_data);
    void policy(const dds::core::policy::EntityFactory& entity_factory);

    template <typename P> const P& policy() const;
    template <typename P> P& policy();

private:
    dds::core::policy::Presentation presentation_;
    dds::core::policy::Partition partition_;
    dds::core::policy::GroupData group_data_;
    dds::core::policy::EntityFactory entity_factory_;
};

}
}
}
}

#endif /* ORG_OPENSPLICE_SUB_QOS_SUBSCRIBER_QOS_IMPL_HPP_ */
