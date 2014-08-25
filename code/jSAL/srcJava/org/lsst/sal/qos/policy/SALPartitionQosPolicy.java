package org.lsst.sal.qos.policy;

import java.util.ArrayList;
import java.util.Collection;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.policy.PartitionQosPolicy;
import org.omg.dds.core.policy.modifiable.ModifiablePartitionQosPolicy;

public class SALPartitionQosPolicy implements
        ModifiablePartitionQosPolicy {

    private Collection<String> name = new ArrayList<String>();

    public String[] getPartition() {
        return (String[]) name.toArray();
    }

    public SALPartitionQosPolicy() {
    }

    public SALPartitionQosPolicy(String[] partition) {
        for (int i = 0; i < partition.length; i++) {
            name.add(partition[i]);
        }
    }

    @Override
    public ModifiablePartitionQosPolicy copyFrom(PartitionQosPolicy other) {
        name.clear();
        name.addAll(other.getName());
        return this;
    }

    @Override
    public PartitionQosPolicy finishModification() {
        return this;
    }

    @Override
    public ModifiablePartitionQosPolicy setName(Collection<String> name) {
        name.clear();
        name.addAll(name);
        return this;
    }

    public SALPartitionQosPolicy clone() {
        SALPartitionQosPolicy theclone = new SALPartitionQosPolicy();
        theclone.setName(name);
        return theclone;
    }

    @Override
    public org.omg.dds.core.policy.QosPolicy.Id getId() {
        return null;
    }

    @Override
    public ModifiablePartitionQosPolicy modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public Collection<String> getName() {
        return name;
    }

}
