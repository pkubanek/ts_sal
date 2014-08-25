/* $Revision: 1.2 $ $Author: nomad $ $Date: 1997/05/04 23:18:55 $ */
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
 * Revision 1.2  1997/05/04  23:18:55  nomad
 * Added telemProducerAdjust to change timer period on the fly
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

/***************************************************************************
 * TYPEDEFS
 ***************************************************************************/
// Enum used as index into timers
enum TP_TIMER_INDEX {fastest, fast, slow, slowest, debug, total_timers};



/***************************************************************************
 * CONSTANTS
 ***************************************************************************/
// Telem producer task parameters
const int TP_PRIORITY = (100);
const int TP_OPTIONS  = (NULL); // USP VX_FP_TASK if floats
const int TP_STACK    = (4000);

// Telem producer ndds parameters
const float TP_NDDS_DEADLINE    = 4000.0;
const float TP_NDDS_SEPARATION  = 1.0;
const float TP_NDDS_STRENGTH    = 1.0;
const float TP_NDDS_PERSISTENCE = 15.0;

// Telem producer timer periods in nanoseconds
const int TP_UPERIOD[total_timers] = {100000000,    //nanoseconds = 10Hz
				      1000000000,   //nanoseconds = 1Hz
				      0,
				      0,
				      0};
// Telem producer timer periods in seconds
const int TP_PERIOD[total_timers] = {0,
				     0,
				     10,            //seconds = 0.1Hz
				     60,            //seconds = 0.016Hz
				     60};

// Telem producer signals
const int TP_SIGNAL[total_timers] = {27,
				     28,
				     29,
				     30,
				     31};

// Telem producer names
const char* TP_NAME[total_timers] = {"TelemProducerFastest",
				     "TelemProducerFast",
				     "TelemProducerSlow",
				     "TelemProducerSlowest",
				     "TelemProducerDebug"};


/***************************************************************************
 * EXTERNS
 ***************************************************************************/
extern "C" {
  void TelemProducerCreate(void);
  void TelemProducerStart(void);
  void TelemProducerStop(void);
  void TelemProducerDelete(void);
  void TelemProducerAdjust(TP_TIMER_INDEX timer,
			   time_t period,
			   time_t nperiod);

  void tpc(void);
  void tps(void);
  void tpe(void);
  void tpd(void);
  void tpa(TP_TIMER_INDEX timer,
	   time_t period,
	   time_t nperiod);
}



#endif /* INCtelemNdds_h */



