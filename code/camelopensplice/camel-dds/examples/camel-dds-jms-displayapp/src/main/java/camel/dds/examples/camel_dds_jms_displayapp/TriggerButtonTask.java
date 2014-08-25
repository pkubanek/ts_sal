/************************************************************************
 * 
 * Copyright (c) 2009 
 * PrismTech Ltd. 
 * All rights Reserved.
 * 
 * LOGICAL_NAME: TriggerButtonTask.java 
 * FUNCTION: OpenSplice DDS Power Tools Tutorial example code. 
 * MODULE: Tutorial for the Java programming language.
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class contains a Runnable that triggers a button click after a specified
 * delay.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import javax.swing.JButton;


public class TriggerButtonTask implements Runnable
{
   private long m_delay;

   private JButton m_button;

   TriggerButtonTask (long delay, JButton button)
   {
      m_delay = delay;
      m_button = button;
   }

   public void run ()
   {
      if (m_delay != 0)
      {
         try
         {
            Thread.sleep (m_delay);
         }
         catch (InterruptedException ie)
         {
            // Ignore.
         }
      }

      m_button.doClick ();
   }
}
