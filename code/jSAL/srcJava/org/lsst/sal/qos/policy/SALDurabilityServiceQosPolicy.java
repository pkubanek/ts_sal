package org.lsst.sal.qos.policy;

import java.util.concurrent.TimeUnit;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.Duration;
import org.omg.dds.core.modifiable.ModifiableDuration;
import org.omg.dds.core.policy.DurabilityServiceQosPolicy;
import org.omg.dds.core.policy.HistoryQosPolicy.Kind;
import org.omg.dds.core.policy.modifiable.ModifiableDurabilityServiceQosPolicy;
import org.lsst.sal.SALDuration;

public class SALDurabilityServiceQosPolicy implements
        ModifiableDurabilityServiceQosPolicy {
    /** Default serialVersionUID. */
    private static final long serialVersionUID = 1L;
    private DDS.DurabilityServiceQosPolicy policy;

    public SALDurabilityServiceQosPolicy(
            DDS.DurabilityServiceQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.DurabilityServiceQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy copyFrom(
            DurabilityServiceQosPolicy other) {
        policy = ((SALDurabilityServiceQosPolicy) other).getPolicy();
        return this;
    }

    @Override
    public DurabilityServiceQosPolicy finishModification() {
        return this;
    }

    public SALDurabilityServiceQosPolicy clone() {
        return new SALDurabilityServiceQosPolicy(policy);
    }

    @Override
    public Kind getHistoryKind() {
        if (DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS
                .equals(policy.history_kind)) {
            return Kind.KEEP_ALL;
        }
        return Kind.KEEP_LAST;
    }

    @Override
    public int getHistoryDepth() {
        return policy.history_depth;
    }

    @Override
    public int getMaxSamples() {
        return policy.max_samples;
    }

    @Override
    public int getMaxInstances() {
        return policy.max_instances;
    }

    @Override
    public int getMaxSamplesPerInstance() {
        return policy.max_samples_per_instance;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setServiceCleanupDelay(
            Duration serviceCleanupDelay) {
        policy.service_cleanup_delay = ((SALDuration) serviceCleanupDelay)
                .getDuration();
        return this;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setServiceCleanupDelay(
            long serviceCleanupDelay, TimeUnit unit) {
        policy.service_cleanup_delay = new SALDuration(
                serviceCleanupDelay, unit).getDuration();
        return this;
    }

    @Override
    public ModifiableDuration getServiceCleanupDelay() {
        return new SALDuration(policy.service_cleanup_delay);
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setHistoryKind(Kind historyKind) {
        if (Kind.KEEP_ALL.equals(historyKind)) {
            policy.history_kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else {
            policy.history_kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        }
        return this;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setHistoryDepth(int historyDepth) {
        policy.history_depth = historyDepth;
        return this;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setMaxSamples(int maxSamples) {
        policy.max_samples = maxSamples;
        return this;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setMaxInstances(int maxInstances) {
        policy.max_instances = maxInstances;
        return this;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy setMaxSamplesPerInstance(
            int maxSamplesPerInstance) {
        policy.max_samples_per_instance = maxSamplesPerInstance;
        return this;
    }

}
