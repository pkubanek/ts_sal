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
import CamelDDS.CamelMessageDataReader;
import CamelDDS.CamelMessageDataReaderHelper;
import CamelDDS.CamelMessageSeqHolder;
import DDS.ANY_INSTANCE_STATE;
import DDS.ANY_SAMPLE_STATE;
import DDS.ANY_STATUS;
import DDS.ANY_VIEW_STATE;
import DDS.ContentFilteredTopic;
import DDS.DataReader;
import DDS.DataReaderListener;
import DDS.DataReaderQosHolder;
import DDS.LENGTH_UNLIMITED;
import DDS.LivelinessChangedStatus;
import DDS.RequestedDeadlineMissedStatus;
import DDS.RequestedIncompatibleQosStatus;
import DDS.SampleInfoSeqHolder;
import DDS.SampleLostStatus;
import DDS.SampleRejectedStatus;
import DDS.Subscriber;
import DDS.SubscriptionMatchedStatus;
import DDS.Topic;
import org.apache.camel.Endpoint;
import org.apache.camel.Processor;
import org.apache.camel.component.dds.DdsErrorHandler;
import org.apache.camel.component.dds.DdsException;
import org.apache.camel.impl.DefaultConsumer;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import static org.apache.camel.util.ObjectHelper.wrapRuntimeCamelException;

public class CamelDdsConsumer extends DefaultConsumer implements
        DataReaderListener {
    private static final transient Log LOG = LogFactory
            .getLog(CamelDdsProducer.class);

    private CamelDdsEndpoint endpoint;
    private DataReader reader;
    private SampleInfoSeqHolder infoSequence = new SampleInfoSeqHolder();
    private CamelMessageDataReader dataReader;

    public CamelDdsConsumer(Endpoint endpoint, Processor processor) {
        super(endpoint, processor);
        this.endpoint = (CamelDdsEndpoint) endpoint;
    }

    @Override
    protected void doStart() throws Exception {
        Topic topic = endpoint.getTopic();
        ContentFilteredTopic cfTopic = endpoint.getContentFilteredTopic();
        Subscriber subscriber = endpoint.getSubscriber();
        DataReaderQosHolder drQosHolder = endpoint.getDdsDataReaderQosHolder();
        if (cfTopic != null) {
            reader = subscriber.create_datareader(cfTopic, drQosHolder.value,
                    this /* listener */, ANY_STATUS.value);
            DdsErrorHandler.checkHandle(reader, "Create DataReader on "
                    + cfTopic.get_name());
        } else {
            reader = subscriber.create_datareader(topic, drQosHolder.value,
                    this /* listener */, ANY_STATUS.value);
            DdsErrorHandler.checkHandle(reader, "Create DataReader on "
                    + topic.get_name());
        }
        dataReader = CamelMessageDataReaderHelper.narrow(reader);
        super.doStart();
    }
    
    @Override
    protected void doStop() throws Exception {
        if (reader != null) {
            endpoint.deleteDataReader(reader);
        }
        super.doStop();
    }

    public void on_data_available(DataReader arg0) {
        try {
            CamelMessageSeqHolder seq = new CamelMessageSeqHolder();
            int status = dataReader.take(seq, infoSequence,
                    LENGTH_UNLIMITED.value, ANY_SAMPLE_STATE.value,
                    ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
            DdsErrorHandler.checkStatus(status, "Taking data");
            for (int i = 0; i < seq.value.length; i++) {
                createExchange(seq.value[i]);
            }
            dataReader.return_loan(seq, infoSequence);
        } catch (DdsException e) {
            LOG.error("Reader take failed", e);
        } catch (Exception e) {
            LOG.error("Create exchange failed", e);
        }
    }

    private void createExchange(Object msg) throws Exception {
        CamelDdsExchange exchange = endpoint.createExchange((CamelMessage) msg);
        getProcessor().process(exchange);
        if (exchange.isFailed()) {
            if (exchange.getException() != null) {
                throw wrapRuntimeCamelException(exchange.getException());
            }
        }
    }

    public void on_liveliness_changed(DataReader arg0,
            LivelinessChangedStatus arg1) {
        // No implementation.
    }

    public void on_requested_deadline_missed(DataReader arg0,
            RequestedDeadlineMissedStatus arg1) {
        // No implementation.
    }

    public void on_requested_incompatible_qos(DataReader arg0,
            RequestedIncompatibleQosStatus arg1) {
        // No implementation.
    }

    public void on_sample_lost(DataReader arg0, SampleLostStatus arg1) {
        // No implementation.
    }

    public void on_sample_rejected(DataReader arg0, SampleRejectedStatus arg1) {
        // No implementation.
    }

    public void on_subscription_matched(DataReader arg0,
            SubscriptionMatchedStatus arg1) {
        // No implementation.
    }
}
