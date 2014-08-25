#ifndef __NDDS_MSG_NAMES_H__
#define __NDDS_MSG_NAMES_H__

#define MAX_NDDS_NAME_LENGTH 100
#define MAX_NDDS_DATA_LENGTH 8096

#ifndef TARGET_ACQ_COMPLETE_MSG_NAME
#define TARGET_ACQ_COMPLETE_MSG_NAME "targetAcqComplete"
#endif
#ifndef TARGET_ACQ_REQUEST_MSG_NAME
#define TARGET_ACQ_REQUEST_MSG_NAME "targetAcqRequest"
#endif
#ifndef TARGET_ACQ_REPLY_MSG_NAME
#define TARGET_ACQ_REPLY_MSG_NAME "targetAcqReply"
#endif
#ifndef SENSOR_REQUEST_MSG_NAME
#define SENSOR_REQUEST_MSG_NAME "sensorRequest"
#endif
#ifndef SENSOR_REPLY_MSG_NAME
#define SENSOR_REPLY_MSG_NAME "sensorReply"
#endif
#ifndef SENSOR_REG_MSG_NAME
#define SENSOR_REG_MSG_NAME "sensorReg"
#endif
#ifndef SENS_MAN_REQUEST_MSG_NAME
#define SENS_MAN_REQUEST_MSG_NAME "sensManRequest"
#endif
#ifndef SENS_MAN_REPLY_MSG_NAME
#define SENS_MAN_REPLY_MSG_NAME "sensManReply"
#endif
#ifndef SENS_MAN_COMPLETE_MSG_NAME
#define SENS_MAN_COMPLETE_MSG_NAME "sensManComplete"
#endif
#ifndef POS_DERIVED_STATE_MSG_NAME
#define POS_DERIVED_STATE_MSG_NAME "posDerivedState"
#endif
#ifndef DB_REQUEST_MSG_NAME
#define DB_REQUEST_MSG_NAME "dbRequest"
#endif
#ifndef DB_REPLY_MSG_NAME
#define DB_REPLY_MSG_NAME "dbReply"
#endif
#ifndef DB_NOTIFY_MSG_NAME
#define DB_NOTIFY_MSG_NAME "dbNotify"
#endif
#ifndef BOD_DERIVED_STATE_MSG_NAME
#define BOD_DERIVED_STATE_MSG_NAME "bodDerivedState"
#endif
#ifndef POS_DERIVED_STATE_MSG_NAME
#define POS_DERIVED_STATE_MSG_NAME "posDerivedState"
#endif
#ifndef WEATHER_STATE_MSG_NAME
#define WEATHER_STATE_MSG_NAME "weatherState"
#endif
#ifndef RT_CONTROL_STATE_MSG_NAME
#define RT_CONTROL_STATE_MSG_NAME "rtControlState"
#endif
#ifndef RT_AMP_STATE_MSG_NAME
#define RT_AMP_STATE_MSG_NAME "rtAmpState"
#endif
#ifndef KVH_DERIVED_STATE_MSG_NAME
#define KVH_DERIVED_STATE_MSG_NAME "kvhDerivedState"
#endif
#ifndef HI_RES_DERIVED_STATE_MSG_NAME
#define HI_RES_DERIVED_STATE_MSG_NAME "hiResDerivedState"
#endif
#ifndef ARM_DERIVED_STATE_MSG_NAME
#define ARM_DERIVED_STATE_MSG_NAME "armDerivedState"
#endif
#ifndef LASER_DERIVED_STATE_MSG_NAME
#define LASER_DERIVED_STATE_MSG_NAME "laserDerivedState"
#endif
#ifndef MOVE_MSG_NAME
#define MOVE_MSG_NAME "rtMove"
#endif
#endif /* __NDDS_MSG_NAMES_H__ */
