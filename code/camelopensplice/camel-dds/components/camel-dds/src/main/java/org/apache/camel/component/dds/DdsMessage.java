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

import java.util.Map;
import DDS.SampleInfo;
import org.apache.camel.impl.DefaultMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Represents a {@link org.apache.camel.Message} for working with DDS
 *
 * @version $Revision:520964 $
 */
public class DdsMessage extends DefaultMessage {
    private static final transient Log LOG = LogFactory.getLog(DdsMessage.class);

    private Object ddsMessageInstance;
    private SampleInfo ddsSampleInfo;

    public DdsMessage() {

    }

    public DdsMessage(Object ddsMessage, SampleInfo si) {
        ddsMessageInstance = ddsMessage;
        ddsSampleInfo = si;
    }

    public DdsMessage(Object ddsMessage) {
        this.ddsMessageInstance = ddsMessage;
    }

    @Override
    public DdsExchange getExchange() {
        return (DdsExchange) super.getExchange();
    }

    /**
     * Returns the underlying DDS message
     */
    public Object getDdsMessage() {
        return ddsMessageInstance;
    }

    public void setDdsMessage(Object ddsMessage) {
        ddsMessageInstance = ddsMessage;
    }

    /**
     * The body is the ddsMessage Object
     */
    @Override
    protected Object createBody() {
        return ddsMessageInstance;
    }

    /**
     *
     * @param map is the empty header map to populate
     */
    @Override
    protected void populateInitialHeaders(Map<String, Object> map) {
        if (ddsSampleInfo != null) {
            map.putAll(getExchange().getBinding().extractHeadersFromSampleInfo(ddsSampleInfo));
        }
    }
    
    @Override
    public String toString() {
        return "DdsMessage: " + getBody();
    }
    
    public Object getBody() {
        if (LOG.isTraceEnabled()) {
            LOG.trace("getBody called");
        }
        return super.getBody();
    }
    
    @SuppressWarnings({"unchecked" })
    public <T> T getBody(Class<T> type) {
        if (LOG.isTraceEnabled()) {
            LOG.trace("getBody called for type " + type);
        }
        return super.getBody(type);
    }
}
