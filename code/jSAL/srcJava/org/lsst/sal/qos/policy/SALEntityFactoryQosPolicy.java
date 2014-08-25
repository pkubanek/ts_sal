package org.lsst.sal.qos.policy;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.EntityFactoryQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableEntityFactoryQosPolicy;

public class SALEntityFactoryQosPolicy implements
        ModifiableEntityFactoryQosPolicy {

    private DDS.EntityFactoryQosPolicy policy;

    public SALEntityFactoryQosPolicy(DDS.EntityFactoryQosPolicy thepolicy) {
        policy = thepolicy;
    }

    public DDS.EntityFactoryQosPolicy getPolicy() {
        return policy;
    }

    @Override
    public boolean isAutoEnableCreatedEntities() {
        return policy.autoenable_created_entities;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        throw new RuntimeException("Not implemented");
    }

    @Override
    public ModifiableEntityFactoryQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableEntityFactoryQosPolicy copyFrom(
            EntityFactoryQosPolicy other) {
        policy = ((SALEntityFactoryQosPolicy) other).policy;
        return this;
    }

    @Override
    public EntityFactoryQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiableEntityFactoryQosPolicy setAutoEnableCreatedEntities(
            boolean autoEnableCreatedEntities) {
        policy.autoenable_created_entities = autoEnableCreatedEntities;
        return this;
    }

    public SALEntityFactoryQosPolicy clone() {
        return new SALEntityFactoryQosPolicy(policy);
    }
}
