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

import java.util.Collection;
import java.util.Map;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.component.dds.camelcentric.CamelDdsEndpoint;
import org.apache.camel.impl.DefaultComponent;
import org.apache.camel.impl.DefaultHeaderFilterStrategy;
import org.apache.camel.spi.HeaderFilterStrategy;

/**
 * @version $Revision:520964 $
 */
public class DdsComponent extends DefaultComponent implements
        HeaderFilterStrategy {

    private HeaderFilterStrategy headerFilterStrategy = new DefaultHeaderFilterStrategy();

    public DdsComponent() {
    }

    public DdsComponent(CamelContext context) {
        super(context);
    }

    /**
     * Static builder method
     */
    public static DdsComponent ddsComponent() {
        return new DdsComponent();
    }

    /**
     * A factory method allowing derived components to create a new endpoint
     * from the given URI, remaining path and optional parameters
     *
     * @param uri the full URI of the endpoint
     * @param remaining the remaining part of the URI without the query
     *                parameters or component prefix
     * @param parameters the optional parameters passed in
     * @return a newly created endpoint or null if the endpoint cannot be
     *         created based on the inputs
     */
    protected Endpoint createEndpoint(String uri,
            String remaining, Map<String, Object> parameters) throws Exception {
        // Parse the remaining part of the URI which should have the topic name,
        // the domain, and the data class name, e.g., Chat:5/Chat.ChatMessage.
        String[] splitStrings = remaining.split("/");
        DdsEndpoint endpoint = null;
        String split[] = splitStrings[0].split(":");
        String topicName = split[0];
        String domainName = split[1];
        String dataclassName = null;
        if (splitStrings.length == 1) {
            endpoint = new CamelDdsEndpoint(uri, this);
        } else {
            endpoint = new DdsEndpoint(uri, this);
            dataclassName = splitStrings[1];
            endpoint.setDataclassName(dataclassName);
        }
        endpoint.setTopic(topicName);
        endpoint.setDomainId(domainName);
        endpoint.setParameters(parameters);
        endpoint.initialize();
        return endpoint;
    }

    public HeaderFilterStrategy getHeaderFilterStrategy() {
        return headerFilterStrategy;
    }

    public void setHeaderFilterStrategy(HeaderFilterStrategy strategy) {
        headerFilterStrategy = strategy;
    }

    /**
     * Stop method called by <code>ServiceSupport</code> class when the
     * CamelContext is stopped. Should clean up all DDS entities.
     */
    protected void doStop() throws Exception {
        Collection<Endpoint> endpoints = getCamelContext().getEndpoints();
        DdsEndpoint ddsendpoint = null;
        for (Endpoint ep : endpoints) {
            if (ep instanceof DdsEndpoint) {
                ddsendpoint = (DdsEndpoint) ep;
                ddsendpoint.clean();
            }
        }
    }

    @Override
    public boolean applyFilterToCamelHeaders(String headerName,
            Object headerValue, Exchange exchange) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean applyFilterToExternalHeaders(String headerName,
            Object headerValue, Exchange exchange) {
        // TODO Auto-generated method stub
        return false;
    }
}
