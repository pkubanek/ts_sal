package nddsJava;

//import nddsJava.*;
import distinct.rpc.*;

public class nddsMsg {
  private XDRType      data; // The XDR structure
  private String       name; // The standardized name
  private int          type; // See next few lines
  private nddsCallback callback; // Called when this message is received
  private Object       callbackParam;
  public static final int PUBLISH_SUBSCRIBE = 0;
  public static final int CLIENT_SERVER = 1;

  public static final int MAX_MSG_NAME_LENGTH = 100;
  public static final int MAX_MSG_DATA_LENGTH = 8096;

  // All NDDS message names go here
  public static final String BOD_DERIVED_STATE_MSG_NAME = "bodDerivedState";
  public static final String POS_DERIVED_STATE_MSG_NAME = "posDerivedState";
  public static final String KVH_DERIVED_STATE_MSG_NAME = "kvhDerivedState";
  public static final String WEATHER_STATE_MSG_NAME = "weatherState";
  public static final String RT_AMP_STATE_MSG_NAME = "rtAmpState";
  public static final String RT_CONTROL_STATE_MSG_NAME = "rtControlState";
  
  public nddsMsg() {}

  public nddsMsg(XDRType data, String name, int type, 
		 nddsCallback callback, Object callbackParam) {
    this.data = data;
    this.name = name;
    this.type = type;
    this.callback = callback;
    this.callbackParam = callbackParam;
  }

  public XDRType getData() {
    return(data);
  }

  public String getName() {
    return(name);
  }

  public int getType() {
    return(type);
  }

  public void setData(XDRType x) {
    this.data = x;
  }

  public void setName(String s) {
    this.name = s;
  }

  public void setType(int i) {
    this.type = i;
  }

  public void doCallback() {
    if(callback != null) {
      callback.exec(callbackParam);
    }
  }
}
