package camel.dds.examples.camel_dds_jms_displayapp;

import org.apache.camel.Consume;
import org.apache.camel.Header;

import track.TrackState;
import DDS.SampleInfo;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class TrackStatetoJSONConverterBean {
    Gson gson = new GsonBuilder().serializeSpecialFloatingPointValues().create ();
    
    @Consume(uri="dds:track_TrackState_topic:0/track.TrackState?Partition=Battlefield")
    public String onTrackState(TrackState message, @Header (value = "DDS_SAMPLE_INFO") SampleInfo sampleInfo) {
        String result = "{\"sample\": ";
        result = result + "{\"data\": " + gson.toJson(message) + ", \"info\": " + gson.toJson(sampleInfo) + "}";
        result = result + "}";
        return result;
    }

}
