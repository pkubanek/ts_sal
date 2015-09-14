/* BSP dependent options file */
/* automatically generated -- DO NOT EDIT!! */

#ifndef __BSP_OPTIONS_H
#define __BSP_OPTIONS_H

/* include/bspopts.tmp.  Generated from bspopts.h.in by configure.  */
/* include/bspopts.h.in.  Generated from configure.ac by autoheader.  */

/* Determines, whether RTEMS will try to use the primary IDE interface.
   Disable it, if: - you have no primary IDE interface - or you have no disk
   attached to this interface - or you do not want to access disks attached to
   this interface */
#define IDE_USE_PRIMARY_INTERFACE 1

/* Determines, whether RTEMS will try to use the primary IDE interface. Enable
   it, if: - you have a secondary IDE interface - and you have at least one
   disk attached to this interface - and you do want to access disks attached
   to this interface */
#define IDE_USE_SECONDARY_INTERFACE 0

/* if using 16 bit mode assembler support */
#define NEW_GAS 1






/* Determines, whether the console will be associated with the standard VGA
   display or with the COM1 serial port. Currently only the VGA display and
   COM1 support printk. */
#define USE_COM1_AS_CONSOLE 0

#endif /* __BSP_OPTIONS_H */
