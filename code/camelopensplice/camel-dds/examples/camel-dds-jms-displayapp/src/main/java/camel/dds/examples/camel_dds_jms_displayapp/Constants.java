/************************************************************************
 * 
 * Copyright (c) 2009 PrismTech Ltd. All rights Reserved.
 * 
 * LOGICAL_NAME: Constants.java 
 * FUNCTION: OpenSplice DDS Power Tools Tutorial example code. 
 * MODULE: Tutorial for the Java programming language. 
 * DATE June 2009.
 ************************************************************************ 
 * 
 * This class contains various constants used "across" the applications. Any
 * constants that are specific to an application are defined within that
 * application.
 * 
 ***/

package camel.dds.examples.camel_dds_jms_displayapp;

public interface Constants
{
   //
   // Battlefield information.
   //

   // Dimensions.
   public static int BATTLEFIELD_MIN_X = 0;

   public static int BATTLEFIELD_MAX_X = 400;

   public static int BATTLEFIELD_MIN_Y = 0;

   public static int BATTLEFIELD_MAX_Y = 400;

   //
   // Sensor information.
   //

   // Position.
   public static int SENSOR_X = (BATTLEFIELD_MIN_X + BATTLEFIELD_MAX_X) / 2;

   public static int SENSOR_Y = (BATTLEFIELD_MIN_Y + BATTLEFIELD_MAX_Y) / 2;

   public static int SENSOR_Z = 0;

   // Range: assumes a central position for the scope and a square battlefield.
   public static float SENSOR_RANGE = (float) ( (BATTLEFIELD_MAX_X - SENSOR_X) - 40 );
}
