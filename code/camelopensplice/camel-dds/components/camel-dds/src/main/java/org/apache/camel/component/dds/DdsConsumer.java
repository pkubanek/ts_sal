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

import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import DDS.ANY_INSTANCE_STATE;
import DDS.ANY_SAMPLE_STATE;
import DDS.ANY_STATUS;
import DDS.ANY_VIEW_STATE;
import DDS.ContentFilteredTopic;
import DDS.DataReader;
import DDS.DataReaderListener;
import DDS.DataReaderQos;
import DDS.DataReaderQosHolder;
import DDS.LENGTH_UNLIMITED;
import DDS.LivelinessChangedStatus;
import DDS.RequestedDeadlineMissedStatus;
import DDS.RequestedIncompatibleQosStatus;
import DDS.SampleInfo;
import DDS.SampleInfoSeqHolder;
import DDS.SampleLostStatus;
import DDS.SampleRejectedStatus;
import DDS.Subscriber;
import DDS.SubscriptionMatchedStatus;
import DDS.Topic;
import DDS.TopicQosHolder;

import org.apache.camel.Processor;
import org.apache.camel.impl.DefaultConsumer;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import static org.apache.camel.util.ObjectHelper.wrapRuntimeCamelException;

/**
 * A {@link org.apache.camel.Consumer Consumer} which listens to DDS packets
 * 
 * @version $Revision: 243 $
 */
public class DdsConsumer extends DefaultConsumer implements
        DataReaderListener {
    private static final transient Log LOG = LogFactory
            .getLog(DdsConsumer.class);

    /** Suffix appended to topic type name for data reader. */
    private static final String READER_CLASS_SUFFIX = "DataReaderImpl";

    /** Suffix appended to topic type name for data sequence. */
    private static final String SEQUENCE_CLASS_SUFFIX = "SeqHolder";

    /** Field name of the SeqHolder class. */
    private static final String SEQ_VAL_FIELD = "value";

    /** Data reader method used to take data. */
    private static final String TAKE_METHOD = "take";

    /** Data reader method used to return data loan. */
    private static final String RETURN_METHOD = "return_loan";

    /** Name for data reader QoS holder class. */
    private static final String DR_QOS_HOLDER_NAME = "DDS.DataReaderQosHolder";

    /** field variable of the SeqHolder class. */
    private Field valueField;

    /** Instance of SequenceHolder class. **/
    private Object sequenceObj;

    private final DdsEndpoint endpoint;

    /** Name of class to be distributed on DDS topic. */
    private String dataClassName;

    /** DDS data reader. */
    private DataReader reader;

    /** DDS topic data type class. */
    private Class dataClass;

    /** DDS data reader implementation class. */
    private Class readerClass;

    private Class sequenceClass;

    /** DDS data reader take method */
    private Method takeMethod;

    /** DDS data reader return method */
    private Method returnMethod;

    /** DDS sample info sequence, used to read data. */
    private SampleInfoSeqHolder infoSequence = new SampleInfoSeqHolder();

    public DdsConsumer(DdsEndpoint endpoint, Processor processor) {
        super(endpoint, processor);
        this.endpoint = endpoint;
    }

    /**
     * Start method.
     */
    @Override
    protected void doStart() throws Exception {
        try {
            dataClassName = endpoint.getDataclassName();

            // Cache topic data type class
            dataClass = Class.forName(dataClassName);

            // Cache data reader implementation class
            String className = dataClassName + READER_CLASS_SUFFIX;
            readerClass = Class.forName(className);

            // Create data sequence
            className = dataClassName + SEQUENCE_CLASS_SUFFIX;
            sequenceClass = Class.forName(className);
            sequenceObj = sequenceClass.newInstance();
            valueField = sequenceClass.getDeclaredField(SEQ_VAL_FIELD);

            // Cache reference to data reader take method
            Class[] arrTakeMethodParams = {sequenceClass,
                SampleInfoSeqHolder.class, int.class, int.class, int.class,
                int.class};
            takeMethod = readerClass
                    .getMethod(TAKE_METHOD, arrTakeMethodParams);

            // Cache reference to data reader return method
            Class[] arrReturnMethodParams = {sequenceClass,
                SampleInfoSeqHolder.class};
            returnMethod = readerClass.getMethod(RETURN_METHOD,
                    arrReturnMethodParams);

            // Get the topic from the endpoint.
            Topic topic = endpoint.getTopic();
            ContentFilteredTopic cfTopic = endpoint.getContentFilteredTopic();

            // Create data reader, registering ourself as a listener
            Subscriber subscriber = endpoint.getSubscriber();

            // We get the values from the topic and then set the values that
            // were explicitly mentioned in the URI.
            TopicQosHolder topicQosHolder = new TopicQosHolder();
            int status = topic.get_qos(topicQosHolder);
            DdsErrorHandler.checkStatus(status, "Get topic QoS");

            // For now, the endpoint keeps track of the topic, data writer,
            // and data reader QoS. Get the QoS from the endpoint.
            // drQosHolder = this.endpoint.getDdsDataReaderQosHolder();

            DataReaderQosHolder mergedDrQosHolder = new DataReaderQosHolder();
            status = subscriber.get_default_datareader_qos(mergedDrQosHolder);
            DdsErrorHandler.checkStatus(status, "Get default data reader QoS");

            // Merge QoS if needed. First, get the QoS from the topic.
            status = subscriber.copy_from_topic_qos(mergedDrQosHolder,
                topicQosHolder.value);
            DdsErrorHandler.checkStatus(status,
                "Copy subscriber QoS from topic QoS");
            Map drQosMap = endpoint.getDrQosMap();
            mergeDrQos(mergedDrQosHolder, drQosMap);

            if (cfTopic != null) {
                reader = subscriber.create_datareader(cfTopic,
                    mergedDrQosHolder.value, this /* listener */,
                    ANY_STATUS.value);
                DdsErrorHandler.checkHandle(reader, "Create data reader");
            } else {
                reader = subscriber.create_datareader(topic,
                    mergedDrQosHolder.value, this /* listener */,
                    ANY_STATUS.value);
                DdsErrorHandler.checkHandle(reader, "Create data reader");
            }

            /*
             * This is the only point where we thrown an Exception back without
             * it being proper DdsException type.
             */
            super.doStart();
        } catch (ClassNotFoundException e) {
            LOG.error("Class not found.");
            throw new DdsException(e);
        } catch (IllegalAccessException e) {
            LOG.error("Illegal access exception raised.");
            throw new DdsException(e);
        } catch (InstantiationException e) {
            LOG.error("Instantiation exception raised.");
            throw new DdsException(e);
        } catch (SecurityException e) {
            LOG.error("Security violation.");
            throw new DdsException(e);
        } catch (NoSuchFieldException e) {
            LOG.error("No such field.");
            throw new DdsException(e);
        } catch (NoSuchMethodException e) {
            LOG.error("No such method.");
            throw new DdsException(e);
        }
    }

    /**
     * Merge in the datareader QoS from the QoS map stored in the
     * Endpoint.
     * @param drQosHolder
     * @param drQosMap
     * @throws DdsException
     */
    private void mergeDrQos(DataReaderQosHolder drQosHolder, Map drQosMap)
        throws DdsException {
        try {
            // From the topic QoS add any Data Reader QoS explicitly set from
            // the URI.
            // Example value field = "deadline.period".
            // Example value = Duration_t with nanosec = 50, sec = 10.
            Field paramField = null;
            Class drQosHolderClass = Class.forName(DR_QOS_HOLDER_NAME);

            final String startFieldName = "value";
            Iterator qosIter = drQosMap.entrySet().iterator();
            while (qosIter.hasNext()) {
                paramField = drQosHolderClass.getDeclaredField(startFieldName);
                DataReaderQos drQos = drQosHolder.value;

                String paramName = null;
                Object paramValue = null;
                Map.Entry pair = (Map.Entry) qosIter.next();
                paramName = (String) pair.getKey();
                paramValue = pair.getValue();

                // Split the field name into the different data members.
                String[] fields = paramName.split("\\.");

                // The first string in fields should be the policy, e.g.,
                // deadline.
                Class drQosClass = paramField.getType();
                Field policyField = drQosClass.getField(fields[0]);
                Object policy = policyField.get(drQos);

                // Iterate through the fields to get the field to be set.
                List fieldList = Arrays.asList(fields);
                ListIterator fieldsIter = fieldList.listIterator();
                while (fieldsIter.hasNext()) {
                    Class fieldClass = paramField.getType();
                    String fieldName = (String) fieldsIter.next();
                    paramField = fieldClass.getField(fieldName);
                }

                // Set the value on the parameter.
                if (fields.length > 1) {
                    paramField.set(policy, paramValue);
                } else {
                    // This code should be used if we are setting the entire
                    // policy.
                    // Right now, we don't do that. We'd need to uncomment this
                    // code
                    // and change the QoS setting methods in DdsEndpoint to set
                    // whole
                    // policies rather than just parameters.
                    // We need to figure out the semantics we want.
                    // paramField.set(drQos, paramValue);
                    throw new DdsException(
                            "Setting entire policy not yet implemented.");
                }
            }
        } catch (ClassNotFoundException e) {
            LOG.error("Class not found.");
            throw new DdsException(e);
        } catch (SecurityException e) {
            LOG.error("Security violation.");
            throw new DdsException(e);
        } catch (NoSuchFieldException e) {
            LOG.error("No such field.");
            throw new DdsException(e);
        } catch (IllegalArgumentException e) {
            LOG.error("Illegal argument.");
            throw new DdsException(e);
        } catch (IllegalAccessException e) {
            LOG.error("Illegal access exception raised.");
            throw new DdsException(e);
        }
    }

    /**
     * Stop method.
     */
    @Override
    protected void doStop() throws Exception {
        if (reader != null) {
            endpoint.deleteDataReader(reader);
        }
        super.doStop();
    }

    /**
     * This method is called when the DataReader detects some new samples.
     * We take each sample and create an exchange, which is then
     * processed to push the message on to the next part of the Camel
     * route.
     */
    public void on_data_available(DataReader reader) {
        Object msgInst = null;
        Object status = null;
        try {
            Object[] arrTakeMethodParams = {sequenceObj, infoSequence,
                LENGTH_UNLIMITED.value, ANY_SAMPLE_STATE.value,
                ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value};
            status = takeMethod.invoke(reader, arrTakeMethodParams);
            DdsErrorHandler.checkStatus(((Integer) status).intValue(),
                dataClassName + ".take ()");
            Object val = valueField.get(sequenceObj);
            int len = Array.getLength(val);

            // Process each sample that has valid data
            for (int i = 0; i < len; ++i) {
                SampleInfo info = (SampleInfo) infoSequence.value[i];
                msgInst = Array.get(val, i);
                createExchange(msgInst, info);
            }
        } catch (Exception e) {
            LOG.info("Reader take failed", e);
        }

        try {
            // Clean up
            Object[] arrReturnMethodParams = {sequenceObj, infoSequence};
            status = returnMethod.invoke(reader, arrReturnMethodParams);
            DdsErrorHandler.checkStatus(((Integer) status).intValue(),
                dataClassName + ".return_loan ()");
        } catch (Exception e) {
            LOG.info("Reader return failed", e);
        }

    }

    /**
     * Create the exchange and call the processor to forward the message.
     * @param msg
     * @param info
     */
    private void createExchange(Object msg, SampleInfo info) {
        try {
            DdsExchange exchange = endpoint.createExchange(msg, info);
            getProcessor().process(exchange);
            if (exchange.isFailed()) {
                if (exchange.getException() != null) {
                    throw wrapRuntimeCamelException(exchange.getException());
                }
            }
        } catch (Exception e) {
            LOG.error("Error in processing DDS message", e);
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

    /**
     * Getter method.
     * @return the DataReader
     */
    DataReader getDataReader() {
        return reader;
    }
    
    public Class getDataClass () {
        return dataClass;
    }
}
