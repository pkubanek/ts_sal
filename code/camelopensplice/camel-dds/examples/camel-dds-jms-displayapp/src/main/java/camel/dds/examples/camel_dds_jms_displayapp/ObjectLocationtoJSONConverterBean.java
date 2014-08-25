package camel.dds.examples.camel_dds_jms_displayapp;

import java.util.Vector;

import org.apache.camel.Consume;
import org.apache.camel.Header;
import org.apache.camel.ProducerTemplate;

import track.ObjectLocation;
import DDS.SampleInfo;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class ObjectLocationtoJSONConverterBean {
    
    /** Vector of ObjectLocations */
    Vector<ObjectLocation> locations = new Vector<ObjectLocation> ();

    /** Vector of SampleInfo to go with the ObjectLocations */
    Vector<SampleInfo> sampleInfos = new Vector<SampleInfo> ();

    /** A producer, to pass the messages on to the URI that we want them to go to */
    ProducerTemplate producer = null;
    
    /** Our Gson object. To convert from object to string */
    Gson gson = new GsonBuilder().serializeSpecialFloatingPointValues().create ();

    /** The end of line character */
    private String eol = System.getProperty("line.separator"); 
    
    /** 
     * The bean method. Invoked when an ObjectLocation comes in on our DDS Endpoint.
     * @param message
     * @param sampleInfo
     */
    @Consume(uri="dds:track_ObjectLocation_topic:0/track.ObjectLocation?Partition=Battlefield")
    public void onObjectLocation(ObjectLocation message, @Header (value = "DDS_SAMPLE_INFO") SampleInfo sampleInfo) {
        synchronized (this) {
            locations.add(message);
            sampleInfos.add(sampleInfo);
            if (locations.size() >= 10) {
                sendJMSMessage ();
            }
        }
    }
 
    /**
     * Send a batch of ObjectLocations through as a JSON parsable string within
     * a ActiveMQTextMessage. We do this because it is more efficient to send
     * a batch than send the objects one at a time. It also demonstrates that
     * a Bean can do its own message forwarding if required.
     */
    public synchronized void sendJMSMessage () {
        String result = "{\"samples\": [" + eol + "  ";
        ObjectLocation val;
        SampleInfo info;
        for (int i = 0; i < locations.size(); i++) {
            val = locations.elementAt(i);
            info = sampleInfos.elementAt(i);
            if (i>0) {
                result = result + "," + eol + "  ";
            }
            result = result + "{\"data\": " + gson.toJson(val) + "," +
                              " \"info\": " + gson.toJson(info) + "}";
        }
        result = result + eol + "] }";
        producer.sendBody("test-jms:topic:object_location.topic", result);
        locations.clear();
        sampleInfos.clear();
    }

    /**
     * The producer object. We use this to push our messages onto the JMS topic.
     * @param producerTemplate
     */
    public void setProducerTemplate(ProducerTemplate producerTemplate) {
        producer = producerTemplate;
    }
}
