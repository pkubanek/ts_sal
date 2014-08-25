package org.lsst.sal.qos.policy;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.EntityFactoryQosPolicy;
import org.omg.dds.core.policy.QosPolicy;
import org.omg.dds.core.policy.QosPolicy.Id;
import org.omg.dds.core.policy.UserDataQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableEntityFactoryQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableUserDataQosPolicy;
import org.omg.dds.domain.DomainParticipantQos;
import org.omg.dds.domain.modifiable.ModifiableDomainParticipantQos;

public class SALDomainParticipantQos implements
        ModifiableDomainParticipantQos {

    private DDS.DomainParticipantQos qos;

    public SALDomainParticipantQos(DDS.DomainParticipantQos theQos) {
        qos = theQos;
    }

    public DDS.DomainParticipantQos getQos() {
        return qos;
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY get(Id id) {
        throw new RuntimeException("Not implemented");
    }

    @Override
    public QosPolicy<?, ?> remove(Object key) {
        throw new RuntimeException("Not implemented");
    }

    @Override
    public void clear() {
        throw new RuntimeException("Not implemented");
    }

    @Override
    public ModifiableDomainParticipantQos modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY put(Id key, POLICY value) {
        throw new RuntimeException("Not implemented");
    }

    @Override
    public ModifiableDomainParticipantQos copyFrom(DomainParticipantQos other) {
        qos = ((SALDomainParticipantQos) other).getQos();
        return this;
    }

    @Override
    public DomainParticipantQos finishModification() {
        return this;
    }

    @Override
    public ModifiableDomainParticipantQos setUserData(UserDataQosPolicy userData) {
        return null;
    }

    @Override
    public ModifiableUserDataQosPolicy getUserData() {
        return null;
    }

    @Override
    public ModifiableDomainParticipantQos setEntityFactory(
            EntityFactoryQosPolicy entityFactory) {
        qos.entity_factory.autoenable_created_entities = entityFactory
                .isAutoEnableCreatedEntities();
        return this;
    }

    @Override
    public ModifiableEntityFactoryQosPolicy getEntityFactory() {
        return new SALEntityFactoryQosPolicy(qos.entity_factory);
    }

    public SALDomainParticipantQos clone() {
        return new SALDomainParticipantQos(qos);
    }
}
