/************************************************************************
 *
 * Copyright (c) 2009
 * PrismTech Ltd.
 * All rights Reserved.
 *
 * LOGICAL_NAME:    DisplayApp.java
 * FUNCTION:        OpenSplice DDS Power Tools Tutorial example code.
 * MODULE:          Tutorial for the Java programming language.
 * DATE             April 2009.
 ************************************************************************
 *
 * This class contains the implementation of the identification application.
 *
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import javax.jms.ConnectionFactory;
import javax.swing.BorderFactory;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingUtilities;
import javax.swing.border.BevelBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.camel.CamelContext;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.impl.DefaultCamelContext;
import org.springframework.jms.connection.CachingConnectionFactory;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import track.Classification_enum;
import track.ObjectLocation;
import track.PointTrack;
import track.Pos;
import track.TrackState;
import DDS.SampleInfo;

public class DisplayApp extends BaseApplication {
   // Interface elements.
   public static JFrame m_frame;

   private static JPanel m_sensorPanel;

   private static JPanel m_infoPanel;

   private static JPanel m_summaryPanel;

   private static JButton m_exitButton;

   private DisplayApplet m_displayApplet;

   // If true, all objects on the battlefield will be displayed: if false, only
   // those
   // within sensor range.
   private boolean m_displayBattlefield = true;

   // If true, object labels show position information: if false, only the
   // object ID
   // is shown.
   private boolean m_fullObjectInfo = true;

   // Delay (in milliseconds) between updating the display of
   // PointTrack/TrackState data.
   // This is calculated from the update frequency.
   public long m_updateDelay;

   // Delay (in milliseconds) between updating the display of ObjectLocation
   // data. This
   // delay is not configurable via the interface and is independent of the
   // update frequency.
   public long m_battlefieldUpdateDelay = 50L;

   // The PointTrack processor reference.
   private PointTrackProcessor m_ptdrListener;

   // The TrackState processor reference.
   private TrackStateProcessor m_tsdrListener;

   // The ObjectLocation data reader listener reference.
   private ObjectLocationProcessor m_oldrListener;

   // Reference to the display update task.
   private UpdateDisplay m_updateTask;

   // Reference to the thread running the display update task.
   private Thread m_updateThread;

   // References for the table in the information panel.
   private static JTable m_infoTable;

   private static ArrayListTableModel m_infoTableModel;

   private static String[] m_infoTableHeaders = { "ID", "Dir", "Dist", "Ang" };

   // References for the table in the summary panel.
   private static JTable m_summaryTable;

   private static ArrayListTableModel m_summaryTableModel;

   private static String[] m_summaryTableHeaders = { "Total", "No Position",
         "Unidentified", "Unknown", "Friendly", "Hostile" };

   // Collection of the combined information from PointTrack and TraceState
   // topics.
   private HashMap<Integer, ObjectData> m_objects = new HashMap<Integer, ObjectData>();

   // Indicates that an object has had classification information but no
   // position information.
   private Pos NO_POSITION = new Pos(-27, -27, -27);

   // Map of current objects on the battlefield (from the ObjectLocation
   // topic).
   private HashMap<Integer, ObjectLocation> m_battlefield = new HashMap<Integer, ObjectLocation>();

   // Default latency budget (for all data readers).
   public static double DEFAULT_LATENCY_BUDGET = 0D;
   
   // Camel context
   private CamelContext context = null;
   
   /**
    * Combined information for an object.
    */
   class ObjectData {
      int m_id;

      Pos m_position;

      Classification_enum m_classification;

      public String toString() {
         StringBuffer sb = new StringBuffer("ID: ");
         sb.append(m_id);
         sb.append(", DIR: ");
         sb.append(Math.round(m_position.direction));
         sb.append(", DIST: ");
         sb.append(Math.round(m_position.distance));
         sb.append(", ANG: ");
         sb.append(Math.round(m_position.angle));

         return sb.toString();
      }

      public String toStringShort() {
         StringBuffer sb = new StringBuffer();
         sb.append(m_id);
         sb.append(" (");
         sb.append(Math.round(m_position.direction));
         sb.append("/");
         sb.append(Math.round(m_position.distance));
         sb.append("/");
         sb.append(Math.round(m_position.angle));
         sb.append(")");

         return sb.toString();
      }
   }

   /**
    * Processor implementation for the ObjectLocation topic. This reads the 
    * ActiveMQTextMessage and translates it back into TrackState objects
    * before updating the display.
    * 
    * We need more processing in this class because the ObjectLocations come
    * in batches.
    */   
   class ObjectLocationProcessor implements Processor {
       private Gson gson = new Gson();

       public void process(Exchange e) {
           // The processor parses the JSON string back into an ObjectLocation
           // object before updating the display.
           String jsonString = (String) e.getIn().getBody();
           int beginIndex = jsonString.indexOf("{\"data\": ");
           int endIndex = 0;
           while (beginIndex != -1) {
               beginIndex = beginIndex + 9;
               endIndex = jsonString.indexOf(", \"info\": ", beginIndex);
               String objectLocationString = jsonString.substring(beginIndex, endIndex);
               ObjectLocation location = gson.fromJson(objectLocationString, ObjectLocation.class);
               String content = new String (location.trackId + ", (" + location.x + ", " + location.y + ", " + location.z + ")");
               beginIndex = endIndex + 10;
               endIndex = jsonString.indexOf ("}}", beginIndex) + 1;
               String sampleInfoString = jsonString.substring(beginIndex, endIndex);
               SampleInfo sample = gson.fromJson(sampleInfoString, SampleInfo.class);
               synchronized (m_syncObject) {
                   synchronized (m_battlefield) {
                       Integer mapKey = new Integer(location.trackId);

                       // Note that this is the ONLY reference to DDS required
                       // in the class. We could substitute this with our own 
                       // constant to remove the dependency on the DDS classes
                       // altogether.
                       if (sample.instance_state != DDS.ALIVE_INSTANCE_STATE.value) {
                           m_battlefield.remove(mapKey);

                           if (DEBUG) {
                               output("Object ID " + location.trackId
                                       + " has left the battlefield");
                           }
                       } else {
                           ObjectLocation mapEntry = (ObjectLocation) m_battlefield.get(mapKey);
                           if (mapEntry == null) {
                               mapEntry = new ObjectLocation();
                               mapEntry.trackId = location.trackId;
                               m_battlefield.put(mapKey, mapEntry);

                               if (DEBUG) {
                                   output("Object ID " + location.trackId
                                           + " has joined the battlefield");
                               }
                           }

                           mapEntry.x = location.x;
                           mapEntry.y = location.y;
                           mapEntry.z = location.z;
                       }
                   }
               }
               beginIndex = jsonString.indexOf("{\"data\": ", endIndex);
           }
       }
   }
   
   /**
    * Processor implementation for the PointTrack topic. This reads the 
    * ActiveMQTextMessage and translates it back into TrackState objects
    * before updating the display.
    */   
   class PointTrackProcessor implements Processor {
       private Gson gson = new Gson();

       public void process(Exchange e) {
           // The processor parses the JSON string back into an ObjectLocation
           // object before updating the display.
           String jsonString = (String) e.getIn().getBody();
           int beginIndex = jsonString.indexOf("{\"data\": ") + 9;
           int endIndex = jsonString.indexOf(", \"info\": ");
           String pointTrackString = jsonString.substring(beginIndex, endIndex);
           PointTrack track = gson.fromJson(pointTrackString, PointTrack.class);
           String content = new String (track.trackId + ", (" + track.position.angle + ", " + track.position.direction + ", " + track.position.distance + ")");
           beginIndex = endIndex + 10;
           endIndex = jsonString.indexOf ("}}}") + 1;
           String sampleInfoString = jsonString.substring(beginIndex, endIndex);
           SampleInfo sample = gson.fromJson(sampleInfoString, SampleInfo.class);
           
           // We monitor for disposals on this topic. We cannot do this on
           // TrackState
           // for two reasons:
           //
           // 1) The target selection filtering on TrackState will mean
           // disposal indications
           // will be "lost" for classifications other than the
           // currently-selected one.
           // 2) When Identification is stopped, all existing PointTrack
           // instances will be
           // disposed. In this case we do not want to trigger map removal as
           // the
           // affected objects are still within scope range.

           synchronized (m_syncObject) {
               // Note that this is the ONLY reference to DDS required
               // in the class. We could substitute this with our own 
               // constant to remove the dependency on the DDS classes
               // altogether.
               if (sample.instance_state != DDS.ALIVE_INSTANCE_STATE.value) {
                   // Process "disposed" / "no longer alive" indications
                   // from the sensor application.
                   if (DEBUG) {
                       output("Object ID "
                               + track.trackId
                               + " has been disposed or is no longer available (instance state "
                               + sample.instance_state
                               + ", topic: PointTrack)");
                   }

                   removeFromMap(track.trackId);
               } else {
                   updateMap(track.trackId, track.position);
               }
           }
       }
   }

   /**
    * Processor implementation for the TrackState topic. This reads the 
    * ActiveMQTextMessage and translates it back into TrackState objects
    * before updating the display.
    * 
    * The class also acts as a custom JsonDeserializer for the Classification_enum
    * class because it does not have a default constructor.
    */
   class TrackStateProcessor implements Processor, JsonDeserializer<Classification_enum> {
       
       private Gson gson = null;
       
       public TrackStateProcessor () {
           gson = new GsonBuilder ().registerTypeAdapter (Classification_enum.class, this).create ();
       }

       public void process(Exchange e) {
           // The processor parses the JSON string back into an ObjectLocation
           // object before updating the display.
           String jsonString = (String) e.getIn().getBody();
           int beginIndex = jsonString.indexOf("{\"data\": ") + 9;
           int endIndex = jsonString.indexOf(", \"info\": ");
           String trackStateString = jsonString.substring(beginIndex, endIndex);
           TrackState state = gson.fromJson(trackStateString, TrackState.class);
           String content = new String (state.trackId + ", (" + state.classification + ")");
           beginIndex = endIndex + 10;
           endIndex = jsonString.indexOf ("}}}") + 1;
           String sampleInfoString = jsonString.substring(beginIndex, endIndex);
           SampleInfo sample = gson.fromJson(sampleInfoString, SampleInfo.class);

           synchronized (m_syncObject) {
               // Note that this is the ONLY reference to DDS required
               // in the class. We could substitute this with our own 
               // constant to remove the dependency on the DDS classes
               // altogether.
               if (sample.instance_state == DDS.ALIVE_INSTANCE_STATE.value) {
                   updateMap(state.trackId, state.classification);
               }
           }
       }

       public Classification_enum deserialize(JsonElement json, Type type,
               JsonDeserializationContext context) throws JsonParseException {
           JsonElement element = ((JsonObject) json).get ("__value");
           return Classification_enum.from_int(element.getAsInt());
       }
   }

   /**
    * Handles the display.
    */
   class UpdateDisplay implements Runnable {
      private boolean m_keepGoing = true;

      private void delay(long duration) {
         if (duration != 0) {
            try {
               synchronized (UpdateDisplay.this) {
                  wait(duration);
               }
            } catch (InterruptedException ie) {
               output("Delay of " + duration + "ms interrupted");
            }
         }
      }

      public String toString() {
         return "UpdateDisplay";
      }

      public void run() {
         while (getKeepGoing()) {
            delay(m_updateDelay);
            m_displayApplet.repaint();
         }
      }

      public synchronized void stopUpdateDisplay() {
         m_keepGoing = false;
      }

      private synchronized boolean getKeepGoing() {
         return m_keepGoing;
      }
   }

   /**
    * Display applet.
    */
   class DisplayApplet extends JApplet {
      private static final long serialVersionUID = 1L;

      // Reference to the display image.
      private BufferedImage m_image;

      // Reference to the Graphics2D instance.
      private Graphics2D m_graphics;

      // Scale and translate data; these are stored as members so they are
      // only
      // recalculated as needed (e.g. each time the screen size changes).
      private double m_scale_x;

      private double m_scale_y;

      private int m_translate_x;

      private int m_translate_y;

      /**
       * Displays an individual object, using whatever scale and
       * transformation are in place on the Graphics2D instance.
       * 
       * @param label
       *            String to place next to the object's marker
       * @param x
       *            X coordinate
       * @param y
       *            Y coordinate
       */
      private void displayObject(String label, int x, int y) {
         // Display the object and its information; the text is offset
         // slightly to
         // improve the appearance and avoid overlapping the circle.
         int width = 8;
         java.awt.geom.Ellipse2D circle = new java.awt.geom.Ellipse2D.Float(
               x - width / 2, y - width / 2, width, width);

         Color old = m_graphics.getColor();
         m_graphics.setColor(Color.LIGHT_GRAY);
         m_graphics.fill(circle);
         m_graphics.draw(circle);

         if (label != null) {
            m_graphics.setColor(Color.DARK_GRAY);
            m_graphics.drawString(label, x + 8, y + 4);
         }

         m_graphics.setColor(old);
      }

      public void paint(Graphics g) {
         // Create the image if needed. This will be because the image hasn't
         // been created before,
         // or it has but the sensor panel has been resized.
         if (m_image == null
               || m_sensorPanel.getWidth() != m_image.getWidth()
               || m_sensorPanel.getHeight() != m_image.getHeight()) {
            m_image = (BufferedImage) createImage(m_sensorPanel.getWidth(),
                  m_sensorPanel.getHeight());
            m_graphics = null;
         }

         // Create and initialise the Graphics2D instance.
         if (m_graphics == null) {
            m_graphics = m_image.createGraphics();
            m_graphics.setBackground(m_summaryPanel.getBackground());
            m_graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                  RenderingHints.VALUE_ANTIALIAS_ON);
            Font font = new Font("Arial", Font.PLAIN, 12);
            m_graphics.setFont(font);

            m_scale_x = ((double) m_image.getWidth() / (double) (Constants.BATTLEFIELD_MAX_X - Constants.BATTLEFIELD_MIN_X));
            m_scale_y = ((double) m_image.getHeight() / (double) (Constants.BATTLEFIELD_MAX_Y - Constants.BATTLEFIELD_MIN_Y));

            m_translate_x = (int) ((double) m_image.getWidth() / ((double) (2 * m_scale_x)));
            m_translate_y = (int) ((double) m_image.getHeight() / ((double) (2 * m_scale_y)));
         }

         // Clear old data.
         m_graphics.clearRect(0, 0, m_image.getWidth(), m_image.getHeight());

         // Scale the display so it fills the entire image.
         m_graphics.scale(m_scale_x, m_scale_y);

         m_graphics.setColor(Color.BLACK);

         //
         // Process the battlefield data (from the ObjectLocation topic).
         // Since this is
         // coordinate-based and maps directly to the Java 2D coordinate
         // system, we display
         // it before the translation. We always use this data to draw the
         // markers (even in
         // the case where the battlefield data is not to be displayed), as
         // displaying markers
         // from both the battlefield and sensor data leads to slight
         // position discrepancies
         // between the two systems.
         //

         synchronized (m_battlefield) {
            Set<Integer> keys = m_battlefield.keySet();
            Iterator<Integer> iter = keys.iterator();
            while (iter.hasNext()) {
               Integer mapKey = iter.next();
               ObjectLocation location = (ObjectLocation) m_battlefield
                     .get(mapKey);
               boolean inRange = false;
               String label = null;
               synchronized (m_objects) {
                  ObjectData data = m_objects.get(mapKey);
                  inRange = (data == null ? false : true);

                  if (!inRange && !m_displayBattlefield) {
                     continue;
                  }

                  if (!m_fullObjectInfo) {
                     label = Integer.toString(mapKey.intValue());
                  } else {
                     if (inRange) {
                        label = data.toStringShort();
                     } else {
                        StringBuffer sb = new StringBuffer();
                        sb.append(location.trackId);
                        sb.append(" ");
                        sb.append(location.x);
                        sb.append(",");
                        sb.append(location.y);
                        sb.append(",");
                        sb.append(location.z);
                        label = sb.toString();
                     }
                  }
               }

               displayObject(label, location.x, location.y);
            }
         }

         //
         // Process the information from the PointTrack and TrackState
         // topics.
         //

         // To simplify display, centre the coordinate system on the sensor
         // origin.
         m_graphics.translate(m_translate_x, m_translate_y);

         // Draw the sensor boundary.
         m_graphics.setColor(Color.BLACK);
         int radius = (int) Constants.SENSOR_RANGE;
         m_graphics.drawOval(-radius, -radius, radius * 2, radius * 2);

         // Collections for the table data models.
         ArrayList<ArrayList<Integer>> infoData = new ArrayList<ArrayList<Integer>>();
         ArrayList<ArrayList<Integer>> summaryData = new ArrayList<ArrayList<Integer>>();

         // Summary counts.
         int countNoPosition = 0;
         int countUnidentified = 0;
         int countUnknown = 0;
         int countFriendly = 0;
         int countHostile = 0;

         // Process all objects reported by the sensor.
         synchronized (m_objects) {
            Iterator<ObjectData> iter = m_objects.values().iterator();

            while (iter.hasNext()) {
               ObjectData data = iter.next();

               // Skip data that does not have position information.
               if (data.m_position == NO_POSITION) {
                  countNoPosition++;
                  continue;
               }

               Color col = null;
               switch (data.m_classification.value()) {
               case Classification_enum._TRACK_CLASSIFICATION_UNIDENTIFIED:
                  col = Color.GRAY;
                  countUnidentified++;
                  break;
               case Classification_enum._TRACK_CLASSIFICATION_UNKNOWN:
                  col = Color.BLUE;
                  countUnknown++;
                  break;
               case Classification_enum._TRACK_CLASSIFICATION_FRIENDLY:
                  col = Color.GREEN;
                  countFriendly++;
                  break;
               case Classification_enum._TRACK_CLASSIFICATION_HOSTILE:
                  col = Color.RED;
                  countHostile++;
                  break;
               default:
                  output("Unexpected object category "
                        + data.m_classification.value()
                        + " for object ID " + data.m_id);
                  col = Color.MAGENTA;
               }

               // Project the real distance onto the flat 2D display plane.
               // Since our coordinate system has the positive Y axis
               // running upwards, and the Java 2D
               // coordinate system has the axis running downwards, we
               // invert the Y position.
               float projDist = (float) (data.m_position.distance * Math
                     .cos(Math.toRadians(data.m_position.angle)));
               int px = (int) (projDist * Math.sin(Math
                     .toRadians(data.m_position.direction)));
               int py = (int) (projDist * Math.cos(Math
                     .toRadians(data.m_position.direction)));
               py = -py;

               // Draw a line from the sensor origin to the object
               // location.
               m_graphics.setColor(col);
               m_graphics.drawLine(0, 0, px, py);

               // Produce a matching row for the information table.
               ArrayList<Integer> infoRow = new ArrayList<Integer>();
               infoRow.add(new Integer(data.m_id));
               infoRow.add(new Integer((int) data.m_position.direction));
               infoRow.add(new Integer((int) data.m_position.distance));
               infoRow.add(new Integer((int) data.m_position.angle));
               infoData.add(infoRow);
            }
         }

         // All drawing operations complete: scale down and reset the
         // coordinate translation
         // and draw the actual image.
         m_graphics.translate(-m_translate_x, -m_translate_y);
         m_graphics
               .scale((double) (1 / m_scale_x), (double) (1 / m_scale_y));
         g.drawImage(m_image, 0, 0, this);

         // Produce the summary data.
         ArrayList<Integer> summaryRow = new ArrayList<Integer>();
         summaryRow.add(new Integer(m_objects.size()));
         summaryRow.add(new Integer(countNoPosition));
         summaryRow.add(new Integer(countUnidentified));
         summaryRow.add(new Integer(countUnknown));
         summaryRow.add(new Integer(countFriendly));
         summaryRow.add(new Integer(countHostile));
         summaryData.add(summaryRow);

         // Ensure the information table data is sorted by object ID.
         ArrayListComparator comp = new ArrayListComparator();
         Collections.sort(infoData, comp);

         // Update the tables.
         SwingUtilities.invokeLater(new ArrayListTableUpdater(
               m_infoTableModel, infoData));
         SwingUtilities.invokeLater(new ArrayListTableUpdater(
               m_summaryTableModel, summaryData));
      }
   }

   /**
    * Updates the object data map with new information the TrackState topic; a
    * new map entry will be created if one does not exist.
    */
   private synchronized void updateMap(int id,
         Classification_enum classification) {
      synchronized (m_objects) {
         Integer key = new Integer(id);
         ObjectData data = m_objects.get(key);
         if (data == null) {
            data = new ObjectData();
            data.m_id = id;
            data.m_position = NO_POSITION;
            m_objects.put(key, data);

            if (DEBUG) {
               output("updateMap: received TrackState update for object "
                     + id + ", created map entry");
            }
         }

         data.m_classification = classification;
      }
   }

   /**
    * Updates the object data map with new information the PointTrack topic; a
    * new map entry will be created if one does not exist.
    */
   private synchronized void updateMap(int id, Pos position) {
      synchronized (m_objects) {
         Integer key = new Integer(id);
         ObjectData data = m_objects.get(key);
         if (data == null) {
            data = new ObjectData();
            data.m_id = id;
            data.m_classification = Classification_enum.TRACK_CLASSIFICATION_UNIDENTIFIED;
            m_objects.put(key, data);

            if (DEBUG) {
               output("updateMap: received PointTrack update for object "
                     + id + ", created map entry");
            }
         }

         data.m_position = position;
      }
   }

   /**
    * Removes an entry from the map.
    */
   private void removeFromMap(int id) {
      if (DEBUG) {
         output("Removing object ID " + id + " from map");
      }

      Integer mapKey = new Integer(id);
      synchronized (m_objects) {
         // We do not check the return for the remove call, since map
         // removals are triggered
         // by disposals on either PointTrack or TrackState topics. If no
         // filtering is in
         // place, there will be two map removal calls. If filtering is in
         // place, map removal
         // can be triggered for a PointTrack disposal where the TrackState
         // filtering meant
         // no map entry was created.

         m_objects.remove(mapKey);
      }
   }

   public DisplayApp(String[] args) {

      parseArguments(args);

      // Initialise the display applet.
      m_displayApplet = new DisplayApplet();
      m_displayApplet.setBackground(Color.white);

      // Initialise the display update task.
      m_updateTask = new UpdateDisplay();
      m_updateThread = new Thread(m_updateTask);

   }

   public void startDisplay() {
      // Start the update thread.
      output("Starting display");
      m_updateThread.start();
   }

   public void stopDisplay() {
      output("Stopping display");

      // Stop the update thread.
      m_updateTask.stopUpdateDisplay();
      try {
         m_updateThread.join();
      } catch (InterruptedException ie) {
         output("Join interrupted");
      }

      output("Stop complete");
   }

   public void waitForDisplay(long timeOut) {
      try {
         Thread.sleep(timeOut);
         m_updateTask.stopUpdateDisplay();
         m_updateThread.join();
      } catch (InterruptedException e) {
         output("Join interrupted");
      }
   }

   public void waitForDisplay() {
      try {
         m_updateThread.join();
      } catch (InterruptedException e) {
      }
   }

   public String toString() {
      return "Display (Camel JMS)";
   }

   public void configure () throws Exception {
       context = new DefaultCamelContext();
       
       // Set up the ActiveMQ JMS Components
       ConnectionFactory aConnectionFactory = new ActiveMQConnectionFactory ("tcp://localhost:61616");
       ConnectionFactory connectionFactory = new CachingConnectionFactory(aConnectionFactory);
       ((CachingConnectionFactory) connectionFactory).setSessionCacheSize(10);
       ((CachingConnectionFactory) connectionFactory).setCacheConsumers(true);
        // Note we can explicity name the component
       context.addComponent("test-jms", JmsComponent.jmsComponentAutoAcknowledge(connectionFactory));

       // Build the route.
       context.addRoutes(new RouteBuilder() {
           public void configure() {               
               // We need a route from the JMS topic to a processor so that we can
               // see the JMS message that has been sent.
               m_oldrListener = new ObjectLocationProcessor ();
               from("test-jms:topic:object_location.topic").process(m_oldrListener);
               
               // We need a route from the JMS topic to a processor so that we can
               // see the JMS message that has been sent.
               m_ptdrListener = new PointTrackProcessor ();
               from("test-jms:topic:point_track.topic").process(m_ptdrListener);

               // We need a route from the JMS topic to a processor so that we can
               // see the JMS message that has been sent.
               m_tsdrListener = new TrackStateProcessor ();
               from("test-jms:topic:track_state.topic").process(m_tsdrListener);
           }
       });       
   }
   
   public void start() throws Exception {
       context.start();
   }
   
   public void stop() throws Exception {
       context.stop();
   }
   
   public static void main(String[] args) {

      // Initialise the application.
      final DisplayApp instance = new DisplayApp(args);
      
      // Configure the Camel route and components.
      try {
         instance.configure();
      } catch (Exception e) {
         System.err.println("Cannot start application: " + e.getMessage());
         return;
      }

      //
      // Create the display components.
      //

      // Sensor panel: displays the tracked objects graphically.
      // The display application is basically the component within this frame,
      // but also updates
      // the information and summary panels.
      m_sensorPanel = new JPanel();
      m_sensorPanel.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createBevelBorder(BevelBorder.RAISED),
            BorderFactory.createBevelBorder(BevelBorder.LOWERED)));
      m_sensorPanel.setPreferredSize(new Dimension(400, 400));
      m_sensorPanel.setLayout(new BorderLayout(10, 5));
      m_sensorPanel.add(instance.m_displayApplet, BorderLayout.CENTER);

      // Information panel: shows the details for all tracked objects.
      m_infoPanel = new JPanel();
      m_infoPanel.setBorder(BorderFactory.createTitledBorder(m_bevelBorder,
            "Info"));
      m_infoPanel.setPreferredSize(new Dimension(400, 400));
      m_infoTable = new JTable();
      m_infoTableModel = new ArrayListTableModel(m_infoTableHeaders,
            new ArrayList<ArrayList<Integer>>());
      m_infoTable.setModel(m_infoTableModel);
      JScrollPane sp1 = new JScrollPane(m_infoTable);
      m_infoPanel.setLayout(new BorderLayout());
      m_infoPanel.add(sp1, BorderLayout.CENTER);

      // Summary panel: a brief overview of the tracked objects. Displayed as
      // part of
      // the information panel.
      m_summaryPanel = new JPanel();
      m_summaryPanel.setBorder(BorderFactory.createTitledBorder(
            m_bevelBorder, "Summary"));
      m_summaryPanel.setPreferredSize(new Dimension(400, 75));
      m_summaryTable = new JTable();
      m_summaryTableModel = new ArrayListTableModel(m_summaryTableHeaders,
            new ArrayList<ArrayList<Integer>>());
      m_summaryTable.setModel(m_summaryTableModel);
      JScrollPane sp2 = new JScrollPane(m_summaryTable);
      m_summaryPanel.setLayout(new BorderLayout());
      m_summaryPanel.add(sp2, BorderLayout.CENTER);
      m_infoPanel.add(m_summaryPanel, BorderLayout.SOUTH);

      // Settings panel: update frequency control. We set the spinner to the
      // minimum value,
      // and not the default, so we can perform initialisation using
      // setValue() later.
      JPanel updatePanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      updatePanel.setBorder(BorderFactory.createTitledBorder(m_bevelBorder,
            "Display Settings"));
      JLabel updateLabel = new JLabel("Update Frequency (Hz)");
      SpinnerNumberModel updateModel = new SpinnerNumberModel(
            MINIMUM_UPDATE_FREQUENCY, MINIMUM_UPDATE_FREQUENCY,
            MAXIMUM_UPDATE_FREQUENCY, UPDATE_FREQUENCY_INTERVAL);
      JSpinner updateSpinner = new JSpinner(updateModel);
      updateSpinner.setPreferredSize(m_controlSize);
      updatePanel.add(updateLabel);
      updatePanel.add(updateSpinner);

      // Settings panel.
      JLabel bfLabel = new JLabel("Show Battlefield Objects");
      JCheckBox bfCheck = new JCheckBox();
      JPanel bfPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      bfPanel.add(bfLabel);
      bfPanel.add(bfCheck);
      JLabel fullLabel = new JLabel("Show Full Object Details");
      JCheckBox fullCheck = new JCheckBox();
      JPanel fullPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      fullPanel.add(fullLabel);
      fullPanel.add(fullCheck);

      // Assemble settings panel.
      JPanel settingsPanel = new JPanel(new GridLayout(2, 1));
      settingsPanel.setBorder(BorderFactory.createTitledBorder(m_bevelBorder,
            "Display Settings"));
      settingsPanel.add(bfPanel);
      settingsPanel.add(fullPanel);

      // Combine sensor panel and information panel.
      JPanel combined1 = new JPanel(new BorderLayout(10, 5));
      combined1.add(m_sensorPanel, BorderLayout.WEST);
      combined1.add(m_infoPanel, BorderLayout.CENTER);

      // Combine update frequency panel and settings panel.
      JPanel combined2 = new JPanel(new BorderLayout(10, 5));
      combined2.add(updatePanel, BorderLayout.NORTH);
      combined2.add(settingsPanel, BorderLayout.SOUTH);

      // Combine JVM panel, reader controls, target selection and settings
      // panels.
      JPanel combined3 = new JPanel(new GridLayout(1, 2));
      combined3.add(instance.m_jvmControl.getPanel());
      combined3.add(combined2);
      JPanel combined4 = new JPanel(new BorderLayout(10, 5));
      combined4.add(combined3, BorderLayout.SOUTH);

      // Button panel.
      m_exitButton = new JButton("Exit");
      JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      buttonPanel.add(m_exitButton);

      // Combine the button panel with the other panels.
      JPanel comboSummary = new JPanel(new BorderLayout(10, 5));
      comboSummary.add(combined4, BorderLayout.CENTER);
      comboSummary.add(buttonPanel, BorderLayout.SOUTH);

      // Exit button action listener.
      m_exitButton.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent ae) {
            instance.stopDisplay();
            instance.stopJVMInformationUpdates();
            synchronized (instance) {
               instance.notify();
            }
         }
      });

      // Add spinner change listener.
      updateSpinner.addChangeListener(new ChangeListener() {
         public void stateChanged(ChangeEvent ce) {
            JSpinner spinner = (JSpinner) ce.getSource();
            Double val = (Double) spinner.getValue();
            double freq = val.doubleValue();

            instance.m_updateDelay = (freq == 0.0 ? 0L
                  : (long) (1000 / freq));
            instance.output("Update delay set to " + instance.m_updateDelay
                  + " (frequency " + freq + "Hz)");
         }
      });

      // Add checkbox action listeners.
      bfCheck.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent ae) {
            JCheckBox check = (JCheckBox) ae.getSource();

            instance.m_displayBattlefield = check.isSelected();
            instance.output("Show Battlefield Objects: "
                  + instance.m_displayBattlefield);
         }
      });
      fullCheck.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent ae) {
            JCheckBox check = (JCheckBox) ae.getSource();

            instance.m_fullObjectInfo = check.isSelected();
            instance.output("Show Full Object Details: "
                  + instance.m_fullObjectInfo);
         }
      });

      // Set up initial interface state.
      updateSpinner.setValue(DEFAULT_UPDATE_FREQUENCY);
      bfCheck.setSelected(instance.m_displayBattlefield);
      fullCheck.setSelected(instance.m_fullObjectInfo);

      //
      // Construct the frame.
      //
      m_frame = new JFrame(instance.toString());
      m_frame.addWindowListener(new WindowAdapter() {
         public void windowClosing(WindowEvent e) {
            m_exitButton.doClick();
         }
      });

      m_frame.getContentPane().setLayout(new BorderLayout(10, 10));
      m_frame.getContentPane().add(combined1, BorderLayout.CENTER);
      m_frame.getContentPane().add(comboSummary, BorderLayout.SOUTH);

      m_frame.pack();
      m_frame.setVisible(true);

      // Start the Camel context.
      try {
          instance.start();
      } catch (Exception e) {
          System.err.println("Cannot start application: " + e.getMessage());
       }

      // Start the display.
      if (runWithTimeOut) {
         instance.startDisplay();
         instance.waitForDisplay(TIME_OUT);
         instance.stopDisplay();
         instance.stopJVMInformationUpdates();
         synchronized (instance) {
            instance.notify();
         }
      } else {
         instance.startDisplay();
         instance.waitForDisplay();
      }
      
      // Stop the Camel context.
      try {
         instance.stop();
      } catch (Exception e) {
         System.err.println("Cannot stop application: " + e.getMessage());
      }

      // Complete.
      System.out.println("DisplayApplication.main :: exiting");
      m_frame.dispose();
   }
}
