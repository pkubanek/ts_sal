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



public class ContentFilteredTopic_Expr2Test extends ContextTestSupport {
    protected String componentName = "dds";

    public void testFilter1() throws Exception {
        MockEndpoint result = getMockEndpoint("mock:result");
        result.expectedMessageCount(1);

        Object msg0 = TestUtil.getDDSMessage(0, "AA");
        template.sendBody("direct:start", msg0);

        Object msg1 = TestUtil.getDDSMessage(1, "BB");
        template.sendBody("direct:start", msg1);


        Object msg2 = TestUtil.getDDSMessage(2, "CC");
        template.sendBody("direct:start", msg2);

        Object msg3 = TestUtil.getDDSMessage(3, "DD");
        template.sendBody("direct:start", msg3);

        result.assertIsSatisfied(10000);
        int value1 = TestUtil.getId(result.getExchanges().get(0).getIn().getBody());
        assertTrue(value1 == 1);
    }

    protected CamelContext createCamelContext() throws Exception {
        CamelContext camelContext = super.createCamelContext();
        return camelContext;
    }

    protected RouteBuilder createRouteBuilder() throws Exception {
        return new RouteBuilder() {
            public void configure() throws Exception {
                // Chat.idl Filter expr: message = 'BB'
                String expr = "?contentFilter=message%20%3D%20%27BB%27";
                from("direct:start").to("dds:T2:5/Chat.ChatMessage" + expr);
                from("dds:T2:5/Chat.ChatMessage" + expr).to("mock:result");
            }
        };
    }
}
