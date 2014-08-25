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

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import junit.framework.Assert;
import junit.framework.TestCase;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.impl.DefaultCamelContext;
import org.apache.camel.impl.ProducerCache;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import DDS.SampleInfo;



public class DDSMessageHeaderTest extends TestCase {
    private static final transient Log LOG = LogFactory.getLog(DDSMessageHeaderTest.class);
    protected DdsExchange receivedExchange;
    protected CamelContext container = new DefaultCamelContext();
    protected CountDownLatch latch = new CountDownLatch(1);
    protected Endpoint endpoint;
    protected ProducerCache client = new ProducerCache(this, container);


    public void testSampleInfoMessageHeader() throws Exception {
            final Object msg = TestUtil.getDDSMessage(1, "HeaderTest");
            client.send(endpoint, new Processor() {
                public void process(Exchange exchange) {
                    exchange.getIn().setBody(msg);
                }
            });
            assertReceivedValidExchange();
    }

    protected void assertReceivedValidExchange() throws Exception {
        boolean received = latch.await(5, TimeUnit.SECONDS);
        assertTrue("Did not receive the message!", received);

        assertNotNull(receivedExchange);
        DdsMessage receivedMessage = (DdsMessage) receivedExchange.getIn();

        Assert.assertEquals("Did not expect dispose header", null, receivedMessage.getHeader("DDS_DISPOSE"));
        SampleInfo info = (SampleInfo)receivedMessage.getHeader("DDS_SAMPLE_INFO");
        assertNotNull(info);
        assertTrue(info.valid_data);

        Object body = receivedMessage.getBody();
        assertNotNull(body);
    }

    public void testWriteDisposeMessageHeader() throws Exception {
        final Object msg = TestUtil.getDDSMessage(1, "HeaderTest");
        client.send(endpoint, new Processor() {
            public void process(Exchange exchange) {
                exchange.getIn().setBody(msg);
                exchange.getIn().setHeader("DDS_DISPOSE", DdsDisposeHeader.WRITEDISPOSE);
                exchange.getIn().setHeader("DDS_SAMPLE_INFO", new SampleInfo());
            }
        });
        assertWriteDisposeExchange();
}

    protected void assertWriteDisposeExchange() throws Exception {
        boolean received = latch.await(5, TimeUnit.SECONDS);
        assertTrue("Did not receive the message!", received);

        assertNotNull(receivedExchange);
        DdsMessage receivedMessage = (DdsMessage) receivedExchange.getIn();

        DdsDisposeHeader header = (DdsDisposeHeader)receivedMessage.getHeader("DDS_DISPOSE");
        assertTrue(header == DdsDisposeHeader.WRITEDISPOSE);

        SampleInfo info = (SampleInfo)receivedMessage.getHeader("DDS_SAMPLE_INFO");
        assertNotNull(info);
        assertTrue(info.valid_data);

        Object body = receivedMessage.getBody();
        assertNotNull(body);
    }


    public void testDisposeMessageHeader() throws Exception {
        final Object msg = TestUtil.getDDSMessage(1, "HeaderTest");
        client.send(endpoint, new Processor() {
            public void process(Exchange exchange) {
                exchange.getIn().setBody(msg);
                exchange.getIn().setHeader("DDS_DISPOSE", DdsDisposeHeader.DISPOSE);
                exchange.getIn().setHeader("DDS_SAMPLE_INFO", new SampleInfo());
            }
        });
        assertDisposeExchange();
}

    protected void assertDisposeExchange() throws Exception {
        boolean received = latch.await(5, TimeUnit.SECONDS);
        assertTrue("Did not receive the message!", received);

        assertNotNull(receivedExchange);
        DdsMessage receivedMessage = (DdsMessage) receivedExchange.getIn();

        DdsDisposeHeader header = (DdsDisposeHeader)receivedMessage.getHeader("DDS_DISPOSE");
        assertTrue(header == DdsDisposeHeader.DISPOSE);

        SampleInfo info = (SampleInfo)receivedMessage.getHeader("DDS_SAMPLE_INFO");
        assertNotNull(info);
        assertFalse(info.valid_data);

        Object body = receivedMessage.getBody();
        assertNotNull(body);
    }

    @Override
    protected void setUp() throws Exception {
        final String uri1 = "dds:Topic1:5/Chat.ChatMessage";
        endpoint = container.getEndpoint(uri1);
        assertNotNull("No endpoint found!", endpoint);

        // lets add some routes
        container.addRoutes(new RouteBuilder() {
            public void configure() {
                from(uri1).process(new Processor() {
                    public void process(Exchange e) {
                        LOG.info("Received exchange: " + e);
                        receivedExchange = (DdsExchange) e;
                        latch.countDown();
                    }
                });
            }
        });
        container.start();
    }






    @Override
    protected void tearDown() throws Exception {
        client.stop();
        container.stop();
    }
}
