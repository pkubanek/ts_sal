/*
 *      netndds.c
 *
 *      Mark Sibenac
 *      Mike Krebs
 *      97-3-25
 *      Field Robotics Center
 */

#include "netndds.h"
#include "cmdNdds.h"
#include "moveNdds.h"
#include "telemNdds.h"

void initNDDS(void) {
/* The following is done in the login.cmd file for now becuase of lockouts
 * when doing it from a telnet session.
 */

  /* nddsStartDaemon (NOMAD_NDDS_DOMAIN, 2); */
/*  cd ("/null"); /* prevent 'tire:' from being the default directory */
  NddsInit(NOMAD_NDDS_DOMAIN,0);
  NddsVerbositySet(0);
/*  NddsVerbosityErrorSet (0);*/
/*  cd ("tire:/"); /* set 'tire:' as the default directory */

/*NddsPeerHostsSet("172.20.3.96:172.20.1.1:172.20.3.201:172.20.3.203:172.20.1.206:172.20.3.97");*/
/*NddsPeerHostsSet("172.20.3.96:172.20.3.201:172.20.3.203:172.20.1.206:172.20.3.97");*/
/*NddsPeerHostsSet("128.2.196.96:128.2.44.203:128.2.44.97:128.102.115.142:128.102.115.143:128.102.115.187:128.102.115.150:128.102.115.191:128.102.115.191:128.2.196.39:128.2.209.96:128.2.196.131:192.204.240.206");*/

/*NddsPeerHostsSet("172.20.3.39:172.20.3.96:172.20.3.131:172.20.3.201:172.20.3.203:172.20.3.154:192.204.240.206:172.20.1.100:128.102.113.197:128.102.113.198:128.102.113.199");
*/

/*  NddsPeerHostsSet("128.2.196.96:128.2.44.201:128.2.196.39:128.2.44.3:128.2.196.198:128.2.44.85"); /* tire:vw2:nav1:gramineae:jeetyet:beet */
  
  NddsPeerHostsSet("128.2.219.193:128.2.219.194:128.2.219.202:128.2.219.203:128.2.219.204:128.2.219.207"); /* tire:sweeper:meteorite:atacama:vw2:nav1 */

  cmdSubscriberCreate();
  moveSubscriberCreate();
  TelemPublisherCreate();

  return;
}

void killNDDS (void)
{
  TelemPublisherStop();
  TelemPublisherDelete();

  moveSubscriberStop();
  moveSubscriberDelete();

  cmdSubscriberStop();
  cmdSubscriberDelete();

  return;
}
