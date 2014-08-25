/* $Revision: 1.1 $ $Author: mwagner $ $Date: 1999/07/23 19:17:04 $ */
#ifndef INCtelemNdds_h
#define INCtelemNdds_h

/****************************************************************************
 *
 * PROJECT:     Nomad
 *
 * MODULE:      Real-time
 *
 * FILE:        telemNdds.h
 *
 * DESCRIPTION: Constant definitions and TelemProducer function declarations
 *
 * EXPORTS:     See definitions below
 *
 * NOTES:       NOMAD_NDDS_DOMAIN should be defined globally
 *
 * REVISION HISTORY:
 * $Log: telemNdds.h,v $
 * Revision 1.1  1999/07/23 19:17:04  mwagner
 * Initial install of working realtime code from tire.frc.ri.cmu.edu on 7/23/99.
 *
 * Revision 1.1.1.1  1998/07/16 19:13:09  sib
 * Realtime code for Nomad.
 * VxWorks 5.3.1 running on a Pep VM62.
 *
 * Revision 1.1.1.1  1998/05/04 16:39:14  sib
 * Initial install of realtime code for vm62 running vxWorks 5.3.
 * Taken from 98-05-04 version.
 *
 * Revision 1.1.1.1  1998/02/20 02:26:31  sib
 * Initial install of Nomad Code for Meteorite Search
 *
 * Revision 1.8  1997/05/13  14:31:37  sib
 * Working before the Run
 *
 * Revision 1.7  1997/04/27  18:17:47  sib
 * Changed Imakefiles to include Imakefile.common with more stuff.
 *
 * Revision 1.1  1997/04/03 08:55:10  dsw
 * Renamed stateProducer.[cc,h] to telemNdds.[cc,h] to match up with CMU
 * convention.  Added additional messages.  Created NO_NOMAD switch that
 * does not access shared memory and use actual data.
 *
 * Revision 1.1  1997/04/03 08:40:38  dsw
 * Renamed stateProducer.[cc,h] to telemNdds.[cc,h] to match up with CMU
 * convention.  Added additional messages.  Created NO_NOMAD switch that
 * does not access shared memory and use actual data.
 *
 * Revision 1.2  1997/04/02 04:16:05  dsw
 * Set up multiple timers running at different rates.  Each timer produces
 * a different signal.  The callback checks signal number to determine
 * which ndds producer to sample.  Tested.  Works.  Need to add more messages.
 *
 * Revision 1.1  1997/03/28 02:26:54  dsw
 * Initial check-in with messages
 *
 * Revision 1.0  1997/03/26 01:34:46  dsw
 * Added Ndds routines to produce state message when timer expires
 *
 * Revision 0.1  1996/12/31 18:31:20  dsw
 * Created timer based routine to estimate state information on at a
 * regular interval.
 *
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 * TYPEDEFS
 ***************************************************************************/
/* Enum used as index into timers */
typedef enum {fastest, fast, slow, slowest, debug, total_timers}TP_TIMER_INDEX;


/***************************************************************************
 * EXTERNS
 ***************************************************************************/

  void TelemPublisherCreate(void);
  void TelemPublisherStart(void);
  void TelemPublisherStop(void);
  void TelemPublisherDelete(void);
  void TelemPublisherAdjust(TP_TIMER_INDEX timer, time_t period,time_t nperiod);

  void tpc(void);
  void tps(void);
  void tpe(void);
  void tpd(void);
  void tpa(TP_TIMER_INDEX timer, time_t period, time_t nperiod);

#ifdef __cplusplus
}
#endif


#endif /* INCtelemNdds_h */



