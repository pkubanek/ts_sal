

#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_accessPrivate ( int handle , char *operation, char *revCode , 
                           long *sndStamp, long *rcvStamp,
                           long *seqNum  , long *origin ) {


  if (strcmp("system_Computer_status",svcSAL_handle[handle].streamname) == 0 ) {
     system_Computer_status_cache *system_Computer_status_ref;
     system_Computer_status_ref  = (system_Computer_status_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = system_Computer_status_ref->private_sndStamp; 
        *rcvStamp = system_Computer_status_ref->private_rcvStamp; 
        *seqNum = system_Computer_status_ref->private_seqNum; 
        *origin = system_Computer_status_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        system_Computer_status_ref->private_sndStamp = *sndStamp; 
        system_Computer_status_ref->private_rcvStamp = *rcvStamp; 
        system_Computer_status_ref->private_seqNum = *seqNum; 
        system_Computer_status_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9366a773c77b5017825951c6d28d7d66") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("system_Software_revision_history",svcSAL_handle[handle].streamname) == 0 ) {
     system_Software_revision_history_cache *system_Software_revision_history_ref;
     system_Software_revision_history_ref  = (system_Software_revision_history_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = system_Software_revision_history_ref->private_sndStamp; 
        *rcvStamp = system_Software_revision_history_ref->private_rcvStamp; 
        *seqNum = system_Software_revision_history_ref->private_seqNum; 
        *origin = system_Software_revision_history_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        system_Software_revision_history_ref->private_sndStamp = *sndStamp; 
        system_Software_revision_history_ref->private_rcvStamp = *rcvStamp; 
        system_Software_revision_history_ref->private_seqNum = *seqNum; 
        system_Software_revision_history_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"4373e713057a4550b5850c8a2051f46a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("system_Hardware_revision_history",svcSAL_handle[handle].streamname) == 0 ) {
     system_Hardware_revision_history_cache *system_Hardware_revision_history_ref;
     system_Hardware_revision_history_ref  = (system_Hardware_revision_history_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = system_Hardware_revision_history_ref->private_sndStamp; 
        *rcvStamp = system_Hardware_revision_history_ref->private_rcvStamp; 
        *seqNum = system_Hardware_revision_history_ref->private_seqNum; 
        *origin = system_Hardware_revision_history_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        system_Hardware_revision_history_ref->private_sndStamp = *sndStamp; 
        system_Hardware_revision_history_ref->private_rcvStamp = *rcvStamp; 
        system_Hardware_revision_history_ref->private_seqNum = *seqNum; 
        system_Hardware_revision_history_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"dcb9123316b55060aa300a1292430041") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("system_Command_history",svcSAL_handle[handle].streamname) == 0 ) {
     system_Command_history_cache *system_Command_history_ref;
     system_Command_history_ref  = (system_Command_history_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = system_Command_history_ref->private_sndStamp; 
        *rcvStamp = system_Command_history_ref->private_rcvStamp; 
        *seqNum = system_Command_history_ref->private_seqNum; 
        *origin = system_Command_history_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        system_Command_history_ref->private_sndStamp = *sndStamp; 
        system_Command_history_ref->private_rcvStamp = *rcvStamp; 
        system_Command_history_ref->private_seqNum = *seqNum; 
        system_Command_history_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9fb6bad388f853a8777f0fcc3f1855c7") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_TC",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_TC_cache *m1m3_TC_ref;
     m1m3_TC_ref  = (m1m3_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_TC_ref->private_sndStamp; 
        *rcvStamp = m1m3_TC_ref->private_rcvStamp; 
        *seqNum = m1m3_TC_ref->private_seqNum; 
        *origin = m1m3_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_TC_ref->private_sndStamp = *sndStamp; 
        m1m3_TC_ref->private_rcvStamp = *rcvStamp; 
        m1m3_TC_ref->private_seqNum = *seqNum; 
        m1m3_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"11d6eeb86875a4283b541c772b67ab29") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Electrical_cache *m1m3_Electrical_ref;
     m1m3_Electrical_ref  = (m1m3_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Electrical_ref->private_sndStamp; 
        *rcvStamp = m1m3_Electrical_ref->private_rcvStamp; 
        *seqNum = m1m3_Electrical_ref->private_seqNum; 
        *origin = m1m3_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Electrical_ref->private_sndStamp = *sndStamp; 
        m1m3_Electrical_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Electrical_ref->private_seqNum = *seqNum; 
        m1m3_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"646cd37f3be48fff42e28c42470ae1a1") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Metrology_cache *m1m3_Metrology_ref;
     m1m3_Metrology_ref  = (m1m3_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Metrology_ref->private_sndStamp; 
        *rcvStamp = m1m3_Metrology_ref->private_rcvStamp; 
        *seqNum = m1m3_Metrology_ref->private_seqNum; 
        *origin = m1m3_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Metrology_ref->private_sndStamp = *sndStamp; 
        m1m3_Metrology_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Metrology_ref->private_seqNum = *seqNum; 
        m1m3_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9c134ea1ac48be45a907b1761c909563") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Application",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Application_cache *m1m3_Application_ref;
     m1m3_Application_ref  = (m1m3_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Application_ref->private_sndStamp; 
        *rcvStamp = m1m3_Application_ref->private_rcvStamp; 
        *seqNum = m1m3_Application_ref->private_seqNum; 
        *origin = m1m3_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Application_ref->private_sndStamp = *sndStamp; 
        m1m3_Application_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Application_ref->private_seqNum = *seqNum; 
        m1m3_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"216b8715649b0f4a082ebd0411b7c326") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Support",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Support_cache *m1m3_Support_ref;
     m1m3_Support_ref  = (m1m3_Support_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Support_ref->private_sndStamp; 
        *rcvStamp = m1m3_Support_ref->private_rcvStamp; 
        *seqNum = m1m3_Support_ref->private_seqNum; 
        *origin = m1m3_Support_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Support_ref->private_sndStamp = *sndStamp; 
        m1m3_Support_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Support_ref->private_seqNum = *seqNum; 
        m1m3_Support_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"6e47e8f485df27cc43f54d43e9cb8673") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Actuators",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Actuators_cache *m1m3_Actuators_ref;
     m1m3_Actuators_ref  = (m1m3_Actuators_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Actuators_ref->private_sndStamp; 
        *rcvStamp = m1m3_Actuators_ref->private_rcvStamp; 
        *seqNum = m1m3_Actuators_ref->private_seqNum; 
        *origin = m1m3_Actuators_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Actuators_ref->private_sndStamp = *sndStamp; 
        m1m3_Actuators_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Actuators_ref->private_seqNum = *seqNum; 
        m1m3_Actuators_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"6dcfc5dec7d01d49ead3241d9df6005e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_Surface",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_Surface_cache *m1m3_Surface_ref;
     m1m3_Surface_ref  = (m1m3_Surface_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_Surface_ref->private_sndStamp; 
        *rcvStamp = m1m3_Surface_ref->private_rcvStamp; 
        *seqNum = m1m3_Surface_ref->private_seqNum; 
        *origin = m1m3_Surface_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_Surface_ref->private_sndStamp = *sndStamp; 
        m1m3_Surface_ref->private_rcvStamp = *rcvStamp; 
        m1m3_Surface_ref->private_seqNum = *seqNum; 
        m1m3_Surface_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"fec997743aee7b13578c40c5c8888259") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_TC",svcSAL_handle[handle].streamname) == 0 ) {
     m2_TC_cache *m2_TC_ref;
     m2_TC_ref  = (m2_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_TC_ref->private_sndStamp; 
        *rcvStamp = m2_TC_ref->private_rcvStamp; 
        *seqNum = m2_TC_ref->private_seqNum; 
        *origin = m2_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_TC_ref->private_sndStamp = *sndStamp; 
        m2_TC_ref->private_rcvStamp = *rcvStamp; 
        m2_TC_ref->private_seqNum = *seqNum; 
        m2_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"755e745fbab565597639e301bf65322c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Electrical_cache *m2_Electrical_ref;
     m2_Electrical_ref  = (m2_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Electrical_ref->private_sndStamp; 
        *rcvStamp = m2_Electrical_ref->private_rcvStamp; 
        *seqNum = m2_Electrical_ref->private_seqNum; 
        *origin = m2_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Electrical_ref->private_sndStamp = *sndStamp; 
        m2_Electrical_ref->private_rcvStamp = *rcvStamp; 
        m2_Electrical_ref->private_seqNum = *seqNum; 
        m2_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"15a212f496e4a45e8971b940d31885a7") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Metrology_cache *m2_Metrology_ref;
     m2_Metrology_ref  = (m2_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Metrology_ref->private_sndStamp; 
        *rcvStamp = m2_Metrology_ref->private_rcvStamp; 
        *seqNum = m2_Metrology_ref->private_seqNum; 
        *origin = m2_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Metrology_ref->private_sndStamp = *sndStamp; 
        m2_Metrology_ref->private_rcvStamp = *rcvStamp; 
        m2_Metrology_ref->private_seqNum = *seqNum; 
        m2_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"202c87a6566068ef448733b0c29e6b55") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Application",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Application_cache *m2_Application_ref;
     m2_Application_ref  = (m2_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Application_ref->private_sndStamp; 
        *rcvStamp = m2_Application_ref->private_rcvStamp; 
        *seqNum = m2_Application_ref->private_seqNum; 
        *origin = m2_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Application_ref->private_sndStamp = *sndStamp; 
        m2_Application_ref->private_rcvStamp = *rcvStamp; 
        m2_Application_ref->private_seqNum = *seqNum; 
        m2_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e6b739d9de2e5c393c4101121e5b14a7") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Hexapod",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Hexapod_cache *m2_Hexapod_ref;
     m2_Hexapod_ref  = (m2_Hexapod_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Hexapod_ref->private_sndStamp; 
        *rcvStamp = m2_Hexapod_ref->private_rcvStamp; 
        *seqNum = m2_Hexapod_ref->private_seqNum; 
        *origin = m2_Hexapod_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Hexapod_ref->private_sndStamp = *sndStamp; 
        m2_Hexapod_ref->private_rcvStamp = *rcvStamp; 
        m2_Hexapod_ref->private_seqNum = *seqNum; 
        m2_Hexapod_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"d75f563513ccf70c3dc370fd3ab1e7ca") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Actuators",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Actuators_cache *m2_Actuators_ref;
     m2_Actuators_ref  = (m2_Actuators_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Actuators_ref->private_sndStamp; 
        *rcvStamp = m2_Actuators_ref->private_rcvStamp; 
        *seqNum = m2_Actuators_ref->private_seqNum; 
        *origin = m2_Actuators_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Actuators_ref->private_sndStamp = *sndStamp; 
        m2_Actuators_ref->private_rcvStamp = *rcvStamp; 
        m2_Actuators_ref->private_seqNum = *seqNum; 
        m2_Actuators_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"981f9536a39541e1330b8b85815e587b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_Surface",svcSAL_handle[handle].streamname) == 0 ) {
     m2_Surface_cache *m2_Surface_ref;
     m2_Surface_ref  = (m2_Surface_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_Surface_ref->private_sndStamp; 
        *rcvStamp = m2_Surface_ref->private_rcvStamp; 
        *seqNum = m2_Surface_ref->private_seqNum; 
        *origin = m2_Surface_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_Surface_ref->private_sndStamp = *sndStamp; 
        m2_Surface_ref->private_rcvStamp = *rcvStamp; 
        m2_Surface_ref->private_seqNum = *seqNum; 
        m2_Surface_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"c0464c7ba38fe0257a45c6593eea43df") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_TC",svcSAL_handle[handle].streamname) == 0 ) {
     mount_TC_cache *mount_TC_ref;
     mount_TC_ref  = (mount_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_TC_ref->private_sndStamp; 
        *rcvStamp = mount_TC_ref->private_rcvStamp; 
        *seqNum = mount_TC_ref->private_seqNum; 
        *origin = mount_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_TC_ref->private_sndStamp = *sndStamp; 
        mount_TC_ref->private_rcvStamp = *rcvStamp; 
        mount_TC_ref->private_seqNum = *seqNum; 
        mount_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"77e258dfd157be43daab4f420142aa8c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Electrical_cache *mount_Electrical_ref;
     mount_Electrical_ref  = (mount_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Electrical_ref->private_sndStamp; 
        *rcvStamp = mount_Electrical_ref->private_rcvStamp; 
        *seqNum = mount_Electrical_ref->private_seqNum; 
        *origin = mount_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Electrical_ref->private_sndStamp = *sndStamp; 
        mount_Electrical_ref->private_rcvStamp = *rcvStamp; 
        mount_Electrical_ref->private_seqNum = *seqNum; 
        mount_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e2e037c710053b25fbf030d7992ced6e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Metrology_cache *mount_Metrology_ref;
     mount_Metrology_ref  = (mount_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Metrology_ref->private_sndStamp; 
        *rcvStamp = mount_Metrology_ref->private_rcvStamp; 
        *seqNum = mount_Metrology_ref->private_seqNum; 
        *origin = mount_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Metrology_ref->private_sndStamp = *sndStamp; 
        mount_Metrology_ref->private_rcvStamp = *rcvStamp; 
        mount_Metrology_ref->private_seqNum = *seqNum; 
        mount_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"378a83be0d5ad0da0b66286a181cac8e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Application",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Application_cache *mount_Application_ref;
     mount_Application_ref  = (mount_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Application_ref->private_sndStamp; 
        *rcvStamp = mount_Application_ref->private_rcvStamp; 
        *seqNum = mount_Application_ref->private_seqNum; 
        *origin = mount_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Application_ref->private_sndStamp = *sndStamp; 
        mount_Application_ref->private_rcvStamp = *rcvStamp; 
        mount_Application_ref->private_seqNum = *seqNum; 
        mount_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"8cfa4041bd7b9b62bf7083ba65609b54") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Alt",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Alt_cache *mount_Alt_ref;
     mount_Alt_ref  = (mount_Alt_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Alt_ref->private_sndStamp; 
        *rcvStamp = mount_Alt_ref->private_rcvStamp; 
        *seqNum = mount_Alt_ref->private_seqNum; 
        *origin = mount_Alt_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Alt_ref->private_sndStamp = *sndStamp; 
        mount_Alt_ref->private_rcvStamp = *rcvStamp; 
        mount_Alt_ref->private_seqNum = *seqNum; 
        mount_Alt_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"bd7defe2cecbac62310d51c76bf37392") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Az",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Az_cache *mount_Az_ref;
     mount_Az_ref  = (mount_Az_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Az_ref->private_sndStamp; 
        *rcvStamp = mount_Az_ref->private_rcvStamp; 
        *seqNum = mount_Az_ref->private_seqNum; 
        *origin = mount_Az_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Az_ref->private_sndStamp = *sndStamp; 
        mount_Az_ref->private_rcvStamp = *rcvStamp; 
        mount_Az_ref->private_seqNum = *seqNum; 
        mount_Az_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"32fb21f3db6ca2d18dca71f0f1b2d42b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_Rotator",svcSAL_handle[handle].streamname) == 0 ) {
     mount_Rotator_cache *mount_Rotator_ref;
     mount_Rotator_ref  = (mount_Rotator_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_Rotator_ref->private_sndStamp; 
        *rcvStamp = mount_Rotator_ref->private_rcvStamp; 
        *seqNum = mount_Rotator_ref->private_seqNum; 
        *origin = mount_Rotator_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_Rotator_ref->private_sndStamp = *sndStamp; 
        mount_Rotator_ref->private_rcvStamp = *rcvStamp; 
        mount_Rotator_ref->private_seqNum = *seqNum; 
        mount_Rotator_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"6f8f570ccbde7fc2dca297a7c2749ce3") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("power_TC",svcSAL_handle[handle].streamname) == 0 ) {
     power_TC_cache *power_TC_ref;
     power_TC_ref  = (power_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = power_TC_ref->private_sndStamp; 
        *rcvStamp = power_TC_ref->private_rcvStamp; 
        *seqNum = power_TC_ref->private_seqNum; 
        *origin = power_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        power_TC_ref->private_sndStamp = *sndStamp; 
        power_TC_ref->private_rcvStamp = *rcvStamp; 
        power_TC_ref->private_seqNum = *seqNum; 
        power_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"b19bc3a3dade942878401b0e5828d810") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("power_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     power_Electrical_cache *power_Electrical_ref;
     power_Electrical_ref  = (power_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = power_Electrical_ref->private_sndStamp; 
        *rcvStamp = power_Electrical_ref->private_rcvStamp; 
        *seqNum = power_Electrical_ref->private_seqNum; 
        *origin = power_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        power_Electrical_ref->private_sndStamp = *sndStamp; 
        power_Electrical_ref->private_rcvStamp = *rcvStamp; 
        power_Electrical_ref->private_seqNum = *seqNum; 
        power_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"641248500a4ed35c7db3f0d1f644cb60") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("power_UPSs",svcSAL_handle[handle].streamname) == 0 ) {
     power_UPSs_cache *power_UPSs_ref;
     power_UPSs_ref  = (power_UPSs_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = power_UPSs_ref->private_sndStamp; 
        *rcvStamp = power_UPSs_ref->private_rcvStamp; 
        *seqNum = power_UPSs_ref->private_seqNum; 
        *origin = power_UPSs_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        power_UPSs_ref->private_sndStamp = *sndStamp; 
        power_UPSs_ref->private_rcvStamp = *rcvStamp; 
        power_UPSs_ref->private_seqNum = *seqNum; 
        power_UPSs_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"bde82180106fb66a51f5bcbbe58b327d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_TC",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_TC_cache *calibration_TC_ref;
     calibration_TC_ref  = (calibration_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_TC_ref->private_sndStamp; 
        *rcvStamp = calibration_TC_ref->private_rcvStamp; 
        *seqNum = calibration_TC_ref->private_seqNum; 
        *origin = calibration_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_TC_ref->private_sndStamp = *sndStamp; 
        calibration_TC_ref->private_rcvStamp = *rcvStamp; 
        calibration_TC_ref->private_seqNum = *seqNum; 
        calibration_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"20aa26fee3f582f6648c1e4b3e8fab58") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_Electrical_cache *calibration_Electrical_ref;
     calibration_Electrical_ref  = (calibration_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_Electrical_ref->private_sndStamp; 
        *rcvStamp = calibration_Electrical_ref->private_rcvStamp; 
        *seqNum = calibration_Electrical_ref->private_seqNum; 
        *origin = calibration_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_Electrical_ref->private_sndStamp = *sndStamp; 
        calibration_Electrical_ref->private_rcvStamp = *rcvStamp; 
        calibration_Electrical_ref->private_seqNum = *seqNum; 
        calibration_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"1b542aa9cba32e5db8dc6f4d09fc9ac8") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_Metrology_cache *calibration_Metrology_ref;
     calibration_Metrology_ref  = (calibration_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_Metrology_ref->private_sndStamp; 
        *rcvStamp = calibration_Metrology_ref->private_rcvStamp; 
        *seqNum = calibration_Metrology_ref->private_seqNum; 
        *origin = calibration_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_Metrology_ref->private_sndStamp = *sndStamp; 
        calibration_Metrology_ref->private_rcvStamp = *rcvStamp; 
        calibration_Metrology_ref->private_seqNum = *seqNum; 
        calibration_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"10f09b41eeb3880454db65e08ff1bea6") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_Application",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_Application_cache *calibration_Application_ref;
     calibration_Application_ref  = (calibration_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_Application_ref->private_sndStamp; 
        *rcvStamp = calibration_Application_ref->private_rcvStamp; 
        *seqNum = calibration_Application_ref->private_seqNum; 
        *origin = calibration_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_Application_ref->private_sndStamp = *sndStamp; 
        calibration_Application_ref->private_rcvStamp = *rcvStamp; 
        calibration_Application_ref->private_seqNum = *seqNum; 
        calibration_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"275d331f146e97150efc81b7b0856f1b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_TC",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_TC_cache *enclosure_TC_ref;
     enclosure_TC_ref  = (enclosure_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_TC_ref->private_sndStamp; 
        *rcvStamp = enclosure_TC_ref->private_rcvStamp; 
        *seqNum = enclosure_TC_ref->private_seqNum; 
        *origin = enclosure_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_TC_ref->private_sndStamp = *sndStamp; 
        enclosure_TC_ref->private_rcvStamp = *rcvStamp; 
        enclosure_TC_ref->private_seqNum = *seqNum; 
        enclosure_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"767f577bf6063da5af55a267d1b28f2d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Electrical_cache *enclosure_Electrical_ref;
     enclosure_Electrical_ref  = (enclosure_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Electrical_ref->private_sndStamp; 
        *rcvStamp = enclosure_Electrical_ref->private_rcvStamp; 
        *seqNum = enclosure_Electrical_ref->private_seqNum; 
        *origin = enclosure_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Electrical_ref->private_sndStamp = *sndStamp; 
        enclosure_Electrical_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Electrical_ref->private_seqNum = *seqNum; 
        enclosure_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"c9589d38774c0330755867c6fd60cadf") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Metrology_cache *enclosure_Metrology_ref;
     enclosure_Metrology_ref  = (enclosure_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Metrology_ref->private_sndStamp; 
        *rcvStamp = enclosure_Metrology_ref->private_rcvStamp; 
        *seqNum = enclosure_Metrology_ref->private_seqNum; 
        *origin = enclosure_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Metrology_ref->private_sndStamp = *sndStamp; 
        enclosure_Metrology_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Metrology_ref->private_seqNum = *seqNum; 
        enclosure_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"95b25a6e45461e80a7c7ff4b73dd0f9f") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Application",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Application_cache *enclosure_Application_ref;
     enclosure_Application_ref  = (enclosure_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Application_ref->private_sndStamp; 
        *rcvStamp = enclosure_Application_ref->private_rcvStamp; 
        *seqNum = enclosure_Application_ref->private_seqNum; 
        *origin = enclosure_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Application_ref->private_sndStamp = *sndStamp; 
        enclosure_Application_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Application_ref->private_seqNum = *seqNum; 
        enclosure_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"1def69a7da12dbb0697034a97ae8a3c6") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Azimuth",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Azimuth_cache *enclosure_Azimuth_ref;
     enclosure_Azimuth_ref  = (enclosure_Azimuth_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Azimuth_ref->private_sndStamp; 
        *rcvStamp = enclosure_Azimuth_ref->private_rcvStamp; 
        *seqNum = enclosure_Azimuth_ref->private_seqNum; 
        *origin = enclosure_Azimuth_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Azimuth_ref->private_sndStamp = *sndStamp; 
        enclosure_Azimuth_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Azimuth_ref->private_seqNum = *seqNum; 
        enclosure_Azimuth_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"8cc257b93b49037cbe4ae88d61b6c0e5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Shutter",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Shutter_cache *enclosure_Shutter_ref;
     enclosure_Shutter_ref  = (enclosure_Shutter_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Shutter_ref->private_sndStamp; 
        *rcvStamp = enclosure_Shutter_ref->private_rcvStamp; 
        *seqNum = enclosure_Shutter_ref->private_seqNum; 
        *origin = enclosure_Shutter_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Shutter_ref->private_sndStamp = *sndStamp; 
        enclosure_Shutter_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Shutter_ref->private_seqNum = *seqNum; 
        enclosure_Shutter_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0815a69512eeb636e9b519d91bf1a4af") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Vents",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Vents_cache *enclosure_Vents_ref;
     enclosure_Vents_ref  = (enclosure_Vents_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Vents_ref->private_sndStamp; 
        *rcvStamp = enclosure_Vents_ref->private_rcvStamp; 
        *seqNum = enclosure_Vents_ref->private_seqNum; 
        *origin = enclosure_Vents_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Vents_ref->private_sndStamp = *sndStamp; 
        enclosure_Vents_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Vents_ref->private_seqNum = *seqNum; 
        enclosure_Vents_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"d09de6ab8c8279b6307db1db20b4f190") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_Thermal_control",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_Thermal_control_cache *enclosure_Thermal_control_ref;
     enclosure_Thermal_control_ref  = (enclosure_Thermal_control_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_Thermal_control_ref->private_sndStamp; 
        *rcvStamp = enclosure_Thermal_control_ref->private_rcvStamp; 
        *seqNum = enclosure_Thermal_control_ref->private_seqNum; 
        *origin = enclosure_Thermal_control_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_Thermal_control_ref->private_sndStamp = *sndStamp; 
        enclosure_Thermal_control_ref->private_rcvStamp = *rcvStamp; 
        enclosure_Thermal_control_ref->private_seqNum = *seqNum; 
        enclosure_Thermal_control_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5e39cbe049058949c61d93700a067278") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("scheduler_Application",svcSAL_handle[handle].streamname) == 0 ) {
     scheduler_Application_cache *scheduler_Application_ref;
     scheduler_Application_ref  = (scheduler_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = scheduler_Application_ref->private_sndStamp; 
        *rcvStamp = scheduler_Application_ref->private_rcvStamp; 
        *seqNum = scheduler_Application_ref->private_seqNum; 
        *origin = scheduler_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        scheduler_Application_ref->private_sndStamp = *sndStamp; 
        scheduler_Application_ref->private_rcvStamp = *rcvStamp; 
        scheduler_Application_ref->private_seqNum = *seqNum; 
        scheduler_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"2f541102b17f0d1dec48793fbafac5dd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("operations_Application",svcSAL_handle[handle].streamname) == 0 ) {
     operations_Application_cache *operations_Application_ref;
     operations_Application_ref  = (operations_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = operations_Application_ref->private_sndStamp; 
        *rcvStamp = operations_Application_ref->private_rcvStamp; 
        *seqNum = operations_Application_ref->private_seqNum; 
        *origin = operations_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        operations_Application_ref->private_sndStamp = *sndStamp; 
        operations_Application_ref->private_rcvStamp = *rcvStamp; 
        operations_Application_ref->private_seqNum = *seqNum; 
        operations_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"80f3b7aeaeda4045e7b9b6275b99e158") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_TC",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_TC_cache *auxscope_TC_ref;
     auxscope_TC_ref  = (auxscope_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_TC_ref->private_sndStamp; 
        *rcvStamp = auxscope_TC_ref->private_rcvStamp; 
        *seqNum = auxscope_TC_ref->private_seqNum; 
        *origin = auxscope_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_TC_ref->private_sndStamp = *sndStamp; 
        auxscope_TC_ref->private_rcvStamp = *rcvStamp; 
        auxscope_TC_ref->private_seqNum = *seqNum; 
        auxscope_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"56cb3bcb0b89f8f1d2d3fba08be15732") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_Electrical_cache *auxscope_Electrical_ref;
     auxscope_Electrical_ref  = (auxscope_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_Electrical_ref->private_sndStamp; 
        *rcvStamp = auxscope_Electrical_ref->private_rcvStamp; 
        *seqNum = auxscope_Electrical_ref->private_seqNum; 
        *origin = auxscope_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_Electrical_ref->private_sndStamp = *sndStamp; 
        auxscope_Electrical_ref->private_rcvStamp = *rcvStamp; 
        auxscope_Electrical_ref->private_seqNum = *seqNum; 
        auxscope_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"be8bd90050d79fcb034a2a745696708c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_Metrology_cache *auxscope_Metrology_ref;
     auxscope_Metrology_ref  = (auxscope_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_Metrology_ref->private_sndStamp; 
        *rcvStamp = auxscope_Metrology_ref->private_rcvStamp; 
        *seqNum = auxscope_Metrology_ref->private_seqNum; 
        *origin = auxscope_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_Metrology_ref->private_sndStamp = *sndStamp; 
        auxscope_Metrology_ref->private_rcvStamp = *rcvStamp; 
        auxscope_Metrology_ref->private_seqNum = *seqNum; 
        auxscope_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"4a5c7ff11b543c6061b1f62fdb5380e0") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_Application",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_Application_cache *auxscope_Application_ref;
     auxscope_Application_ref  = (auxscope_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_Application_ref->private_sndStamp; 
        *rcvStamp = auxscope_Application_ref->private_rcvStamp; 
        *seqNum = auxscope_Application_ref->private_seqNum; 
        *origin = auxscope_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_Application_ref->private_sndStamp = *sndStamp; 
        auxscope_Application_ref->private_rcvStamp = *rcvStamp; 
        auxscope_Application_ref->private_seqNum = *seqNum; 
        auxscope_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0ded5f7eba3e76f7abca1043244762aa") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_TCS",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_TCS_cache *auxscope_TCS_ref;
     auxscope_TCS_ref  = (auxscope_TCS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_TCS_ref->private_sndStamp; 
        *rcvStamp = auxscope_TCS_ref->private_rcvStamp; 
        *seqNum = auxscope_TCS_ref->private_seqNum; 
        *origin = auxscope_TCS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_TCS_ref->private_sndStamp = *sndStamp; 
        auxscope_TCS_ref->private_rcvStamp = *rcvStamp; 
        auxscope_TCS_ref->private_seqNum = *seqNum; 
        auxscope_TCS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"4ec26027ae55ba66c231f6335b23b889") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_Spectrometer",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_Spectrometer_cache *auxscope_Spectrometer_ref;
     auxscope_Spectrometer_ref  = (auxscope_Spectrometer_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_Spectrometer_ref->private_sndStamp; 
        *rcvStamp = auxscope_Spectrometer_ref->private_rcvStamp; 
        *seqNum = auxscope_Spectrometer_ref->private_seqNum; 
        *origin = auxscope_Spectrometer_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_Spectrometer_ref->private_sndStamp = *sndStamp; 
        auxscope_Spectrometer_ref->private_rcvStamp = *rcvStamp; 
        auxscope_Spectrometer_ref->private_seqNum = *seqNum; 
        auxscope_Spectrometer_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"c8de5e0a35cd7add4029334ed6bb87ea") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_Camera",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_Camera_cache *auxscope_Camera_ref;
     auxscope_Camera_ref  = (auxscope_Camera_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_Camera_ref->private_sndStamp; 
        *rcvStamp = auxscope_Camera_ref->private_rcvStamp; 
        *seqNum = auxscope_Camera_ref->private_seqNum; 
        *origin = auxscope_Camera_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_Camera_ref->private_sndStamp = *sndStamp; 
        auxscope_Camera_ref->private_rcvStamp = *rcvStamp; 
        auxscope_Camera_ref->private_seqNum = *seqNum; 
        auxscope_Camera_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"2df655104a2f11d99930de6b4f25d355") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("lasercal_TC",svcSAL_handle[handle].streamname) == 0 ) {
     lasercal_TC_cache *lasercal_TC_ref;
     lasercal_TC_ref  = (lasercal_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = lasercal_TC_ref->private_sndStamp; 
        *rcvStamp = lasercal_TC_ref->private_rcvStamp; 
        *seqNum = lasercal_TC_ref->private_seqNum; 
        *origin = lasercal_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        lasercal_TC_ref->private_sndStamp = *sndStamp; 
        lasercal_TC_ref->private_rcvStamp = *rcvStamp; 
        lasercal_TC_ref->private_seqNum = *seqNum; 
        lasercal_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"6c50a20cb58d439ffc7ac5fd24cc0bec") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("lasercal_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     lasercal_Electrical_cache *lasercal_Electrical_ref;
     lasercal_Electrical_ref  = (lasercal_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = lasercal_Electrical_ref->private_sndStamp; 
        *rcvStamp = lasercal_Electrical_ref->private_rcvStamp; 
        *seqNum = lasercal_Electrical_ref->private_seqNum; 
        *origin = lasercal_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        lasercal_Electrical_ref->private_sndStamp = *sndStamp; 
        lasercal_Electrical_ref->private_rcvStamp = *rcvStamp; 
        lasercal_Electrical_ref->private_seqNum = *seqNum; 
        lasercal_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e2bbf82b9077c3923942e8d1477792cc") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("lasercal_Application",svcSAL_handle[handle].streamname) == 0 ) {
     lasercal_Application_cache *lasercal_Application_ref;
     lasercal_Application_ref  = (lasercal_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = lasercal_Application_ref->private_sndStamp; 
        *rcvStamp = lasercal_Application_ref->private_rcvStamp; 
        *seqNum = lasercal_Application_ref->private_seqNum; 
        *origin = lasercal_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        lasercal_Application_ref->private_sndStamp = *sndStamp; 
        lasercal_Application_ref->private_rcvStamp = *rcvStamp; 
        lasercal_Application_ref->private_seqNum = *seqNum; 
        lasercal_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"91976bfce4cbcd2575c4aa310ca6276d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_TC",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_TC_cache *seeing_dimm_TC_ref;
     seeing_dimm_TC_ref  = (seeing_dimm_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_TC_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_TC_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_TC_ref->private_seqNum; 
        *origin = seeing_dimm_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_TC_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_TC_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_TC_ref->private_seqNum = *seqNum; 
        seeing_dimm_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"38eae5c52a5fed2eeeab50f444a104eb") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_Electrical_cache *seeing_dimm_Electrical_ref;
     seeing_dimm_Electrical_ref  = (seeing_dimm_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_Electrical_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_Electrical_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_Electrical_ref->private_seqNum; 
        *origin = seeing_dimm_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_Electrical_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_Electrical_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_Electrical_ref->private_seqNum = *seqNum; 
        seeing_dimm_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"504243b9aa680f806babef8dffdd1b23") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_Metrology_cache *seeing_dimm_Metrology_ref;
     seeing_dimm_Metrology_ref  = (seeing_dimm_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_Metrology_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_Metrology_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_Metrology_ref->private_seqNum; 
        *origin = seeing_dimm_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_Metrology_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_Metrology_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_Metrology_ref->private_seqNum = *seqNum; 
        seeing_dimm_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"3e89bcf13d43fbe2fff95af566008608") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_Application",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_Application_cache *seeing_dimm_Application_ref;
     seeing_dimm_Application_ref  = (seeing_dimm_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_Application_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_Application_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_Application_ref->private_seqNum; 
        *origin = seeing_dimm_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_Application_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_Application_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_Application_ref->private_seqNum = *seqNum; 
        seeing_dimm_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"50d5656c20f795efbfd46387796d4b97") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_TC",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_TC_cache *seeing_mass_TC_ref;
     seeing_mass_TC_ref  = (seeing_mass_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_TC_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_TC_ref->private_rcvStamp; 
        *seqNum = seeing_mass_TC_ref->private_seqNum; 
        *origin = seeing_mass_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_TC_ref->private_sndStamp = *sndStamp; 
        seeing_mass_TC_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_TC_ref->private_seqNum = *seqNum; 
        seeing_mass_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"bf7055ff8493c560e725e40c94cc3dd2") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_Electrical_cache *seeing_mass_Electrical_ref;
     seeing_mass_Electrical_ref  = (seeing_mass_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_Electrical_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_Electrical_ref->private_rcvStamp; 
        *seqNum = seeing_mass_Electrical_ref->private_seqNum; 
        *origin = seeing_mass_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_Electrical_ref->private_sndStamp = *sndStamp; 
        seeing_mass_Electrical_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_Electrical_ref->private_seqNum = *seqNum; 
        seeing_mass_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"396ca80c5249f8901735ddaff43a2d63") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_Metrology_cache *seeing_mass_Metrology_ref;
     seeing_mass_Metrology_ref  = (seeing_mass_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_Metrology_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_Metrology_ref->private_rcvStamp; 
        *seqNum = seeing_mass_Metrology_ref->private_seqNum; 
        *origin = seeing_mass_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_Metrology_ref->private_sndStamp = *sndStamp; 
        seeing_mass_Metrology_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_Metrology_ref->private_seqNum = *seqNum; 
        seeing_mass_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"3aeff37b5c0b407ffb92d7ef67f7739d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_Application",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_Application_cache *seeing_mass_Application_ref;
     seeing_mass_Application_ref  = (seeing_mass_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_Application_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_Application_ref->private_rcvStamp; 
        *seqNum = seeing_mass_Application_ref->private_seqNum; 
        *origin = seeing_mass_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_Application_ref->private_sndStamp = *sndStamp; 
        seeing_mass_Application_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_Application_ref->private_seqNum = *seqNum; 
        seeing_mass_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"609f8240798338f617f6fbd4658b1f11") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_TC",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_TC_cache *skycam_TC_ref;
     skycam_TC_ref  = (skycam_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_TC_ref->private_sndStamp; 
        *rcvStamp = skycam_TC_ref->private_rcvStamp; 
        *seqNum = skycam_TC_ref->private_seqNum; 
        *origin = skycam_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_TC_ref->private_sndStamp = *sndStamp; 
        skycam_TC_ref->private_rcvStamp = *rcvStamp; 
        skycam_TC_ref->private_seqNum = *seqNum; 
        skycam_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"f55e0c7dc01cf7ac3460ec9cbf6e3a7b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_Electrical_cache *skycam_Electrical_ref;
     skycam_Electrical_ref  = (skycam_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_Electrical_ref->private_sndStamp; 
        *rcvStamp = skycam_Electrical_ref->private_rcvStamp; 
        *seqNum = skycam_Electrical_ref->private_seqNum; 
        *origin = skycam_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_Electrical_ref->private_sndStamp = *sndStamp; 
        skycam_Electrical_ref->private_rcvStamp = *rcvStamp; 
        skycam_Electrical_ref->private_seqNum = *seqNum; 
        skycam_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a2768886e08cc4bbcf86b332f9cece54") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_Metrology",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_Metrology_cache *skycam_Metrology_ref;
     skycam_Metrology_ref  = (skycam_Metrology_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_Metrology_ref->private_sndStamp; 
        *rcvStamp = skycam_Metrology_ref->private_rcvStamp; 
        *seqNum = skycam_Metrology_ref->private_seqNum; 
        *origin = skycam_Metrology_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_Metrology_ref->private_sndStamp = *sndStamp; 
        skycam_Metrology_ref->private_rcvStamp = *rcvStamp; 
        skycam_Metrology_ref->private_seqNum = *seqNum; 
        skycam_Metrology_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0c39297a95bee2f228e12659b7c16249") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_Application",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_Application_cache *skycam_Application_ref;
     skycam_Application_ref  = (skycam_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_Application_ref->private_sndStamp; 
        *rcvStamp = skycam_Application_ref->private_rcvStamp; 
        *seqNum = skycam_Application_ref->private_seqNum; 
        *origin = skycam_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_Application_ref->private_sndStamp = *sndStamp; 
        skycam_Application_ref->private_rcvStamp = *rcvStamp; 
        skycam_Application_ref->private_seqNum = *seqNum; 
        skycam_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"27fdd74b8fcb4980ee80ba6ea787ca40") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_TC",svcSAL_handle[handle].streamname) == 0 ) {
     environment_TC_cache *environment_TC_ref;
     environment_TC_ref  = (environment_TC_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_TC_ref->private_sndStamp; 
        *rcvStamp = environment_TC_ref->private_rcvStamp; 
        *seqNum = environment_TC_ref->private_seqNum; 
        *origin = environment_TC_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_TC_ref->private_sndStamp = *sndStamp; 
        environment_TC_ref->private_rcvStamp = *rcvStamp; 
        environment_TC_ref->private_seqNum = *seqNum; 
        environment_TC_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"8653b0c19fe5201a598b409ea2ef8068") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Electrical",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Electrical_cache *environment_Electrical_ref;
     environment_Electrical_ref  = (environment_Electrical_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Electrical_ref->private_sndStamp; 
        *rcvStamp = environment_Electrical_ref->private_rcvStamp; 
        *seqNum = environment_Electrical_ref->private_seqNum; 
        *origin = environment_Electrical_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Electrical_ref->private_sndStamp = *sndStamp; 
        environment_Electrical_ref->private_rcvStamp = *rcvStamp; 
        environment_Electrical_ref->private_seqNum = *seqNum; 
        environment_Electrical_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"7bd52c6e8e81af08016e2cedccf557d8") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Weather",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Weather_cache *environment_Weather_ref;
     environment_Weather_ref  = (environment_Weather_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Weather_ref->private_sndStamp; 
        *rcvStamp = environment_Weather_ref->private_rcvStamp; 
        *seqNum = environment_Weather_ref->private_seqNum; 
        *origin = environment_Weather_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Weather_ref->private_sndStamp = *sndStamp; 
        environment_Weather_ref->private_rcvStamp = *rcvStamp; 
        environment_Weather_ref->private_seqNum = *seqNum; 
        environment_Weather_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"db896db674955f0dc558ac9f9a451ffd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Dust_monitor",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Dust_monitor_cache *environment_Dust_monitor_ref;
     environment_Dust_monitor_ref  = (environment_Dust_monitor_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Dust_monitor_ref->private_sndStamp; 
        *rcvStamp = environment_Dust_monitor_ref->private_rcvStamp; 
        *seqNum = environment_Dust_monitor_ref->private_seqNum; 
        *origin = environment_Dust_monitor_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Dust_monitor_ref->private_sndStamp = *sndStamp; 
        environment_Dust_monitor_ref->private_rcvStamp = *rcvStamp; 
        environment_Dust_monitor_ref->private_seqNum = *seqNum; 
        environment_Dust_monitor_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"31146090080b7f2f66a960ce6d6ea56a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Lightning_detector",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Lightning_detector_cache *environment_Lightning_detector_ref;
     environment_Lightning_detector_ref  = (environment_Lightning_detector_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Lightning_detector_ref->private_sndStamp; 
        *rcvStamp = environment_Lightning_detector_ref->private_rcvStamp; 
        *seqNum = environment_Lightning_detector_ref->private_seqNum; 
        *origin = environment_Lightning_detector_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Lightning_detector_ref->private_sndStamp = *sndStamp; 
        environment_Lightning_detector_ref->private_rcvStamp = *rcvStamp; 
        environment_Lightning_detector_ref->private_seqNum = *seqNum; 
        environment_Lightning_detector_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"223e8f9c8232601b3863ea7328c05667") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Seismometer",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Seismometer_cache *environment_Seismometer_ref;
     environment_Seismometer_ref  = (environment_Seismometer_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Seismometer_ref->private_sndStamp; 
        *rcvStamp = environment_Seismometer_ref->private_rcvStamp; 
        *seqNum = environment_Seismometer_ref->private_seqNum; 
        *origin = environment_Seismometer_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Seismometer_ref->private_sndStamp = *sndStamp; 
        environment_Seismometer_ref->private_rcvStamp = *rcvStamp; 
        environment_Seismometer_ref->private_seqNum = *seqNum; 
        environment_Seismometer_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a9f6baa05d912a49b7828c241cb27b80") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_Video_cameras",svcSAL_handle[handle].streamname) == 0 ) {
     environment_Video_cameras_cache *environment_Video_cameras_ref;
     environment_Video_cameras_ref  = (environment_Video_cameras_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_Video_cameras_ref->private_sndStamp; 
        *rcvStamp = environment_Video_cameras_ref->private_rcvStamp; 
        *seqNum = environment_Video_cameras_ref->private_seqNum; 
        *origin = environment_Video_cameras_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_Video_cameras_ref->private_sndStamp = *sndStamp; 
        environment_Video_cameras_ref->private_rcvStamp = *rcvStamp; 
        environment_Video_cameras_ref->private_seqNum = *seqNum; 
        environment_Video_cameras_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"082a052ed5c65233dc5b2ca818637f89") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("network_Application",svcSAL_handle[handle].streamname) == 0 ) {
     network_Application_cache *network_Application_ref;
     network_Application_ref  = (network_Application_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = network_Application_ref->private_sndStamp; 
        *rcvStamp = network_Application_ref->private_rcvStamp; 
        *seqNum = network_Application_ref->private_seqNum; 
        *origin = network_Application_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        network_Application_ref->private_sndStamp = *sndStamp; 
        network_Application_ref->private_rcvStamp = *rcvStamp; 
        network_Application_ref->private_seqNum = *seqNum; 
        network_Application_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a71c6735991fe130385f3437f48d4327") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_TrackRefSys",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_TrackRefSys_cache *tcs_kernel_TrackRefSys_ref;
     tcs_kernel_TrackRefSys_ref  = (tcs_kernel_TrackRefSys_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_TrackRefSys_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_TrackRefSys_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_TrackRefSys_ref->private_seqNum; 
        *origin = tcs_kernel_TrackRefSys_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_TrackRefSys_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_TrackRefSys_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_TrackRefSys_ref->private_seqNum = *seqNum; 
        tcs_kernel_TrackRefSys_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"60f831260f63f92219d7dffd3e97c67e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_Target",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_Target_cache *tcs_kernel_Target_ref;
     tcs_kernel_Target_ref  = (tcs_kernel_Target_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_Target_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_Target_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_Target_ref->private_seqNum; 
        *origin = tcs_kernel_Target_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_Target_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_Target_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_Target_ref->private_seqNum = *seqNum; 
        tcs_kernel_Target_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"40cc262a6af4fd7a68134af6163e146a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_DawdleFilter",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_DawdleFilter_cache *tcs_kernel_DawdleFilter_ref;
     tcs_kernel_DawdleFilter_ref  = (tcs_kernel_DawdleFilter_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_DawdleFilter_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_DawdleFilter_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_DawdleFilter_ref->private_seqNum; 
        *origin = tcs_kernel_DawdleFilter_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_DawdleFilter_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_DawdleFilter_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_DawdleFilter_ref->private_seqNum = *seqNum; 
        tcs_kernel_DawdleFilter_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"babd549d662b7370edb02fffaa248dc5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_FK5Target",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_FK5Target_cache *tcs_kernel_FK5Target_ref;
     tcs_kernel_FK5Target_ref  = (tcs_kernel_FK5Target_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_FK5Target_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_FK5Target_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_FK5Target_ref->private_seqNum; 
        *origin = tcs_kernel_FK5Target_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_FK5Target_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_FK5Target_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_FK5Target_ref->private_seqNum = *seqNum; 
        tcs_kernel_FK5Target_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5362be43cea4f49265e970916eb561a8") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_OpticsVt",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_OpticsVt_cache *tcs_kernel_OpticsVt_ref;
     tcs_kernel_OpticsVt_ref  = (tcs_kernel_OpticsVt_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_OpticsVt_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_OpticsVt_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_OpticsVt_ref->private_seqNum; 
        *origin = tcs_kernel_OpticsVt_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_OpticsVt_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_OpticsVt_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_OpticsVt_ref->private_seqNum = *seqNum; 
        tcs_kernel_OpticsVt_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"98afbe13c88b951c5b7e7b9effeca8ee") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_PointingControl",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_PointingControl_cache *tcs_kernel_PointingControl_ref;
     tcs_kernel_PointingControl_ref  = (tcs_kernel_PointingControl_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_PointingControl_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_PointingControl_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_PointingControl_ref->private_seqNum; 
        *origin = tcs_kernel_PointingControl_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_PointingControl_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_PointingControl_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_PointingControl_ref->private_seqNum = *seqNum; 
        tcs_kernel_PointingControl_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"54acf012f5ad6014f94168e2e0ab5466") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_PointingLog",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_PointingLog_cache *tcs_kernel_PointingLog_ref;
     tcs_kernel_PointingLog_ref  = (tcs_kernel_PointingLog_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_PointingLog_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_PointingLog_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_PointingLog_ref->private_seqNum; 
        *origin = tcs_kernel_PointingLog_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_PointingLog_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_PointingLog_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_PointingLog_ref->private_seqNum = *seqNum; 
        tcs_kernel_PointingLog_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e1ea5a849f942164fdfa2331cf0a3f46") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_PointingModel",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_PointingModel_cache *tcs_kernel_PointingModel_ref;
     tcs_kernel_PointingModel_ref  = (tcs_kernel_PointingModel_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_PointingModel_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_PointingModel_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_PointingModel_ref->private_seqNum; 
        *origin = tcs_kernel_PointingModel_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_PointingModel_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_PointingModel_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_PointingModel_ref->private_seqNum = *seqNum; 
        tcs_kernel_PointingModel_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"8b9e0f4c7837f920abf6f11075ab208d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_Site",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_Site_cache *tcs_kernel_Site_ref;
     tcs_kernel_Site_ref  = (tcs_kernel_Site_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_Site_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_Site_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_Site_ref->private_seqNum; 
        *origin = tcs_kernel_Site_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_Site_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_Site_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_Site_ref->private_seqNum = *seqNum; 
        tcs_kernel_Site_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"105fadba3994a0c35ba6f34353de2706") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_TimeKeeper",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_TimeKeeper_cache *tcs_kernel_TimeKeeper_ref;
     tcs_kernel_TimeKeeper_ref  = (tcs_kernel_TimeKeeper_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_TimeKeeper_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_TimeKeeper_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_TimeKeeper_ref->private_seqNum; 
        *origin = tcs_kernel_TimeKeeper_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_TimeKeeper_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_TimeKeeper_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_TimeKeeper_ref->private_seqNum = *seqNum; 
        tcs_kernel_TimeKeeper_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"210ad6c4eb43738a20f78f946a2e777c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_kernel_TrackingTarget",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_kernel_TrackingTarget_cache *tcs_kernel_TrackingTarget_ref;
     tcs_kernel_TrackingTarget_ref  = (tcs_kernel_TrackingTarget_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_kernel_TrackingTarget_ref->private_sndStamp; 
        *rcvStamp = tcs_kernel_TrackingTarget_ref->private_rcvStamp; 
        *seqNum = tcs_kernel_TrackingTarget_ref->private_seqNum; 
        *origin = tcs_kernel_TrackingTarget_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_kernel_TrackingTarget_ref->private_sndStamp = *sndStamp; 
        tcs_kernel_TrackingTarget_ref->private_rcvStamp = *rcvStamp; 
        tcs_kernel_TrackingTarget_ref->private_seqNum = *seqNum; 
        tcs_kernel_TrackingTarget_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"b913cc9c3ff8c0b599f96ae8233154ba") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_BEE_biases",svcSAL_handle[handle].streamname) == 0 ) {
     camera_BEE_biases_cache *camera_BEE_biases_ref;
     camera_BEE_biases_ref  = (camera_BEE_biases_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_BEE_biases_ref->private_sndStamp; 
        *rcvStamp = camera_BEE_biases_ref->private_rcvStamp; 
        *seqNum = camera_BEE_biases_ref->private_seqNum; 
        *origin = camera_BEE_biases_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_BEE_biases_ref->private_sndStamp = *sndStamp; 
        camera_BEE_biases_ref->private_rcvStamp = *rcvStamp; 
        camera_BEE_biases_ref->private_seqNum = *seqNum; 
        camera_BEE_biases_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5f1b3775bfabf2d7f4bba708625aea62") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_BEE_clocks",svcSAL_handle[handle].streamname) == 0 ) {
     camera_BEE_clocks_cache *camera_BEE_clocks_ref;
     camera_BEE_clocks_ref  = (camera_BEE_clocks_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_BEE_clocks_ref->private_sndStamp; 
        *rcvStamp = camera_BEE_clocks_ref->private_rcvStamp; 
        *seqNum = camera_BEE_clocks_ref->private_seqNum; 
        *origin = camera_BEE_clocks_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_BEE_clocks_ref->private_sndStamp = *sndStamp; 
        camera_BEE_clocks_ref->private_rcvStamp = *rcvStamp; 
        camera_BEE_clocks_ref->private_seqNum = *seqNum; 
        camera_BEE_clocks_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9c9de87676ac699938d7a0e9b69e74f5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_BEE_thermal",svcSAL_handle[handle].streamname) == 0 ) {
     camera_BEE_thermal_cache *camera_BEE_thermal_ref;
     camera_BEE_thermal_ref  = (camera_BEE_thermal_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_BEE_thermal_ref->private_sndStamp; 
        *rcvStamp = camera_BEE_thermal_ref->private_rcvStamp; 
        *seqNum = camera_BEE_thermal_ref->private_seqNum; 
        *origin = camera_BEE_thermal_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_BEE_thermal_ref->private_sndStamp = *sndStamp; 
        camera_BEE_thermal_ref->private_rcvStamp = *rcvStamp; 
        camera_BEE_thermal_ref->private_seqNum = *seqNum; 
        camera_BEE_thermal_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0a8720e90fd3db2f8825cb78b9bd4702") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_CALSYS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_CALSYS_cache *camera_CALSYS_ref;
     camera_CALSYS_ref  = (camera_CALSYS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_CALSYS_ref->private_sndStamp; 
        *rcvStamp = camera_CALSYS_ref->private_rcvStamp; 
        *seqNum = camera_CALSYS_ref->private_seqNum; 
        *origin = camera_CALSYS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_CALSYS_ref->private_sndStamp = *sndStamp; 
        camera_CALSYS_ref->private_rcvStamp = *rcvStamp; 
        camera_CALSYS_ref->private_seqNum = *seqNum; 
        camera_CALSYS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"7009d99c803ac354767b2214188fb5dd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_CCS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_CCS_cache *camera_CCS_ref;
     camera_CCS_ref  = (camera_CCS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_CCS_ref->private_sndStamp; 
        *rcvStamp = camera_CCS_ref->private_rcvStamp; 
        *seqNum = camera_CCS_ref->private_seqNum; 
        *origin = camera_CCS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_CCS_ref->private_sndStamp = *sndStamp; 
        camera_CCS_ref->private_rcvStamp = *rcvStamp; 
        camera_CCS_ref->private_seqNum = *seqNum; 
        camera_CCS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"1824785d953c60ba6e93e1a8f073f26b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_FCS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_FCS_cache *camera_FCS_ref;
     camera_FCS_ref  = (camera_FCS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_FCS_ref->private_sndStamp; 
        *rcvStamp = camera_FCS_ref->private_rcvStamp; 
        *seqNum = camera_FCS_ref->private_seqNum; 
        *origin = camera_FCS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_FCS_ref->private_sndStamp = *sndStamp; 
        camera_FCS_ref->private_rcvStamp = *rcvStamp; 
        camera_FCS_ref->private_seqNum = *seqNum; 
        camera_FCS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e1100b901fcf5b396d8fbc572edf196b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_GAS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_GAS_cache *camera_GAS_ref;
     camera_GAS_ref  = (camera_GAS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_GAS_ref->private_sndStamp; 
        *rcvStamp = camera_GAS_ref->private_rcvStamp; 
        *seqNum = camera_GAS_ref->private_seqNum; 
        *origin = camera_GAS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_GAS_ref->private_sndStamp = *sndStamp; 
        camera_GAS_ref->private_rcvStamp = *rcvStamp; 
        camera_GAS_ref->private_seqNum = *seqNum; 
        camera_GAS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"784394b87313e691a31614f01720e71e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_LASERCAL",svcSAL_handle[handle].streamname) == 0 ) {
     camera_LASERCAL_cache *camera_LASERCAL_ref;
     camera_LASERCAL_ref  = (camera_LASERCAL_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_LASERCAL_ref->private_sndStamp; 
        *rcvStamp = camera_LASERCAL_ref->private_rcvStamp; 
        *seqNum = camera_LASERCAL_ref->private_seqNum; 
        *origin = camera_LASERCAL_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_LASERCAL_ref->private_sndStamp = *sndStamp; 
        camera_LASERCAL_ref->private_rcvStamp = *rcvStamp; 
        camera_LASERCAL_ref->private_seqNum = *seqNum; 
        camera_LASERCAL_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"328a61a03331ef6a02a98cb5ecb1bf0a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_PWR",svcSAL_handle[handle].streamname) == 0 ) {
     camera_PWR_cache *camera_PWR_ref;
     camera_PWR_ref  = (camera_PWR_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_PWR_ref->private_sndStamp; 
        *rcvStamp = camera_PWR_ref->private_rcvStamp; 
        *seqNum = camera_PWR_ref->private_seqNum; 
        *origin = camera_PWR_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_PWR_ref->private_sndStamp = *sndStamp; 
        camera_PWR_ref->private_rcvStamp = *rcvStamp; 
        camera_PWR_ref->private_seqNum = *seqNum; 
        camera_PWR_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"22395aacfe7777c1b7049c2309cf9512") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_QA_measured",svcSAL_handle[handle].streamname) == 0 ) {
     camera_QA_measured_cache *camera_QA_measured_ref;
     camera_QA_measured_ref  = (camera_QA_measured_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_QA_measured_ref->private_sndStamp; 
        *rcvStamp = camera_QA_measured_ref->private_rcvStamp; 
        *seqNum = camera_QA_measured_ref->private_seqNum; 
        *origin = camera_QA_measured_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_QA_measured_ref->private_sndStamp = *sndStamp; 
        camera_QA_measured_ref->private_rcvStamp = *rcvStamp; 
        camera_QA_measured_ref->private_seqNum = *seqNum; 
        camera_QA_measured_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5fe209515d9d422d0434b36b46f6009c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_SCS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_SCS_cache *camera_SCS_ref;
     camera_SCS_ref  = (camera_SCS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_SCS_ref->private_sndStamp; 
        *rcvStamp = camera_SCS_ref->private_rcvStamp; 
        *seqNum = camera_SCS_ref->private_seqNum; 
        *origin = camera_SCS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_SCS_ref->private_sndStamp = *sndStamp; 
        camera_SCS_ref->private_rcvStamp = *rcvStamp; 
        camera_SCS_ref->private_seqNum = *seqNum; 
        camera_SCS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"68f4d941b8d494c9803d595a30cbaa25") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_SDS_amplifiers",svcSAL_handle[handle].streamname) == 0 ) {
     camera_SDS_amplifiers_cache *camera_SDS_amplifiers_ref;
     camera_SDS_amplifiers_ref  = (camera_SDS_amplifiers_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_SDS_amplifiers_ref->private_sndStamp; 
        *rcvStamp = camera_SDS_amplifiers_ref->private_rcvStamp; 
        *seqNum = camera_SDS_amplifiers_ref->private_seqNum; 
        *origin = camera_SDS_amplifiers_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_SDS_amplifiers_ref->private_sndStamp = *sndStamp; 
        camera_SDS_amplifiers_ref->private_rcvStamp = *rcvStamp; 
        camera_SDS_amplifiers_ref->private_seqNum = *seqNum; 
        camera_SDS_amplifiers_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5f08fd3c760a2c3a24edc00bf34cd5ee") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_SDS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_SDS_cache *camera_SDS_ref;
     camera_SDS_ref  = (camera_SDS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_SDS_ref->private_sndStamp; 
        *rcvStamp = camera_SDS_ref->private_rcvStamp; 
        *seqNum = camera_SDS_ref->private_seqNum; 
        *origin = camera_SDS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_SDS_ref->private_sndStamp = *sndStamp; 
        camera_SDS_ref->private_rcvStamp = *rcvStamp; 
        camera_SDS_ref->private_seqNum = *seqNum; 
        camera_SDS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"1c28ceb149bd6ee59644b4822c9e8a7d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_control",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_control_cache *camera_TC_control_ref;
     camera_TC_control_ref  = (camera_TC_control_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_control_ref->private_sndStamp; 
        *rcvStamp = camera_TC_control_ref->private_rcvStamp; 
        *seqNum = camera_TC_control_ref->private_seqNum; 
        *origin = camera_TC_control_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_control_ref->private_sndStamp = *sndStamp; 
        camera_TC_control_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_control_ref->private_seqNum = *seqNum; 
        camera_TC_control_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"59d29d70cb4ab973691c8f8a0fc18212") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TCM",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TCM_cache *camera_TCM_ref;
     camera_TCM_ref  = (camera_TCM_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TCM_ref->private_sndStamp; 
        *rcvStamp = camera_TCM_ref->private_rcvStamp; 
        *seqNum = camera_TCM_ref->private_seqNum; 
        *origin = camera_TCM_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TCM_ref->private_sndStamp = *sndStamp; 
        camera_TCM_ref->private_rcvStamp = *rcvStamp; 
        camera_TCM_ref->private_seqNum = *seqNum; 
        camera_TCM_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0a70d06bdd24f1e83434664c47efd063") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone1",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone1_cache *camera_TC_zone1_ref;
     camera_TC_zone1_ref  = (camera_TC_zone1_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone1_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone1_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone1_ref->private_seqNum; 
        *origin = camera_TC_zone1_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone1_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone1_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone1_ref->private_seqNum = *seqNum; 
        camera_TC_zone1_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"3e920d44e1ae84bf8b43a770f4b32d78") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone2",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone2_cache *camera_TC_zone2_ref;
     camera_TC_zone2_ref  = (camera_TC_zone2_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone2_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone2_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone2_ref->private_seqNum; 
        *origin = camera_TC_zone2_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone2_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone2_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone2_ref->private_seqNum = *seqNum; 
        camera_TC_zone2_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"3c30018cb874e39e4ed4e70d0c0a2e79") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone3",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone3_cache *camera_TC_zone3_ref;
     camera_TC_zone3_ref  = (camera_TC_zone3_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone3_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone3_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone3_ref->private_seqNum; 
        *origin = camera_TC_zone3_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone3_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone3_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone3_ref->private_seqNum = *seqNum; 
        camera_TC_zone3_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"7048415db3b60cb9b230d49d8550406b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone4",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone4_cache *camera_TC_zone4_ref;
     camera_TC_zone4_ref  = (camera_TC_zone4_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone4_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone4_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone4_ref->private_seqNum; 
        *origin = camera_TC_zone4_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone4_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone4_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone4_ref->private_seqNum = *seqNum; 
        camera_TC_zone4_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"477c042d40eb29b05261a0cc4425f7a5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone5",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone5_cache *camera_TC_zone5_ref;
     camera_TC_zone5_ref  = (camera_TC_zone5_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone5_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone5_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone5_ref->private_seqNum; 
        *origin = camera_TC_zone5_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone5_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone5_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone5_ref->private_seqNum = *seqNum; 
        camera_TC_zone5_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"8dca49a053c766d9b9ce54424f2cfbdd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_TC_zone6",svcSAL_handle[handle].streamname) == 0 ) {
     camera_TC_zone6_cache *camera_TC_zone6_ref;
     camera_TC_zone6_ref  = (camera_TC_zone6_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_TC_zone6_ref->private_sndStamp; 
        *rcvStamp = camera_TC_zone6_ref->private_rcvStamp; 
        *seqNum = camera_TC_zone6_ref->private_seqNum; 
        *origin = camera_TC_zone6_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_TC_zone6_ref->private_sndStamp = *sndStamp; 
        camera_TC_zone6_ref->private_rcvStamp = *rcvStamp; 
        camera_TC_zone6_ref->private_seqNum = *seqNum; 
        camera_TC_zone6_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"e3479c9d3855bf41d94dee05d4cc5a1b") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_UTIL",svcSAL_handle[handle].streamname) == 0 ) {
     camera_UTIL_cache *camera_UTIL_ref;
     camera_UTIL_ref  = (camera_UTIL_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_UTIL_ref->private_sndStamp; 
        *rcvStamp = camera_UTIL_ref->private_rcvStamp; 
        *seqNum = camera_UTIL_ref->private_seqNum; 
        *origin = camera_UTIL_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_UTIL_ref->private_sndStamp = *sndStamp; 
        camera_UTIL_ref->private_rcvStamp = *rcvStamp; 
        camera_UTIL_ref->private_seqNum = *seqNum; 
        camera_UTIL_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"76d769da32196c7f9521f62af9799a46") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_VCS",svcSAL_handle[handle].streamname) == 0 ) {
     camera_VCS_cache *camera_VCS_ref;
     camera_VCS_ref  = (camera_VCS_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_VCS_ref->private_sndStamp; 
        *rcvStamp = camera_VCS_ref->private_rcvStamp; 
        *seqNum = camera_VCS_ref->private_seqNum; 
        *origin = camera_VCS_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_VCS_ref->private_sndStamp = *sndStamp; 
        camera_VCS_ref->private_rcvStamp = *rcvStamp; 
        camera_VCS_ref->private_seqNum = *seqNum; 
        camera_VCS_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"33e0b666489f019e5407fe530f695666") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_WDS_wfsRaft",svcSAL_handle[handle].streamname) == 0 ) {
     camera_WDS_wfsRaft_cache *camera_WDS_wfsRaft_ref;
     camera_WDS_wfsRaft_ref  = (camera_WDS_wfsRaft_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_WDS_wfsRaft_ref->private_sndStamp; 
        *rcvStamp = camera_WDS_wfsRaft_ref->private_rcvStamp; 
        *seqNum = camera_WDS_wfsRaft_ref->private_seqNum; 
        *origin = camera_WDS_wfsRaft_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_WDS_wfsRaft_ref->private_sndStamp = *sndStamp; 
        camera_WDS_wfsRaft_ref->private_rcvStamp = *rcvStamp; 
        camera_WDS_wfsRaft_ref->private_seqNum = *seqNum; 
        camera_WDS_wfsRaft_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"57b9a0ce4ec36e0ac4e8dcadc4073ccb") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_command",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_command_cache *auxscope_command_ref;
     auxscope_command_ref  = (auxscope_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_command_ref->private_sndStamp; 
        *rcvStamp = auxscope_command_ref->private_rcvStamp; 
        *seqNum = auxscope_command_ref->private_seqNum; 
        *origin = auxscope_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_command_ref->private_sndStamp = *sndStamp; 
        auxscope_command_ref->private_rcvStamp = *rcvStamp; 
        auxscope_command_ref->private_seqNum = *seqNum; 
        auxscope_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"11f14765bf1c22cc7b257351b5dcb609") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("auxscope_response",svcSAL_handle[handle].streamname) == 0 ) {
     auxscope_response_cache *auxscope_response_ref;
     auxscope_response_ref  = (auxscope_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = auxscope_response_ref->private_sndStamp; 
        *rcvStamp = auxscope_response_ref->private_rcvStamp; 
        *seqNum = auxscope_response_ref->private_seqNum; 
        *origin = auxscope_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        auxscope_response_ref->private_sndStamp = *sndStamp; 
        auxscope_response_ref->private_rcvStamp = *rcvStamp; 
        auxscope_response_ref->private_seqNum = *seqNum; 
        auxscope_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5f1130ed46b7614fafecb611a085c5ea") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_command",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_command_cache *calibration_command_ref;
     calibration_command_ref  = (calibration_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_command_ref->private_sndStamp; 
        *rcvStamp = calibration_command_ref->private_rcvStamp; 
        *seqNum = calibration_command_ref->private_seqNum; 
        *origin = calibration_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_command_ref->private_sndStamp = *sndStamp; 
        calibration_command_ref->private_rcvStamp = *rcvStamp; 
        calibration_command_ref->private_seqNum = *seqNum; 
        calibration_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"941e74992ec4c6a73196c8e992aaaaa0") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("calibration_response",svcSAL_handle[handle].streamname) == 0 ) {
     calibration_response_cache *calibration_response_ref;
     calibration_response_ref  = (calibration_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = calibration_response_ref->private_sndStamp; 
        *rcvStamp = calibration_response_ref->private_rcvStamp; 
        *seqNum = calibration_response_ref->private_seqNum; 
        *origin = calibration_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        calibration_response_ref->private_sndStamp = *sndStamp; 
        calibration_response_ref->private_rcvStamp = *rcvStamp; 
        calibration_response_ref->private_seqNum = *seqNum; 
        calibration_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a90ced6d45f9e80bb07187afe55a767a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_command",svcSAL_handle[handle].streamname) == 0 ) {
     camera_command_cache *camera_command_ref;
     camera_command_ref  = (camera_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_command_ref->private_sndStamp; 
        *rcvStamp = camera_command_ref->private_rcvStamp; 
        *seqNum = camera_command_ref->private_seqNum; 
        *origin = camera_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_command_ref->private_sndStamp = *sndStamp; 
        camera_command_ref->private_rcvStamp = *rcvStamp; 
        camera_command_ref->private_seqNum = *seqNum; 
        camera_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"655fcd30706b1046bef0d6c4208567fb") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("camera_response",svcSAL_handle[handle].streamname) == 0 ) {
     camera_response_cache *camera_response_ref;
     camera_response_ref  = (camera_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = camera_response_ref->private_sndStamp; 
        *rcvStamp = camera_response_ref->private_rcvStamp; 
        *seqNum = camera_response_ref->private_seqNum; 
        *origin = camera_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        camera_response_ref->private_sndStamp = *sndStamp; 
        camera_response_ref->private_rcvStamp = *rcvStamp; 
        camera_response_ref->private_seqNum = *seqNum; 
        camera_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"c1f30e2266d6e5d2c6d8780b2a7e87d3") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_command",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_command_cache *enclosure_command_ref;
     enclosure_command_ref  = (enclosure_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_command_ref->private_sndStamp; 
        *rcvStamp = enclosure_command_ref->private_rcvStamp; 
        *seqNum = enclosure_command_ref->private_seqNum; 
        *origin = enclosure_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_command_ref->private_sndStamp = *sndStamp; 
        enclosure_command_ref->private_rcvStamp = *rcvStamp; 
        enclosure_command_ref->private_seqNum = *seqNum; 
        enclosure_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"cd44dee5cd65bf1d96a7ec6d03e92e3e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("enclosure_response",svcSAL_handle[handle].streamname) == 0 ) {
     enclosure_response_cache *enclosure_response_ref;
     enclosure_response_ref  = (enclosure_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = enclosure_response_ref->private_sndStamp; 
        *rcvStamp = enclosure_response_ref->private_rcvStamp; 
        *seqNum = enclosure_response_ref->private_seqNum; 
        *origin = enclosure_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        enclosure_response_ref->private_sndStamp = *sndStamp; 
        enclosure_response_ref->private_rcvStamp = *rcvStamp; 
        enclosure_response_ref->private_seqNum = *seqNum; 
        enclosure_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"f6f7151ca42fe83f36d057ff0839f0e1") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_command",svcSAL_handle[handle].streamname) == 0 ) {
     environment_command_cache *environment_command_ref;
     environment_command_ref  = (environment_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_command_ref->private_sndStamp; 
        *rcvStamp = environment_command_ref->private_rcvStamp; 
        *seqNum = environment_command_ref->private_seqNum; 
        *origin = environment_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_command_ref->private_sndStamp = *sndStamp; 
        environment_command_ref->private_rcvStamp = *rcvStamp; 
        environment_command_ref->private_seqNum = *seqNum; 
        environment_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"5acbd5c0b18b68c91846bd985670bba4") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("environment_response",svcSAL_handle[handle].streamname) == 0 ) {
     environment_response_cache *environment_response_ref;
     environment_response_ref  = (environment_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = environment_response_ref->private_sndStamp; 
        *rcvStamp = environment_response_ref->private_rcvStamp; 
        *seqNum = environment_response_ref->private_seqNum; 
        *origin = environment_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        environment_response_ref->private_sndStamp = *sndStamp; 
        environment_response_ref->private_rcvStamp = *rcvStamp; 
        environment_response_ref->private_seqNum = *seqNum; 
        environment_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"d00c310f4c7b6d5c986ec19cd835fe38") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("lasercal_command",svcSAL_handle[handle].streamname) == 0 ) {
     lasercal_command_cache *lasercal_command_ref;
     lasercal_command_ref  = (lasercal_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = lasercal_command_ref->private_sndStamp; 
        *rcvStamp = lasercal_command_ref->private_rcvStamp; 
        *seqNum = lasercal_command_ref->private_seqNum; 
        *origin = lasercal_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        lasercal_command_ref->private_sndStamp = *sndStamp; 
        lasercal_command_ref->private_rcvStamp = *rcvStamp; 
        lasercal_command_ref->private_seqNum = *seqNum; 
        lasercal_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"70b70ae99309e54d0d3e45afdd31c144") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("lasercal_response",svcSAL_handle[handle].streamname) == 0 ) {
     lasercal_response_cache *lasercal_response_ref;
     lasercal_response_ref  = (lasercal_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = lasercal_response_ref->private_sndStamp; 
        *rcvStamp = lasercal_response_ref->private_rcvStamp; 
        *seqNum = lasercal_response_ref->private_seqNum; 
        *origin = lasercal_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        lasercal_response_ref->private_sndStamp = *sndStamp; 
        lasercal_response_ref->private_rcvStamp = *rcvStamp; 
        lasercal_response_ref->private_seqNum = *seqNum; 
        lasercal_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"6d80abfa4d357af809012a9c0e1a00f1") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_command",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_command_cache *m1m3_command_ref;
     m1m3_command_ref  = (m1m3_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_command_ref->private_sndStamp; 
        *rcvStamp = m1m3_command_ref->private_rcvStamp; 
        *seqNum = m1m3_command_ref->private_seqNum; 
        *origin = m1m3_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_command_ref->private_sndStamp = *sndStamp; 
        m1m3_command_ref->private_rcvStamp = *rcvStamp; 
        m1m3_command_ref->private_seqNum = *seqNum; 
        m1m3_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"26677ca27ad77e92aab3d088f05dcdf5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m1m3_response",svcSAL_handle[handle].streamname) == 0 ) {
     m1m3_response_cache *m1m3_response_ref;
     m1m3_response_ref  = (m1m3_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m1m3_response_ref->private_sndStamp; 
        *rcvStamp = m1m3_response_ref->private_rcvStamp; 
        *seqNum = m1m3_response_ref->private_seqNum; 
        *origin = m1m3_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m1m3_response_ref->private_sndStamp = *sndStamp; 
        m1m3_response_ref->private_rcvStamp = *rcvStamp; 
        m1m3_response_ref->private_seqNum = *seqNum; 
        m1m3_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"fa972b36fb67f5d9e8a94573b442f7b6") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_command",svcSAL_handle[handle].streamname) == 0 ) {
     m2_command_cache *m2_command_ref;
     m2_command_ref  = (m2_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_command_ref->private_sndStamp; 
        *rcvStamp = m2_command_ref->private_rcvStamp; 
        *seqNum = m2_command_ref->private_seqNum; 
        *origin = m2_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_command_ref->private_sndStamp = *sndStamp; 
        m2_command_ref->private_rcvStamp = *rcvStamp; 
        m2_command_ref->private_seqNum = *seqNum; 
        m2_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"76c5a145366d481cfe06f515ba38296e") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("m2_response",svcSAL_handle[handle].streamname) == 0 ) {
     m2_response_cache *m2_response_ref;
     m2_response_ref  = (m2_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = m2_response_ref->private_sndStamp; 
        *rcvStamp = m2_response_ref->private_rcvStamp; 
        *seqNum = m2_response_ref->private_seqNum; 
        *origin = m2_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        m2_response_ref->private_sndStamp = *sndStamp; 
        m2_response_ref->private_rcvStamp = *rcvStamp; 
        m2_response_ref->private_seqNum = *seqNum; 
        m2_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"17c9d99c436a781ce393456704ca7a58") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_command",svcSAL_handle[handle].streamname) == 0 ) {
     mount_command_cache *mount_command_ref;
     mount_command_ref  = (mount_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_command_ref->private_sndStamp; 
        *rcvStamp = mount_command_ref->private_rcvStamp; 
        *seqNum = mount_command_ref->private_seqNum; 
        *origin = mount_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_command_ref->private_sndStamp = *sndStamp; 
        mount_command_ref->private_rcvStamp = *rcvStamp; 
        mount_command_ref->private_seqNum = *seqNum; 
        mount_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0c7d336160596f1096bc013ff3f31de6") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("mount_response",svcSAL_handle[handle].streamname) == 0 ) {
     mount_response_cache *mount_response_ref;
     mount_response_ref  = (mount_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = mount_response_ref->private_sndStamp; 
        *rcvStamp = mount_response_ref->private_rcvStamp; 
        *seqNum = mount_response_ref->private_seqNum; 
        *origin = mount_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        mount_response_ref->private_sndStamp = *sndStamp; 
        mount_response_ref->private_rcvStamp = *rcvStamp; 
        mount_response_ref->private_seqNum = *seqNum; 
        mount_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"2b4e6f768b51aa59035fabeef4e6decd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("network_command",svcSAL_handle[handle].streamname) == 0 ) {
     network_command_cache *network_command_ref;
     network_command_ref  = (network_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = network_command_ref->private_sndStamp; 
        *rcvStamp = network_command_ref->private_rcvStamp; 
        *seqNum = network_command_ref->private_seqNum; 
        *origin = network_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        network_command_ref->private_sndStamp = *sndStamp; 
        network_command_ref->private_rcvStamp = *rcvStamp; 
        network_command_ref->private_seqNum = *seqNum; 
        network_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"45e91d1acc26618c1536dba3e2bda7c5") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("network_response",svcSAL_handle[handle].streamname) == 0 ) {
     network_response_cache *network_response_ref;
     network_response_ref  = (network_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = network_response_ref->private_sndStamp; 
        *rcvStamp = network_response_ref->private_rcvStamp; 
        *seqNum = network_response_ref->private_seqNum; 
        *origin = network_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        network_response_ref->private_sndStamp = *sndStamp; 
        network_response_ref->private_rcvStamp = *rcvStamp; 
        network_response_ref->private_seqNum = *seqNum; 
        network_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"01907e119cb2c05390d869516f629c7c") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("operations_command",svcSAL_handle[handle].streamname) == 0 ) {
     operations_command_cache *operations_command_ref;
     operations_command_ref  = (operations_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = operations_command_ref->private_sndStamp; 
        *rcvStamp = operations_command_ref->private_rcvStamp; 
        *seqNum = operations_command_ref->private_seqNum; 
        *origin = operations_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        operations_command_ref->private_sndStamp = *sndStamp; 
        operations_command_ref->private_rcvStamp = *rcvStamp; 
        operations_command_ref->private_seqNum = *seqNum; 
        operations_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"c9aac6df9b95ab2cd64d1c10bdb3f706") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("operations_response",svcSAL_handle[handle].streamname) == 0 ) {
     operations_response_cache *operations_response_ref;
     operations_response_ref  = (operations_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = operations_response_ref->private_sndStamp; 
        *rcvStamp = operations_response_ref->private_rcvStamp; 
        *seqNum = operations_response_ref->private_seqNum; 
        *origin = operations_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        operations_response_ref->private_sndStamp = *sndStamp; 
        operations_response_ref->private_rcvStamp = *rcvStamp; 
        operations_response_ref->private_seqNum = *seqNum; 
        operations_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"997702adb41c5f4a439f21f5dda5e1e0") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("power_command",svcSAL_handle[handle].streamname) == 0 ) {
     power_command_cache *power_command_ref;
     power_command_ref  = (power_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = power_command_ref->private_sndStamp; 
        *rcvStamp = power_command_ref->private_rcvStamp; 
        *seqNum = power_command_ref->private_seqNum; 
        *origin = power_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        power_command_ref->private_sndStamp = *sndStamp; 
        power_command_ref->private_rcvStamp = *rcvStamp; 
        power_command_ref->private_seqNum = *seqNum; 
        power_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"b51425f450639cd2661aedadbd9086bd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("power_response",svcSAL_handle[handle].streamname) == 0 ) {
     power_response_cache *power_response_ref;
     power_response_ref  = (power_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = power_response_ref->private_sndStamp; 
        *rcvStamp = power_response_ref->private_rcvStamp; 
        *seqNum = power_response_ref->private_seqNum; 
        *origin = power_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        power_response_ref->private_sndStamp = *sndStamp; 
        power_response_ref->private_rcvStamp = *rcvStamp; 
        power_response_ref->private_seqNum = *seqNum; 
        power_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a990a3c3d993ce24222d920f07589844") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("scheduler_command",svcSAL_handle[handle].streamname) == 0 ) {
     scheduler_command_cache *scheduler_command_ref;
     scheduler_command_ref  = (scheduler_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = scheduler_command_ref->private_sndStamp; 
        *rcvStamp = scheduler_command_ref->private_rcvStamp; 
        *seqNum = scheduler_command_ref->private_seqNum; 
        *origin = scheduler_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        scheduler_command_ref->private_sndStamp = *sndStamp; 
        scheduler_command_ref->private_rcvStamp = *rcvStamp; 
        scheduler_command_ref->private_seqNum = *seqNum; 
        scheduler_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"0befd3ae04ce63e13222bc3e88a4fa09") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("scheduler_response",svcSAL_handle[handle].streamname) == 0 ) {
     scheduler_response_cache *scheduler_response_ref;
     scheduler_response_ref  = (scheduler_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = scheduler_response_ref->private_sndStamp; 
        *rcvStamp = scheduler_response_ref->private_rcvStamp; 
        *seqNum = scheduler_response_ref->private_seqNum; 
        *origin = scheduler_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        scheduler_response_ref->private_sndStamp = *sndStamp; 
        scheduler_response_ref->private_rcvStamp = *rcvStamp; 
        scheduler_response_ref->private_seqNum = *seqNum; 
        scheduler_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"953db588f09ae198e714423f4723eef6") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_command",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_command_cache *seeing_dimm_command_ref;
     seeing_dimm_command_ref  = (seeing_dimm_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_command_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_command_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_command_ref->private_seqNum; 
        *origin = seeing_dimm_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_command_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_command_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_command_ref->private_seqNum = *seqNum; 
        seeing_dimm_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"b00904471cd062bedd1ec43a065f8a8a") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_dimm_response",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_dimm_response_cache *seeing_dimm_response_ref;
     seeing_dimm_response_ref  = (seeing_dimm_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_dimm_response_ref->private_sndStamp; 
        *rcvStamp = seeing_dimm_response_ref->private_rcvStamp; 
        *seqNum = seeing_dimm_response_ref->private_seqNum; 
        *origin = seeing_dimm_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_dimm_response_ref->private_sndStamp = *sndStamp; 
        seeing_dimm_response_ref->private_rcvStamp = *rcvStamp; 
        seeing_dimm_response_ref->private_seqNum = *seqNum; 
        seeing_dimm_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"01e01678e6c0f4a961290d18c01fc97d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_command",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_command_cache *seeing_mass_command_ref;
     seeing_mass_command_ref  = (seeing_mass_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_command_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_command_ref->private_rcvStamp; 
        *seqNum = seeing_mass_command_ref->private_seqNum; 
        *origin = seeing_mass_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_command_ref->private_sndStamp = *sndStamp; 
        seeing_mass_command_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_command_ref->private_seqNum = *seqNum; 
        seeing_mass_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a7bbff3e73fa9bb79ac31606c531384d") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("seeing_mass_response",svcSAL_handle[handle].streamname) == 0 ) {
     seeing_mass_response_cache *seeing_mass_response_ref;
     seeing_mass_response_ref  = (seeing_mass_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = seeing_mass_response_ref->private_sndStamp; 
        *rcvStamp = seeing_mass_response_ref->private_rcvStamp; 
        *seqNum = seeing_mass_response_ref->private_seqNum; 
        *origin = seeing_mass_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        seeing_mass_response_ref->private_sndStamp = *sndStamp; 
        seeing_mass_response_ref->private_rcvStamp = *rcvStamp; 
        seeing_mass_response_ref->private_seqNum = *seqNum; 
        seeing_mass_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"1314e86b669f18917dbc433397acb6cd") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_command",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_command_cache *skycam_command_ref;
     skycam_command_ref  = (skycam_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_command_ref->private_sndStamp; 
        *rcvStamp = skycam_command_ref->private_rcvStamp; 
        *seqNum = skycam_command_ref->private_seqNum; 
        *origin = skycam_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_command_ref->private_sndStamp = *sndStamp; 
        skycam_command_ref->private_rcvStamp = *rcvStamp; 
        skycam_command_ref->private_seqNum = *seqNum; 
        skycam_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9b3b342b80bfef756cd1c44c441de7fe") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("skycam_response",svcSAL_handle[handle].streamname) == 0 ) {
     skycam_response_cache *skycam_response_ref;
     skycam_response_ref  = (skycam_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = skycam_response_ref->private_sndStamp; 
        *rcvStamp = skycam_response_ref->private_rcvStamp; 
        *seqNum = skycam_response_ref->private_seqNum; 
        *origin = skycam_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        skycam_response_ref->private_sndStamp = *sndStamp; 
        skycam_response_ref->private_rcvStamp = *rcvStamp; 
        skycam_response_ref->private_seqNum = *seqNum; 
        skycam_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"a839857790f83a58eff5bad250c00262") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_command",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_command_cache *tcs_command_ref;
     tcs_command_ref  = (tcs_command_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_command_ref->private_sndStamp; 
        *rcvStamp = tcs_command_ref->private_rcvStamp; 
        *seqNum = tcs_command_ref->private_seqNum; 
        *origin = tcs_command_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_command_ref->private_sndStamp = *sndStamp; 
        tcs_command_ref->private_rcvStamp = *rcvStamp; 
        tcs_command_ref->private_seqNum = *seqNum; 
        tcs_command_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"9540443c5693d7ae5af8d110c2abde27") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  if (strcmp("tcs_response",svcSAL_handle[handle].streamname) == 0 ) {
     tcs_response_cache *tcs_response_ref;
     tcs_response_ref  = (tcs_response_cache *) svcSAL_handle[handle].ref;
     if (strcmp(operation,"read") == 0 ) {
        *sndStamp = tcs_response_ref->private_sndStamp; 
        *rcvStamp = tcs_response_ref->private_rcvStamp; 
        *seqNum = tcs_response_ref->private_seqNum; 
        *origin = tcs_response_ref->private_origin; 
     }
     if (strcmp(operation,"write") == 0 ) {
        tcs_response_ref->private_sndStamp = *sndStamp; 
        tcs_response_ref->private_rcvStamp = *rcvStamp; 
        tcs_response_ref->private_seqNum = *seqNum; 
        tcs_response_ref->private_origin = *origin; 
     }
     if (strcmp(operation,"verify") == 0 ) {
        if ( strcmp(revCode,"819126f5d88fd71d89baa5b1a2718643") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     }
     return SAL__OK;
  }

  return SAL__ERR;
}

