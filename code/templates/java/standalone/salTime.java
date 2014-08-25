import java.sql.Timestamp;
import java.util.Date;

public class salTime
{
    public static void main( String[] args )
    throws InterruptedException     {
         
	 java.util.Date date= new java.util.Date();
         java.sql.Timestamp stamp = new Timestamp(date.getTime());
	 System.out.println(stamp);
	 System.out.println(stamp.getTime());
         Thread.sleep(1000);
	 System.out.println(stamp.getTime());
         int pid = CLibrary.INSTANCE.getpid();
         System.out.println("pid is " + pid);
    }
}
