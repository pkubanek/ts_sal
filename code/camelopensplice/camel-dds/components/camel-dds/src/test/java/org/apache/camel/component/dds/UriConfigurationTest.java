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

import junit.framework.TestCase;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.impl.DefaultCamelContext;

/**
 * @version $Revision: 142 $
 */
public class UriConfigurationTest extends TestCase {
    protected CamelContext context = new DefaultCamelContext();

    /*
    public void testPrivateChatConfiguration() throws Exception {
        Endpoint endpoint = context.getEndpoint("dds://camel-user@localhost:123/test-user@localhost?password=secret&serviceName=someCoolChat");
        assertTrue("Endpoint not an DdsEndpoint: " + endpoint, endpoint instanceof DdsEndpoint);
        DdsEndpoint ddsEndpoint = (DdsEndpoint) endpoint;


        assertEquals("localhost", ddsEndpoint.getHost());
        assertEquals(123, ddsEndpoint.getPort());
        assertEquals("camel-user", ddsEndpoint.getUser());
        assertEquals("test-user@localhost", ddsEndpoint.getParticipant());
        assertEquals("secret", ddsEndpoint.getPassword());
        assertEquals("someCoolChat", ddsEndpoint.getServiceName());
    }

    public void testGroupChatConfiguration() throws Exception {
        Endpoint endpoint = context.getEndpoint("dds://camel-user@im.google.com:123?room=cheese&password=secret&nickname=incognito");
        assertTrue("Endpoint not an DdsEndpoint: " + endpoint, endpoint instanceof DdsEndpoint);
        DdsEndpoint ddsEndpoint = (DdsEndpoint) endpoint;


        assertEquals("im.google.com", ddsEndpoint.getHost());
        assertEquals(123, ddsEndpoint.getPort());
        assertEquals("camel-user", ddsEndpoint.getUser());
        assertEquals("cheese", ddsEndpoint.getRoom());
        assertEquals("secret", ddsEndpoint.getPassword());
        assertEquals("incognito", ddsEndpoint.getNickname());
    }
    */

    public void testDdsConfiguration() throws Exception {
        //Endpoint endpoint =
        //    context.getEndpoint("dds://Chat.ChatMessage@Chat:5?HistoryQosPolicyKind=KEEP_ALL&HistoryQosPolicyDepth=15&LifespanQosPolicyDuration=50&contentFilter=height%3C1000%20AND%20x%3C23");
        Endpoint endpoint =
            context.getEndpoint("dds:T11:5/Chat.ChatMessage?HistoryKind=KEEP_ALL&HistoryDepth=15&LifespanDuration=50&contentFilter=height%3C1000%20AND%20x%3C23");
        assertTrue("Endpoint not an DdsEndpoint: " + endpoint, endpoint instanceof DdsEndpoint);
        DdsEndpoint ddsEndpoint = (DdsEndpoint) endpoint;

        assertEquals("T11", ddsEndpoint.getTopicName());
        assertEquals("5", ddsEndpoint.getDomainId());
        assertEquals("Chat.ChatMessage", ddsEndpoint.getDataclassName());
        assertEquals(DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS, ddsEndpoint.getHistoryKind());
        assertEquals(15, ddsEndpoint.getHistoryDepth());
        assertEquals(50.0, ddsEndpoint.getLifespanDuration());
        assertEquals("height<1000 AND x<23", ddsEndpoint.getContentFilter());
    }

    /*
    // Changes in default resource name may break
    // clients program assuming the default "Camel" resource name
    // so it is better to avoid changing it.
    public void testDefaultResource() throws Exception {
        Endpoint endpoint = context.getEndpoint("dds://camel-user@im.google.com?password=secret");
        assertTrue("Endpoint not an DdsEndpoint: " + endpoint, endpoint instanceof DdsEndpoint);
        DdsEndpoint ddsEndpoint = (DdsEndpoint) endpoint;

        assertEquals("Camel", ddsEndpoint.getResource());
    }
    */
}
