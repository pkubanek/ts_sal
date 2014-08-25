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

import CamelDDS.CamelMessage;
import CamelDDS.CamelMessageTypeSupport;
import DDS.DataReader;
import DDS.DataWriter;
import DDS.Topic;
import org.apache.camel.Consumer;
import org.apache.camel.Processor;
import org.apache.camel.Producer;
import org.apache.camel.component.dds.DdsComponent;
import org.apache.camel.component.dds.DdsEndpoint;
import org.apache.camel.component.dds.DdsErrorHandler;
import org.apache.camel.component.dds.DdsException;

public class CamelDdsEndpoint extends DdsEndpoint {

    private CamelDdsBinding binding;

    private String target;

    public CamelDdsEndpoint(String endpointUri) {
        super(endpointUri);
    }

    public CamelDdsEndpoint(String uri, DdsComponent component) {
        super(uri, component);
    }

    /**
     * return Topic
     * 
     */
    protected Topic findOrCreateTopic() throws DdsException {
        // Get topic type name
        CamelMessageTypeSupport typeSupport = new CamelMessageTypeSupport();
        String typeName = typeSupport.get_type_name();
        int status = typeSupport.register_type(participant, typeName);
        DdsErrorHandler.checkStatus(status, "Register type");

        DDS.Duration_t duration = new DDS.Duration_t();
        duration.nanosec = 0;
        duration.sec = 0;
        ddsTopic = this.participant.find_topic(topicName, duration);
        if (ddsTopic == null) {
            ddsTopic = participant.create_topic(topicName, typeName,
            // defQos.value,
                    this.topicQosHolder.value, null, // listener
                    DDS.ANY_STATUS.value);
        }
        DdsErrorHandler.checkHandle(ddsTopic, "Find or create topic "
                + topicName);

        String target = null;
        if (contentFilteredTopic == null) {
            target = getTarget();
            if (target != null) {
                int hash = target.hashCode();
                String filteredTopic = "target" + hash + topicName;
                String filter = "target = '" + target + "'";
                contentFilteredTopic = participant.create_contentfilteredtopic(
                        filteredTopic, ddsTopic, filter, new String[0]);
                DdsErrorHandler.checkHandle(contentFilteredTopic,
                        "Create content filtered topic");
            }
        }
        return ddsTopic;
    }

    public Producer createProducer() throws DdsException {
        createSupportingDdsEntities();
        CamelDdsProducer producer = new CamelDdsProducer(this);
        producers.add(producer);
        return producer;
    }

    public Consumer createConsumer(Processor processor)
        throws DdsException {
        this.createSupportingDdsEntities();
        CamelDdsConsumer consumer = new CamelDdsConsumer(this, processor);
        consumers.add(consumer);
        return consumer;
    }

    public CamelDdsBinding getCamelBinding() {
        if (binding == null) {
            binding = new CamelDdsBinding();
        }
        return binding;
    }

    /**
     * 
     * @param writer
     */
    protected void deleteDataWriter(DataWriter writer) throws DdsException {
        super.deleteDataWriter(writer);
    }

    /**
     * 
     * @param reader
     */
    protected void deleteDataReader(DataReader reader) throws DdsException {
        super.deleteDataReader(reader);
    }

    public CamelDdsExchange createExchange(CamelMessage messageInstance) {
        return new CamelDdsExchange(getCamelContext(), getExchangePattern(),
                getCamelBinding(), messageInstance);
    }

    public void setTarget(String tgt) {
        target = tgt;
    }

    public String getTarget() {
        return target;
    }
}
