/************************************************************************
 * 
 * Copyright (c) 2009 PrismTech Ltd. All rights Reserved.
 * 
 * LOGICAL_NAME: ArrayListTableUpdater.java FUNCTION: OpenSplice DDS Power Tools
 * Tutorial example code. MODULE: Tutorial for the Java programming language.
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class is a Runnable (for use with SwingUtilities.invokeLater()) that
 * will update the data in an ArrayListTableModel instance.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import java.util.ArrayList;


public class ArrayListTableUpdater implements Runnable
{
   ArrayListTableModel m_model;

   ArrayList<ArrayList<Integer>> m_data;

   public ArrayListTableUpdater (ArrayListTableModel model, ArrayList<ArrayList<Integer>> data)
   {
      m_model = model;
      m_data = data;
   }

   public void run ()
   {
      m_model.clear ();
      m_model.setData (m_data);
   }
}
