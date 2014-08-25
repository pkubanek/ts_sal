package camel.dds.demo;

import org.apache.camel.Consume;
import org.apache.camel.Header;

import com.google.gson.Gson;

import Chat.SimpleChatMessage;
import DDS.SampleInfo;

public class ChatMessagetoJSONConverterBean {

      @Consume(uri="dds:Chat_SimpleChatMessage:0/Chat.SimpleChatMessage?ReliabilityKind=RELIABLE&contentFilter=userID%20%3C%3E%201&Partition=ChatRoom")
	  public String onChat(SimpleChatMessage message, @Header (value = "DDS_SAMPLE_INFO") SampleInfo sampleInfo) {
		  String result = "{\"sample\": ";
		  Gson gson = new Gson();
		  result = result + "{\"data\": " + gson.toJson(message) + ", \"info\": " + gson.toJson(sampleInfo) + "}";
		  result = result + "}";
		  return result;
	  }
}
