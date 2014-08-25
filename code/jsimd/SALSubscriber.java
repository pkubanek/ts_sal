package org.opensplice.demo.sal_SALTOPIC;


import org.omg.dds.core.event.*;
import org.omg.dds.core.policy.Durability;
import org.omg.dds.core.policy.History;
import org.omg.dds.core.policy.Reliability;
import org.omg.dds.domain.*;
import org.omg.dds.topic.Topic;
import org.omg.dds.sub.*;
import org.opensplice.demo.sal_SALTOPICType;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Arrays;

import static java.lang.System.out;


public class SALTOPICSubscriber {
    public static void main(String args[]) {

        DomainParticipantFactory dpf =
                DomainParticipantFactory.getInstance();

        // Join the domain with ID = 0
        DomainParticipant dp = dpf.createParticipant(0);

        // Create the SALTOPICTopic
        Topic<sal_SALTOPICType> topic =
                dp.createTopic("SALTOPICTopic", sal_SALTOPICType.class);

        // Create a Subscriber on the default Partition
        Subscriber sub = dp.createSubscriber();

        // Get the default DataRederQos
        DataReaderQos tdrQos = sub.getDefaultDataReaderQos();

        // Override the defaults to reflect your needs...
        DataReaderQos drQos =
                tdrQos.with(
                        Reliability.Reliable(),
                        History.KeepLast(10),
                        Durability.Transient()
                );

        // Create a DataReader
        DataReader<sal_SALTOPICType> dr = sub.createDataReader(topic, drQos);

        // Add a listener
        dr.setListener(
                new SimpleDataReaderListener<sal_SALTOPICType>() {
                    @Override
                    public void onDataAvailable(DataAvailableEvent<sal_SALTOPICType> e) {
                        DataReader<sal_SALTOPICType> dr = e.getSource();
                        List<Sample<sal_SALTOPICType>> data = new LinkedList<Sample<sal_SALTOPICType>>();
                        dr.read(data);
                        System.out.println("------------------------------------------");
                        Iterator<Sample<sal_SALTOPICType>> iterator = data.iterator();
                        while (iterator.hasNext()) {
                            sal_SALTOPICType s = iterator.next().getData();
###SAL_DATA_PRINT
                        }
                        System.out.println("------------------------------------------");
                    }
                }
        );

        try {
            Thread.currentThread().join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
