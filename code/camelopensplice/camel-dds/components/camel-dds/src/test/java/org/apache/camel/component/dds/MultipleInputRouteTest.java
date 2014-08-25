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



public class MultipleInputRouteTest extends ContextTestSupport {
    protected String componentName = "dds";

    public void testRoute() throws Exception {
        MockEndpoint result = getMockEndpoint("mock:result");
        result.expectedMessageCount(30);
        int ctr = 0;
        int ktr = 20;

        for(int x = 0; x < 15; x++)
        {
           Object msg1 = TestUtil.getDDSMessage(ctr, ctr+"");
           template.sendBody("direct:start1", msg1);
           ctr++;
           Object msg2 = TestUtil.getDDSMessage(ktr, ktr+"");
           template.sendBody("direct:start2", msg2);
           ktr++;
        }
        result.assertIsSatisfied(10000);
    }

    protected CamelContext createCamelContext() throws Exception {
        CamelContext camelContext = super.createCamelContext();
        return camelContext;
    }

    protected RouteBuilder createRouteBuilder() throws Exception {
        return new RouteBuilder() {
            public void configure() throws Exception {
                from("direct:start1").to("dds:T9:5/Chat.ChatMessage");
                from("direct:start2").to("dds:T9:5/Chat.ChatMessage");
                from("dds:T9:5/Chat.ChatMessage").to("mock:result");

            }
        };
    }
}
