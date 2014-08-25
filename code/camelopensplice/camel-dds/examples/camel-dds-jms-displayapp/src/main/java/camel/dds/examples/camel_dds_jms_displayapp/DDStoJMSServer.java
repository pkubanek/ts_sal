package camel.dds.examples.camel_dds_jms_displayapp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.jms.ConnectionFactory;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.broker.BrokerService;
import org.apache.camel.CamelContext;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.impl.DefaultCamelContext;
import org.springframework.jms.connection.CachingConnectionFactory;

public class DDStoJMSServer {
    // Camel context
    private CamelContext context = null;
    // ActiveMQ broker
    private BrokerService broker = null;
    // ActiveMQ connection factory
    private ConnectionFactory connectionFactory = null;
    private ObjectLocationtoJSONConverterBean oljcb = null;
    
    public static void main (String[] args) {
        DDStoJMSServer server = new DDStoJMSServer();

        try {
            server.initialize();
        } catch(Exception exp) {
            exp.printStackTrace();
        }

        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

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
           server.stop();
        } catch (Exception e) {
           System.err.println("Cannot stop server: " + e.getMessage());
        }
    }

    public void initialize() throws Exception {
        // Start the ActiveMQ broker
        BrokerService broker = new BrokerService();

        // configure the broker
        broker.addConnector("tcp://localhost:61616");

        broker.start();
        
        context = new DefaultCamelContext();
        // Set up the ActiveMQ JMS Components
        ConnectionFactory aconnectionFactory = new ActiveMQConnectionFactory ("tcp://localhost:61616");
        connectionFactory = new CachingConnectionFactory(aconnectionFactory);
        ((CachingConnectionFactory) connectionFactory).setSessionCacheSize(3);
        ((CachingConnectionFactory) connectionFactory).setCacheProducers(true);
        // Note we can explicity name the component
        context.addComponent("test-jms", JmsComponent.jmsComponentAutoAcknowledge(connectionFactory));
        // Add some configuration by hand ...
        String partition = "?Partition=Battlefield";
        final String objectLocationURI = "dds:track_ObjectLocation_topic:0/track.ObjectLocation" + partition;
        partition = "?Partition=Battleship";
        // The qos values below are introduced to be consistent against the 
        // topics in the Battleship demo.
        String qos = "&OwnershipKind=EXCLUSIVE";
        final String pointTrackURI = "dds:track_PointTrack_topic:0/track.PointTrack" + partition + qos;
        qos = "&ReliabilityKind=RELIABLE&DurabilityKind=TRANSIENT";
        final String trackStateURI = "dds:track_TrackState_topic:0/track.TrackState" + partition + qos;

        oljcb = new ObjectLocationtoJSONConverterBean ();
        oljcb.setProducerTemplate (context.createProducerTemplate());

        // Build the route.
        context.addRoutes(new RouteBuilder() {
            public void configure() {
                // From the DDS URI through the converter bean to the JMS queue.
                from(objectLocationURI).bean(oljcb, "onObjectLocation");
                
                from(pointTrackURI).bean(PointTracktoJSONConverterBean.class, "onPointTrack").to("test-jms:topic:point_track.topic");
                
                from(trackStateURI).bean(TrackStatetoJSONConverterBean.class, "onTrackState").to("test-jms:topic:track_state.topic");
            }
        });       
        
        context.start();
    }

    private void stop() throws Exception {
        broker.stop();
        context.stop();
    }
}
