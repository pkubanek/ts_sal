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
package camel.dds.examples.camel_dds_jms_displayapp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.jms.ConnectionFactory;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.camel.CamelContext;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.impl.DefaultCamelContext;

/**
 * An example class for demonstrating some of the basics behind Camel. This
 * example sends some text messages on to a JMS Queue, consumes them and
 * persists them to disk
 * 
 * @version $Revision: 663796 $
 */
public final class CamelJmsExample {

    private CamelJmsExample() {        
    }
    
    public static void main(String args[]) throws Exception {
        CamelContext context = new DefaultCamelContext();

        // Set up the ActiveMQ JMS Components
        ConnectionFactory connectionFactory = new ActiveMQConnectionFactory("tcp://localhost:61616");
        
        // Note we can explicity name the component
        context.addComponent("test-jms", JmsComponent.jmsComponentAutoAcknowledge(connectionFactory));

        // Add some configuration by hand ...
        context.addRoutes(new RouteBuilder() {

            public void configure() {
                from("test-jms:topic:object_location.topic").process(new Processor() {

                    public void process(Exchange e) {
                        System.out.println("Received exchange: " + e.getIn());
                        System.out.println("Received message: " + e.getIn().getBody());
                    }
                });
            }
        });

        // Now everything is set up - lets start the context
        context.start();

        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        
        // END SNIPPET: e5
        while(true) {
            try {
                br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }            
            break;
        }
        
        // Stop the Camel context.
        try {
           context.stop();
        } catch (Exception e) {
           System.err.println("Cannot stop server: " + e.getMessage());
        }
    }
}
