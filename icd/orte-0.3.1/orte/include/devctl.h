/**
 * @file devctl.h
 */

/*
 *  $Id: devctl.h,v 1.7 2005/02/21 07:20:13 ralf Exp $
 */

#ifndef _DEVCTL_H
#define _DEVCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>

#if defined(_POSIX_DEVICE_CONTROL)

#include <sys/types.h>
#include <unistd.h>

/*
 *  21.2.1 Control a Device, P1003.4b/D8, p. 65
 */

int devctl(
  int     filedes,
  void   *dev_data_ptr,
  size_t  nbyte,
  int    *dev_info_ptr
);

#endif

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
