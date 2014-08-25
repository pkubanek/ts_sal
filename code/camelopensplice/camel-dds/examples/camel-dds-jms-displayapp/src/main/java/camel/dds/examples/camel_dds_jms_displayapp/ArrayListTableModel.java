/************************************************************************
 * 
 * Copyright (c) 2009 PrismTech Ltd. All rights Reserved.
 * 
 * LOGICAL_NAME: ArrayListTableModel.java FUNCTION: OpenSplice DDS Power Tools
 * Tutorial example code. MODULE: Tutorial for the Java programming language.
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class is a table model implementation with the data held in an
 * ArrayList.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;


public class ArrayListTableModel extends AbstractTableModel
{
   static final long serialVersionUID = -1215242223547441915L;

   protected String[] m_columnNames;

   protected ArrayList<ArrayList<Integer>> m_data;

   public ArrayListTableModel (String[] columnNames, ArrayList<ArrayList<Integer>> data)
   {
      m_columnNames = columnNames;
      m_data = data;
   }

   public String getColumnName (int col)
   {
      return m_columnNames[col];
   }

   public int getRowCount ()
   {
      return m_data.size ();
   }

   public int getColumnCount ()
   {
      return m_columnNames.length;
   }

   public Object getValueAt (int row, int col)
   {
      ArrayList<Integer> a = m_data.get (row);
      return a.get (col);
   }

   public boolean isCellEditable (int row, int col)
   {
      return false;
   }

   public void setValueAt (Object value, int row, int col)
   {
      ArrayList<Integer> a = m_data.get (row);
      a.set (col, (Integer) value);
      fireTableCellUpdated (row, col);
   }

   public void setData (ArrayList<ArrayList<Integer>> data)
   {
      m_data = data;
      fireTableDataChanged ();
   }

   public void clear ()
   {
      setData (new ArrayList<ArrayList<Integer>> (0));
   }
}
