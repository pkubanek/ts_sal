
    if (strcmp(subsysid,"tcs_kernel_Target") == 0) {
       tcs_kernel_Target_cache *tcs_kernel_Target_ref;
       tcs_kernel_Target_ref = (tcs_kernel_Target_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_Target_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "site", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_Target_ref->site,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "t0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->t0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "az", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->az);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "el", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->el);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "azdot", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->azdot);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "eldot", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->eldot);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Wavel", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Wavel);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "XOffset", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->XOffset);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "YOffset", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->YOffset);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "OffSys", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_Target_ref->OffSys,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "focalplaneX", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->focalplaneX);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "focalplaneY", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->focalplaneY);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Temp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Temp);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Press", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Press);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Humid", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Humid);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "TLR", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->TLR);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Tai", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Tai);
      tcs_kernel_Target_ref->syncO = 1;
    }
