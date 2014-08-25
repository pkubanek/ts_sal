/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.apache.camel.component.dds;

import java.util.Arrays;
import java.util.Vector;

//import junit.framework.TestCase;

import org.apache.camel.CamelContext;
import org.apache.camel.Consumer;
import org.apache.camel.ContextTestSupport;
import org.apache.camel.Endpoint;
import org.apache.camel.builder.RouteBuilder;

import DDS.DataReader;
import DDS.DataReaderQosHolder;
import DDS.Subscriber;
import DDS.SubscriberQosHolder;
import DDS.Topic;
import DDS.TopicQosHolder;

/**
 * @version $Revision: 232 $
 */
//public class QoSSettingTest extends TestCase {
public class QoSSettingTest extends ContextTestSupport {
    protected CamelContext context;
    private String ddsUriTopicDataReader = "dds:TestQosTopic:5/TestQosTopic.TestQos?HistoryKindD=KEEP_ALL&HistoryDepthR=100&HistoryDepthW=1&HistoryKindT=KEEP_LAST&LifespanDuration=0.001&DeadlinePeriod=1.5&GroupData=MySubscriberGroupData&Partition=MyDRPartition1%25MyDRPartition2";

    public void testDdsConsumerQosSettings() throws Exception {
        Endpoint endpoint = (Endpoint) context.getEndpoint(ddsUriTopicDataReader);
        assertTrue("Endpoint not an DdsEndpoint: " + endpoint, endpoint instanceof DdsEndpoint);
        DdsEndpoint ddsEndpoint = (DdsEndpoint) endpoint;
        Subscriber subscriber = ddsEndpoint.getSubscriber();

        Vector producers = ddsEndpoint.getProducers();
        // There should be no producers for this test case.
        assertTrue("Producers found for endpoint " + endpoint, producers.size() == 0);

        Vector consumers = ddsEndpoint.getConsumers();
        // There should only be one consumer for this test case.
        assertTrue("No consumers found for endpoint " + endpoint, consumers.size() == 1);

        // The consumer should be a DdsConsumer.
        Consumer consumer = (Consumer) consumers.get(0);
        assertTrue("Consumer not an DdsConsumer: " + consumer, consumer instanceof DdsConsumer);
        DdsConsumer ddsConsumer = (DdsConsumer) consumer;

        // Get the QoS settings from the Consumer to make sure they are correct.
        DataReader reader = ddsConsumer.getDataReader();
        DataReaderQosHolder holder = new DataReaderQosHolder();
        DataReaderQosHolder defHolder = new DataReaderQosHolder();
        subscriber.get_default_datareader_qos(defHolder);
        int status = reader.get_qos(holder);

        // Get the QoS settings for the topic.
        Topic topic = ddsEndpoint.getDdsTopic();
        DDS.TopicQosHolder topicHolder = new TopicQosHolder();
        topic.get_qos(topicHolder);

        // Get the QoS settings for the subscriber.
        DDS.SubscriberQosHolder subHolder = new SubscriberQosHolder();
        subscriber.get_qos(subHolder);

        // Check the topic QoS settings.
        assertTrue("Topic's deadline period seconds mismatch" + topic, topicHolder.value.deadline.period.sec == 1);
        assertTrue("Topic's deadline period nanoseconds mismatch" + topic, topicHolder.value.deadline.period.nanosec == 500000000);
        assertTrue("Topic's history kind mismatch" + topic, topicHolder.value.history.kind == DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS);
        assertTrue("Topic's lifespan duration sec mismatch " + topic, topicHolder.value.lifespan.duration.sec == 0);
        assertTrue("Topic's lifespan duration nanosec mismatch " + topic, topicHolder.value.lifespan.duration.nanosec == 1000000);

        // Check the subscriber QoS settings.
        assertTrue("Subscriber's group data mismatch" + subscriber, Arrays.equals(subHolder.value.group_data.value, "MySubscriberGroupData".getBytes()));
        assertTrue("Subscriber's partition mismatch" + subscriber, Arrays.equals(subHolder.value.partition.name, "MyDRPartition1%MyDRPartition2".split("%")));

        // Check some default QoS settings.
        assertTrue("Reader's latency budget seconds mismatch" + reader, holder.value.latency_budget.duration.sec == defHolder.value.latency_budget.duration.sec);
        assertTrue("Reader's latency budget nanoseconds mismatch" + reader, holder.value.latency_budget.duration.nanosec == defHolder.value.latency_budget.duration.nanosec);
        assertTrue("Reader's durability kind mismatch" + reader, holder.value.durability.kind == defHolder.value.durability.kind);

        // Check the explicit QoS settings.
        assertTrue("Reader's deadline period seconds mismatch" + reader, holder.value.deadline.period.sec == 1);
        assertTrue("Reader's deadline period nanoseconds mismatch" + reader, holder.value.deadline.period.nanosec == 500000000);
        assertTrue("Reader's history kind mismatch" + reader, holder.value.history.kind == DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS);
        assertTrue("Reader's history depth mismatch " + reader, holder.value.history.depth == 100);
        // Lifespan only applies to topics and data writers.
        //assertTrue("Reader's lifespan duration sec mismatch " + reader, holder.value.lifespan.duration.sec == 10);
        //assertTrue("Reader's lifespan duration nanosec mismatch " + reader, holder.value.lifespan.duration.nanosec == 5000000);

        // Check the settings on the endpoint.
        assertEquals("TestQosTopic", ddsEndpoint.getTopicName());
        assertEquals("5", ddsEndpoint.getDomainId());
        assertEquals("TestQosTopic.TestQos", ddsEndpoint.getDataclassName());
        // For this endpoint the general history has not been set - only specifically
        // for topic and then specifically for data reader/writer.
        assertEquals(null, ddsEndpoint.getHistoryKind());
        assertEquals(0, ddsEndpoint.getHistoryDepth());
        // Check the lifespan duration from the previous topic data reader URI since the lifespan was set there.
        assertEquals(0.001, ddsEndpoint.getLifespanDuration());
    }

    protected CamelContext createCamelContext() throws Exception {
        this.context = super.createCamelContext();
        return this.context;
    }

    protected RouteBuilder createRouteBuilder() throws Exception {
        return new RouteBuilder() {
            public void configure() throws Exception {
                // The writer route and second test case has been removed from 
                // this class as it relied on Camel constructing the route in 
                // a specific order (the reader part first to create the Topic, 
                // then the writer part to create a producer). Camel doesn't 
                // specify an order in which the route is produced so the test
                // failed when the component was updated to Camel 2.4.0. The 
                // second part of the test was removed as invalid.
                from(ddsUriTopicDataReader).to("mock:result");
            }
        };
    }
}
