/* A subclass of dbClient specifically for the 1999 classifier.
   It adds extra functionality so the classifier can easily grab
   specific sensor data out of the db. */

#ifndef __NDDS_CLASSIFIER_COMMS_H__
#define __NDDS_CLASSIFIER_COMMS_H__

#include "ndds/NDDS.h"
#include "dbRecord.h"
#include "dbClient.h"
#include "matrix/vector.h"

// MAKE SURE THESE STAY CURRENT!!!!
#define HI_RES_DRIVER_NAME "smHiResDriver"
#define ARM_DRIVER_NAME "smManipulatorDriver"

class ClassifierNddsComms : public dbClient {
 public:
  int getImageParameters(const dbRecord &record, int readingNum,
			 float &originRow, float &originCol,
			 float &scaleRow, float &scaleCol,
			 vector &features);
  int getSpectrumParameters(const dbRecord &record, int readingNum,
			    vector &features);
  int getMetalDetectorParameters(const dbRecord &record, int readingNum,
				 vector &features);
  int insertImageFeatures(dbRecord &record, int readingNum,
			  vector features);
  int insertSpectrumFeatures(dbRecord &record, int readingNum,
			     vector features);
  int insertMetalDetectorFeatures(dbRecord &record, int readingNum,
			  vector features);
  int getImageFileName(const dbRecord &record, int readingNum, char &filename);
  int getManipulatorFileName(const dbRecord &record, int readingNum, char &filename);

 private:
  int getDriverNum(int &num, char *name); /* Returns 1 on success, 0 on failure */
};

#endif /* __NDDS_CLASSIFIER_COMMS_H__ */
