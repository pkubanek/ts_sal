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

package org.apache.camel.component.dds.camelcentric;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.mail.util.ByteArrayDataSource;

import org.apache.camel.CamelContext;
import org.apache.camel.ContextTestSupport;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.dds.DDSMessageHeaderTest;
import org.apache.camel.impl.DefaultCamelContext;
import org.apache.camel.impl.ProducerCache;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;



public class MessageAttachmentTest extends ContextTestSupport {
    private static final transient Log LOG = LogFactory.getLog(DDSMessageHeaderTest.class);
    protected CamelDdsExchange receivedExchange;
    protected CamelContext container = new DefaultCamelContext();
    protected CountDownLatch latch = new CountDownLatch(1);
    protected Endpoint endpoint;
    protected ProducerCache client = new ProducerCache(this, container);
    DataHandler attachment;
    DataSource ds;
    Map<String, DataHandler> attachments;
    public void testMessageHeader() throws Exception {
            final String msg = "TestMessage";
            String attachmentStr = new String("Attachment");
            ByteArrayDataSource s = new ByteArrayDataSource(attachmentStr.getBytes(), "text");
            attachment = new DataHandler(s);
            attachments = new HashMap<String, DataHandler>();
            attachments.put("FILE", attachment);
            client.send(endpoint, new Processor() {
                public void process(Exchange exchange) {
                    exchange.getIn().setBody(msg);
                    exchange.getIn().setHeader("HEADER1", "DDS_HEADER1");
                    exchange.getIn().setAttachments(attachments);
                }
            });
            assertReceivedValidExchange();
    }

    protected void assertReceivedValidExchange() throws Exception {
        boolean received = latch.await(5, TimeUnit.SECONDS);
        assertTrue("Did not receive the message!", received);

        assertNotNull(receivedExchange);
        CamelDdsMessage receivedMessage = (CamelDdsMessage) receivedExchange.getIn();

        String hdr = (String)receivedMessage.getHeader("HEADER1");
        assertNotNull(hdr);
        assertTrue(hdr.equals("DDS_HEADER1"));

        String body = (String)receivedMessage.getBody();
        assertNotNull(body);
        assertTrue(body.equals("TestMessage"));

        DataHandler handler = receivedMessage.getAttachment("FILE");
        byte[] result = new byte[100];
        InputStream is = handler.getInputStream();
        is.read(result);
        String str = new String(result);
        assertTrue(str.trim().equals("Attachment"));

        assertTrue(handler.getContentType().equals("text"));
    }

    @Override
    protected void setUp() throws Exception {
        final String uri1 = "dds:MessageAttachment:5";
        endpoint = container.getEndpoint(uri1);
        assertNotNull("No endpoint found!", endpoint);

        // lets add some routes
        container.addRoutes(new RouteBuilder() {
            public void configure() {
                from(uri1).process(new Processor() {
                    public void process(Exchange e) {
                        LOG.info("Received exchange: " + e);
                        receivedExchange = (CamelDdsExchange) e;
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

