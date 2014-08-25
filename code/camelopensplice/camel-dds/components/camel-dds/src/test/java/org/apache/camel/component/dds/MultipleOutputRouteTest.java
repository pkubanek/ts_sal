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


import org.apache.camel.CamelContext;
import org.apache.camel.ContextTestSupport;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.mock.MockEndpoint;



public class MultipleOutputRouteTest extends ContextTestSupport {
    protected String componentName = "dds";

    public void testRoute() throws Exception {
        MockEndpoint result1 = getMockEndpoint("mock:result1");
        result1.expectedMessageCount(15);
        MockEndpoint result2 = getMockEndpoint("mock:result2");
        result1.expectedMessageCount(15);

        for(int x = 0; x < 15; x++)
        {
           Object msg1 = TestUtil.getDDSMessage(x, x+"");
           template.sendBody("dds:T10:5/Chat.ChatMessage", msg1);
           template.sendBody("dds:T11:5/Chat.ChatMessage", msg1);
        }
        result1.assertIsSatisfied(5000);
        result2.assertIsSatisfied(5000);
    }

    protected CamelContext createCamelContext() throws Exception {
        CamelContext camelContext = super.createCamelContext();
        return camelContext;
    }

    protected RouteBuilder createRouteBuilder() throws Exception {
        return new RouteBuilder() {
            public void configure() throws Exception {
                from("dds:T10:5/Chat.ChatMessage").to("mock:result1");
                from("dds:T11:5/Chat.ChatMessage").to("mock:result2");
            }
        };
    }
}
