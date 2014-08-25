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

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import DDS.ContentFilteredTopic;
import DDS.DataReader;
import DDS.DataReaderQosHolder;
import DDS.DataWriter;
import DDS.DataWriterQosHolder;
import DDS.DestinationOrderQosPolicyKind;
import DDS.DomainParticipant;
import DDS.DomainParticipantFactory;
import DDS.DomainParticipantFactoryQosHolder;
import DDS.DomainParticipantQosHolder;
import DDS.DurabilityQosPolicyKind;
import DDS.DurabilityServiceQosPolicy;
import DDS.HistoryQosPolicyKind;
import DDS.LivelinessQosPolicyKind;
import DDS.OwnershipQosPolicyKind;
import DDS.PresentationQosPolicyAccessScopeKind;
import DDS.Publisher;
import DDS.PublisherQosHolder;
import DDS.ReliabilityQosPolicyKind;
import DDS.SampleInfo;
import DDS.Subscriber;
import DDS.SubscriberQosHolder;
import DDS.Topic;
import DDS.TopicQosHolder;

import org.apache.camel.Consumer;
import org.apache.camel.ExchangePattern;
import org.apache.camel.Processor;
import org.apache.camel.Producer;
import org.apache.camel.impl.DefaultConsumer;
import org.apache.camel.impl.DefaultEndpoint;
import org.apache.camel.impl.DefaultProducer;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * A DDS Endpoint
 * 
 * @version $Revision:520964 $
 */
public class DdsEndpoint extends DefaultEndpoint {

    private static final transient Log LOG = LogFactory
            .getLog(DdsEndpoint.class);

    /** Suffix appended to topic type name for type support. */
    private static final String TYPE_SUPPORT_CLASS_SUFFIX = "TypeSupport";

    /** Type support method used to get type name. */
    private static final String GET_TYPE_METHOD = "get_type_name";

    /** Type support method used to register type. */
    private static final String REGISTER_TYPE_METHOD = "register_type";

    /** Constant for nanoseconds in a second */
    private static final int NANOSECONDS_IN_SECONDS = 1000000000;

    /** The delimiter for the partition strings. */
    private static final String PARTITION_DELIMITER = "%";

    protected String topicName;
    protected String contentFilter;
    protected Map<String, Object> parameters;

    /** Vector of producers created */
    protected Vector<DefaultProducer> producers = new Vector<DefaultProducer>();

    /** Vector of consumers created */
    protected Vector<DefaultConsumer> consumers = new Vector<DefaultConsumer>();

    /** QoS for Domain Participant Factory */
    protected DomainParticipantFactoryQosHolder participantFactoryQosHolder;

    /** QoS for Domain Participant */
    protected DomainParticipantQosHolder participantQosHolder;

    /** QoS for Publisher */
    protected PublisherQosHolder publisherQosHolder;

    /** QoS for Subscriber */
    protected SubscriberQosHolder subscriberQosHolder;

    /** QoS for Topic */
    protected TopicQosHolder topicQosHolder;

    /** QoS for Data Writer */
    protected DataWriterQosHolder writerQosHolder;

    /** QoS for Data Reader */
    protected DataReaderQosHolder readerQosHolder;

    /*
     * OpenSplice DDS code
     */
    // DDS domain participant.
    protected DomainParticipant participant;

    // DDS publisher.
    protected Publisher publisher;

    // DDS subscriber.
    protected Subscriber subscriber;

    // DDS topic
    protected Topic ddsTopic;

    // DDS contentFilteredTopic
    protected ContentFilteredTopic contentFilteredTopic;

    protected DomainParticipantFactory dpf;

    private DdsBinding binding;
    // private String password;
    // private String resource = "Camel";
    // private boolean login = true;
    // private boolean createAccount;
    // private String room;
    // private String participant;
    // private String nickname;
    private String serviceName;

    private DurabilityQosPolicyKind durabilityKind;
    private HistoryQosPolicyKind historyKind;
    private int historyDepth;
    private double lifespanDuration;
    private byte[] topicData;
    private byte[] userData;

    private String dataclassName;

    /** Domain ID used to create DDS domain participant. */
    private String domainId;
    private String domain;

    /** Map from topic name to DDS topic */
    // private Map<String, Topic> topicMap = new Hashtable<String, Topic>();
    private byte[] groupData;

    private DurabilityServiceQosPolicy durabilityServiceKind;

    private double durabilityServiceCleanupDelay;

    private int durabilityServiceDepth;

    private int durabilityServiceMaxSamples;

    private int durabilityServiceMaxInstances;

    private int durabilityServiceMaxSamplesPerInstance;

    private PresentationQosPolicyAccessScopeKind presentationAccessScope;

    private boolean presentationCoherentAccess;

    private boolean presentationOrderedAccess;

    private double deadlinePeriod;

    private double latencyDuration;

    private OwnershipQosPolicyKind ownershipKind;

    private int ownershipStrength;

    private LivelinessQosPolicyKind livelinessKind;

    private double livelinessDuration;

    private double timebasedFilter;

    private String[] partition;

    private ReliabilityQosPolicyKind reliabilityKind;

    private double reliabilityBlockingTime;

    private int transportPriority;

    private DestinationOrderQosPolicyKind destinationOrderKind;

    private int maxSamples;

    private int maxInstances;

    private int maxSamplesPerInstance;

    private boolean writerDataLifecycleAutodispose;

    private double nowriterSamplesDelay;

    private double disposedSamplesDelay;

    // private String partitionStr;

    private Publisher dummyPublisher;

    private Subscriber dummySubscriber;

    private HashMap<String, Object> drQosMap;

    private HashMap<String, Object> dwQosMap;

    public DdsEndpoint(String uri, DdsComponent component) {
        super(uri, component);
        binding = new DdsBinding(component.getHeaderFilterStrategy());
    }

    public DdsEndpoint(String endpointUri) {
        super(endpointUri);
    }

    /**
     * Initialize method sets up the initial dds entities for use
     * within out route.
     * @throws DdsException
     */
    public void initialize() throws DdsException {
        /*
         * Keep only the domain participant factory and the domain participant
         * at this point since the other DDS entities have QoS policies that
         * can't be changed after the entity is created.
         */
        dpf = DomainParticipantFactory.get_instance();
        participantFactoryQosHolder = new DomainParticipantFactoryQosHolder();
        int status = dpf.get_qos(participantFactoryQosHolder);
        DdsErrorHandler.checkStatus(status,
                "Get domain participant factory QoS");

        // Create DDS domain participant
        participantQosHolder = new DomainParticipantQosHolder();
        status = dpf.get_default_participant_qos(participantQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default participant QoS");

        participant = dpf.create_participant(domain, // domainId.toString(),
                participantQosHolder.value, null, DDS.ANY_STATUS.value);
        DdsErrorHandler.checkHandle(participant, "Create participant");

        /*
         * Create a dummy publisher and subscriber to get default QoS holders
         * for a data writer and reader. We need to wait until all the URI/XML
         * QoS parameters are parsed and assigned to create the DDS entities
         * which have QoS policies that can't be changed after the entity is
         * created.
         */
        // Create dummy publisher.
        //PublisherQosHolder pQos = new PublisherQosHolder();
        //status = participant.get_default_publisher_qos(pQos);
        //DdsErrorHandler.checkStatus(status, "Get default publisher QoS");

        //pQos = null;
        
        // Create dummy subscriber.
        //SubscriberQosHolder sQos = new SubscriberQosHolder();
        //status = participant.get_default_subscriber_qos(sQos);
        //DdsErrorHandler.checkStatus(status, "Get default subscriber QoS");

        //sQos = null;

        // Get the default QoS holders.
        publisherQosHolder = new PublisherQosHolder();
        status = participant.get_default_publisher_qos(publisherQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default publisher QoS");

        dummyPublisher = participant.create_publisher(publisherQosHolder.value, null,
                DDS.ANY_STATUS.value);
        DdsErrorHandler.checkHandle(dummyPublisher, "Create dummy publisher");

        subscriberQosHolder = new SubscriberQosHolder();
        status = participant.get_default_subscriber_qos(subscriberQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default subscriber QoS");

        dummySubscriber = participant.create_subscriber(subscriberQosHolder.value, null,
                DDS.ANY_STATUS.value);
        DdsErrorHandler.checkHandle(dummySubscriber, "Create dummy subscriber");

        topicQosHolder = new TopicQosHolder();
        status = participant.get_default_topic_qos(topicQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default topic QoS");

        readerQosHolder = new DataReaderQosHolder();
        status = dummySubscriber.get_default_datareader_qos(readerQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default data reader QoS");
        writerQosHolder = new DataWriterQosHolder();
        status = dummyPublisher.get_default_datawriter_qos(writerQosHolder);
        DdsErrorHandler.checkStatus(status, "Get default data writer QoS");

        // Clean up the dummy objects because we just used them to get 
        // the default QoS values.
        status = participant.delete_publisher(dummyPublisher);
        DdsErrorHandler.checkStatus(status, "Delete publisher");
        status = participant.delete_subscriber(dummySubscriber);
        DdsErrorHandler.checkStatus(status, "Delete subscriber");

        // Create the maps for the data reader and data writer.
        drQosMap = new HashMap<String, Object>();
        dwQosMap = new HashMap<String, Object>();
    }

    /**
     * Getter method for the topic.
     * @return Topic
     * @throws DdsException
     */
    public Topic getTopic() throws DdsException {
        if (ddsTopic == null) {
            return findOrCreateTopic();
        } else {
            return ddsTopic;
        }
    }

    /**
     * OpenSplice DDS code, obtains the topic for use within the Camel
     * route.
     * @return Topic
     * @throws DdsException
     */
    protected Topic findOrCreateTopic() throws DdsException {
        try {
            // Get topic type name
            String typeSupportName = dataclassName + TYPE_SUPPORT_CLASS_SUFFIX;
            Class<?> typeSupport = Class.forName(typeSupportName);
            Method getType = typeSupport.getMethod(GET_TYPE_METHOD,
                    (Class[]) null);

            String typeName = (String) getType.invoke(
                    typeSupport.newInstance(), (Object[]) null);

            // Register type before creating topic
            Class<?>[] arrRegisterTypeTypeParams = {DomainParticipant.class,
                String.class};
            Method registerType = typeSupport.getMethod(REGISTER_TYPE_METHOD,
                arrRegisterTypeTypeParams);
            Object[] arrRegisterTypeParams = {participant, typeName};
            Object statusObj = registerType.invoke(typeSupport.newInstance(),
                 arrRegisterTypeParams);
            DdsErrorHandler.checkStatus(((Integer) statusObj).intValue(),
                    "Register type support for " + typeSupportName);

            // Create topic
            DDS.Duration_t duration = new DDS.Duration_t();
            duration.nanosec = 0;
            duration.sec = 0;
            ddsTopic = participant.find_topic(topicName, duration);
            if (ddsTopic == null) {
                ddsTopic = participant.create_topic(topicName, typeName,
                        topicQosHolder.value, null, // listener
                        DDS.ANY_STATUS.value);
            }
            DdsErrorHandler.checkHandle(ddsTopic, "Find or create topic "
                    + topicName);

            String filter = null;

            if (contentFilteredTopic == null) {
                filter = getContentFilter();
                if (filter != null) {
                    int hash = filter.hashCode();
                    String filteredTopic = "filter" + hash + topicName;
                    contentFilteredTopic = participant
                            .create_contentfilteredtopic(filteredTopic,
                                    ddsTopic, filter, new String[0]);
                    DdsErrorHandler.checkHandle(contentFilteredTopic,
                            "Create content filtered topic");
                }
            }
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
        } catch (NoSuchMethodException e) {
            LOG.error("No such method.");
            throw new DdsException(e);
        } catch (IllegalArgumentException e) {
            LOG.error("Illegal argument.");
            throw new DdsException(e);
        } catch (InvocationTargetException e) {
            LOG.error("Invocation target exception raised.");
            throw new DdsException(e);
        }
        return ddsTopic;
    }

    /**
     * 
     * @return ContentFilteredTopic
     */
    public ContentFilteredTopic getContentFilteredTopic() {
        return contentFilteredTopic;
    }

    /**
     * 
     * @param writer
     */
    protected void deleteDataWriter(DataWriter writer) throws DdsException {
        int status = publisher.delete_datawriter(writer);
        DdsErrorHandler.checkStatus(status, "Delete data writer");
    }

    /**
     * 
     * @param reader
     */
    protected void deleteDataReader(DataReader reader) throws DdsException {
        int status = subscriber.delete_datareader(reader);
        DdsErrorHandler.checkStatus(status, "Delete data reader");
    }

    protected void clean() throws DdsException {
        try {
            for (Producer producer : producers) {
                producer.stop();
            }
        } catch (Exception ex) {
            LOG.error("Exception thrown while stopping producer ", ex);
        }
        int status = participant.delete_publisher(publisher);
        DdsErrorHandler.checkStatus(status, "Delete publisher");
        
        try {
            for (Consumer consumer : consumers) {
                consumer.stop();
            }
        } catch (Exception ex) {
            LOG.error("Exception thrown while stopping producer ", ex);
        }
        status = participant.delete_subscriber(subscriber);
        DdsErrorHandler.checkStatus(status, "Delete subscriber");

        if (contentFilteredTopic != null) {
            status = participant
                    .delete_contentfilteredtopic(contentFilteredTopic);
            DdsErrorHandler
                    .checkStatus(status, "Delete content filtered topic");
        }
        //Comment out error handling, currently returns PRECONDITION_NOT_MET.
        status = participant.delete_topic(ddsTopic);
        DdsErrorHandler.checkStatus(status, "Delete topic");
        //Comment out error handling, currently returns PRECONDITION_NOT_MET.
        status = dpf.delete_participant(participant);
        DdsErrorHandler.checkStatus(status, "Delete participant");
    }

    public Producer createProducer() throws Exception {
        createSupportingDdsEntities();

        // return new DdsProducer(this);
        DdsProducer producer = new DdsProducer(this);
        producers.add(producer);
        return producer;
    }

    protected void createSupportingDdsEntities() throws DdsException {
        // Reset the QoS policies for the domain participant factory and the
        // domain participant. PAG 10-04-21, we don't set the QoS for the
        // domain participant factory any more as it only has one QoS.
        // See commented out method setEntityFactoryAutoenable for details.

        int status = participant.set_qos(participantQosHolder.value);
        DdsErrorHandler.checkStatus(status, "participant set QoS");

        // Create publisher if needed.
        if (publisher == null) {
            publisher = participant.create_publisher(publisherQosHolder.value,
                    null, // listener
                    DDS.ANY_STATUS.value);
            DdsErrorHandler.checkHandle(publisher, "create publisher");
        }

        // Create subscriber if needed.
        if (subscriber == null) {
            subscriber = participant.create_subscriber(
                    subscriberQosHolder.value, null, DDS.ANY_STATUS.value);
            DdsErrorHandler.checkHandle(subscriber, "create subscriber");
        }
    }

    public Consumer createConsumer(Processor processor)
        throws Exception {
        createSupportingDdsEntities();

        // return new DdsConsumer(this, processor);
        DdsConsumer consumer = new DdsConsumer(this, processor);
        consumers.add(consumer);
        return consumer;
    }

    @Override
    public DdsExchange createExchange(ExchangePattern pattern) {
        return new DdsExchange(getCamelContext(), pattern, getBinding());
    }

    public DdsExchange createExchange(Object messageInstance, SampleInfo info) {
        return new DdsExchange(getCamelContext(), getExchangePattern(),
                getBinding(), messageInstance, info);
    }

    public boolean isSingleton() {
        return true;
    }

    public Vector<DefaultProducer> getProducers() {
        return producers;
    }

    public Vector<DefaultConsumer> getConsumers() {
        return consumers;
    }

    // -------------------------------------------------------------------------
    // Properties
    // -------------------------------------------------------------------------
    public DdsBinding getBinding() {
        if (binding == null) {
            binding = new DdsBinding();
        }
        return binding;
    }

    /**
     * Sets the binding used to convert from a Camel message to and from an DDS
     * message
     */
    public void setBinding(DdsBinding binding) {
        this.binding = binding;
    }

    public String getTopicName() {
        return topicName;
    }

    public Publisher getPublisher() {
        return publisher;
    }

    public Subscriber getSubscriber() {
        return subscriber;
    }

    public Topic getDdsTopic() {
        return ddsTopic;
    }

    public void setTopic(String topicName) {
        this.topicName = topicName;
    }

    public String getDomainId() {
        return domainId;
    }

    public void setDomainId(String domainId) {
        this.domainId = domainId;
    }

    public String getDataclassName() {
        return dataclassName;
    }

    public void setDataclassName(String dataclassName) {
        this.dataclassName = dataclassName;
    }

    public void setServiceName(String serviceName) {
        this.serviceName = serviceName;
    }

    public String getServiceName() {
        return serviceName;
    }

    public void setContentFilter(String contentFilter) {
        this.contentFilter = contentFilter;
    }

    public String getContentFilter() {
        return contentFilter;
    }

    public Map<String, Object> getParameters() {
        return parameters;
    }

    public void setParameters(Map<String, Object> parameters) {
        this.parameters = parameters;
    }

    public TopicQosHolder getDdsTopicQosHolder() {
        return topicQosHolder;
    }

    public DataWriterQosHolder getDdsDataWriterQosHolder() {
        return writerQosHolder;
    }

    public DataReaderQosHolder getDdsDataReaderQosHolder() {
        return readerQosHolder;
    }

    public DomainParticipantFactoryQosHolder getDdsParticipantFactoryQosHolder() {
        System.out.println("DdsEndpoint::getDdsParticipantFactoryQosHolder");
        return participantFactoryQosHolder;
    }

    public DomainParticipantQosHolder getDdsParticipantQosHolder() {
        return participantQosHolder;
    }

    /*
     * Deadline Period.
     */
    public void setDeadlinePeriod(double deadlinePeriod) {
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) deadlinePeriod;
        int nanoseconds = (int) ((deadlinePeriod - seconds) * NANOSECONDS_IN_SECONDS);

        this.deadlinePeriod = deadlinePeriod;
        // Deadline only applies to topic, data reader, and data writer.
        topicQosHolder.value.deadline.period.sec = seconds;
        topicQosHolder.value.deadline.period.nanosec = nanoseconds;
        writerQosHolder.value.deadline.period.sec = seconds;
        writerQosHolder.value.deadline.period.nanosec = nanoseconds;
        readerQosHolder.value.deadline.period.sec = seconds;
        readerQosHolder.value.deadline.period.nanosec = nanoseconds;
    }

    public void setDeadlinePeriodT(double deadlinePeriod) {
        // Topic QoS
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) deadlinePeriod;
        int nanoseconds = (int) ((deadlinePeriod - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.deadline.period.sec = seconds;
        topicQosHolder.value.deadline.period.nanosec = nanoseconds;
    }

    public void setDeadlinePeriodD(double deadlinePeriod) {
        // DataReader and DataWriter QoS
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) deadlinePeriod;
        int nanoseconds = (int) ((deadlinePeriod - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.deadline.period.sec = seconds;
        writerQosHolder.value.deadline.period.nanosec = nanoseconds;
        readerQosHolder.value.deadline.period.sec = seconds;
        readerQosHolder.value.deadline.period.nanosec = nanoseconds;

        dwQosMap.put("deadline.period", writerQosHolder.value.deadline.period);
        drQosMap.put("deadline.period", readerQosHolder.value.deadline.period);
    }

    public void setDeadlinePeriodR(double deadlinePeriod) {
        // Reader QoS
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) deadlinePeriod;
        int nanoseconds = (int) ((deadlinePeriod - seconds) * NANOSECONDS_IN_SECONDS);

        readerQosHolder.value.deadline.period.sec = seconds;
        readerQosHolder.value.deadline.period.nanosec = nanoseconds;

        drQosMap.put("deadline.period", readerQosHolder.value.deadline.period);
    }

    public void setDeadlinePeriodW(double deadlinePeriod) {
        // Writer QoS
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) deadlinePeriod;
        int nanoseconds = (int) ((deadlinePeriod - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.deadline.period.sec = seconds;
        writerQosHolder.value.deadline.period.nanosec = nanoseconds;

        dwQosMap.put("deadline.period", writerQosHolder.value.deadline.period);
    }

    public double getDeadlinePeriod() {
        return deadlinePeriod;
    }

    /*
     * Destination Order.
     */
    public void setDestinationOrder(String destinationOrderString)
        throws DdsException {
        // Everything
        // Destination order only applies to topic, data reader and data writer.
        if (destinationOrderString.equals("BY_RECEPTION_TIMESTAMP")) {
            destinationOrderKind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
            topicQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
        } else if (destinationOrderString.equals("BY_SOURCE_TIMESTAMP")) {
            destinationOrderKind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
            topicQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
        } else {
            throw new DdsException("Invalid destination order string specified");
        }

        dwQosMap.put("destination_order.kind",
                writerQosHolder.value.destination_order.kind);
        drQosMap.put("destination_order.kind",
                readerQosHolder.value.destination_order.kind);
    }

    public void setDestinationOrderT(String destinationOrderString)
        throws DdsException {
        // Topic
        if (destinationOrderString.equals("BY_RECEPTION_TIMESTAMP")) {
            topicQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
        } else if (destinationOrderString.equals("BY_SOURCE_TIMESTAMP")) {
            topicQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
        } else {
            throw new DdsException(
                    "Invalid destination order string specified for topic");
        }
    }

    public void setDestinationOrderD(String destinationOrderString)
        throws DdsException {
        // DataReader and DataWriter
        if (destinationOrderString.equals("BY_RECEPTION_TIMESTAMP")) {
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
        } else if (destinationOrderString.equals("BY_SOURCE_TIMESTAMP")) {
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
        } else {
            throw new DdsException(
                    "Invalid destination order string specified for data reader / writer");
        }

        dwQosMap.put("destination_order.kind",
                writerQosHolder.value.destination_order.kind);
        drQosMap.put("destination_order.kind",
                readerQosHolder.value.destination_order.kind);
    }

    public void setDestinationOrderR(String destinationOrderString)
        throws DdsException {
        // DataReader
        if (destinationOrderString.equals("BY_RECEPTION_TIMESTAMP")) {
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
        } else if (destinationOrderString.equals("BY_SOURCE_TIMESTAMP")) {
            readerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
        } else {
            throw new DdsException(
                    "Invalid destination order string specified for data reader");
        }

        drQosMap.put("destination_order.kind",
                readerQosHolder.value.destination_order.kind);
    }

    public void setDestinationOrderW(String destinationOrderString)
        throws DdsException {
        // DataWriter
        if (destinationOrderString.equals("BY_RECEPTION_TIMESTAMP")) {
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
        } else if (destinationOrderString.equals("BY_SOURCE_TIMESTAMP")) {
            writerQosHolder.value.destination_order.kind = DDS.DestinationOrderQosPolicyKind.BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
        } else {
            throw new DdsException(
                    "Invalid destination order string specified for data writer");
        }

        dwQosMap.put("destination_order.kind",
                writerQosHolder.value.destination_order.kind);
    }

    public DestinationOrderQosPolicyKind getDestinationOrder() {
        return destinationOrderKind;
    }

    /*
     * Durability Kind.
     */
    public void setDurabilityKind(String durabilityKindString)
        throws DdsException {
        // Everything
        // Durability only applies to topic, data reader and data writer.
        if (durabilityKindString.equals("VOLATILE")) {
            durabilityKind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT")) {
            durabilityKind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT_LOCAL")) {
            durabilityKind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (durabilityKindString.equals("PERSISTENT")) {
            durabilityKind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
        } else {
            throw new DdsException("Invalid durability string specified");
        }

        dwQosMap.put("durability.kind", writerQosHolder.value.durability.kind);
        drQosMap.put("durability.kind", readerQosHolder.value.durability.kind);
    }

    public void setDurabilityKindT(String durabilityKindString)
        throws DdsException {
        // Topic
        if (durabilityKindString.equals("VOLATILE")) {
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT")) {
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT_LOCAL")) {
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (durabilityKindString.equals("PERSISTENT")) {
            topicQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability string specified for topic");
        }
    }

    public void setDurabilityKindD(String durabilityKindString)
        throws DdsException {
        // DataReader and DataWriter
        if (durabilityKindString.equals("VOLATILE")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT_LOCAL")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (durabilityKindString.equals("PERSISTENT")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability string specified for data reader / writer");
        }

        dwQosMap.put("durability.kind", writerQosHolder.value.durability.kind);
        drQosMap.put("durability.kind", readerQosHolder.value.durability.kind);
    }

    public void setDurabilityKindR(String durabilityKindString)
        throws DdsException {
        // DataReader
        if (durabilityKindString.equals("VOLATILE")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT_LOCAL")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (durabilityKindString.equals("PERSISTENT")) {
            readerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability string specified for data reader");
        }

        drQosMap.put("durability.kind", readerQosHolder.value.durability.kind);
    }

    public void setDurabilityKindW(String durabilityKindString)
        throws DdsException {
        // DataWriter
        if (durabilityKindString.equals("VOLATILE")) {
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.VOLATILE_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT")) {
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
        } else if (durabilityKindString.equals("TRANSIENT_LOCAL")) {
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (durabilityKindString.equals("PERSISTENT")) {
            writerQosHolder.value.durability.kind = DDS.DurabilityQosPolicyKind.PERSISTENT_DURABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability string specified for data writer");
        }

        dwQosMap.put("durability.kind", writerQosHolder.value.durability.kind);
    }

    public DurabilityQosPolicyKind getDurabilityKind() {
        return durabilityKind;
    }

    /*
     * Durability service cleanup delay.
     */
    public void setDurabilityServiceCleanupDelay(
            double durabilityServiceCleanupDelay) {
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) durabilityServiceCleanupDelay;
        int nanoseconds = (int) ((durabilityServiceCleanupDelay - seconds) * NANOSECONDS_IN_SECONDS);

        // Durability service only applies to topic and data writer.
        this.durabilityServiceCleanupDelay = durabilityServiceCleanupDelay;
        topicQosHolder.value.durability_service.service_cleanup_delay.sec = seconds;
        topicQosHolder.value.durability_service.service_cleanup_delay.nanosec = nanoseconds;
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.service_cleanup_delay.sec
        // = seconds;
        // this.writerQosHolder.value.durability_service.service_cleanup_delay.nanosec
        // = nanoseconds;
    }

    public void setDurabilityServiceCleanupDelayT(
            double durabilityServiceCleanupDelay) {
        // TODO - this is the same as the previous method.
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) durabilityServiceCleanupDelay;
        int nanoseconds = (int) ((durabilityServiceCleanupDelay - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.durability_service.service_cleanup_delay.sec = seconds;
        topicQosHolder.value.durability_service.service_cleanup_delay.nanosec = nanoseconds;
    }

    public void setDurabilityServiceCleanupDelayW(
            double durabilityServiceCleanupDelay) {
        // TODO - This doesn't do anything.
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) durabilityServiceCleanupDelay;
        int nanoseconds = (int) ((durabilityServiceCleanupDelay - seconds) * NANOSECONDS_IN_SECONDS);

        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.service_cleanup_delay.sec
        // = seconds;
        // this.writerQosHolder.value.durability_service.service_cleanup_delay.nanosec
        // = nanoseconds;

        // dwQosMap.put("durability_service.service_cleanup_delay",
        // this.writerQosHolder.value.durability_service.service_cleanup_delay);
    }

    public double getDurabilityServiceCleanupDelay() {
        return durabilityServiceCleanupDelay;
    }

    /*
     * Durability service depth.
     */
    public void setDurabilityServiceDepth(int durabilityServiceDepth) {
        // Topic
        // Durability service only applies to topic and data writer.
        this.durabilityServiceDepth = durabilityServiceDepth;
        topicQosHolder.value.durability_service.history_depth = durabilityServiceDepth;
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.history_depth =
        // durabilityServiceDepth;
    }

    public void setDurabilityServiceDepthT(int durabilityServiceDepth) {
        // Topic
        // TODO - What's the difference between this and the above?
        topicQosHolder.value.durability_service.history_depth = durabilityServiceDepth;
    }

    public void setDurabilityServiceDepthW(int durabilityServiceDepth) {
        // TODO - This method does NOTHING!
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.history_depth =
        // durabilityServiceDepth;

        // dwQosMap.put("durability_service.history_depth",
        // this.writerQosHolder.value.durability_service.history_depth);
    }

    public int getDurabilityServiceDepth() {
        return durabilityServiceDepth;
    }

    /*
     * Durability service kind.
     */
    public void setDurabilityServiceKind(String durabilityServiceKindString)
        throws DdsException {
        // Everything
        // Durability service only applies to topic and data writer.
        if (durabilityServiceKindString.equals("KEEP_ALL")) {
            durabilityServiceKind.history_kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            topicQosHolder.value.durability_service.history_kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            // ? No durability service support for data writers?
            // this.writerQosHolder.value.durability_service.history_kind =
            // DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (durabilityServiceKindString.equals("KEEP_LAST")) {
            durabilityServiceKind.history_kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            topicQosHolder.value.durability_service.history_kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            // ? No durability service support for data writers?
            // this.writerQosHolder.value.durability_service.history_kind =
            // DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability service kind string specified");
        }
    }

    public void setDurabilityServiceKindT(String durabilityServiceKindString)
        throws DdsException {
        // Topic
        if (durabilityServiceKindString.equals("KEEP_ALL")) {
            topicQosHolder.value.durability_service.history_kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (durabilityServiceKindString.equals("KEEP_LAST")) {
            topicQosHolder.value.durability_service.history_kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability service kind string specified for topic");
        }
    }

    public void setDurabilityServiceKindW(String durabilityServiceKindString)
        throws DdsException {
        // TODO - This method does NOTHING
        if (durabilityServiceKindString.equals("KEEP_ALL")) {
            // ? No durability service support for data writers?
            // writerQosHolder.value.durability_service.history_kind =
            // DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (durabilityServiceKindString.equals("KEEP_LAST")) {
            // ? No durability service support for data writers?
            // writerQosHolder.value.durability_service.history_kind =
            // DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid durability service kind string specified for data writer");
        }

        // dwQosMap.put("durability_service.history_kind",
        // this.writerQosHolder.value.durability_service.history_kind);
    }

    public HistoryQosPolicyKind getDurabilityServiceKind() {
        return durabilityServiceKind.history_kind;
    }

    /*
     * Durability Service Max Instances
     */
    public void setDurabilityServiceMaxInstances(
            int durabilityServiceMaxInstances) {
        // Everything
        // Durability service only applies to topic and data writer.
        this.durabilityServiceMaxInstances = durabilityServiceMaxInstances;
        topicQosHolder.value.durability_service.max_instances = durabilityServiceMaxInstances;
        // ? No durability service support for data writers?
        // writerQosHolder.value.durability_service.max_instances =
        // durabilityServiceMaxInstances;
    }

    public void setDurabilityServiceMaxInstancesT(
            int durabilityServiceMaxInstances) {
        // Topic
        // TODO - This is the same as the above
        this.topicQosHolder.value.durability_service.max_instances = durabilityServiceMaxInstances;
    }

    public void setDurabilityServiceMaxInstancesW(
            int durabilityServiceMaxInstances) {
        // TODO - This method does NOTHING
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.max_instances =
        // durabilityServiceMaxInstances;

        // dwQosMap.put("durability_service.max_instances",
        // this.writerQosHolder.value.durability_service.max_instances);
    }

    public int getDurabilityServiceMaxInstances() {
        return durabilityServiceMaxInstances;
    }

    /*
     * Durability Service Max Samples
     */
    public void setDurabilityServiceMaxSamples(int durabilityServiceMaxSamples) {
        // Everything
        // Durability service only applies to topic and data writer.
        this.durabilityServiceMaxSamples = durabilityServiceMaxSamples;
        topicQosHolder.value.durability_service.max_samples = durabilityServiceMaxSamples;
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.max_samples =
        // durabilityServiceMaxSamples;
    }

    public void setDurabilityServiceMaxSamplesT(int durabilityServiceMaxSamples) {
        // Topic
        topicQosHolder.value.durability_service.max_samples = durabilityServiceMaxSamples;
    }

    public void setDurabilityServiceMaxSamplesW(int durabilityServiceMaxSamples) {
        // TODO - This method does NOTHING
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.max_samples =
        // durabilityServiceMaxSamples;

        // dwQosMap.put("durability_service.max_samples",
        // this.writerQosHolder.value.durability_service.max_samples);
    }

    public int getDurabilityServiceMaxSamples() {
        return durabilityServiceMaxSamples;
    }

    /*
     * Durability service max samples per instance
     */
    public void setDurabilityServiceMaxSamplesPerInstance(
            int durabilityServiceMaxSamplesPerInstance) {
        // Everything
        // Durability service only applies to topic and data writer.
        this.durabilityServiceMaxSamplesPerInstance = durabilityServiceMaxSamplesPerInstance;
        topicQosHolder.value.durability_service.max_samples_per_instance = durabilityServiceMaxSamplesPerInstance;
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.max_samples_per_instance
        // = durabilityServiceMaxSamplesPerInstance;
    }

    public void setDurabilityServiceMaxSamplesPerInstanceT(
            int durabilityServiceMaxSamplesPerInstance) {
        // Topic
        topicQosHolder.value.durability_service.max_samples_per_instance = durabilityServiceMaxSamplesPerInstance;
    }

    public void setDurabilityServiceMaxSamplesPerInstanceW(
            int durabilityServiceMaxSamplesPerInstance) {
        // TODO - This method does NOTHING
        // ? No durability service support for data writers?
        // this.writerQosHolder.value.durability_service.max_samples_per_instance
        // = durabilityServiceMaxSamplesPerInstance;

        // dwQosMap.put("durability_service.max_samples_per_instance",
        // this.writerQosHolder.value.durability_service.max_samples_per_instance);
    }

    public int getDurabilityServiceMaxSamplesPerInstance() {
        return durabilityServiceMaxSamplesPerInstance;
    }

    /*
     * Entity Factory auto enable
     * PAG - 10-04-21, if we disable the auto enable QoS then the code
     * needs to change to explicitly enable any entities we create. The
     * code will not change based on the user setting this QoS, so it's 
     * probably best not to allow the QoS to be changed either.
    public void setEntityFactoryAutoenable(boolean autoenable) {
        System.out.println("DdsEndpoint setEntityFactoryAutoenable");
        // Everything
        // Entity factory only applies to domain participant factory, domain
        // participant,
        // publisher, and subscriber.
        entityFactoryAutoenable = autoenable;
        participantFactoryQosHolder.value.entity_factory.autoenable_created_entities = autoenable;
        participantQosHolder.value.entity_factory.autoenable_created_entities = autoenable;
        publisherQosHolder.value.entity_factory.autoenable_created_entities = autoenable;
        subscriberQosHolder.value.entity_factory.autoenable_created_entities = autoenable;
    }

    public boolean getEntityFactoryAutoenable() {
        System.out.println("DdsEndpoint getEntityFactoryAutoenable");
        return entityFactoryAutoenable;
    }
    */
    
    /*
     * Group data
     */
    public void setGroupData(byte[] data) {
        groupData = data;
        // Group data only applies to publisher and subscriber.
        publisherQosHolder.value.group_data.value = data;
        subscriberQosHolder.value.group_data.value = data;
    }

    public byte[] getGroupData() {
        return groupData;
    }

    /*
     * History depth
     */
    public void setHistoryDepth(int historyDepth) {
        // Everything
        this.historyDepth = historyDepth;
        // History only applies to topic, data reader, and data writer.
        topicQosHolder.value.history.depth = historyDepth;
        readerQosHolder.value.history.depth = historyDepth;
        writerQosHolder.value.history.depth = historyDepth;

        dwQosMap.put("history.depth", writerQosHolder.value.history.depth);
        drQosMap.put("history.depth", readerQosHolder.value.history.depth);
    }

    public void setHistoryDepthT(int historyDepth) {
        // Topic
        topicQosHolder.value.history.depth = historyDepth;
    }

    public void setHistoryDepthD(int historyDepth) {
        // DataReader / DataWriter
        readerQosHolder.value.history.depth = historyDepth;
        writerQosHolder.value.history.depth = historyDepth;

        dwQosMap.put("history.depth", writerQosHolder.value.history.depth);
        drQosMap.put("history.depth", readerQosHolder.value.history.depth);
    }

    public void setHistoryDepthR(int historyDepth) {
        // DataReader
        readerQosHolder.value.history.depth = historyDepth;

        drQosMap.put("history.depth", readerQosHolder.value.history.depth);
    }

    public void setHistoryDepthW(int historyDepth) {
        // DataWriter
        writerQosHolder.value.history.depth = historyDepth;

        dwQosMap.put("history.depth", writerQosHolder.value.history.depth);
    }

    public int getHistoryDepth() {
        return historyDepth;
    }

    /*
     * History Kind
     */
    public void setHistoryKind(String historyKindString) throws DdsException {
        // Everything
        // History only applies to topic, data reader, and data writer.
        if (historyKindString.equals("KEEP_ALL")) {
            historyKind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            topicQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (historyKindString.equals("KEEP_LAST")) {
            historyKind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            topicQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException("Invalid history kind string specified");
        }
    }

    public void setHistoryKindT(String historyKindString) throws DdsException {
        // Topic
        if (historyKindString.equals("KEEP_ALL")) {
            topicQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (historyKindString.equals("KEEP_LAST")) {
            topicQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for topic");
        }
    }

    public void setHistoryKindD(String historyKindString) throws DdsException {
        // DataReader / DataWriter
        if (historyKindString.equals("KEEP_ALL")) {
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (historyKindString.equals("KEEP_LAST")) {
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for topic");
        }

        dwQosMap.put("history.kind", writerQosHolder.value.history.kind);
        drQosMap.put("history.kind", readerQosHolder.value.history.kind);
    }

    public void setHistoryKindR(String historyKindString) throws DdsException {
        // DataReader
        if (historyKindString.equals("KEEP_ALL")) {
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (historyKindString.equals("KEEP_LAST")) {
            readerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for data reader");
        }

        drQosMap.put("history.kind", readerQosHolder.value.history.kind);
    }

    public void setHistoryKindW(String historyKindString) throws DdsException {
        // DataWriter
        if (historyKindString.equals("KEEP_ALL")) {
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
        } else if (historyKindString.equals("KEEP_LAST")) {
            writerQosHolder.value.history.kind = DDS.HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for data writer");
        }

        dwQosMap.put("history.kind", writerQosHolder.value.history.kind);
    }

    public HistoryQosPolicyKind getHistoryKind() {
        return historyKind;
    }

    /*
     * Latency duration
     */
    public void setLatencyDuration(double latencyDuration) {
        // Everything
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) latencyDuration;
        int nanoseconds = (int) ((latencyDuration - seconds) * NANOSECONDS_IN_SECONDS);

        this.latencyDuration = latencyDuration;
        // Latency only applies to topic, data reader, and data writer.
        topicQosHolder.value.latency_budget.duration.sec = seconds;
        topicQosHolder.value.latency_budget.duration.nanosec = nanoseconds;
        writerQosHolder.value.latency_budget.duration.sec = seconds;
        writerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;
        readerQosHolder.value.latency_budget.duration.sec = seconds;
        readerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;
    }

    public void setLatencyDurationT(double latencyDuration) {
        // Topic
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) latencyDuration;
        int nanoseconds = (int) ((latencyDuration - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.latency_budget.duration.sec = seconds;
        topicQosHolder.value.latency_budget.duration.nanosec = nanoseconds;
    }

    public void setLatencyDurationD(double latencyDuration) {
        // DataReader / DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) latencyDuration;
        int nanoseconds = (int) ((latencyDuration - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.latency_budget.duration.sec = seconds;
        writerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;
        readerQosHolder.value.latency_budget.duration.sec = seconds;
        readerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;

        dwQosMap.put("latency_budget.duration",
                writerQosHolder.value.latency_budget.duration);
        drQosMap.put("latency_budget.duration",
                readerQosHolder.value.latency_budget.duration);
    }

    public void setLatencyDurationR(double latencyDuration) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) latencyDuration;
        int nanoseconds = (int) ((latencyDuration - seconds) * NANOSECONDS_IN_SECONDS);

        readerQosHolder.value.latency_budget.duration.sec = seconds;
        readerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;

        drQosMap.put("latency_budget.duration",
                readerQosHolder.value.latency_budget.duration);
    }

    public void setLatencyDurationW(double latencyDuration) {
        // DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) latencyDuration;
        int nanoseconds = (int) ((latencyDuration - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.latency_budget.duration.sec = seconds;
        writerQosHolder.value.latency_budget.duration.nanosec = nanoseconds;

        dwQosMap.put("latency_budget.duration",
                writerQosHolder.value.latency_budget.duration);
    }

    public double getLatencyDuration() {
        return latencyDuration;
    }

    /*
     * Lifespan duration
     */
    public void setLifespanDuration(double lifespanDuration) {
        // Everything
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) lifespanDuration;
        int nanoseconds = (int) ((lifespanDuration - seconds) * NANOSECONDS_IN_SECONDS);

        this.lifespanDuration = lifespanDuration;
        // Lifespan only applies to topic and data writer.
        topicQosHolder.value.lifespan.duration.sec = seconds;
        topicQosHolder.value.lifespan.duration.nanosec = nanoseconds;
        writerQosHolder.value.lifespan.duration.sec = seconds;
        writerQosHolder.value.lifespan.duration.nanosec = nanoseconds;
    }

    public void setLifespanDurationT(double lifespanDuration) {
        // Topic
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) lifespanDuration;
        int nanoseconds = (int) ((lifespanDuration - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.lifespan.duration.sec = seconds;
        topicQosHolder.value.lifespan.duration.nanosec = nanoseconds;
    }

    public void setLifespanDurationW(double lifespanDuration) {
        // DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) lifespanDuration;
        int nanoseconds = (int) ((lifespanDuration - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.lifespan.duration.sec = seconds;
        writerQosHolder.value.lifespan.duration.nanosec = nanoseconds;

        dwQosMap.put("lifespan.duration",
                writerQosHolder.value.lifespan.duration);
    }

    public double getLifespanDuration() {
        return lifespanDuration;
    }

    /*
     * Liveliness duration
     */
    public void setLivelinessDuration(double livelinessDuration) {
        // Everything
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) livelinessDuration;
        int nanoseconds = (int) ((livelinessDuration - seconds) * NANOSECONDS_IN_SECONDS);

        this.livelinessDuration = livelinessDuration;
        // Liveliness lease duration only applies to data writer.
        topicQosHolder.value.liveliness.lease_duration.sec = seconds;
        topicQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;
        writerQosHolder.value.liveliness.lease_duration.sec = seconds;
        writerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;
        readerQosHolder.value.liveliness.lease_duration.sec = seconds;
        readerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;
    }

    public void setLivelinessDurationT(double livelinessDuration) {
        // Topic
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) livelinessDuration;
        int nanoseconds = (int) ((livelinessDuration - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.liveliness.lease_duration.sec = seconds;
        topicQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;
    }

    public void setLivelinessDurationD(double livelinessDuration) {
        // DataReader / DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) livelinessDuration;
        int nanoseconds = (int) ((livelinessDuration - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.liveliness.lease_duration.sec = seconds;
        writerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;
        readerQosHolder.value.liveliness.lease_duration.sec = seconds;
        readerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;

        dwQosMap.put("liveliness.lease_duration",
                writerQosHolder.value.liveliness.lease_duration);
        drQosMap.put("liveliness.lease_duration",
                readerQosHolder.value.liveliness.lease_duration);
    }

    public void setLivelinessDurationR(double livelinessDuration) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) livelinessDuration;
        int nanoseconds = (int) ((livelinessDuration - seconds) * NANOSECONDS_IN_SECONDS);

        readerQosHolder.value.liveliness.lease_duration.sec = seconds;
        readerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;

        drQosMap.put("liveliness.lease_duration",
                readerQosHolder.value.liveliness.lease_duration);
    }

    public void setLivelinessDurationW(double livelinessDuration) {
        // DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) livelinessDuration;
        int nanoseconds = (int) ((livelinessDuration - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.liveliness.lease_duration.sec = seconds;
        writerQosHolder.value.liveliness.lease_duration.nanosec = nanoseconds;

        dwQosMap.put("liveliness.lease_duration",
                writerQosHolder.value.liveliness.lease_duration);
    }

    public double getLivelinessDuration() {
        return livelinessDuration;
    }

    /*
     * Liveliness Kind
     */
    public void setLivelinessKind(String livelinessKindString) throws Exception {
        // Everything
        // Liveliness only applies to topic, data reader, and data writer.
        if (livelinessKindString.equals("AUTOMATIC")) {
            livelinessKind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_PARTICPANT")) {
            livelinessKind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_TOPIC")) {
            livelinessKind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
        } else {
            throw new DdsException("Invalid history kind string specified");
        }
    }

    public void setLivelinessKindT(String livelinessKindString)
        throws DdsException {
        // Topic
        if (livelinessKindString.equals("AUTOMATIC")) {
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_PARTICPANT")) {
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_TOPIC")) {
            topicQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for topic");
        }
    }

    public void setLivelinessKindD(String livelinessKindString)
        throws DdsException {
        // DataReader / DataWriter
        if (livelinessKindString.equals("AUTOMATIC")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_PARTICPANT")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_TOPIC")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for data reader / writer");
        }

        dwQosMap.put("liveliness.kind", writerQosHolder.value.liveliness.kind);
        drQosMap.put("liveliness.kind", readerQosHolder.value.liveliness.kind);
    }

    public void setLivelinessKindR(String livelinessKindString)
        throws DdsException {
        // Data Reader
        if (livelinessKindString.equals("AUTOMATIC")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_PARTICPANT")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_TOPIC")) {
            readerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for data reader");
        }

        drQosMap.put("liveliness.kind", readerQosHolder.value.liveliness.kind);
    }

    public void setLivelinessKindW(String livelinessKindString)
        throws DdsException {
        // Data Writer
        if (livelinessKindString.equals("AUTOMATIC")) {
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.AUTOMATIC_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_PARTICPANT")) {
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
        } else if (livelinessKindString.equals("MANUAL_BY_TOPIC")) {
            writerQosHolder.value.liveliness.kind = DDS.LivelinessQosPolicyKind.MANUAL_BY_TOPIC_LIVELINESS_QOS;
        } else {
            throw new DdsException(
                    "Invalid history kind string specified for data writer");
        }

        dwQosMap.put("liveliness.kind", writerQosHolder.value.liveliness.kind);
    }

    public LivelinessQosPolicyKind getLivelinessKind() {
        return livelinessKind;
    }

    /*
     * Ownership kind
     */
    public void setOwnershipKind(String ownershipKindString)
        throws DdsException {
        // Everything
        // Ownership kind only applies to topic, data reader, and data writer.
        if (ownershipKindString.equals("SHARED")) {
            ownershipKind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
            topicQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        } else if (ownershipKindString.equals("EXCLUSIVE")) {
            ownershipKind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
            topicQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            throw new DdsException("Invalid ownership kind string specified");
        }
    }

    public void setOwnershipKindT(String ownershipKindString)
        throws DdsException {
        // Topic
        if (ownershipKindString.equals("SHARED")) {
            topicQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        } else if (ownershipKindString.equals("EXCLUSIVE")) {
            topicQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            throw new DdsException(
                    "Invalid ownership kind string specified for topic");
        }
    }

    public void setOwnershipKindD(String ownershipKindString)
        throws DdsException {
        // DataReader / DataWriter
        if (ownershipKindString.equals("SHARED")) {
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        } else if (ownershipKindString.equals("EXCLUSIVE")) {
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            throw new DdsException(
                    "Invalid ownership kind string specified for data reader / writer");
        }

        dwQosMap.put("ownership.kind", writerQosHolder.value.ownership.kind);
        drQosMap.put("ownership.kind", readerQosHolder.value.ownership.kind);
    }

    public void setOwnershipKindR(String ownershipKindString)
        throws DdsException {
        // DataReader
        if (ownershipKindString.equals("SHARED")) {
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        } else if (ownershipKindString.equals("EXCLUSIVE")) {
            readerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            throw new DdsException(
                    "Invalid ownership kind string specified for data reader");
        }

        drQosMap.put("ownership.kind", readerQosHolder.value.ownership.kind);
    }

    public void setOwnershipKindW(String ownershipKindString)
        throws DdsException {
        // DataWriter
        if (ownershipKindString.equals("SHARED")) {
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.SHARED_OWNERSHIP_QOS;
        } else if (ownershipKindString.equals("EXCLUSIVE")) {
            writerQosHolder.value.ownership.kind = DDS.OwnershipQosPolicyKind.EXCLUSIVE_OWNERSHIP_QOS;
        } else {
            throw new DdsException(
                    "Invalid ownership kind string specified for data writer");
        }

        dwQosMap.put("ownership.kind", writerQosHolder.value.ownership.kind);
    }

    public OwnershipQosPolicyKind getOwnershipKind() {
        return ownershipKind;
    }

    /*
     * Ownership strength
     */
    public void setOwnershipStrength(int strength) {
        // Ownership strength only applies to data writer.
        ownershipStrength = strength;
        writerQosHolder.value.ownership_strength.value = strength;

        dwQosMap.put("ownership_strength.value",
                writerQosHolder.value.ownership_strength.value);
    }

    public int getOwnershipStrength() {
        return ownershipStrength;
    }

    /*
     * Partition name
     */
    public void setPartition(String partitionStr) {
        // Find the number of strings embedded in the URI string.
        // Partition only applies to publisher and subscriber.
        partition = partitionStr.split(PARTITION_DELIMITER);
        publisherQosHolder.value.partition.name = partition;
        subscriberQosHolder.value.partition.name = partition;
    }

    public String[] getPartition() {
        return partition;
    }

    /*
     * Presentation Access Scope
     */
    public void setPresentationAccessScope(String presentationAccessScopeString)
        throws DdsException {
        // Everything
        // Presentation only applies to publisher and subscriber.
        if (presentationAccessScopeString.equals("INSTANCE")) {
            presentationAccessScope = DDS.PresentationQosPolicyAccessScopeKind.INSTANCE_PRESENTATION_QOS;
            publisherQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.INSTANCE_PRESENTATION_QOS;
            subscriberQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.INSTANCE_PRESENTATION_QOS;
        } else if (presentationAccessScopeString.equals("TOPIC")) {
            presentationAccessScope = DDS.PresentationQosPolicyAccessScopeKind.TOPIC_PRESENTATION_QOS;
            publisherQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.TOPIC_PRESENTATION_QOS;
            subscriberQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.TOPIC_PRESENTATION_QOS;
        } else if (presentationAccessScopeString.equals("GROUP")) {
            presentationAccessScope = DDS.PresentationQosPolicyAccessScopeKind.GROUP_PRESENTATION_QOS;
            publisherQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.GROUP_PRESENTATION_QOS;
            subscriberQosHolder.value.presentation.access_scope = DDS.PresentationQosPolicyAccessScopeKind.GROUP_PRESENTATION_QOS;
        } else {
            throw new DdsException(
                    "Invalid presentation access scope string specified");
        }
    }

    public PresentationQosPolicyAccessScopeKind getPresentationAccessScope() {
        return presentationAccessScope;
    }

    /*
     * Presentation Coherent Access
     */
    public void setPresentationCoherentAccess(boolean presentationCoherentAccess) {
        // Presentation only applies to publisher and subscriber.
        this.presentationCoherentAccess = presentationCoherentAccess;
        publisherQosHolder.value.presentation.coherent_access = presentationCoherentAccess;
        subscriberQosHolder.value.presentation.coherent_access = presentationCoherentAccess;
    }

    public boolean getPresentationCoherentAccess() {
        return presentationCoherentAccess;
    }

    /*
     * Presentation Ordered Access
     */
    public void setPresentationOrderedAccess(boolean presentationOrderedAccess) {
        // Presentation only applies to publisher and subscriber.
        this.presentationOrderedAccess = presentationOrderedAccess;
        publisherQosHolder.value.presentation.ordered_access = presentationOrderedAccess;
        subscriberQosHolder.value.presentation.ordered_access = presentationOrderedAccess;
    }

    public boolean getPresentationOrderedAccess() {
        return presentationOrderedAccess;
    }

    /*
     * Reader Data Lifecycle Autopurge Disposed Delay
     */
    public void setReaderDataLifecycleAutopurgeDisposedDelay(
            double disposedSamplesDelay) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) disposedSamplesDelay;
        int nanoseconds = (int) ((disposedSamplesDelay - seconds) * NANOSECONDS_IN_SECONDS);

        this.disposedSamplesDelay = disposedSamplesDelay;
        // Reader data lifecycle only applies to data reader.
        readerQosHolder.value.reader_data_lifecycle.autopurge_disposed_samples_delay.sec = seconds;
        readerQosHolder.value.reader_data_lifecycle.autopurge_disposed_samples_delay.nanosec = nanoseconds;

        drQosMap
                .put(
                        "reader_data_lifecycle.autopurge_disposed_samples_delay",
                        readerQosHolder.value.reader_data_lifecycle.autopurge_disposed_samples_delay);
    }

    public double getReaderDataLifecycleAutopurgeDisposedDelay() {
        return disposedSamplesDelay;
    }

    /*
     * Reader Data Lifecycle Autopurge Nowriter Delay
     */
    public void setReaderDataLifecycleAutopurgeNowriterDelay(
            double nowriterSamplesDelay) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) nowriterSamplesDelay;
        int nanoseconds = (int) ((nowriterSamplesDelay - seconds) * NANOSECONDS_IN_SECONDS);

        this.nowriterSamplesDelay = nowriterSamplesDelay;
        // Reader data lifecycle only applies to data reader.
        readerQosHolder.value.reader_data_lifecycle.autopurge_nowriter_samples_delay.sec = seconds;
        readerQosHolder.value.reader_data_lifecycle.autopurge_nowriter_samples_delay.nanosec = nanoseconds;

        drQosMap
                .put(
                        "reader_data_lifecycle.autopurge_nowriter_samples_delay",
                        readerQosHolder.value.reader_data_lifecycle.autopurge_nowriter_samples_delay);
    }

    public double getReaderDataLifecycleAutopurgeNowriterDelay() {
        return nowriterSamplesDelay;
    }

    /*
     * Reliability blocking time
     */
    public void setReliabilityBlockingTime(double blockingTime) {
        // Everything
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) blockingTime;
        int nanoseconds = (int) ((blockingTime - seconds) * NANOSECONDS_IN_SECONDS);

        reliabilityBlockingTime = blockingTime;
        // Reliability only applies to topic, data reader, and data writer.
        topicQosHolder.value.reliability.max_blocking_time.sec = seconds;
        topicQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;
        writerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        writerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;
        readerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        readerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;
    }

    public void setReliabilityBlockingTimeT(double blockingTime) {
        // Topic
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) blockingTime;
        int nanoseconds = (int) ((blockingTime - seconds) * NANOSECONDS_IN_SECONDS);

        topicQosHolder.value.reliability.max_blocking_time.sec = seconds;
        topicQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;
    }

    public void setReliabilityBlockingTimeD(double blockingTime) {
        // DataReader / DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) blockingTime;
        int nanoseconds = (int) ((blockingTime - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        writerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;
        readerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        readerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;

        dwQosMap.put("reliability.max_blocking_time",
                writerQosHolder.value.reliability.max_blocking_time);
        drQosMap.put("reliability.max_blocking_time",
                readerQosHolder.value.reliability.max_blocking_time);
    }

    public void setReliabilityBlockingTimeR(double blockingTime) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) blockingTime;
        int nanoseconds = (int) ((blockingTime - seconds) * NANOSECONDS_IN_SECONDS);

        readerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        readerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;

        drQosMap.put("reliability.max_blocking_time",
                readerQosHolder.value.reliability.max_blocking_time);
    }

    public void setReliabilityBlockingTimeW(double blockingTime) {
        // DataWriter
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) blockingTime;
        int nanoseconds = (int) ((blockingTime - seconds) * NANOSECONDS_IN_SECONDS);

        writerQosHolder.value.reliability.max_blocking_time.sec = seconds;
        writerQosHolder.value.reliability.max_blocking_time.nanosec = nanoseconds;

        dwQosMap.put("reliability.max_blocking_time",
                writerQosHolder.value.reliability.max_blocking_time);
    }

    public double getReliabilityBlockingTime() {
        return reliabilityBlockingTime;
    }

    /*
     * Reliability Kind
     */
    public void setReliabilityKind(String reliabilityKindString)
        throws DdsException {
        // Everything
        // Reliability only applies to topic, data reader, and data writer.
        if (reliabilityKindString.equals("RELIABLE")) {
            reliabilityKind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
            topicQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
        } else if (reliabilityKindString.equals("BEST_EFFORT")) {
            reliabilityKind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
            topicQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
        } else {
            throw new DdsException("Invalid reliability kind string specified");
        }
    }

    public void setReliabilityKindT(String reliabilityKindString)
        throws DdsException {
        // Topic
        if (reliabilityKindString.equals("RELIABLE")) {
            topicQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
        } else if (reliabilityKindString.equals("BEST_EFFORT")) {
            topicQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid reliability kind string specified for topic");
        }
    }

    public void setReliabilityKindD(String reliabilityKindString)
        throws DdsException {
        // DataReader / DataWriter
        if (reliabilityKindString.equals("RELIABLE")) {
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
        } else if (reliabilityKindString.equals("BEST_EFFORT")) {
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid reliability kind string specified for data reader / writer");
        }

        dwQosMap
                .put("reliability.kind", writerQosHolder.value.reliability.kind);
        drQosMap
                .put("reliability.kind", readerQosHolder.value.reliability.kind);
    }

    public void setReliabilityKindR(String reliabilityKindString)
        throws DdsException {
        // DataReader
        if (reliabilityKindString.equals("RELIABLE")) {
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
        } else if (reliabilityKindString.equals("BEST_EFFORT")) {
            readerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid reliability kind string specified for data reader / writer");
        }

        drQosMap
                .put("reliability.kind", readerQosHolder.value.reliability.kind);
    }

    public void setReliabilityKindW(String reliabilityKindString)
        throws DdsException {
        // DataWriter
        if (reliabilityKindString.equals("RELIABLE")) {
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
        } else if (reliabilityKindString.equals("BEST_EFFORT")) {
            writerQosHolder.value.reliability.kind = DDS.ReliabilityQosPolicyKind.BEST_EFFORT_RELIABILITY_QOS;
        } else {
            throw new DdsException(
                    "Invalid reliability kind string specified for data reader / writer");
        }

        dwQosMap
                .put("reliability.kind", writerQosHolder.value.reliability.kind);
    }

    public ReliabilityQosPolicyKind getReliabilityKind() {
        return reliabilityKind;
    }

    /*
     * Resource Limits Max Instances
     */
    public void setResourceLimitsMaxInstances(int maxInstances) {
        // Everything
        // Resource limits only applies to topic, data reader, and data writer.
        this.maxInstances = maxInstances;
        topicQosHolder.value.resource_limits.max_instances = maxInstances;
        readerQosHolder.value.resource_limits.max_instances = maxInstances;
        writerQosHolder.value.resource_limits.max_instances = maxInstances;
    }

    public void setResourceLimitsMaxInstancesT(int maxInstances) {
        // Topic
        topicQosHolder.value.resource_limits.max_instances = maxInstances;
    }

    public void setResourceLimitsMaxInstancesD(int maxInstances) {
        // DataReader / DataWriter
        readerQosHolder.value.resource_limits.max_instances = maxInstances;
        writerQosHolder.value.resource_limits.max_instances = maxInstances;

        dwQosMap.put("resource_limits.max_instances",
                writerQosHolder.value.resource_limits.max_instances);
        drQosMap.put("resource_limits.max_instances",
                readerQosHolder.value.resource_limits.max_instances);
    }

    public void setResourceLimitsMaxInstancesR(int maxInstances) {
        // DataReader
        readerQosHolder.value.resource_limits.max_instances = maxInstances;

        drQosMap.put("resource_limits.max_instances",
                readerQosHolder.value.resource_limits.max_instances);
    }

    public void setResourceLimitsMaxInstancesW(int maxInstances) {
        // DataWriter
        writerQosHolder.value.resource_limits.max_instances = maxInstances;

        dwQosMap.put("resource_limits.max_instances",
                writerQosHolder.value.resource_limits.max_instances);
    }

    public int getResourceLimitsMaxInstances() {
        return maxInstances;
    }

    /*
     * Resource Limits Max Samples
     */
    public void setResourceLimitsMaxSamples(int maxSamples) {
        // Everything
        // Resource limits only applies to topic, data reader, and data writer.
        this.maxSamples = maxSamples;
        topicQosHolder.value.resource_limits.max_samples = maxSamples;
        readerQosHolder.value.resource_limits.max_samples = maxSamples;
        writerQosHolder.value.resource_limits.max_samples = maxSamples;
    }

    public void setResourceLimitsMaxSamplesT(int maxSamples) {
        // Topic
        topicQosHolder.value.resource_limits.max_samples = maxSamples;
    }

    public void setResourceLimitsMaxSamplesD(int maxSamples) {
        // DataReader / DataWriter
        readerQosHolder.value.resource_limits.max_samples = maxSamples;
        writerQosHolder.value.resource_limits.max_samples = maxSamples;

        dwQosMap.put("resource_limits.max_samples",
                writerQosHolder.value.resource_limits.max_samples);
        drQosMap.put("resource_limits.max_samples",
                readerQosHolder.value.resource_limits.max_samples);
    }

    public void setResourceLimitsMaxSamplesR(int maxSamples) {
        // DataReader
        readerQosHolder.value.resource_limits.max_samples = maxSamples;

        drQosMap.put("resource_limits.max_samples",
                readerQosHolder.value.resource_limits.max_samples);
    }

    public void setResourceLimitsMaxSamplesW(int maxSamples) {
        // DataWriter
        writerQosHolder.value.resource_limits.max_samples = maxSamples;

        dwQosMap.put("resource_limits.max_samples",
                writerQosHolder.value.resource_limits.max_samples);
    }

    public int getResourceLimitsMaxSamples() {
        return maxSamples;
    }

    /*
     * Resource Limits Max Samples Per Instance
     */
    public void setResourceLimitsMaxSamplesPerInstance(int maxSamplesPerInstance) {
        // Everything
        // Resource limits only applies to topic, data reader, and data writer.
        this.maxSamplesPerInstance = maxSamplesPerInstance;
        topicQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;
        readerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;
        writerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;
    }

    public void setResourceLimitsMaxSamplesPerInstanceT(
            int maxSamplesPerInstance) {
        // Topic
        topicQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;
    }

    public void setResourceLimitsMaxSamplesPerInstanceD(
            int maxSamplesPerInstance) {
        // DataReader / DataWriter
        readerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;
        writerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;

        dwQosMap.put("resource_limits.max_samples_per_instance",
                writerQosHolder.value.resource_limits.max_samples_per_instance);
        drQosMap.put("resource_limits.max_samples_per_instance",
                readerQosHolder.value.resource_limits.max_samples_per_instance);
    }

    public void setResourceLimitsMaxSamplesPerInstanceR(
            int maxSamplesPerInstance) {
        // DataReader
        readerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;

        drQosMap.put("resource_limits.max_samples_per_instance",
                readerQosHolder.value.resource_limits.max_samples_per_instance);
    }

    public void setResourceLimitsMaxSamplesPerInstanceW(
            int maxSamplesPerInstance) {
        // DataWriter
        writerQosHolder.value.resource_limits.max_samples_per_instance = maxSamplesPerInstance;

        dwQosMap.put("resource_limits.max_samples_per_instance",
                writerQosHolder.value.resource_limits.max_samples_per_instance);
    }

    public int getResourceLimitsMaxSamplesPerInstance() {
        return maxSamplesPerInstance;
    }

    /*
     * Time Based Filter
     */
    public void setTimebasedFilter(double timebasedFilter) {
        // DataReader
        // Convert the float to seconds and nanoseconds.
        int seconds = (int) timebasedFilter;
        int nanoseconds = (int) ((timebasedFilter - seconds) * NANOSECONDS_IN_SECONDS);

        this.timebasedFilter = timebasedFilter;
        // Time based filter only applies to data reader.
        readerQosHolder.value.time_based_filter.minimum_separation.sec = seconds;
        readerQosHolder.value.time_based_filter.minimum_separation.nanosec = nanoseconds;

        drQosMap.put("time_based_filter.minimum_separation",
                readerQosHolder.value.time_based_filter.minimum_separation);
    }

    public double getTimebasedFilter() {
        return timebasedFilter;
    }

    /*
     * Topic data
     */
    public void setTopicData(byte[] data) {
        topicData = data;
        // Topic data only applies to topic.
        topicQosHolder.value.topic_data.value = data;
    }

    public byte[] getTopicData() {
        return topicData;
    }

    /*
     * Transport Priority
     */
    public void setTransportPriority(int priority) {
        // Transport priority only applies to topic and data writer.
        transportPriority = priority;
        topicQosHolder.value.transport_priority.value = priority;
        writerQosHolder.value.transport_priority.value = priority;
    }

    public void setTransportPriorityT(int priority) {
        // Topic
        topicQosHolder.value.transport_priority.value = priority;
    }

    public void setTransportPriorityW(int priority) {
        // DataWriter
        writerQosHolder.value.transport_priority.value = priority;

        dwQosMap.put("transport_priority.value",
                writerQosHolder.value.transport_priority.value);
    }

    public int getTransportPriority() {
        return transportPriority;
    }

    /*
     * User data
     */
    public void setUserData(byte[] data) {
        // Everything
        userData = data;
        // User data only applies to domain participant, data reader, and data
        // writer.
        participantQosHolder.value.user_data.value = data;
        readerQosHolder.value.user_data.value = data;
        writerQosHolder.value.user_data.value = data;

        dwQosMap.put("user_data", writerQosHolder.value.user_data);
        drQosMap.put("user_data", writerQosHolder.value.user_data);
    }

    public byte[] getUserData() {
        return userData;
    }

    /*
     * Writer Data Lifecycle Autodispose
     */
    public void setWriterDataLifecycleAutodispose(boolean autodispose) {
        // Writer data lifecycle only applies to data writer.
        writerDataLifecycleAutodispose = autodispose;
        writerQosHolder.value.writer_data_lifecycle.autodispose_unregistered_instances = autodispose;

        dwQosMap
                .put(
                        "writer_data_lifecycle.autodispose_unregistered_instances",
                        writerQosHolder.value.writer_data_lifecycle.autodispose_unregistered_instances);
    }

    public boolean getWriterDataLifecycleAutodispose() {
        return writerDataLifecycleAutodispose;
    }

    public DomainParticipant getDdsParticipant() {
        return participant;
    }

    public Map<String, Object> getDrQosMap() {
        return drQosMap;
    }

    public Map<String, Object> getDwQosMap() {
        return dwQosMap;
    }
}
