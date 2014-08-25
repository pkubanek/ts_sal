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

import java.util.HashMap;
import java.util.Map;

import DDS.NOT_ALIVE_DISPOSED_INSTANCE_STATE;
import DDS.SampleInfo;

import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.camel.impl.DefaultHeaderFilterStrategy;
import org.apache.camel.spi.HeaderFilterStrategy;

/**
 * A Strategy used to convert between a Camel {@link DdsExchange} and
 * {@link DdsMessage} to and from a DDS {@link Message}
 * 
 * @version $Revision: 243 $
 */
public class DdsBinding {

    private HeaderFilterStrategy headerFilterStrategy;

    public DdsBinding() {
        this.headerFilterStrategy = new DefaultHeaderFilterStrategy();
    }

    public DdsBinding(HeaderFilterStrategy headerFilterStrategy) {
        this.headerFilterStrategy = headerFilterStrategy;
    }

    /**
     * @param exchange
     * @return Object is the DDS message object wrapped in the exchange body
     */
    public Object extractBodyFromExchange(Exchange exchange) {
        return exchange.getIn().getBody();
    }

    public Object extractHeaderFromExchange(Exchange exchange, String key) {
        return exchange.getIn().getHeader(key);
    }

    /**
     * @param info
     * @return Map<String, Object> containing the exchange headers
     */
    public Map<String, Object> extractHeadersFromSampleInfo(SampleInfo info) {
        Map<String, Object> answer = new HashMap<String, Object>();
        answer.put("DDS_SAMPLE_INFO", info);
        if (info.instance_state == NOT_ALIVE_DISPOSED_INSTANCE_STATE.value) {
            if (info.valid_data) {
                answer.put("DDS_DISPOSE", DdsDisposeHeader.WRITEDISPOSE);
            } else {
                answer.put("DDS_DISPOSE", DdsDisposeHeader.DISPOSE);
            }
        }
        return answer;
    }

    public HeaderFilterStrategy getHeaderFilterStrategy () {
        return headerFilterStrategy;
    }
}
