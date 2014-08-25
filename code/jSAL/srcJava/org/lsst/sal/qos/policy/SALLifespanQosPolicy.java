package org.lsst.sal.qos.policy;

import java.util.concurrent.TimeUnit;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.Duration;
import org.omg.dds.core.modifiable.ModifiableDuration;
import org.omg.dds.core.policy.LifespanQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableLifespanQosPolicy;
import org.lsst.sal.SALDuration;

public class SALLifespanQosPolicy implements ModifiableLifespanQosPolicy {

    /** The default serialVersionUID. */
    private static final long serialVersionUID = 1L;
    private DDS.LifespanQosPolicy policy;

    public SALLifespanQosPolicy(DDS.LifespanQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.LifespanQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableLifespanQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableLifespanQosPolicy copyFrom(LifespanQosPolicy other) {
        policy = ((SALLifespanQosPolicy) other).getPolicy();
        return this;
    }

    @Override
    public LifespanQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableLifespanQosPolicy setDuration(Duration duration) {
        policy.duration = ((SALDuration) duration).getDuration();
        return this;
    }

    @Override
    public ModifiableLifespanQosPolicy setDuration(long duration, TimeUnit unit) {
        policy.duration = new SALDuration(duration, unit).getDuration();
        return this;
    }

    @Override
    public ModifiableDuration getDuration() {
        return new SALDuration(policy.duration);
    }

    public SALLifespanQosPolicy clone() {
        return new SALLifespanQosPolicy(policy);
    }
}
