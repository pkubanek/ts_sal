package org.lsst.sal.qos.policy;

import java.util.concurrent.TimeUnit;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.Duration;
import org.omg.dds.core.modifiable.ModifiableDuration;
import org.omg.dds.core.policy.LatencyBudgetQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableLatencyBudgetQosPolicy;
import org.lsst.sal.SALDuration;

public class SALLatencyBudgetQosPolicy implements
        ModifiableLatencyBudgetQosPolicy {

    private DDS.LatencyBudgetQosPolicy policy;

    public SALLatencyBudgetQosPolicy(DDS.LatencyBudgetQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.LatencyBudgetQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy copyFrom(
            LatencyBudgetQosPolicy other) {
        policy = ((SALLatencyBudgetQosPolicy) other).getPolicy();
        return this;
    }

    @Override
    public LatencyBudgetQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy setDuration(Duration duration) {
        policy.duration = ((SALDuration) duration).getDuration();
        return this;
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy setDuration(long duration,
            TimeUnit unit) {
        SALDuration theduration = new SALDuration(duration,
                unit);
        policy.duration = theduration.getDuration();
        return this;
    }

    @Override
    public ModifiableDuration getDuration() {
        return new SALDuration(policy.duration);
    }

    public SALLatencyBudgetQosPolicy clone() {
        return new SALLatencyBudgetQosPolicy(policy);
    }
}
