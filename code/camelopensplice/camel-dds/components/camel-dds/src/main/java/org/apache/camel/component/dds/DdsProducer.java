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

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import DDS.DataWriter;
import DDS.DataWriterQos;
import DDS.DataWriterQosHolder;
import DDS.HANDLE_NIL;
import DDS.Publisher;
import DDS.Topic;
import DDS.TopicQosHolder;

import org.apache.camel.Exchange;
import org.apache.camel.FailedToCreateProducerException;
import org.apache.camel.RuntimeExchangeException;
import org.apache.camel.impl.DefaultProducer;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * @version
 */
public class DdsProducer extends DefaultProducer {
    private static final transient Log LOG = LogFactory
            .getLog(DdsProducer.class);

    /** Suffix appended to topic type name for data writer. */
    private static final String WRITER_CLASS_SUFFIX = "DataWriterImpl";

    /** Data writer method used to write data. */
    private static final String WRITE_METHOD = "write";

    /** Data writer dispose method used to write data. */
    private static final String DISPOSE_METHOD = "dispose";

    /** Data writer writedispose method used to write data. */
    private static final String WRITEDISPOSE_METHOD = "writedispose";

    /** Name for data writer QoS holder class. */
    private static final String DW_QOS_HOLDER_NAME = "DDS.DataWriterQosHolder";

    private final DdsEndpoint endpoint;

    /** Name of class to be distributed on DDS topic. */
    private String dataClassName;

    /** DDS data writer. */
    private DataWriter writer;

    /** DDS topic data type class. */
    private Class dataClass;

    /** DDS data writer implementation class. */
    private Class writerClass;

    /** DDS data writer QoS class. */
    // private Class dwQosClass;
    /** DDS data writer write method */
    private Method writeMethod;

    /** Parameters (via URI or XML) */
    private Map<String, Object> parameters;

    /** DDS data writer writeDispose method */
    private Method writeDisposeMethod;

    /** DDS data writer dispose method */
    private Method disposeMethod;

    /**
     * Constructor.
     * @param endpoint
     * @throws DdsException
     * @throws FailedToCreateProducerException
     */
    public DdsProducer(DdsEndpoint endpoint) throws DdsException,
            FailedToCreateProducerException {
        super(endpoint);
        this.endpoint = endpoint;
        this.dataClassName = endpoint.getDataclassName();
        this.parameters = endpoint.getParameters();

        // Cache topic data type class
        try {
            dataClass = Class.forName(dataClassName);
        } catch (ClassNotFoundException e) {
            throw new FailedToCreateProducerException(endpoint, e);
        }

        // Cache data writer implementation class
        String writerName = dataClassName + WRITER_CLASS_SUFFIX;
        try {
            writerClass = Class.forName(writerName);
        } catch (ClassNotFoundException e) {
            throw new FailedToCreateProducerException(endpoint, e);
        }

        // Cache reference to data writer write method
        Class[] arrWriteMethodParams = {dataClass, long.class};
        Class[] registerMethodParams = {dataClass};
        try {
            writeMethod = writerClass.getMethod(WRITE_METHOD,
                    arrWriteMethodParams);
            disposeMethod = writerClass.getMethod(DISPOSE_METHOD,
                    arrWriteMethodParams);
            writeDisposeMethod = writerClass.getMethod(WRITEDISPOSE_METHOD,
                    arrWriteMethodParams);
        } catch (SecurityException e) {
            throw new FailedToCreateProducerException(endpoint, e);
        } catch (NoSuchMethodException e) {
            throw new FailedToCreateProducerException(endpoint, e);
        }

        /*
         * OpenSplice DDS code
         */

        /*
         * // Set QoS for domain participant factory, domain participant, //
         * topic, publisher, and subscriber. DomainParticipantFactoryQosHolder
         * dpfQosHolder = endpoint.getDdsParticipantFactoryQosHolder();
         * DomainParticipantFactory dpf =
         * DomainParticipantFactory.get_instance();
         * dpf.set_qos(dpfQosHolder.value);
         * 
         * DomainParticipantQosHolder dpQosHolder =
         * endpoint.getDdsParticipantQosHolder(); DomainParticipant dp =
         * endpoint.getDdsParticipant(); dp.set_qos(dpQosHolder.value);
         */

        // Use endpoint to retrieve the topic.
        Topic topic = this.endpoint.getTopic();

        // Create data writer
        Publisher publisher = endpoint.getPublisher();
        // DataWriterQosHolder dwQosHolder = new DataWriterQosHolder();

        // We should be able to leverage the Topic QoS but I'm not
        // sure how to get it in Java. DDS.DATAWRITER_QOS_USE_TOPIC_QOS
        // is an interface - not a class - so I'm not sure what subclass
        // to use.
        TopicQosHolder topicQosHolder = new TopicQosHolder();
        int status = topic.get_qos(topicQosHolder);
        DdsErrorHandler.checkStatus(status, "Get topic QoS");
        // TopicQosHolder topicQosHolder = endpoint.getDdsTopicQosHolder();
        // topic.set_qos(topicQosHolder.value);

        DataWriterQosHolder mergedDwQosHolder = new DataWriterQosHolder();
        // Merge QoS if needed. First, get the QoS from the topic.
        status = publisher.get_default_datawriter_qos(mergedDwQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default DataWriter QoS");
        status = publisher.copy_from_topic_qos(mergedDwQosHolder,
                topicQosHolder.value);
        DdsErrorHandler.checkStatus(status, "Copy topic QoS");
        Map dwQosMap = this.endpoint.getDwQosMap();
        mergeDwQos(mergedDwQosHolder, dwQosMap);

        // For now, the endpoint keeps track of the topic, data writer,
        // and data reader QoS. Get the QoS from the endpoint.
        // dwQosHolder = this.endpoint.getDdsDataWriterQosHolder();
        this.writer = publisher.create_datawriter(topic, this.endpoint
                .getDdsDataWriterQosHolder().value, null, // listener
                DDS.ANY_STATUS.value);
        DdsErrorHandler.checkHandle(writer, "Create DataWriter");
    }

    /**
     * Merge in the datawriter QoS from the QoS map stored in the
     * Endpoint.
     * @param dwQosHolder
     * @param dwQosMap
     * @throws DdsException
     */
    private void mergeDwQos(DataWriterQosHolder dwQosHolder, Map dwQosMap)
        throws DdsException {
        try {
            // From the topic QoS add any Data Reader QoS explicitly set from
            // the URI.
            // Example value field = "deadline.period".
            // Example value = Duration_t with nanosec = 50, sec = 10.
            Field paramField = null;
            Class dwQosHolderClass = Class.forName(DW_QOS_HOLDER_NAME);

            final String startFieldName = "value";
            Iterator qosIter = dwQosMap.entrySet().iterator();
            while (qosIter.hasNext()) {
                paramField = dwQosHolderClass.getDeclaredField(startFieldName);
                DataWriterQos dwQos = dwQosHolder.value;

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
                Object policy = policyField.get(dwQos);

                // Iterate through the fields to get the field to be set.
                List fieldList = Arrays.asList(fields);
                ListIterator fieldsIter = fieldList.listIterator();
                while (fieldsIter.hasNext()) {
                    Class fieldClass = paramField.getType();
                    String fieldName = (String) fieldsIter.next();
                    paramField = fieldClass.getField(fieldName);
                }

                // Set the value on the policy unless we are setting the entire
                // policy.
                // We need to figure out the semantics we want.
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
                    // paramField.set(dwQos, paramValue);
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
     * Process an exchange.
     */
    public void process(Exchange exchange) {
        Object ddsMsgInstance = endpoint.getBinding().extractBodyFromExchange(
                exchange);
        DdsDisposeHeader dispose = null;
        boolean disposeHeaderPresent = false;
        try {
            dispose = (DdsDisposeHeader) endpoint.getBinding()
                    .extractHeaderFromExchange(exchange, "DDS_DISPOSE");
            if (dispose != null) {
                disposeHeaderPresent = true;
            }
        } catch (Exception exp) {
            disposeHeaderPresent = false;
        }
        Object[] arrWriteMethodParams = {ddsMsgInstance, HANDLE_NIL.value};
        try {
            if (disposeHeaderPresent) {
                if (dispose == DdsDisposeHeader.WRITEDISPOSE) {
                    writeDisposeMethod.invoke(writer, arrWriteMethodParams);
                } else if (dispose == DdsDisposeHeader.DISPOSE) {
                    disposeMethod.invoke(writer, arrWriteMethodParams);
                }
            } else {
                writeMethod.invoke(writer, arrWriteMethodParams);
            }
        } catch (IllegalArgumentException e) {
            throw new RuntimeExchangeException(e.getMessage(), exchange, e);
        } catch (IllegalAccessException e) {
            throw new RuntimeExchangeException(e.getMessage(), exchange, e);
        } catch (InvocationTargetException e) {
            throw new RuntimeExchangeException(e.getMessage(), exchange, e);
        }
    }

    /**
     * Start.
     */
    @Override
    protected void doStart() throws Exception {
        super.doStart();
    }

    /**
     * Stop and clean up.
     */
    @Override
    protected void doStop() throws Exception {
        if (writer != null) {
            endpoint.deleteDataWriter(writer);
        }
        super.doStop();
    }

    /**
     * Getter method.
     * @return the DataWriter
     */
    DataWriter getDataWriter() {
        return this.writer;
    }
    
    public Map<String, Object> getParameters () {
        return parameters;
    }
}
