/*
 *  $Id: tftp.h,v 1.5 2005/02/02 10:09:30 ralf Exp $
 */

/*
 * Trivial File Transfer Protocol (TFTP)
 *
 * Transfer file to/from remote host
 *
 * W. Eric Norum
 * Saskatchewan Accelerator Laboratory
 * University of Saskatchewan
 * Saskatoon, Saskatchewan, CANADA
 * eric@skatter.usask.ca
 */

/*
 * Usage:
 *
 * To open `/bootfiles/image' on `hostname' for reading:
 *         fd = open ("/TFTP/hostname/bootfiles/image", O_RDONLY);
 *
 * The `hostname' must be four dot-separated decimal values.
 */

#ifndef _RTEMS_TFTP_H
#define _RTEMS_TFTP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Filesystem initialization routine
 */

int rtems_bsdnet_initialize_tftp_filesystem( void );

#ifdef __cplusplus
}
#endif

#endif
