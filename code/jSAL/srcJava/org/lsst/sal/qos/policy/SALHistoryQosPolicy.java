package org.lsst.sal.qos.policy;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.HistoryQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableHistoryQosPolicy;

public class SALHistoryQosPolicy implements ModifiableHistoryQosPolicy {

    private DDS.HistoryQosPolicy policy;

    public SALHistoryQosPolicy(DDS.HistoryQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.HistoryQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public Kind getKind() {
        if (DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS.equals(policy.kind)) {
            return Kind.KEEP_ALL;
        } else {
            return Kind.KEEP_LAST;
        }
    }

    @Override
    public int getDepth() {
        return policy.depth;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableHistoryQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableHistoryQosPolicy copyFrom(HistoryQosPolicy other) {
        policy.kind = ((SALHistoryQosPolicy) other).policy.kind;
        policy.depth = ((SALHistoryQosPolicy) other).policy.depth;
        return this;
    }

    @Override
    public HistoryQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableHistoryQosPolicy setKind(Kind kind) {
        if (kind.equals(Kind.KEEP_ALL)) {
            policy.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else {
            policy.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        }
        return this;
    }

    @Override
    public ModifiableHistoryQosPolicy setDepth(int depth) {
        policy.depth = depth;
        return this;
    }

    public SALHistoryQosPolicy clone() {
        return new SALHistoryQosPolicy(policy);
    }
}
