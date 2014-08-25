/************************************************************************
 * 
 * Copyright (c) 2009 PrismTech Ltd. All rights Reserved.
 * 
 * LOGICAL_NAME: BaseApplication.java FUNCTION: OpenSplice DDS Power Tools
 * Tutorial example code. MODULE: Tutorial for the Java programming language.
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class contains the common functionality for the applications in the
 * example.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.util.Date;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;
import javax.swing.border.Border;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.text.DefaultFormatter;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;

import DDS.Duration_t;


abstract public class BaseApplication
{
   // Random number generator and seed value.
   protected Random m_random;

   private long m_seed = 0L;

   // GUI: simple bevelled border used for the titled borders.
   protected static Border m_bevelBorder;

   // JVM information control reference.
   protected JVMControl m_jvmControl = new JVMControl ();

   // Controls debug output.
   protected boolean DEBUG = true;

   // Determines if application should automatically start.
   protected static boolean AUTO_START = false;

   // Timeout for shutdown initially set to 0 , i.e. no timeout run
   // indefinitely
   protected static long TIME_OUT = 0;

   protected static boolean runWithTimeOut = false;

   // Constants for transport priority. Integer.MAX_VALUE-1 is the highest
   // permissable
   // value for both latency budget and transport priority.
   protected static final int MINIMUM_TRANSPORT_PRIORITY = 0;

   protected static final int MAXIMUM_TRANSPORT_PRIORITY = Integer.MAX_VALUE - 1;

   protected static final int TRANSPORT_PRIORITY_INTERVAL = 1;

   // Constants for JVM information panel update interval.
   protected static final int MINIMUM_JVM_UPDATE_FREQ = 1;

   protected static final int MAXIMUM_JVM_UPDATE_FREQ = 30;

   protected static final int JVM_UPDATE_FREQ_INTERVAL = 1;

   protected static final int DEFAULT_JVM_UPDATE_FREQ = 5;

   // Constants for update frequency panel (Sensor and Display).
   protected static double DEFAULT_UPDATE_FREQUENCY = 20.0D;

   protected static double MINIMUM_UPDATE_FREQUENCY = 0.0D;

   protected static double MAXIMUM_UPDATE_FREQUENCY = 50.0D;

   protected static double UPDATE_FREQUENCY_INTERVAL = 0.2D;

   // "Standard" size for various controls.
   protected static Dimension m_controlSize = new Dimension (100, 20);

   // Synchronisation object for data readers and data writers. This object is
   // used to
   // ensure that QoS changes and calls to readers/writers do not happen at the
   // same time. The
   // DataReaderControl and DataWriterControl classes synchronise on this when
   // changing the QoS
   // properties; application code should do the same before performing calls.
   protected Object m_syncObject = new Integer (27);

   /**
    * Base control panel for data reader/writer configuration.
    */
   private abstract class BaseControl
   {
      // Title reference.
      protected String m_title;

      // GUI elements.
      protected JPanel m_panel;

      protected JPanel m_lbPanel;

      protected JLabel m_lbLabel;

      protected JFormattedTextField m_lbField;

      // Default value for latency budget.
      private double m_defaultLB;

      // Flag: set true when the QoS is set.
      protected boolean m_lbChanged = false;

      private BaseControl (String title, double defaultLB)
      {
         m_title = title;
         m_defaultLB = defaultLB;
      }

      public String getTitle ()
      {
         return m_title;
      }

      /**
       * Sets the latency budget QoS.
       *
       * @param budget
       *            The latency budget value to apply
       */
      protected abstract void setLatencyBudgetQoS (double budget);

      protected void initialise ()
      {
         // Main panel.
         m_panel = new JPanel ();
         m_panel.setBorder (BorderFactory.createTitledBorder (m_bevelBorder, m_title));

         // Latency budget controls.
         m_lbLabel = new JLabel ("Latency Budget");
         m_lbField = new JFormattedTextField (new Double (m_defaultLB));
         DefaultFormatter fmt = new NumberFormatter (new DecimalFormat ("#.#########"));
         fmt.setValueClass (m_lbField.getValue ().getClass ());
         DefaultFormatterFactory fmtFactory = new DefaultFormatterFactory (fmt, fmt, fmt);
         m_lbField.setFormatterFactory (fmtFactory);
         m_lbField.setPreferredSize (m_controlSize);

         // Latency budget listener.
         m_lbField.addPropertyChangeListener ("value", new PropertyChangeListener ()
         {
            public void propertyChange (PropertyChangeEvent pce)
            {
               double newValue = ((Double) pce.getNewValue ()).doubleValue ();
               setLatencyBudgetQoS (newValue);
            }
         });

         // Latency budget panel.
         m_lbPanel = new JPanel (new FlowLayout (FlowLayout.RIGHT));
         m_lbPanel.add (m_lbLabel);
         m_lbPanel.add (m_lbField);
      }

      /**
       * Returns a reference to the panel used to display the controls.
       *
       * @return The panel
       */
      public JPanel getPanel ()
      {
         return m_panel;
      }

      /**
       * Sets the latency budget. Updates the spinner value and ensures that
       * the data writer QoS is set.
       *
       * @param budget
       *            The latency budget value to apply
       */
      public void setLatencyBudget (double budget)
      {
         m_lbChanged = false;
         m_lbField.setValue (budget);
         if (!m_lbChanged)
         {
            setLatencyBudgetQoS (budget);
         }
      }

      /**
       * Creates a Duration_t instance from the passed double.
       *
       * @param value
       *            The double value to use
       * @return The Duration_t instance
       */
      protected Duration_t getDuration (double value)
      {
         int secs = 0;
         int nanosecs = 0;

         Double d = new Double (value);
         secs = d.intValue ();

         // If the value is greater than Duration_t can store,
         // leave the nanoseconds as zero.
         if (secs != Integer.MAX_VALUE)
         {
            float rem = (float) (value - secs);
            int factor = (int) Math.pow (10, 9);
            nanosecs = (int) (rem * factor);
         }

         Duration_t dur = new Duration_t ();
         dur.sec = secs;
         dur.nanosec = nanosecs;

         return dur;
      }
   }

   /**
    * Creates a string (used for message padding) of the specified size.
    *
    * @param size
    *            The size of the array
    * @return The string
    */
   protected String createPadding (int size)
   {
      byte[] padding = new byte[size];
      for (int i = 0; i < size; i++)
      {
         padding[i] = 'm';
      }

      String s = new String (padding);
      if (DEBUG)
      {
         output ("Padding string length = " + s.length ());
      }

      return s;
   }

   /**
    * Controls for displaying the JVM information.
    */
   protected class JVMControl
   {
      // MBean reference for memory figures.
      private MemoryMXBean m_memBean;

      // Update task/thread references and delay.
      private PerformanceUpdater m_performanceTask;

      private Thread m_performanceThread;

      private long m_perfDelay = (long) (DEFAULT_JVM_UPDATE_FREQ * 1000);

      // GUI elements.
      private JPanel m_panel;

      private JLabel m_chLabel;

      private JTextField m_chField;

      private JLabel m_cnhLabel;

      private JTextField m_cnhField;

      private JLabel m_luLabel;

      private JTextField m_luField;

      private JLabel m_ufLabel;

      private JSpinner m_ufSpinner;

      public JVMControl ()
      {
         m_chLabel = new JLabel ("Current Memory (heap)");
         m_chField = new JTextField (10);
         m_chField.setEditable (false);
         m_chField.setHorizontalAlignment (JTextField.RIGHT);
         m_cnhLabel = new JLabel ("Current Memory (Non-heap)");
         m_cnhField = new JTextField (10);
         m_cnhField.setEditable (false);
         m_cnhField.setHorizontalAlignment (JTextField.RIGHT);
         m_luLabel = new JLabel ("Last Update");
         m_luField = new JTextField (12);
         m_luField.setEditable (false);
         m_luField.setHorizontalAlignment (JTextField.RIGHT);
         m_ufLabel = new JLabel ("Delay between updates (sec)");

         SpinnerNumberModel ufModel = new SpinnerNumberModel (DEFAULT_JVM_UPDATE_FREQ, MINIMUM_JVM_UPDATE_FREQ,
               MAXIMUM_JVM_UPDATE_FREQ, JVM_UPDATE_FREQ_INTERVAL);
         m_ufSpinner = new JSpinner (ufModel);

         // Update frequency listener.
         m_ufSpinner.addChangeListener (new ChangeListener ()
         {
            public void stateChanged (ChangeEvent ce)
            {
               JSpinner spinner = (JSpinner) ce.getSource ();
               Integer val = (Integer) spinner.getValue ();
               int freq = val.intValue ();

               m_perfDelay = (long) (freq * 1000);
               output ("JVM information update delay set to " + m_perfDelay + "ms");
            }
         });

         //
         // Construct the performance panel.
         //

         JPanel p1 = new JPanel (new FlowLayout (FlowLayout.RIGHT));
         p1.add (m_chLabel);
         p1.add (m_chField);

         JPanel p2 = new JPanel (new FlowLayout (FlowLayout.RIGHT));
         p2.add (m_cnhLabel);
         p2.add (m_cnhField);

         JPanel p3 = new JPanel (new FlowLayout (FlowLayout.RIGHT));
         p3.add (m_ufLabel);
         p3.add (m_ufSpinner);

         JPanel p4 = new JPanel (new FlowLayout (FlowLayout.RIGHT));
         p4.add (m_luLabel);
         p4.add (m_luField);

         JPanel innerPanel = new JPanel (new GridLayout (4, 1));
         innerPanel.add (p1);
         innerPanel.add (p2);
         innerPanel.add (p3);
         innerPanel.add (p4);

         m_panel = new JPanel (new BorderLayout (10, 5));
         m_panel.setBorder (BorderFactory.createTitledBorder (m_bevelBorder, "JVM / System Information"));
         m_panel.add (innerPanel, BorderLayout.NORTH);

         // Obtain MBean reference.
         m_memBean = ManagementFactory.getMemoryMXBean ();
      }

      /**
       * Starts the updates.
       */
      protected void startUpdates ()
      {
         if (m_performanceTask == null)
         {
            m_performanceTask = new PerformanceUpdater ();
            m_performanceThread = new Thread (m_performanceTask);
            m_performanceThread.start ();
         }
      }

      /**
       * Stops the updates.
       */
      protected void stopUpdates ()
      {
         if (m_performanceTask != null)
         {
            synchronized (m_performanceTask)
            {
               m_performanceTask.m_keepGoing = false;
               m_performanceTask.notify ();
            }

            try
            {
               m_performanceThread.join ();
            }
            catch (InterruptedException ie)
            {
               output ("Join on performance thread interrupted");
            }
         }
      }

      /**
       * Returns a reference to the panel used to display the information.
       *
       * @return The panel
       */
      public JPanel getPanel ()
      {
         return m_panel;
      }

      /**
       * Runnable to update the performance figures.
       */
      private class PerformanceUpdater implements Runnable
      {
         boolean m_keepGoing = true;

         boolean m_firstRun = true;

         DateFormat m_df = DateFormat.getDateTimeInstance (DateFormat.SHORT, DateFormat.MEDIUM);

         private void delay (long duration)
         {
            if (duration != 0)
            {
               try
               {
                  synchronized (this)
                  {
                     wait (duration);
                  }
               }
               catch (InterruptedException ie)
               {
                  output ("Delay of " + duration + "ms interrupted");
               }
            }
         }

         public void run ()
         {
            long lastCurrentHeap = 0L;
            long lastCurrentNonHeap = 0L;

            while (m_keepGoing)
            {
               delay (m_perfDelay);

               long currentHeap = m_memBean.getHeapMemoryUsage ().getUsed () / 1024;
               long currentNonHeap = m_memBean.getNonHeapMemoryUsage ().getUsed () / 1024;

               m_chField.setText (createText (Long.toString (currentHeap), Long.toString (currentHeap - lastCurrentHeap), "K"));
               m_cnhField.setText (createText (Long.toString (currentNonHeap), Long.toString (currentNonHeap - lastCurrentNonHeap),
                     "K"));
               m_luField.setText (m_df.format (new java.util.Date ()));

               lastCurrentHeap = currentHeap;
               lastCurrentNonHeap = currentNonHeap;
               m_firstRun = false;
            }
         }

         private String createText (String value, String diff, String suffix)
         {
            StringBuffer sb = new StringBuffer (value);
            if (suffix != null)
            {
               sb.append (suffix);
            }

            if (!m_firstRun)
            {
               sb.append (" (");

               float f = Float.parseFloat (diff);
               if (f > 0)
               {
                  sb.append ("+");
               }

               sb.append (diff);

               if (suffix != null)
               {
                  sb.append (suffix);
               }

               sb.append (")");
            }

            return sb.toString ();
         }
      }
   }

   public BaseApplication ()
   {
      // General GUI initialisation.
      m_bevelBorder = BorderFactory.createLoweredBevelBorder ();

      // Create the JVM information control and start the updates.
      m_jvmControl = new JVMControl ();
      startJVMInformationUpdates ();
   }

   /**
    * Handles command line arguments. Currently only the DEBUG flag and random
    * number generator seed are passed.
    */
   protected void parseArguments (String[] args)
   {
      // First argument: debug output flag (string, "true" or otherwise).
      if (args.length >= 1)
      {
         DEBUG = args[0].equalsIgnoreCase ("true");
      }

      // Second argument: seed for random number generator (numeric).
      if (args.length >= 2)
      {
         try
         {
            m_seed = Long.parseLong (args[1]);
         }
         catch (NumberFormatException nfe)
         {
            // Ignore.
         }
      }
      m_random = initialiseRandom (m_seed);

      // Third argument: automatically start the application.
      if (args.length >= 3)
      {
         AUTO_START = args[2].equalsIgnoreCase ("true");
      }

      // Fourth argument: timeout
      if (args.length >= 4)
      {
         TIME_OUT = new Long (args[3]).longValue ();
         if (TIME_OUT > 0)
         {
            runWithTimeOut = true;
         }
      }
   }

   /**
    * Initialises a random number generator and sets the seed. If the passed
    * long is non-zero it is used as the seed, else the value of
    * System.currentTimeMillis() is used.
    */
   protected Random initialiseRandom (long seed)
   {
      Random random = new Random ();
      if (seed != 0)
      {
         random.setSeed (seed);
         if (DEBUG)
         {
            output ("Set seed to " + seed + " (specified value)");
         }
      }
      else
      {
         long currentTime = System.currentTimeMillis ();
         random.setSeed (currentTime);
         if (DEBUG)
         {
            output ("Set seed to " + currentTime + " (current time)");
         }
      }

      return random;
   }

   /**
    * Launches a thread that triggers a click on the specified button after a
    * delay.
    *
    * @param delay
    *            How long to delay (milliseconds) before triggering the click
    * @param button
    *            The button to click
    */
   protected static void launchStartThread (long delay, JButton button)
   {
      TriggerButtonTask startTask = new TriggerButtonTask (delay, button);
      Thread t = new Thread (startTask);
      t.start ();
   }

   /**
    * Starts the updates for the JVM information panel.
    */
   protected void startJVMInformationUpdates ()
   {
      m_jvmControl.startUpdates ();
   }

   /**
    * Stops the updates for the JVM information panel.
    */
   protected void stopJVMInformationUpdates ()
   {
      m_jvmControl.stopUpdates ();
   }

   /**
    * Triggers a wait for a specific period of time. Used for applications that
    * need to keep running but don't have a thread to join on.
    */
   protected synchronized void triggerWait (long timeout)
   {
      try
      {
         wait (timeout);
      }
      catch (InterruptedException ie)
      {
         // Ignore.
      }
   }

   /**
    * Triggers a wait. Used for applications that need to keep running but
    * don't have a thread to join on.
    */
   protected synchronized void triggerWait ()
   {
      try
      {
         wait ();
      }
      catch (InterruptedException ie)
      {
         // Ignore.
      }
   }

   /**
    * Output a message.
    *
    * @param message
    *            The message to display
    * @return The "complete" message (with application name and timestamp) that
    *         has been sent to the console
    */
   protected String output (String message)
   {
      StringBuffer sb = new StringBuffer ();
      sb.append (new Date ());
      sb.append (" :: ");
      sb.append (toString ());
      sb.append (" :: ");
      sb.append (message);
      String s = sb.toString ();

      System.out.println (s);
      return s;
   }
}
