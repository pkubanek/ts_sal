package org.lsst.sal.qos.policy;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.OwnershipQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableOwnershipQosPolicy;

public class SALOwnershipQosPolicy implements
        ModifiableOwnershipQosPolicy {
    /** The default serialVersionUID. */
    private static final long serialVersionUID = 1L;
    private DDS.OwnershipQosPolicy policy;

    public SALOwnershipQosPolicy(DDS.OwnershipQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.OwnershipQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public Kind getKind() {
        if (DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS
                .equals(policy.kind)) {
            return Kind.EXCLUSIVE;
        }
        return Kind.SHARED;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableOwnershipQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableOwnershipQosPolicy copyFrom(OwnershipQosPolicy other) {
        policy.kind = ((SALOwnershipQosPolicy) other).getPolicy().kind;
        return this;
    }

    @Override
    public OwnershipQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableOwnershipQosPolicy setKind(Kind kind) {
        if (Kind.EXCLUSIVE.equals(kind)) {
            policy.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            policy.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        }
        return this;
    }

    public SALOwnershipQosPolicy clone() {
        return new SALOwnershipQosPolicy(policy);
    }
}
