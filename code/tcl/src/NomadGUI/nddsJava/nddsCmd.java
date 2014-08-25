package nddsJava;

import distinct.rpc.*;
import java.lang.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.*;
import java.util.*;

public class nddsCmd {
  private Socket serverSocket;
  private XDRStream xdrStream;
  private boolean isConnected;
  private BufferedWriter buffWriter;
  private OutputStreamWriter osWriter;

  public nddsCmd() {
    xdrStream = new XDRStream(nddsMsg.MAX_MSG_DATA_LENGTH);
    isConnected = false;
  }

  public boolean isConnected() {
    return(this.isConnected());
  }

  // Connect to server
  public void connect(String serverIP, int serverPort) {
    try {
      serverSocket = new Socket(serverIP, serverPort);
    } catch(UnknownHostException e) {
      System.err.println("[nddsCmd] ERROR: Don't know about server " + serverIP + ":" + serverPort);
      return;
    } catch (IOException e) {
      System.err.println("[nddsCmd] ERROR: Couldn't get socket to connect to " +
			 serverIP + ":" + serverPort); 
      return;
    }
    try {
      osWriter = new OutputStreamWriter
	(new BufferedOutputStream(serverSocket.getOutputStream()));
      buffWriter = new BufferedWriter(osWriter);
    } catch (IOException e) {
      System.err.println("[nddsCmd] ERROR: Could not open output stream.");
      return;
    }
      
    System.err.println("[nddsCmd] Connected to NDDS telemetry server!");
    this.isConnected = true;
  }

  // Disconnect from server
  public void disconnect() {
    if(this.isConnected) {
      try {
	buffWriter.close();
	serverSocket.close();
      } catch (IOException e) {
	System.err.println("[nddsCmd] ERROR: Disconnect failure!");
	return;
      }
      System.err.println("[nddsCmd] Disconnected from NDDS telemetry server!");
      this.isConnected = false;
    }
  }

  public nddsMsg sendCmd(nddsMsg cmd) {
    if(cmd == null) {
      return(null);
    }

    if(this.isConnected == false) {
      System.out.println("[nddsCmd] ERROR: Thread not connected to server!");
      return(null);
    }

    char tmpCharArray[];
    byte tmpByteArray[];
    char tmpNameArray[];

    // Write name to the socket
    tmpNameArray = new char[nddsMsg.MAX_MSG_NAME_LENGTH];
    tmpCharArray = cmd.getName().toCharArray();
    int len = cmd.getName().toCharArray().length;
    for(int i=0; i < len; i++) { // NOTE: This assumes that tmpCharray is 
                                 // initialized to 0 in the last 'new' 
                                 // statement
      tmpNameArray[i] = tmpCharArray[i];
    }
    try {
      buffWriter.write(tmpNameArray, 0, nddsMsg.MAX_MSG_NAME_LENGTH); 
      buffWriter.flush();
    } catch(IOException e) {
      System.err.println("[nddsCmd] ERROR: Failed to write NDDS message name: " + tmpCharArray);
    }

    // Encode data and write it to the socket
    cmd.getData().xdr_encode(xdrStream);
    try { 
      tmpCharArray = new char[nddsMsg.MAX_MSG_DATA_LENGTH];
      tmpByteArray = xdrStream.get_data();
      for(int i=0; i < tmpByteArray.length; i++) { // NOTE: This assumes that
	                                           // tmpCharArray is 
	                                           // initialized to 0 in the
	                                           // last 'new' statement
	tmpCharArray[i] = (char)tmpByteArray[i];
      }
      buffWriter.write(tmpCharArray, 0, nddsMsg.MAX_MSG_DATA_LENGTH);
      buffWriter.flush();
     
    } catch(IOException e) {
      System.err.println("[nddsCmd] ERROR: Failed to write NDDS message XDR data");
    }
    xdrStream.reset();
    
    if(cmd.getType() == nddsMsg.CLIENT_SERVER) {
      // TBD: A return message is expected
      return(null);
    } else {
      return(null);
    }
  }
}
