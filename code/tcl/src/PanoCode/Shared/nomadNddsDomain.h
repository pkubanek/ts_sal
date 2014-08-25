/* $Revision: 1.5 $ $Author: nomad $ $Date: 1997/05/03 22:15:43 $ */
#ifndef INCnomadNddsDomain_h
#define INCnomadNddsDomain_h

/****************************************************************************
 *
 * PROJECT: Nomad
 *
 * MODULE:  <all>
 *
 * FILE:    nomadNddsDomain.h
 *
 * DESCRIPTION: This file contains only the definition of the NDDS domain
 *  used throughout the Nomad project.
 *
 * EXPORTS: NOMAD_NDDS_DOMAIN
 *
 * NOTES:        
 *
 * REVISION HISTORY:
 * $Log: nomadNddsDomain.h,v $
 * Revision 1.5  1997/05/03 22:15:43  nomad
 * Added Multicast defines.  -Kurt Schwehr
 * 	NOMAD_NDDS_MULTICAST_DOMAIN
 * 	NOMAD_NDDS_MULTICAST_TTL
 * 	NOMAD_NDDS_MULTICAST_ADDRESS
 *
 * Revision 1.4  1997/04/27 19:04:55  hjt
 * update from ames tree
 *
 * Revision 1.3  1997/04/16 21:35:41  jl
 * Eliminated bogus semi-collon in #define
 *
 * Revision 1.2  1997/04/16 21:21:03  jl
 * Fixed static define in header file (!?)
 *
 * Revision 1.1  1997/04/15 21:33:07  jl
 * Shuffling some stuff up from NAV into True common areas.
 *
 * Revision 1.1  1997/04/03 17:38:44  dsw
 * Added nomadNddsDomain.h to define projectwide variable.
 *
 *
 ***************************************************************************/

/* Declaring space for a variable in a header file leads to
 * multiple instances of the symbol and variable being defined
 * in separate object files --> linkage fails
 * 
 * This is not true in VxWorks with its global naming space.
 *
 * If you would like to return the const declaration, please put
 * an ifdef VxWorksXXXX Thanks.
 */
/*
 *#if defined(__STDC__) || defined(__cplusplus)
 *const unsigned int NOMAD_NDDS_DOMAIN = 7401;
 *#else
 */
#define NOMAD_NDDS_DOMAIN (7401)
#define NOMAD_NDDS_MULTICAST_DOMAIN (7402)
#define NOMAD_NDDS_MULTICAST_TTL (100)		/* Time To Live */

/* This is passed to NDDS in NddsConsumerMulticastAddressSet */
/* Same as RTI sample code.  What is a good value? */
#define NOMAD_NDDS_MULTICAST_ADDRESS ("225.100.5.3")

/*
 *#endif
 */



#endif /* INCNomadNddsDomain_h */
