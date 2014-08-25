package org.opensplice.demo.sal_SALTOPIC;
import java.util.Date;
import java.util.Random;
import org.omg.dds.core.Duration;
import org.omg.dds.core.event.InconsistentTopicEvent;
import org.omg.dds.core.policy.*;
import org.omg.dds.domain.*;
import org.omg.dds.topic.Topic;
import org.omg.dds.pub.*;
import org.omg.dds.topic.TopicQos;
import org.opensplice.demo.sal_SALTOPICType;
import sun.rmi.log.ReliableLog;

public class SALTOPICPublisher {
    public static void main(String args[]) throws Exception {
        Random generator=new Random();
        Date date=new Date();

        if (args.length < 4) {
            System.out.println("USAGE:\n\tSALTOPICPublisher <period ms> <iterations> <id> <name>");
            System.exit(1);
        }


        DomainParticipantFactory dpf =
                DomainParticipantFactory.getInstance();

        DomainParticipant dp = dpf.createParticipant(0);

        TopicQos tQos = new TopicQos(Reliability.Reliable());

        Topic<sal_SALTOPICType> topic = dp.createTopic("SALTOPICTopic", sal_SALTOPICType.class);

        Publisher pub = dp.createPublisher();

        DataWriterQos dwQos =
                new DataWriterQos(Reliability.Reliable(),
                                  Durability.Transient(),
                                  History.KeepLast(10));

        DataWriter<sal_SALTOPICType> writer =
                pub.createDataWriter(topic, dwQos);

        sal_SALTOPICType SALTOPIC = new sal_SALTOPICType();

	int j;
        int period  = Integer.parseInt(args[0]);
        int N = Integer.parseInt(args[1]);
        int id = Integer.parseInt(args[2]);
        String name = args[3];
        for (int i = 0; i < N; ++i) {
###SAL_DATA_SIM
            writer.write(SALTOPIC);
            System.out.println("Published " + i);

            try {
                Thread.sleep(period);
            } catch (InterruptedException e) { }
        }
    }
}
