import java.util.*;
import java.lang.*;
import java.net.*;

public class GetIP
{
  public static void main(String args[]) {
  try{
  InetAddress ownIP=InetAddress.getLocalHost();
  byte[] localIP = ownIP.getAddress();
  System.out.println("IP of my system is := "+ownIP.getHostAddress());
  System.out.println("addr of my system is := "+localIP[0]+ localIP[1]+ localIP[2]+localIP[3]);
  }catch (Exception e){
  System.out.println("Exception caught ="+e.getMessage());
  }
  }
}
