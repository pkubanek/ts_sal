

#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_accessSync ( int handle , int direction, int optype ) {
  int status;


  if (strcmp("system_Computer_status",svcSAL_handle[handle].streamname) == 0 ) {
    system_Computer_status_cache *system_Computer_status_ref;
    system_Computer_status_ref  = (system_Computer_status_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Computer_status_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Computer_status_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Computer_status_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Computer_status_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Computer_status_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Computer_status_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("system_Software_revision_history",svcSAL_handle[handle].streamname) == 0 ) {
    system_Software_revision_history_cache *system_Software_revision_history_ref;
    system_Software_revision_history_ref  = (system_Software_revision_history_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Software_revision_history_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Software_revision_history_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Software_revision_history_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Software_revision_history_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Software_revision_history_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Software_revision_history_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("system_Hardware_revision_history",svcSAL_handle[handle].streamname) == 0 ) {
    system_Hardware_revision_history_cache *system_Hardware_revision_history_ref;
    system_Hardware_revision_history_ref  = (system_Hardware_revision_history_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Hardware_revision_history_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Hardware_revision_history_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Hardware_revision_history_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Hardware_revision_history_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Hardware_revision_history_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Hardware_revision_history_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("system_Command_history",svcSAL_handle[handle].streamname) == 0 ) {
    system_Command_history_cache *system_Command_history_ref;
    system_Command_history_ref  = (system_Command_history_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Command_history_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Command_history_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Command_history_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           system_Command_history_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           system_Command_history_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = system_Command_history_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_TC",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_TC_cache *m1m3_TC_ref;
    m1m3_TC_ref  = (m1m3_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Electrical_cache *m1m3_Electrical_ref;
    m1m3_Electrical_ref  = (m1m3_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Metrology_cache *m1m3_Metrology_ref;
    m1m3_Metrology_ref  = (m1m3_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Application",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Application_cache *m1m3_Application_ref;
    m1m3_Application_ref  = (m1m3_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Support",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Support_cache *m1m3_Support_ref;
    m1m3_Support_ref  = (m1m3_Support_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Support_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Support_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Support_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Support_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Support_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Support_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Actuators",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Actuators_cache *m1m3_Actuators_ref;
    m1m3_Actuators_ref  = (m1m3_Actuators_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Actuators_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Actuators_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Actuators_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Actuators_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Actuators_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Actuators_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_Surface",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_Surface_cache *m1m3_Surface_ref;
    m1m3_Surface_ref  = (m1m3_Surface_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Surface_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Surface_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Surface_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_Surface_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_Surface_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_Surface_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_TC",svcSAL_handle[handle].streamname) == 0 ) {
    m2_TC_cache *m2_TC_ref;
    m2_TC_ref  = (m2_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Electrical_cache *m2_Electrical_ref;
    m2_Electrical_ref  = (m2_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Metrology_cache *m2_Metrology_ref;
    m2_Metrology_ref  = (m2_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Application",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Application_cache *m2_Application_ref;
    m2_Application_ref  = (m2_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Hexapod",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Hexapod_cache *m2_Hexapod_ref;
    m2_Hexapod_ref  = (m2_Hexapod_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Hexapod_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Hexapod_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Hexapod_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Hexapod_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Hexapod_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Hexapod_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Actuators",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Actuators_cache *m2_Actuators_ref;
    m2_Actuators_ref  = (m2_Actuators_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Actuators_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Actuators_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Actuators_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Actuators_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Actuators_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Actuators_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_Surface",svcSAL_handle[handle].streamname) == 0 ) {
    m2_Surface_cache *m2_Surface_ref;
    m2_Surface_ref  = (m2_Surface_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Surface_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Surface_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Surface_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_Surface_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_Surface_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_Surface_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_TC",svcSAL_handle[handle].streamname) == 0 ) {
    mount_TC_cache *mount_TC_ref;
    mount_TC_ref  = (mount_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Electrical_cache *mount_Electrical_ref;
    mount_Electrical_ref  = (mount_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Metrology_cache *mount_Metrology_ref;
    mount_Metrology_ref  = (mount_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Application",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Application_cache *mount_Application_ref;
    mount_Application_ref  = (mount_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Alt",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Alt_cache *mount_Alt_ref;
    mount_Alt_ref  = (mount_Alt_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Alt_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Alt_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Alt_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Alt_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Alt_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Alt_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Az",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Az_cache *mount_Az_ref;
    mount_Az_ref  = (mount_Az_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Az_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Az_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Az_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Az_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Az_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Az_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_Rotator",svcSAL_handle[handle].streamname) == 0 ) {
    mount_Rotator_cache *mount_Rotator_ref;
    mount_Rotator_ref  = (mount_Rotator_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Rotator_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Rotator_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Rotator_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_Rotator_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_Rotator_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_Rotator_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("power_TC",svcSAL_handle[handle].streamname) == 0 ) {
    power_TC_cache *power_TC_ref;
    power_TC_ref  = (power_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           power_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           power_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("power_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    power_Electrical_cache *power_Electrical_ref;
    power_Electrical_ref  = (power_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           power_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           power_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("power_UPSs",svcSAL_handle[handle].streamname) == 0 ) {
    power_UPSs_cache *power_UPSs_ref;
    power_UPSs_ref  = (power_UPSs_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           power_UPSs_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_UPSs_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_UPSs_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           power_UPSs_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_UPSs_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_UPSs_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_TC",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_TC_cache *calibration_TC_ref;
    calibration_TC_ref  = (calibration_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_Electrical_cache *calibration_Electrical_ref;
    calibration_Electrical_ref  = (calibration_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_Metrology_cache *calibration_Metrology_ref;
    calibration_Metrology_ref  = (calibration_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_Application",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_Application_cache *calibration_Application_ref;
    calibration_Application_ref  = (calibration_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_TC",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_TC_cache *enclosure_TC_ref;
    enclosure_TC_ref  = (enclosure_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Electrical_cache *enclosure_Electrical_ref;
    enclosure_Electrical_ref  = (enclosure_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Metrology_cache *enclosure_Metrology_ref;
    enclosure_Metrology_ref  = (enclosure_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Application",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Application_cache *enclosure_Application_ref;
    enclosure_Application_ref  = (enclosure_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Azimuth",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Azimuth_cache *enclosure_Azimuth_ref;
    enclosure_Azimuth_ref  = (enclosure_Azimuth_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Azimuth_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Azimuth_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Azimuth_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Azimuth_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Azimuth_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Azimuth_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Shutter",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Shutter_cache *enclosure_Shutter_ref;
    enclosure_Shutter_ref  = (enclosure_Shutter_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Shutter_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Shutter_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Shutter_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Shutter_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Shutter_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Shutter_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Vents",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Vents_cache *enclosure_Vents_ref;
    enclosure_Vents_ref  = (enclosure_Vents_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Vents_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Vents_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Vents_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Vents_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Vents_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Vents_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_Thermal_control",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_Thermal_control_cache *enclosure_Thermal_control_ref;
    enclosure_Thermal_control_ref  = (enclosure_Thermal_control_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Thermal_control_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Thermal_control_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Thermal_control_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_Thermal_control_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_Thermal_control_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_Thermal_control_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("scheduler_Application",svcSAL_handle[handle].streamname) == 0 ) {
    scheduler_Application_cache *scheduler_Application_ref;
    scheduler_Application_ref  = (scheduler_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("operations_Application",svcSAL_handle[handle].streamname) == 0 ) {
    operations_Application_cache *operations_Application_ref;
    operations_Application_ref  = (operations_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_TC",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_TC_cache *auxscope_TC_ref;
    auxscope_TC_ref  = (auxscope_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_Electrical_cache *auxscope_Electrical_ref;
    auxscope_Electrical_ref  = (auxscope_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_Metrology_cache *auxscope_Metrology_ref;
    auxscope_Metrology_ref  = (auxscope_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_Application",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_Application_cache *auxscope_Application_ref;
    auxscope_Application_ref  = (auxscope_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_TCS",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_TCS_cache *auxscope_TCS_ref;
    auxscope_TCS_ref  = (auxscope_TCS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_TCS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_TCS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_TCS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_TCS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_TCS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_TCS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_Spectrometer",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_Spectrometer_cache *auxscope_Spectrometer_ref;
    auxscope_Spectrometer_ref  = (auxscope_Spectrometer_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Spectrometer_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Spectrometer_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Spectrometer_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Spectrometer_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Spectrometer_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Spectrometer_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_Camera",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_Camera_cache *auxscope_Camera_ref;
    auxscope_Camera_ref  = (auxscope_Camera_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Camera_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Camera_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Camera_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_Camera_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_Camera_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_Camera_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("lasercal_TC",svcSAL_handle[handle].streamname) == 0 ) {
    lasercal_TC_cache *lasercal_TC_ref;
    lasercal_TC_ref  = (lasercal_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("lasercal_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    lasercal_Electrical_cache *lasercal_Electrical_ref;
    lasercal_Electrical_ref  = (lasercal_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("lasercal_Application",svcSAL_handle[handle].streamname) == 0 ) {
    lasercal_Application_cache *lasercal_Application_ref;
    lasercal_Application_ref  = (lasercal_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_TC",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_TC_cache *seeing_dimm_TC_ref;
    seeing_dimm_TC_ref  = (seeing_dimm_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_Electrical_cache *seeing_dimm_Electrical_ref;
    seeing_dimm_Electrical_ref  = (seeing_dimm_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_Metrology_cache *seeing_dimm_Metrology_ref;
    seeing_dimm_Metrology_ref  = (seeing_dimm_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_Application",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_Application_cache *seeing_dimm_Application_ref;
    seeing_dimm_Application_ref  = (seeing_dimm_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_TC",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_TC_cache *seeing_mass_TC_ref;
    seeing_mass_TC_ref  = (seeing_mass_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_Electrical_cache *seeing_mass_Electrical_ref;
    seeing_mass_Electrical_ref  = (seeing_mass_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_Metrology_cache *seeing_mass_Metrology_ref;
    seeing_mass_Metrology_ref  = (seeing_mass_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_Application",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_Application_cache *seeing_mass_Application_ref;
    seeing_mass_Application_ref  = (seeing_mass_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_TC",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_TC_cache *skycam_TC_ref;
    skycam_TC_ref  = (skycam_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_Electrical_cache *skycam_Electrical_ref;
    skycam_Electrical_ref  = (skycam_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_Metrology_cache *skycam_Metrology_ref;
    skycam_Metrology_ref  = (skycam_Metrology_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Metrology_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Metrology_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Metrology_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Metrology_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Metrology_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Metrology_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_Application",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_Application_cache *skycam_Application_ref;
    skycam_Application_ref  = (skycam_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_TC",svcSAL_handle[handle].streamname) == 0 ) {
    environment_TC_cache *environment_TC_ref;
    environment_TC_ref  = (environment_TC_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_TC_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_TC_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_TC_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_TC_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_TC_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_TC_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Electrical_cache *environment_Electrical_ref;
    environment_Electrical_ref  = (environment_Electrical_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Electrical_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Electrical_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Electrical_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Electrical_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Electrical_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Electrical_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Weather",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Weather_cache *environment_Weather_ref;
    environment_Weather_ref  = (environment_Weather_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Weather_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Weather_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Weather_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Weather_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Weather_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Weather_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Dust_monitor",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Dust_monitor_cache *environment_Dust_monitor_ref;
    environment_Dust_monitor_ref  = (environment_Dust_monitor_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Dust_monitor_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Dust_monitor_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Dust_monitor_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Dust_monitor_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Dust_monitor_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Dust_monitor_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Lightning_detector",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Lightning_detector_cache *environment_Lightning_detector_ref;
    environment_Lightning_detector_ref  = (environment_Lightning_detector_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Lightning_detector_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Lightning_detector_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Lightning_detector_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Lightning_detector_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Lightning_detector_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Lightning_detector_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Seismometer",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Seismometer_cache *environment_Seismometer_ref;
    environment_Seismometer_ref  = (environment_Seismometer_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Seismometer_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Seismometer_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Seismometer_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Seismometer_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Seismometer_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Seismometer_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_Video_cameras",svcSAL_handle[handle].streamname) == 0 ) {
    environment_Video_cameras_cache *environment_Video_cameras_ref;
    environment_Video_cameras_ref  = (environment_Video_cameras_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Video_cameras_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Video_cameras_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Video_cameras_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_Video_cameras_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_Video_cameras_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_Video_cameras_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("network_Application",svcSAL_handle[handle].streamname) == 0 ) {
    network_Application_cache *network_Application_ref;
    network_Application_ref  = (network_Application_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           network_Application_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_Application_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_Application_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           network_Application_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_Application_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_Application_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_TrackRefSys",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_TrackRefSys_cache *tcs_kernel_TrackRefSys_ref;
    tcs_kernel_TrackRefSys_ref  = (tcs_kernel_TrackRefSys_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TrackRefSys_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TrackRefSys_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TrackRefSys_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TrackRefSys_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TrackRefSys_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TrackRefSys_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_Target",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_Target_cache *tcs_kernel_Target_ref;
    tcs_kernel_Target_ref  = (tcs_kernel_Target_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_Target_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_Target_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_Target_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_Target_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_Target_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_Target_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_DawdleFilter",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_DawdleFilter_cache *tcs_kernel_DawdleFilter_ref;
    tcs_kernel_DawdleFilter_ref  = (tcs_kernel_DawdleFilter_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_DawdleFilter_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_DawdleFilter_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_DawdleFilter_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_DawdleFilter_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_DawdleFilter_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_DawdleFilter_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_FK5Target",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_FK5Target_cache *tcs_kernel_FK5Target_ref;
    tcs_kernel_FK5Target_ref  = (tcs_kernel_FK5Target_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_FK5Target_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_FK5Target_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_FK5Target_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_FK5Target_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_FK5Target_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_FK5Target_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_OpticsVt",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_OpticsVt_cache *tcs_kernel_OpticsVt_ref;
    tcs_kernel_OpticsVt_ref  = (tcs_kernel_OpticsVt_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_OpticsVt_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_OpticsVt_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_OpticsVt_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_OpticsVt_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_OpticsVt_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_OpticsVt_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_PointingControl",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_PointingControl_cache *tcs_kernel_PointingControl_ref;
    tcs_kernel_PointingControl_ref  = (tcs_kernel_PointingControl_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingControl_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingControl_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingControl_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingControl_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingControl_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingControl_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_PointingLog",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_PointingLog_cache *tcs_kernel_PointingLog_ref;
    tcs_kernel_PointingLog_ref  = (tcs_kernel_PointingLog_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingLog_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingLog_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingLog_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingLog_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingLog_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingLog_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_PointingModel",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_PointingModel_cache *tcs_kernel_PointingModel_ref;
    tcs_kernel_PointingModel_ref  = (tcs_kernel_PointingModel_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingModel_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingModel_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingModel_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_PointingModel_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_PointingModel_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_PointingModel_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_Site",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_Site_cache *tcs_kernel_Site_ref;
    tcs_kernel_Site_ref  = (tcs_kernel_Site_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_Site_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_Site_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_Site_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_Site_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_Site_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_Site_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_TimeKeeper",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_TimeKeeper_cache *tcs_kernel_TimeKeeper_ref;
    tcs_kernel_TimeKeeper_ref  = (tcs_kernel_TimeKeeper_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TimeKeeper_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TimeKeeper_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TimeKeeper_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TimeKeeper_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TimeKeeper_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TimeKeeper_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_kernel_TrackingTarget",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_kernel_TrackingTarget_cache *tcs_kernel_TrackingTarget_ref;
    tcs_kernel_TrackingTarget_ref  = (tcs_kernel_TrackingTarget_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TrackingTarget_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TrackingTarget_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TrackingTarget_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_kernel_TrackingTarget_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_kernel_TrackingTarget_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_kernel_TrackingTarget_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_BEE_biases",svcSAL_handle[handle].streamname) == 0 ) {
    camera_BEE_biases_cache *camera_BEE_biases_ref;
    camera_BEE_biases_ref  = (camera_BEE_biases_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_biases_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_biases_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_biases_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_biases_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_biases_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_biases_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_BEE_clocks",svcSAL_handle[handle].streamname) == 0 ) {
    camera_BEE_clocks_cache *camera_BEE_clocks_ref;
    camera_BEE_clocks_ref  = (camera_BEE_clocks_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_clocks_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_clocks_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_clocks_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_clocks_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_clocks_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_clocks_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_BEE_thermal",svcSAL_handle[handle].streamname) == 0 ) {
    camera_BEE_thermal_cache *camera_BEE_thermal_ref;
    camera_BEE_thermal_ref  = (camera_BEE_thermal_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_thermal_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_thermal_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_thermal_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_BEE_thermal_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_BEE_thermal_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_BEE_thermal_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_CALSYS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_CALSYS_cache *camera_CALSYS_ref;
    camera_CALSYS_ref  = (camera_CALSYS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_CALSYS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_CALSYS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_CALSYS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_CALSYS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_CALSYS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_CALSYS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_CCS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_CCS_cache *camera_CCS_ref;
    camera_CCS_ref  = (camera_CCS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_CCS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_CCS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_CCS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_CCS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_CCS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_CCS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_FCS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_FCS_cache *camera_FCS_ref;
    camera_FCS_ref  = (camera_FCS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_FCS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_FCS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_FCS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_FCS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_FCS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_FCS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_GAS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_GAS_cache *camera_GAS_ref;
    camera_GAS_ref  = (camera_GAS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_GAS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_GAS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_GAS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_GAS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_GAS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_GAS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_LASERCAL",svcSAL_handle[handle].streamname) == 0 ) {
    camera_LASERCAL_cache *camera_LASERCAL_ref;
    camera_LASERCAL_ref  = (camera_LASERCAL_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_LASERCAL_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_LASERCAL_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_LASERCAL_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_LASERCAL_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_LASERCAL_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_LASERCAL_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_PWR",svcSAL_handle[handle].streamname) == 0 ) {
    camera_PWR_cache *camera_PWR_ref;
    camera_PWR_ref  = (camera_PWR_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_PWR_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_PWR_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_PWR_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_PWR_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_PWR_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_PWR_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_QA_measured",svcSAL_handle[handle].streamname) == 0 ) {
    camera_QA_measured_cache *camera_QA_measured_ref;
    camera_QA_measured_ref  = (camera_QA_measured_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_QA_measured_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_QA_measured_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_QA_measured_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_QA_measured_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_QA_measured_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_QA_measured_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_SCS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_SCS_cache *camera_SCS_ref;
    camera_SCS_ref  = (camera_SCS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SCS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SCS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SCS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SCS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SCS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SCS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_SDS_amplifiers",svcSAL_handle[handle].streamname) == 0 ) {
    camera_SDS_amplifiers_cache *camera_SDS_amplifiers_ref;
    camera_SDS_amplifiers_ref  = (camera_SDS_amplifiers_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SDS_amplifiers_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SDS_amplifiers_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SDS_amplifiers_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SDS_amplifiers_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SDS_amplifiers_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SDS_amplifiers_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_SDS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_SDS_cache *camera_SDS_ref;
    camera_SDS_ref  = (camera_SDS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SDS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SDS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SDS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_SDS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_SDS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_SDS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_control",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_control_cache *camera_TC_control_ref;
    camera_TC_control_ref  = (camera_TC_control_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_control_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_control_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_control_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_control_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_control_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_control_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TCM",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TCM_cache *camera_TCM_ref;
    camera_TCM_ref  = (camera_TCM_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TCM_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TCM_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TCM_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TCM_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TCM_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TCM_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone1",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone1_cache *camera_TC_zone1_ref;
    camera_TC_zone1_ref  = (camera_TC_zone1_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone1_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone1_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone1_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone1_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone1_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone1_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone2",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone2_cache *camera_TC_zone2_ref;
    camera_TC_zone2_ref  = (camera_TC_zone2_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone2_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone2_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone2_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone2_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone2_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone2_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone3",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone3_cache *camera_TC_zone3_ref;
    camera_TC_zone3_ref  = (camera_TC_zone3_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone3_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone3_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone3_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone3_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone3_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone3_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone4",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone4_cache *camera_TC_zone4_ref;
    camera_TC_zone4_ref  = (camera_TC_zone4_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone4_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone4_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone4_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone4_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone4_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone4_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone5",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone5_cache *camera_TC_zone5_ref;
    camera_TC_zone5_ref  = (camera_TC_zone5_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone5_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone5_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone5_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone5_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone5_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone5_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_TC_zone6",svcSAL_handle[handle].streamname) == 0 ) {
    camera_TC_zone6_cache *camera_TC_zone6_ref;
    camera_TC_zone6_ref  = (camera_TC_zone6_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone6_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone6_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone6_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_TC_zone6_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_TC_zone6_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_TC_zone6_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_UTIL",svcSAL_handle[handle].streamname) == 0 ) {
    camera_UTIL_cache *camera_UTIL_ref;
    camera_UTIL_ref  = (camera_UTIL_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_UTIL_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_UTIL_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_UTIL_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_UTIL_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_UTIL_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_UTIL_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_VCS",svcSAL_handle[handle].streamname) == 0 ) {
    camera_VCS_cache *camera_VCS_ref;
    camera_VCS_ref  = (camera_VCS_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_VCS_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_VCS_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_VCS_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_VCS_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_VCS_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_VCS_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_WDS_wfsRaft",svcSAL_handle[handle].streamname) == 0 ) {
    camera_WDS_wfsRaft_cache *camera_WDS_wfsRaft_ref;
    camera_WDS_wfsRaft_ref  = (camera_WDS_wfsRaft_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_WDS_wfsRaft_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_WDS_wfsRaft_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_WDS_wfsRaft_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_WDS_wfsRaft_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_WDS_wfsRaft_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_WDS_wfsRaft_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_command",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_command_cache *auxscope_command_ref;
    auxscope_command_ref  = (auxscope_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("auxscope_response",svcSAL_handle[handle].streamname) == 0 ) {
    auxscope_response_cache *auxscope_response_ref;
    auxscope_response_ref  = (auxscope_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           auxscope_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           auxscope_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = auxscope_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_command",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_command_cache *calibration_command_ref;
    calibration_command_ref  = (calibration_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("calibration_response",svcSAL_handle[handle].streamname) == 0 ) {
    calibration_response_cache *calibration_response_ref;
    calibration_response_ref  = (calibration_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           calibration_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           calibration_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = calibration_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_command",svcSAL_handle[handle].streamname) == 0 ) {
    camera_command_cache *camera_command_ref;
    camera_command_ref  = (camera_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("camera_response",svcSAL_handle[handle].streamname) == 0 ) {
    camera_response_cache *camera_response_ref;
    camera_response_ref  = (camera_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           camera_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           camera_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = camera_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_command",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_command_cache *enclosure_command_ref;
    enclosure_command_ref  = (enclosure_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("enclosure_response",svcSAL_handle[handle].streamname) == 0 ) {
    enclosure_response_cache *enclosure_response_ref;
    enclosure_response_ref  = (enclosure_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           enclosure_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           enclosure_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = enclosure_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_command",svcSAL_handle[handle].streamname) == 0 ) {
    environment_command_cache *environment_command_ref;
    environment_command_ref  = (environment_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("environment_response",svcSAL_handle[handle].streamname) == 0 ) {
    environment_response_cache *environment_response_ref;
    environment_response_ref  = (environment_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           environment_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           environment_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = environment_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("lasercal_command",svcSAL_handle[handle].streamname) == 0 ) {
    lasercal_command_cache *lasercal_command_ref;
    lasercal_command_ref  = (lasercal_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("lasercal_response",svcSAL_handle[handle].streamname) == 0 ) {
    lasercal_response_cache *lasercal_response_ref;
    lasercal_response_ref  = (lasercal_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           lasercal_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           lasercal_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = lasercal_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_command",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_command_cache *m1m3_command_ref;
    m1m3_command_ref  = (m1m3_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m1m3_response",svcSAL_handle[handle].streamname) == 0 ) {
    m1m3_response_cache *m1m3_response_ref;
    m1m3_response_ref  = (m1m3_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m1m3_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m1m3_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m1m3_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_command",svcSAL_handle[handle].streamname) == 0 ) {
    m2_command_cache *m2_command_ref;
    m2_command_ref  = (m2_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("m2_response",svcSAL_handle[handle].streamname) == 0 ) {
    m2_response_cache *m2_response_ref;
    m2_response_ref  = (m2_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           m2_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           m2_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = m2_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_command",svcSAL_handle[handle].streamname) == 0 ) {
    mount_command_cache *mount_command_ref;
    mount_command_ref  = (mount_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("mount_response",svcSAL_handle[handle].streamname) == 0 ) {
    mount_response_cache *mount_response_ref;
    mount_response_ref  = (mount_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           mount_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           mount_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = mount_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("network_command",svcSAL_handle[handle].streamname) == 0 ) {
    network_command_cache *network_command_ref;
    network_command_ref  = (network_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           network_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           network_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("network_response",svcSAL_handle[handle].streamname) == 0 ) {
    network_response_cache *network_response_ref;
    network_response_ref  = (network_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           network_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           network_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           network_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = network_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("operations_command",svcSAL_handle[handle].streamname) == 0 ) {
    operations_command_cache *operations_command_ref;
    operations_command_ref  = (operations_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("operations_response",svcSAL_handle[handle].streamname) == 0 ) {
    operations_response_cache *operations_response_ref;
    operations_response_ref  = (operations_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           operations_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           operations_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = operations_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("power_command",svcSAL_handle[handle].streamname) == 0 ) {
    power_command_cache *power_command_ref;
    power_command_ref  = (power_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           power_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           power_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("power_response",svcSAL_handle[handle].streamname) == 0 ) {
    power_response_cache *power_response_ref;
    power_response_ref  = (power_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           power_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           power_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           power_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = power_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("scheduler_command",svcSAL_handle[handle].streamname) == 0 ) {
    scheduler_command_cache *scheduler_command_ref;
    scheduler_command_ref  = (scheduler_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("scheduler_response",svcSAL_handle[handle].streamname) == 0 ) {
    scheduler_response_cache *scheduler_response_ref;
    scheduler_response_ref  = (scheduler_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           scheduler_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           scheduler_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = scheduler_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_command",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_command_cache *seeing_dimm_command_ref;
    seeing_dimm_command_ref  = (seeing_dimm_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_dimm_response",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_dimm_response_cache *seeing_dimm_response_ref;
    seeing_dimm_response_ref  = (seeing_dimm_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_dimm_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_dimm_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_dimm_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_command",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_command_cache *seeing_mass_command_ref;
    seeing_mass_command_ref  = (seeing_mass_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("seeing_mass_response",svcSAL_handle[handle].streamname) == 0 ) {
    seeing_mass_response_cache *seeing_mass_response_ref;
    seeing_mass_response_ref  = (seeing_mass_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           seeing_mass_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           seeing_mass_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = seeing_mass_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_command",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_command_cache *skycam_command_ref;
    skycam_command_ref  = (skycam_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("skycam_response",svcSAL_handle[handle].streamname) == 0 ) {
    skycam_response_cache *skycam_response_ref;
    skycam_response_ref  = (skycam_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           skycam_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           skycam_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = skycam_response_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_command",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_command_cache *tcs_command_ref;
    tcs_command_ref  = (tcs_command_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_command_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_command_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_command_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_command_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_command_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_command_ref->syncO;
        }
     }

     return status;
  }

  if (strcmp("tcs_response",svcSAL_handle[handle].streamname) == 0 ) {
    tcs_response_cache *tcs_response_ref;
    tcs_response_ref  = (tcs_response_cache *) svcSAL_handle[handle].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_response_ref->syncI = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_response_ref->syncI = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_response_ref->syncI;
        }
     }
     if ( direction == SAL__SYNC_OUT ) {
        if ( optype == SAL__SYNC_SET ) {
           tcs_response_ref->syncO = 1;
        }
        if ( optype == SAL__SYNC_CLEAR ) {
           tcs_response_ref->syncO = 0;
        }
        if ( optype == SAL__SYNC_READ ) {
           status = tcs_response_ref->syncO;
        }
     }

     return status;
  }

  return SAL__ERR;
}

