package camel.dds.examples.camel_dds_jms_displayapp;

import org.apache.camel.Consume;
import org.apache.camel.Header;

import track.PointTrack;
import DDS.SampleInfo;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class PointTracktoJSONConverterBean {
    Gson gson = new GsonBuilder().serializeSpecialFloatingPointValues().create ();
    
    @Consume(uri="dds:track_PointTrack_topic:0/track.PointTrack?Partition=Battleship")
    public String onPointTrack(PointTrack message, @Header (value = "DDS_SAMPLE_INFO") SampleInfo sampleInfo) {
        String result = "{\"sample\": ";
        result = result + "{\"data\": " + gson.toJson(message);
        result = result + ", \"info\": " + gson.toJson(sampleInfo) + "}";
        result = result + "}";
        return result;
    }

}
