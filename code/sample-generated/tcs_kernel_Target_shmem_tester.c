
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from tcs_kernel_Target.idl using "genshmem".
  The genshmem tool is part of the LSST SAL middleware stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "tcs_kernel_Target_cache.h"

int main(int argc, char *argv[])
{
   int tcs_kernel_Target_shmsize;
   int lshmid;
   int icount=0;
   int tcs_kernel_Target_shmid = 0xde92;
   tcs_kernel_Target_cache *tcs_kernel_Target_ref;
   tcs_kernel_Target_shmsize = sizeof(struct tcs_kernel_Target_cache);
   lshmid = shmget(tcs_kernel_Target_shmid, tcs_kernel_Target_shmsize , IPC_CREAT|0666);
   tcs_kernel_Target_ref  = (tcs_kernel_Target_cache *) shmat(lshmid, NULL, 0);
 

   tcs_kernel_Target_ref->syncI++;
   icount++;
   sprintf(tcs_kernel_Target_ref->site,"Sample string %d",icount);
   tcs_kernel_Target_ref->t0++;
   tcs_kernel_Target_ref->az++;
   tcs_kernel_Target_ref->el++;
   tcs_kernel_Target_ref->azdot++;
   tcs_kernel_Target_ref->eldot++;
   tcs_kernel_Target_ref->Wavel++;
   tcs_kernel_Target_ref->XOffset++;
   tcs_kernel_Target_ref->YOffset++;
   icount++;
   sprintf(tcs_kernel_Target_ref->OffSys,"Sample string %d",icount);
   tcs_kernel_Target_ref->focalplaneX++;
   tcs_kernel_Target_ref->focalplaneY++;
   tcs_kernel_Target_ref->Temp++;
   tcs_kernel_Target_ref->Press++;
   tcs_kernel_Target_ref->Humid++;
   tcs_kernel_Target_ref->TLR++;
   tcs_kernel_Target_ref->Tai++;
   tcs_kernel_Target_ref->syncO = 1;
   return(0);
}

