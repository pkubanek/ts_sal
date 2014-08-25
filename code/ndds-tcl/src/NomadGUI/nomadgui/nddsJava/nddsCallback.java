package nomadgui.nddsJava;

import distinct.rpc.*;

// This is an interface that should be implemented by callback functions.
// It should be noted that unlike NDDS callback functions, these are THREAD
// SAFE! Therefore you can produce a message in response to it!

public abstract class nddsCallback {
  protected XDRType msg;
  public nddsCallback() {
    System.err.println("[nddsCallback] ERROR: Do not call the default constructor!");
  }
  public nddsCallback(XDRType x) {
    msg = x;
  }
  abstract public void exec(Object o);
} 
