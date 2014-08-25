#include <iostream.h>
#include <fstream.h>
#include "dbRecordDef.h"
#include "sensorDef.h"
#include "ClassifierNddsComms.h"


// Public methods

int ClassifierNddsComms::getImageParameters(const dbRecord &record, int readingNum,
					    float &originRow, float &originCol,
					    float &scaleRow, float &scaleCol,
					    vector &features) {

  int hiResDriverNum;
  
  if(!getDriverNum(hiResDriverNum, HI_RES_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[hiResDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      // For the high-res data, optionalData[0-3] are reserved for origin and scaling info.
      originRow = record.sensorData[hiResDriverNum].readings[readingNum].optionalData.optionalData[0];
      originCol = record.sensorData[hiResDriverNum].readings[readingNum].optionalData.optionalData[1];
      scaleRow = record.sensorData[hiResDriverNum].readings[readingNum].optionalData.optionalData[2];
      scaleCol = record.sensorData[hiResDriverNum].readings[readingNum].optionalData.optionalData[3];
      for(int i=0; i < MAX_FEATURE_VECTOR_SIZE; i++) {
	features[i] = record.sensorData[hiResDriverNum].readings[readingNum].features.featureVector[i];
      }
      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::getSpectrumParameters(const dbRecord &record, int readingNum,
					       vector &features) {

  int armDriverNum;
  
  if(!getDriverNum(armDriverNum, ARM_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[armDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      /* 
	 For spectrum and metal detector data, optionalData is used to record start and end indexes
	 of feature vector data:

	 Index  Description
	 ------ ------------------------------
	 0      First index of spectrometer feature vector (inclusive, usually 0)
	 1      Last index of spectrometer feature vector (inclusive)
	 2      First index of metal detector feature vector (inclusive, usually 1 + last spec index)
	 3      Last index of metal detector feature vector (inclusive)

      */
      int firstSpec = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[0];
      int lastSpec = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[1];
      for(int i=firstSpec; i <= lastSpec; i++) {
	features[i] = record.sensorData[armDriverNum].readings[readingNum].features.featureVector[i];
      }
      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::getMetalDetectorParameters(const dbRecord &record, int readingNum,
						    vector &features) {

  int armDriverNum;
  
  if(!getDriverNum(armDriverNum, ARM_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[armDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      /* 
	 For spectrum and metal detector data, optionalData is used to record start and end indexes
	 of feature vector data:

	 Index  Description
	 ------ ------------------------------
	 0      First index of spectrometer feature vector (inclusive, usually 0)
	 1      Last index of spectrometer feature vector (inclusive)
	 2      First index of metal detector feature vector (inclusive, usually 1 + last spec index)
	 3      Last index of metal detector feature vector (inclusive)

      */
      int firstMetal = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[2];
      int lastMetal = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[3];
      for(int i=firstMetal; i <= lastMetal; i++) {
	features[i] = record.sensorData[armDriverNum].readings[readingNum].features.featureVector[i];
      }
      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::insertImageFeatures(dbRecord &record, int readingNum, vector features) {
  int hiResDriverNum;

  if(!getDriverNum(hiResDriverNum, HI_RES_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[hiResDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      for(int i=0; i < features.num(); i++) {
	record.sensorData[hiResDriverNum].readings[readingNum].features.featureVector[i] = features[i];
      }
      return(DB_OK);
    }
  }
}
    
int ClassifierNddsComms::insertSpectrumFeatures(dbRecord &record, int readingNum, vector features) {
  int armDriverNum;

  if(!getDriverNum(armDriverNum, ARM_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[armDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      int firstSpec = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[0];
      int oldLastSpec = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[1];
      int oldFirstMetal = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[2];
      int oldLastMetal = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[3];

      // Find new indexes
      int lastSpec = firstSpec + features.num() - 1;
      int lastMetal = oldLastMetal + oldLastSpec - oldFirstMetal;
      int firstMetal = lastSpec + 1;

      // First move around metal detector data
      for(int i=oldFirstMetal; i <= oldLastMetal; i++) {
	record.sensorData[armDriverNum].readings[readingNum].features.featureVector[firstMetal+i-oldFirstMetal] = features[i-oldFirstMetal];
      } 
	
      // Now add spectrometer data
      for(int i=firstSpec; i <= lastSpec; i++) {
	record.sensorData[armDriverNum].readings[readingNum].features.featureVector[i] = features[i-firstSpec];
      }

      record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[0] = firstSpec;
      record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[1] = lastSpec;
      record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[2] = firstMetal;
      record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[3] = lastMetal;

      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::insertMetalDetectorFeatures(dbRecord &record, int readingNum, vector features) {
  int armDriverNum;

  if(!getDriverNum(armDriverNum, ARM_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[armDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      int oldFirstMetal = (int)record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[2];

      // Find new indexes
      int lastMetal = oldFirstMetal + features.num() - 1;

      // Add metal detector data
      for(int i=oldFirstMetal; i <= lastMetal; i++) {
	record.sensorData[armDriverNum].readings[readingNum].features.featureVector[i] = features[i-oldFirstMetal];
      }
      
      record.sensorData[armDriverNum].readings[readingNum].optionalData.optionalData[3] = lastMetal;

      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::getImageFileName(const dbRecord &record, int readingNum, char *filename) {
  int hiResDriverNum;

  if(!getDriverNum(hiResDriverNum, HI_RES_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[hiResDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      strcpy(filename, record.sensorData[hiResDriverNum].readings[readingNum].filename);
      return(DB_OK);
    }
  }
}

int ClassifierNddsComms::getSpectrometerFileName(const dbRecord &record, int readingNum, char *filename) {
  if(getManipulatorFileName(record, readingNum, filename) == DB_OK) {
    // Now grab the _first_ filename listed in this file.

    fstream inFile(filename, ios::in);
    if(inFile.fail()) {
      return(DB_ERROR);
    }

    inFile >> filename;
    inFile.close();

    return(DB_OK);
  } else {
    return(DB_ERROR);
  }
}

int ClassifierNddsComms::getMetalDetectorFileName(const dbRecord &record, int readingNum, char *filename) {
  if(getManipulatorFileName(record, readingNum, filename) == DB_OK) {
    // Now grab the _second_ filename listed in this file.

    fstream inFile(filename, ios::in);
    if(inFile.fail()) {
      return(DB_ERROR);
    }

    inFile >> filename;
    inFile >> filename;
    inFile.close();

    return(DB_OK);
  } else {
    return(DB_ERROR);
  }
}


// Private methods

int ClassifierNddsComms::getDriverNum(int &driverNum, char *name) {
  for(int i=0; i < MAX_SENSORS; i++) {
    if(getDriverName(i, name) == DB_OK) {
      if(strcmp(name, HI_RES_DRIVER_NAME) == 0) {
	driverNum = i;
	return(1);
      }
    }
  }
  return(0);
}

int ClassifierNddsComms::getManipulatorFileName(const dbRecord &record, int readingNum, char *filename) {
  int armDriverNum;

  if(!getDriverNum(armDriverNum, ARM_DRIVER_NAME)) {
    return(DB_ERROR);
  } else {
    if(readingNum < 0 || readingNum >= record.sensorData[armDriverNum].numReadings) {
      return(DB_ERROR);
    } else {
      strcpy(filename, record.sensorData[armDriverNum].readings[readingNum].filename);
      return(DB_OK);
    }
  }
}

