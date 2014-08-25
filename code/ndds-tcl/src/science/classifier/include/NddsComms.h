/* NddsComms.h -- module to handle communications between the classifier and the rest
   of the SAS.

   Liam Pedersen, Carnegie Mellon University, September 1999
   Micheal Wagner, Carnegie Mellon University, September 1999

   version 1.0

   */

#include <matrix/vector.h>

/**************/
/* database Q */
/**************/
extern Queue dbQ;

/*************************/
/* Ndds dbNotify handler */
/*************************/
... handler(...);

/***************************************************************************/
/* Start the NDDS service.  Returns 1 on success, else some error code <= 0*/
/***************************************************************************/
int StartNDDS(...);

/***************************************************************/
/* functions to retrieve and insert records from the database. */
/***************************************************************/

int GetRecord(int target_id, int sensor_id, dbRecord& record);
/*           - returns no. of sensor readings in record, else negative error code */
int PutRecord(int target_id, int sensor_id, const dbRecord& record);
/*           - returns 1 on success, else negative error code                     */

/*******************************************************/
/* Retrieve sensor specific parameters from db records */
/*******************************************************/

int GetImageParameters(const dbRecord& record, int reading_id,
		       float& ox, float& oy,
		       float& sx, float& sy,
		       vector& features);
/* (ox, oy) : rock origin coordinates (DEFINE COORDINATE SYSTEM).
   (sx, sy) : image scaling parameters /[mm/pixel].
   features : feature vector.  Empty if features undefined.
   
   returns 1 on success.
*/ 
		       
int GetSpectrumParameters(const dbRecord& record, int reading_id, vector& features);
/* returns 1 on success.*/

int GetMetalDetectorParameters(const dbRecord& record, int reading_id, vector& features);
/* returns 1 on success. */


/********************************/
/* store features in dbRecord's */
/********************************/
int InsertFeatures(dbRecord& record, int reading_id, vector features);
/* returns 1 on success */



/* IMPLEMENTATION NOTES: 

   - please put implementation in NddsComms.C
   - NddsComms.C:
        while(1) {
	  - print out any records received in dbNotify
	  - modify record and put back in db.
	  - quit if user hits key.
	}

    - need appropriate makefile.
    - return values and error codes are suggestions only.

    - please use the vector class defined in matrix/vector.h
      important members:
      vector v;   // v is empty vector
      vector v(N) // v is N member vector, initialized to 0.0
      vector v(N,double default) // v initialized to default value.
      v[i];       // access vector v as if it was of type double v[N].
                  // Please note that this is UNPROTECTED access - ie don't overflow!
      v.num()     // number of elements in v.  0 if v is empty.

      vector.h is in the include section of my directory structure, is also in CVS.
      library is libmatrix.a

    - need to modify db so that can fake a dbNotify in db text interface.
    */

    
