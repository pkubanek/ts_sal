package org.opensplice.demo.sal_Telemetry;
import java.util.Date;
import java.util.Random;
import java.net.*;
import java.io.*;
import java.sql.Timestamp;
import org.omg.dds.core.Duration;
import org.omg.dds.core.event.InconsistentTopicEvent;
import org.omg.dds.core.policy.*;
import org.omg.dds.domain.*;
import org.omg.dds.topic.Topic;
import org.omg.dds.pub.*;
import org.omg.dds.topic.TopicQos;
import org.opensplice.demo.sal_SALTOPICType;
import com.jezhumble.javasysmon.JavaSysMon;

public class salTelemetry<T> {
    private T saltype;
    private static DomainParticipantFactory dpf;
    private static DomainParticipant dp;
    private static Boolean isConnected=FALSE;
    private static Boolean isSubscriber=FALSE;
    private static Boolean isPublisher=FALSE;
    private TopicQos tQos;
    private Publisher pub;
    private Subscriber pub;
    private DataWriter<T> writer;
    private DataWriterQos dwQos;
    private DataReaderQos tdrQos, drQos; 
    private DataReader<T> dr;
    private Topic<T> topic;
    private int p_timeout=1;
    private int p_seqnum = 0;
    private int p_debug = 0;
    private double lastOuttime;
    private double lastIntime;
    private static InetAddress thisIp=InetAddress.getLocalHost();
    private static byte[] localIp=thisIp.getAddress;
    private static int p_ipaddr = 0;
    private static int p_pid = 0;

    public static void connect() throws Exception {
       if (!isConnected) {
          salTelemetry.dpf = DomainParticipantFactory.getInstance();
          salTelemetry.dp = dpf.createParticipant(0);
          tQos = new TopicQos(Reliability.Reliable());
          isConnected = TRUE;
          p_pid = salUtil.getPID();
          p_ipaddr = localIp[0]*256*256*256 + localIp[1]*256*256 + localIp[2]*256 + localIp[3];
       }
      } catch (InterruptedException e) { }
    }
 
    public void publisher(String topicId) throws Exception {
        if (!isConnected) {
           connect();
        }
        topic = dp.createTopic(topicId, saltype.class);
        pub = dp.createPublisher();
        dwQos = new DataWriterQos(Reliability.Reliable(),
                                  Durability.Transient(),
                                  History.KeepLast(10));
        writer = pub.createDataWriter(topic, dwQos);
        isPublisher = TRUE;
        if (p_debug > 0) {
           System.out.println("Created DataWriter for "+topicId);
        }
      } catch (InterruptedException e) { }
    }

    public void subscriber(String topicId) {
        if (!isConnected) {
           connect();
        }
        topic = dp.createTopic(topicId, saltype.class);
        // Create a Subscriber on the default Partition
        sub = dp.createSubscriber();
        // Get the default DataRederQos
        tdrQos = sub.getDefaultDataReaderQos();
        // Override the defaults to reflect your needs...
        drQos = tdrQos.with(
                        Reliability.Reliable(),
                        History.KeepLast(10),
                        Durability.Transient()
                );
        // Create a DataReader
        DataReader<T> dr = sub.createDataReader(topic, drQos);
        isSubscriber = TRUE;
    }


    public void putSample(T sample) throws Exception {
      p_seqnum++;
      sample.private_seqNum = p_seqnum;
      sample.private_origin = p_pid;
      sample.private_host = p_ipaddr;
      sample.private_sndStamp = salUtil.getTStamp();
      lastOuttime = sample.private_sndStamp;
      writer.write(sample);
      if (p_debug > 0) {
         System.out.println("putSample" + p_seqnum);
      }
     }catch (InterruptedException e) { }
    }

    public T getEachSample() throws Exception {
      List<Sample<T>> data = new LinkedList<Sample<T>>();
      dr.read(data);
      Iterator<Sample<T>> iterator = data.iterator();
      if (iterator.hasNext()) {
         T s = iterator.next().getData();
         s.private_rcvStamp = salUtil.getTStamp();
         lastIntime = s.private_rcvStamp;
         if (p_debug > 0) {
            System.out.println("getEachSample");
         }
         return s;
      } else {
         return null;
      }
     }catch (InterruptedException e) { }
    }



    public T getSample() throws Exception {
      List<Sample<T>> data = new LinkedList<Sample<T>>();
      dr.read(data);
      Iterator<Sample<T>> iterator = data.iterator();
      while (iterator.hasNext()) {
         T s = iterator.next().getData();
      }
      s.private_rcvStamp = salUtil.getTStamp();
      lastIntime = s.private_rcvStamp;
      if (p_debug > 0) {
         System.out.println("getSample");
      }
      return s;
     }catch (InterruptedException e) { }
    }

    public void setProperty(String key, String value) {
       switch (key.toLowerCase()) {
          case "timeout":
             p_timeout = Integer.parseInt(value);
             break;
          case "debug":
             p_debug = value;
             break;
       }
    }

    public String getProperty(String key) {
       String value="unknown";
       switch (key.toLowerCase()) {
          case "timeout":
             value = p_timeout.toString();
             break;
          case "debug":
             value = p_debug;
             break;
       }
       return value;
    }


    public static void main(String args[]) throws Exception {
        Random generator=new Random();
        Date date=new Date();
	int j;
        int period  = Integer.parseInt(args[0]);
        int N = Integer.parseInt(args[1]);

        sal_SALTOPICType SALTOPIC = new sal_SALTOPICType();
        salTelemetry<sal_SALTOPICType> myTelemetry;

        myTelemetry.connect();
        myTelemetry.publisher("SALTOPICTopic");
 
       for (int i = 0; i < N; ++i) {
//###SAL_DATA_SIM
            myTelemetry.putSample(SALTOPIC);
            if (p_debug > 0) {
               System.out.println("Published " + i);
            }

            try {
                Thread.sleep(period);
            } catch (InterruptedException e) { }
        }

        } catch (InterruptedException e) { }
    }
}


