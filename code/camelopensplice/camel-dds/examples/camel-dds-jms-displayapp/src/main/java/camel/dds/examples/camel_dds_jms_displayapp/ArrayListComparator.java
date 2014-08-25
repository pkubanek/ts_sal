/**
 * 
 * Copyright (c) 2009 PrismTech Ltd. All rights Reserved.
 * 
 * LOGICAL_NAME: ArrayListComparator.java FUNCTION: OpenSplice DDS Power Tools
 * Tutorial example code. MODULE: Tutorial for the Java programming language.
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class is a comparator for an ArrayList with the first item (on which the
 * sort is performed) being an Integer.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

import java.util.ArrayList;
import java.util.Comparator;


public class ArrayListComparator implements Comparator<ArrayList<Integer>>
{
   public int compare (ArrayList<Integer> a, ArrayList<Integer> b)
   {
      int val1 = a.get (0).intValue ();
      int val2 = b.get (0).intValue ();

      if (val1 < val2)
         return -1;
      else if (val1 == val2)
         return 0;
      else
         return 1;
   }
}
