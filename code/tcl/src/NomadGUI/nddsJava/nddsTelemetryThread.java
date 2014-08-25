package nddsJava;

import distinct.rpc.*;
import java.lang.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.*;
import java.util.*;

public class nddsTelemetryThread extends Thread {
  private Vector regMsgs; // Contains a registry of nddsMsg objects
  private Socket serverSocket;
  private InputStreamReader ir;
  private BufferedReader br;
  private BufferedWriter buffWriter;
  private OutputStreamWriter osWriter;
  private String nameBuff;
  private char dataBuff[];
  //  private byte xdrBuff[];
  private boolean isConnected;
  private XDRStream xdrStream;
  private boolean runThread;

  public final String EXIT_STRING = "EXIT";
  public final int MAX_CLIENT_MSG_LEN = 1024;
  
  // Constructor
  public nddsTelemetryThread(Vector v) {
    regMsgs = v;
    nameBuff = new String();
    dataBuff = new char[nddsMsg.MAX_MSG_DATA_LENGTH];
    //    xdrBuff  = new byte[nddsMsg.MAX_MSG_DATA_LENGTH];
    xdrStream = new XDRStream(nddsMsg.MAX_MSG_DATA_LENGTH);
    this.isConnected = false;
  }

  public boolean isConnected() {
    return(this.isConnected());
  }

  // Connect to server
  public void connect(String serverIP, int serverPort) {
    try {
      serverSocket = new Socket(serverIP, serverPort);
    } catch(UnknownHostException e) {
      System.err.println("[nddsTelemetryThread] ERROR: Don't know about server " + 
			 serverIP + ":" + serverPort);
      return;
    } catch (IOException e) {
      System.err.println("[nddsTelemetryThread] ERROR: Couldn't get socket to connect to " +
			 serverIP + ":" + serverPort); 
      return;
    }
      
    try {
      ir = new InputStreamReader(serverSocket.getInputStream());
      br = new BufferedReader(ir); 
      osWriter = new OutputStreamWriter(new BufferedOutputStream(serverSocket.getOutputStream()));
      buffWriter = new BufferedWriter(osWriter);
    } catch (IOException e) {
      System.err.println("[nddsTelemetryThread] ERROR: Couldn't get I/O working!");
      return;
    }
    
    System.err.println("[nddsTelemetryThread] Connected to NDDS telemetry server!");
    this.isConnected = true;
  }

  // Disconnect from server
  public void disconnect() {
    if(this.isConnected) {
      try {
	buffWriter.write(EXIT_STRING, 0, EXIT_STRING.length());
	buffWriter.flush();
	runThread = false;
	this.isConnected = false;
	br.close();
	buffWriter.close();
	serverSocket.close();
      } catch (Exception e) {
	System.err.println("[nddsTelemetryThread] ERROR: " + e);
      }
    }
  }

  // Searches through the vector for an nddsMsg object that matches
  // 'name'. Returns null otherwise.
  public nddsMsg getMsg(String name) {
    if(name != null) {
      nddsMsg m;
      for(int i=0; i < regMsgs.size(); i++) {
	m = (nddsMsg)regMsgs.get(i);
	if(name.equals(m.getName())) {
	  return(m);
	}
      }
    }
    return(null);
  }

  // Main run loop for the thread.
  public void run() {
    char tmpBuff[] = new char[nddsMsg.MAX_MSG_DATA_LENGTH]; 
    nddsMsg msg;
    if(this.isConnected) {
      runThread = true;
      int count;
      try {
	while(runThread) {
	  for(nameBuff = br.readLine(); nameBuff != null; nameBuff = br.readLine()) {

	    for(int i=0; i < nddsMsg.MAX_MSG_DATA_LENGTH; i++) {
	      dataBuff[i] = 0;
	    }

	    // Read the XDR data
	    count = br.read(dataBuff, 0, nddsMsg.MAX_MSG_DATA_LENGTH);
	    if(count < nddsMsg.MAX_MSG_DATA_LENGTH) {
	      while(count < nddsMsg.MAX_MSG_DATA_LENGTH) {
		count += br.read(tmpBuff, count, nddsMsg.MAX_MSG_DATA_LENGTH - count);
	      }
	    }

	    // Place the data into the XDR byte buffer
	    for(int i=0; i < nddsMsg.MAX_MSG_DATA_LENGTH; i++) {
	      xdrStream.put_byte((byte)dataBuff[i]);
	    }

	    
	    
	    // Get the proper message, so it can be decoded.
	    msg = getMsg(nameBuff);
	    if(msg != null) {             // Got a valid message name
	      XDRType x = msg.getData();
	      try {
		// Decode the message data
		x.xdr_decode(xdrStream);
		xdrStream.reset();

		// Do callback, if any
		msg.doCallback();

	      } catch (distinct.rpc.RPCError e) {
		System.err.println("[nddsTelemetryThread] ERROR: " + e); 
	      }
	    } // TBD: Do something if the message name is invalid?
	  }
	}
      } catch (IOException e) {
	System.err.println("[nddsTelemetryThread] ERROR: I/O error during main thread loop!");
	return;
      }
       
      try {
	br.close();
	serverSocket.close();
	xdrStream.reset();
      } catch (IOException e) {
	System.err.println("[nddsTelemetryThread] ERROR: Failure while quitting thread!");
	return;
      } 
    } else {
      System.err.println("[nddsTelemetryThread] ERROR: Thread not connected to server!");
      return;
    }
    
    System.out.println("[nddsTelemetryThread] Exiting thread...");
  }

}
      


