package org.lsst.sal.qos;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.EntityFactoryQosPolicy;
import org.omg.dds.core.policy.GroupDataQosPolicy;
import org.omg.dds.core.policy.PartitionQosPolicy;
import org.omg.dds.core.policy.PresentationQosPolicy;
import org.omg.dds.core.policy.QosPolicy;
import org.omg.dds.core.policy.QosPolicy.Id;
import org.omg.dds.core.policy.modifiable.ModifiableEntityFactoryQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableGroupDataQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiablePartitionQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiablePresentationQosPolicy;
import org.omg.dds.pub.PublisherQos;
import org.omg.dds.pub.modifiable.ModifiablePublisherQos;
import org.lsst.sal.qos.policy.SALGroupDataPolicy;
import org.lsst.sal.qos.policy.SALPartitionQosPolicy;
import org.lsst.sal.qos.policy.SALPresentationQosPolicy;

public class SALPublisherQos implements ModifiablePublisherQos {

    private DDS.PublisherQos qos;
    private Bootstrap bootStrap;

    public DDS.PublisherQos getQos() {
        return qos;
    }

    public SALPublisherQos(DDS.PublisherQos theqos,
            Bootstrap thebootStrap) {
        bootStrap = thebootStrap;
        qos = theqos;

    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY get(Id id) {
        throw new RuntimeException("Not yet implemented");
    }

    @Override
    public QosPolicy<?, ?> remove(Object key) {
        throw new RuntimeException("Not yet implemented");
    }

    @Override
    public void clear() {
        throw new RuntimeException("Not yet implemented");
    }

    @Override
    public ModifiablePublisherQos modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return bootStrap;
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY put(Id key, POLICY value) {
        throw new RuntimeException("Not yet implemented");
    }

    @Override
    public ModifiablePublisherQos copyFrom(PublisherQos other) {
        bootStrap = (other.getBootstrap());
        qos = ((SALPublisherQos) other).qos;
        return this;
    }

    @Override
    public PublisherQos finishModification() {
        return this;
    }

    @Override
    public ModifiablePublisherQos setPresentation(
            PresentationQosPolicy presentation) {
        qos.presentation = ((SALPresentationQosPolicy) presentation)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiablePresentationQosPolicy getPresentation() {
        return new SALPresentationQosPolicy(qos.presentation);
    }

    @Override
    public ModifiablePublisherQos setPartition(PartitionQosPolicy partition) {
        qos.partition.name = ((SALPartitionQosPolicy) partition)
                .getPartition();
        return this;
    }

    @Override
    public ModifiablePartitionQosPolicy getPartition() {
        return new SALPartitionQosPolicy(qos.partition.name);
    }

    @Override
    public ModifiablePublisherQos setGroupData(GroupDataQosPolicy groupData) {
        qos.group_data = ((SALGroupDataPolicy) groupData).getPolicy();
        return this;
    }

    @Override
    public ModifiableGroupDataQosPolicy getGroupData() {
        return new SALGroupDataPolicy(qos.group_data);
    }

    @Override
    public ModifiablePublisherQos setEntityFactory(
            EntityFactoryQosPolicy entityFactory) {
        throw new RuntimeException("Not yet implemented");
    }

    @Override
    public ModifiableEntityFactoryQosPolicy getEntityFactory() {
        throw new RuntimeException("Not yet implemented");
    }

    public SALPublisherQos clone() {
        return new SALPublisherQos(qos, bootStrap);
    }
}
