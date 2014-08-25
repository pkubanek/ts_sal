/*
 *	netndds.h
 *
 *	Mark Sibenac
 *	Mike Krebs
 *	97-3-24
 *	Field Robotics Center
 *
 */

#ifndef __NETNDDS_H__
#define __NETNDDS_H__

#include <vxWorks.h>
#include <sysLib.h>
#include <vme.h>

#include <smLib.h>
#include "NDDS.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SM_NDDS_SIZE (10240)
#define SM_NDDS_NAME "smNDDS"

/* Nomad ndds parameter */
#define NOMAD_NDDS_DOMAIN 0


/* Initialize NDDS */
void initNDDS(void);
void killNDDS(void);

#ifdef __cplusplus
}
#endif


#endif
