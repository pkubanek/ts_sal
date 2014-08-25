package org.lsst.sal.qos.policy;

import java.util.concurrent.TimeUnit;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.Duration;
import org.omg.dds.core.modifiable.ModifiableDuration;
import org.omg.dds.core.policy.DeadlineQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDeadlineQosPolicy;
import org.lsst.sal.SALDuration;

public class SALDeadlineQosPolicy implements ModifiableDeadlineQosPolicy {

    private DDS.DeadlineQosPolicy policy;

    public SALDeadlineQosPolicy(DDS.DeadlineQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.DeadlineQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableDeadlineQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableDeadlineQosPolicy copyFrom(DeadlineQosPolicy other) {
        policy = ((SALDeadlineQosPolicy) other).getPolicy();
        return this;
    }

    @Override
    public DeadlineQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableDeadlineQosPolicy setPeriod(Duration period) {
        policy.period = ((SALDuration) period).getDuration();
        return this;
    }

    @Override
    public ModifiableDeadlineQosPolicy setPeriod(long period, TimeUnit unit) {
        SALDuration duration = new SALDuration(period, unit);
        policy.period = duration.getDuration();
        return this;
    }

    @Override
    public ModifiableDuration getPeriod() {
        return new SALDuration(policy.period);
    }

    public SALDeadlineQosPolicy clone() {
        return new SALDeadlineQosPolicy(policy);
    }

}
