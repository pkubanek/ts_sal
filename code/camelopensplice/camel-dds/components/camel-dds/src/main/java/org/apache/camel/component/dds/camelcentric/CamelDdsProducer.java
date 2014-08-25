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
import CamelDDS.CamelMessageDataWriter;
import CamelDDS.CamelMessageDataWriterHelper;
import DDS.DataWriter;
import DDS.HANDLE_NIL;
import DDS.Publisher;
import DDS.Topic;

import org.apache.camel.Exchange;
import org.apache.camel.RuntimeExchangeException;
import org.apache.camel.component.dds.DdsErrorHandler;
import org.apache.camel.component.dds.DdsException;
import org.apache.camel.impl.DefaultProducer;

public class CamelDdsProducer extends DefaultProducer {

    private DataWriter writer;
    private CamelDdsEndpoint endpoint;
    private CamelMessageDataWriter dataWriter;

    public CamelDdsProducer(CamelDdsEndpoint endpoint) throws DdsException {
        super(endpoint);
        this.endpoint = endpoint;
        Topic topic = endpoint.getTopic();
        Publisher publisher = endpoint.getPublisher();
        writer = publisher.create_datawriter(topic,
                endpoint.getDdsDataWriterQosHolder().value,
                null,
                DDS.ANY_STATUS.value);
        DdsErrorHandler.checkHandle(writer, "Create DataWriter on " + topic.get_name());
        dataWriter = CamelMessageDataWriterHelper.narrow(writer);
    }

    public void process(Exchange exchange) throws DdsException {
        try {
            CamelMessage msg = endpoint.getCamelBinding().createCamelMessageFromExchange(endpoint.getTarget(), exchange);
            int status = dataWriter.write(msg, HANDLE_NIL.value);
            DdsErrorHandler.checkStatus(status, "Writing message");
        } catch (DdsException e) {
            throw e;
        } catch (Exception e) {
            throw new RuntimeExchangeException(e.getMessage(), exchange, e);
        }
    }

    @Override
    protected void doStop() throws Exception {
        if (writer != null) {
            endpoint.deleteDataWriter(writer);
        }
        super.doStop();
    }

    DataWriter getDataWriter() {
        return this.writer;
    }
}
