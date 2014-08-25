package org.lsst.sal.qos;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.DataRepresentationQosPolicy;
import org.omg.dds.core.policy.DeadlineQosPolicy;
import org.omg.dds.core.policy.DestinationOrderQosPolicy;
import org.omg.dds.core.policy.DurabilityQosPolicy;
import org.omg.dds.core.policy.DurabilityServiceQosPolicy;
import org.omg.dds.core.policy.HistoryQosPolicy;
import org.omg.dds.core.policy.LatencyBudgetQosPolicy;
import org.omg.dds.core.policy.LifespanQosPolicy;
import org.omg.dds.core.policy.LivelinessQosPolicy;
import org.omg.dds.core.policy.OwnershipQosPolicy;
import org.omg.dds.core.policy.QosPolicy;
import org.omg.dds.core.policy.QosPolicy.Id;
import org.omg.dds.core.policy.ReliabilityQosPolicy;
import org.omg.dds.core.policy.ResourceLimitsQosPolicy;
import org.omg.dds.core.policy.TopicDataQosPolicy;
import org.omg.dds.core.policy.TransportPriorityQosPolicy;
import org.omg.dds.core.policy.TypeConsistencyEnforcementQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDataRepresentationQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDeadlineQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDestinationOrderQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDurabilityQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableDurabilityServiceQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableHistoryQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableLatencyBudgetQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableLifespanQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableLivelinessQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableOwnershipQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableReliabilityQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableResourceLimitsQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableTopicDataQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableTransportPriorityQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableTypeConsistencyEnforcementQosPolicy;
import org.omg.dds.topic.TopicQos;
import org.omg.dds.topic.modifiable.ModifiableTopicQos;
import org.lsst.sal.qos.policy.SALDeadlineQosPolicy;
import org.lsst.sal.qos.policy.SALDurabilityQosPolicy;
import org.lsst.sal.qos.policy.SALLatencyBudgetQosPolicy;
import org.lsst.sal.qos.policy.SALReliabilityQosPolicy;
import org.lsst.sal.qos.policy.SALTopicDataQosPolicy;

public class SALTopicQos implements ModifiableTopicQos {

    private DDS.TopicQos qos;

    public SALTopicQos() {
    }

    public SALTopicQos(final DDS.TopicQos theqos) {
        qos = theqos;
    }

    public DDS.TopicQos getQos() {
        return qos;
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY get(Id id) {
        return null;
    }

    @Override
    public QosPolicy<?, ?> remove(Object key) {
        return null;
    }

    @Override
    public void clear() {
    }

    @Override
    public ModifiableTopicQos modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY put(Id key, POLICY value) {
        return null;
    }

    @Override
    public ModifiableTopicQos copyFrom(TopicQos other) {
        qos = ((SALTopicQos) other).getQos();
        return this;
    }

    @Override
    public TopicQos finishModification() {
        return this;
    }

    @Override
    public ModifiableTopicQos setTopicData(TopicDataQosPolicy topicData) {
        qos.topic_data = ((SALTopicDataQosPolicy) topicData).getPolicy();
        return this;
    }

    @Override
    public ModifiableTopicDataQosPolicy getTopicData() {
        return new SALTopicDataQosPolicy(qos.topic_data);
    }

    @Override
    public ModifiableTopicQos setDurability(DurabilityQosPolicy durability) {
        qos.durability = ((SALDurabilityQosPolicy) durability)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDurabilityQosPolicy getDurability() {
        return new SALDurabilityQosPolicy(qos.durability);
    }

    @Override
    public ModifiableTopicQos setDurabilityService(
            DurabilityServiceQosPolicy durabilityService) {
        return null;
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy getDurabilityService() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setDeadline(DeadlineQosPolicy deadline) {
        qos.deadline = ((SALDeadlineQosPolicy) deadline).getPolicy();
        return this;
    }

    @Override
    public ModifiableDeadlineQosPolicy getDeadline() {
        return new SALDeadlineQosPolicy(qos.deadline);
    }

    @Override
    public ModifiableTopicQos setLatencyBudget(
            LatencyBudgetQosPolicy latencyBudget) {
        qos.latency_budget = ((SALLatencyBudgetQosPolicy) latencyBudget)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy getLatencyBudget() {
        return new SALLatencyBudgetQosPolicy(qos.latency_budget);
    }

    @Override
    public ModifiableTopicQos setLiveliness(LivelinessQosPolicy liveliness) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableLivelinessQosPolicy getLiveliness() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setReliability(ReliabilityQosPolicy reliability) {
        qos.reliability = ((SALReliabilityQosPolicy) reliability)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableReliabilityQosPolicy getReliability() {
        return new SALReliabilityQosPolicy(qos.reliability);
    }

    @Override
    public ModifiableTopicQos setDestinationOrder(
            DestinationOrderQosPolicy destinationOrder) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDestinationOrderQosPolicy getDestinationOrder() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setHistory(HistoryQosPolicy history) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableHistoryQosPolicy getHistory() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setResourceLimits(
            ResourceLimitsQosPolicy resourceLimits) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableResourceLimitsQosPolicy getResourceLimits() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setTransportPriority(
            TransportPriorityQosPolicy transportPriority) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTransportPriorityQosPolicy getTransportPriority() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setLifespan(LifespanQosPolicy lifespan) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableLifespanQosPolicy getLifespan() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setOwnership(OwnershipQosPolicy ownership) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableOwnershipQosPolicy getOwnership() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDataRepresentationQosPolicy getRepresentation() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setRepresentation(
            DataRepresentationQosPolicy representation) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTypeConsistencyEnforcementQosPolicy getTypeConsistency() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTopicQos setTypeConsistency(
            TypeConsistencyEnforcementQosPolicy typeConsistency) {
        // TODO Auto-generated method stub
        return null;
    }

    public SALTopicQos clone() {
        return null;
    }

}
