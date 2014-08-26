
/* Sample datastream reader , intended to be called automatically
   from svcSAL_receiveDatastream on arrival of new data.
   Remove cases for non-applicable datastreams and add 
   stream dependent processing code.
 */

#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_test_datastreamCallback (char *subsystem, int *shmdata_ref ) {
   printf("%s command received",subsystem);


   if (strcmp("system_Computer_status",subsystem) == 0 ) {
     system_Computer_status_cache *system_Computer_status_ref;
     system_Computer_status_ref = (system_Computer_status_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     system_Computer_status_ref->syncI = 0;
   }
}



