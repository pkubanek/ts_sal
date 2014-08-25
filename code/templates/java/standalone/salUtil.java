import java.sql.Timestamp;
import java.util.Date;
import com.jezhumble.javasysmon.JavaSysMon;

public class salUtil
{
	
	public static int getPID () {
 	    JavaSysMon monitor = new JavaSysMon();
            int pid = monitor.currentPid();
            return pid;
        }

        public static double getTStamp () {
            double ts;
            java.util.Date date= new java.util.Date();
            java.sql.Timestamp stamp = new Timestamp(date.getTime());
            ts = (double) stamp.getTime()/1000.;
            return ts;
        }

// Invoke with java -classpath ./jar/javasysmon.jar:. salUtil
        public static void main( String[] args )
        throws InterruptedException {
            System.out.println("Process id is " + salUtil.getPID());
            System.out.println("Time in secs since 1970.0 is " + salUtil.getTStamp());
            Thread.sleep(1000);
            System.out.println("Time in secs since 1970.0 is " + salUtil.getTStamp());
        }
}


