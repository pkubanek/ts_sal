/* import java.util.Timer;
import java.util.TimerTask;

class MyTask extends TimerTask {
    public void run() {
	MyListener myListener = new MyListener();
	System.out.println("Time's up!");
    }
  }
class Main { 
    public static void main(String args[]) {
	Timer timer = new Timer();
        timer.schedule(new MyTask(),1000,1000);
	System.out.println("Task scheduled.");
    }
}
 */

import javax.swing.Timer;
class Main { 
    public static void main(String args[]) {
    MyListener myListener = new MyListener();
        Timer timer = new Timer(10, myListener);
        timer.start();
        while(timer.isRunning()) {
            System.out.print(".");
        }
    }
}

