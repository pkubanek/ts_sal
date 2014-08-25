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
import org.omg.dds.core.policy.OwnershipStrengthQosPolicy;
import org.omg.dds.core.policy.QosPolicy;
import org.omg.dds.core.policy.QosPolicy.Id;
import org.omg.dds.core.policy.ReliabilityQosPolicy;
import org.omg.dds.core.policy.ResourceLimitsQosPolicy;
import org.omg.dds.core.policy.TransportPriorityQosPolicy;
import org.omg.dds.core.policy.TypeConsistencyEnforcementQosPolicy;
import org.omg.dds.core.policy.UserDataQosPolicy;
import org.omg.dds.core.policy.WriterDataLifecycleQosPolicy;
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
import org.omg.dds.core.policy.modifiable.ModifiableOwnershipStrengthQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableReliabilityQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableResourceLimitsQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableTransportPriorityQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableTypeConsistencyEnforcementQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableUserDataQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiableWriterDataLifecycleQosPolicy;
import org.omg.dds.pub.DataWriterQos;
import org.omg.dds.pub.modifiable.ModifiableDataWriterQos;
import org.omg.dds.topic.TopicQos;
import org.lsst.sal.qos.policy.SALDeadlineQosPolicy;
import org.lsst.sal.qos.policy.SALDestinationOrderQosPolicy;
import org.lsst.sal.qos.policy.SALDurabilityQosPolicy;
import org.lsst.sal.qos.policy.SALHistoryQosPolicy;
import org.lsst.sal.qos.policy.SALLatencyBudgetQosPolicy;
import org.lsst.sal.qos.policy.SALLifespanQosPolicy;
import org.lsst.sal.qos.policy.SALLivelinessQosPolicy;
import org.lsst.sal.qos.policy.SALOwnershipQosPolicy;
import org.lsst.sal.qos.policy.SALOwnershipStrengthQosPolicy;
import org.lsst.sal.qos.policy.SALReliabilityQosPolicy;
import org.lsst.sal.qos.policy.SALResourceLimitsQosPolicy;
import org.lsst.sal.qos.policy.SALTransportPriorityQosPolicy;

public class SALDataWriterQos implements ModifiableDataWriterQos {

    private DDS.DataWriterQos qos;
    private Bootstrap bootStrap;

    public SALDataWriterQos(DDS.DataWriterQos theqos,
            Bootstrap thebootStrap) {
        bootStrap = thebootStrap;
        qos = theqos;
    }

    public DDS.DataWriterQos getQos() {
        return qos;
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
    public ModifiableDataWriterQos modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return bootStrap;
    }

    @Override
    public ModifiableDurabilityQosPolicy getDurability() {
        return new SALDurabilityQosPolicy(qos.durability);
    }

    @Override
    public ModifiableDurabilityServiceQosPolicy getDurabilityService() {
        // return new
        // SALDurabilityServiceQosPolicy(qos.durabilityService);
        return null;
    }

    @Override
    public ModifiableDeadlineQosPolicy getDeadline() {
        return new SALDeadlineQosPolicy(qos.deadline);
    }

    @Override
    public ModifiableLatencyBudgetQosPolicy getLatencyBudget() {
        return new SALLatencyBudgetQosPolicy(qos.latency_budget);
    }

    @Override
    public ModifiableLivelinessQosPolicy getLiveliness() {
        return new SALLivelinessQosPolicy(qos.liveliness);
    }

    @Override
    public ModifiableReliabilityQosPolicy getReliability() {
        return new SALReliabilityQosPolicy(qos.reliability);
    }

    @Override
    public ModifiableDestinationOrderQosPolicy getDestinationOrder() {
        return new SALDestinationOrderQosPolicy(qos.destination_order);
    }

    @Override
    public ModifiableHistoryQosPolicy getHistory() {
        return new SALHistoryQosPolicy(qos.history);
    }

    @Override
    public ModifiableResourceLimitsQosPolicy getResourceLimits() {
        return new SALResourceLimitsQosPolicy(qos.resource_limits);
    }

    @Override
    public ModifiableTransportPriorityQosPolicy getTransportPriority() {
        return new SALTransportPriorityQosPolicy(qos.transport_priority);
    }

    @Override
    public ModifiableLifespanQosPolicy getLifespan() {
        return new SALLifespanQosPolicy(qos.lifespan);
    }

    @Override
    public ModifiableUserDataQosPolicy getUserData() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableOwnershipQosPolicy getOwnership() {
        return new SALOwnershipQosPolicy(qos.ownership);
    }

    @Override
    public ModifiableOwnershipStrengthQosPolicy getOwnershipStrength() {
        return new SALOwnershipStrengthQosPolicy(qos.ownership_strength);
    }

    @Override
    public ModifiableWriterDataLifecycleQosPolicy getWriterDataLifecycle() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDataRepresentationQosPolicy getRepresentation() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableTypeConsistencyEnforcementQosPolicy getTypeConsistency() {
        // TODO Auto-generated method stub
        return null;
    }

    public SALDataWriterQos clone() {
        return new SALDataWriterQos(qos, bootStrap);
    }

    @Override
    public <POLICY extends QosPolicy<POLICY, ?>> POLICY put(Id key, POLICY value) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDataWriterQos copyFrom(DataWriterQos other) {
        bootStrap = (other.getBootstrap());
        qos = ((SALDataWriterQos) other).qos;
        return this;
    }

    @Override
    public DataWriterQos finishModification() {
        return this;
    }

    @Override
    public ModifiableDataWriterQos setDurability(DurabilityQosPolicy durability) {
        qos.durability = ((SALDurabilityQosPolicy) durability)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setDurabilityService(
            DurabilityServiceQosPolicy durabilityService) {
        // qos.durability_service =
        // ((SALDurabilityServiceQosPolicy) durabilityService)
        // .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setDeadline(DeadlineQosPolicy deadline) {
        qos.deadline = ((SALDeadlineQosPolicy) deadline).getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setLatencyBudget(
            LatencyBudgetQosPolicy latencyBudget) {
        qos.latency_budget = ((SALLatencyBudgetQosPolicy) latencyBudget)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setLiveliness(LivelinessQosPolicy liveliness) {
        // policy.liveliness =
        // ((SALLivelynessQosPolicy)liveliness).getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setReliability(
            ReliabilityQosPolicy reliability) {
        qos.reliability = ((SALReliabilityQosPolicy) reliability)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setDestinationOrder(
            DestinationOrderQosPolicy destinationOrder) {
        qos.destination_order = ((SALDestinationOrderQosPolicy) destinationOrder)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setHistory(HistoryQosPolicy history) {
        qos.history = ((SALHistoryQosPolicy) history).getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setResourceLimits(
            ResourceLimitsQosPolicy resourceLimits) {
        qos.resource_limits = ((SALResourceLimitsQosPolicy) resourceLimits)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setTransportPriority(
            TransportPriorityQosPolicy transportPriority) {
        qos.transport_priority = ((SALTransportPriorityQosPolicy) transportPriority)
                .getPpolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setLifespan(LifespanQosPolicy lifespan) {
        qos.lifespan = ((SALLifespanQosPolicy) lifespan).getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setUserData(UserDataQosPolicy userData) {
        // TODO Auto-generated method stub
        return this;
    }

    @Override
    public ModifiableDataWriterQos setOwnership(OwnershipQosPolicy ownership) {
        qos.ownership = ((SALOwnershipQosPolicy) ownership).getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setOwnershipStrength(
            OwnershipStrengthQosPolicy ownershipStrength) {
        qos.ownership_strength = ((SALOwnershipStrengthQosPolicy) ownershipStrength)
                .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setWriterDataLifecycle(
            WriterDataLifecycleQosPolicy writerDataLifecycle) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDataWriterQos setRepresentation(
            DataRepresentationQosPolicy representation) {
        // policy.presentation = ((SALPresentationQosPolicy)
        // presentation)
        // .getPolicy();
        return this;
    }

    @Override
    public ModifiableDataWriterQos setTypeConsistency(
            TypeConsistencyEnforcementQosPolicy typeConsistency) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ModifiableDataWriterQos copyFrom(TopicQos src) {
        // TODO Auto-generated method stub
        return null;
    }
}
