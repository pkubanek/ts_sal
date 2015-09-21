

#include "svcSAL.h"

int svcSAL_commandSHMID ( char *subsys, int *cmdid, int *respid ) {

  cmdid = 0;
  respid = 0;

  if (strcmp("m1m3",subsys) == 0 ) {
     *cmdid = 0xc0c4;
     *respid = 0x353b;
  }

  if (strcmp("m2",subsys) == 0 ) {
     *cmdid = 0xd6a5;
     *respid = 0x0a80;
  }

  if (strcmp("mount",subsys) == 0 ) {
     *cmdid = 0x83c4;
     *respid = 0x6563;
  }

  if (strcmp("power",subsys) == 0 ) {
     *cmdid = 0x70db;
     *respid = 0x7c16;
  }

  if (strcmp("calibration",subsys) == 0 ) {
     *cmdid = 0x3720;
     *respid = 0xa72d;
  }

  if (strcmp("enclosure",subsys) == 0 ) {
     *cmdid = 0x6ee7;
     *respid = 0xe34f;
  }

  if (strcmp("scheduler",subsys) == 0 ) {
     *cmdid = 0x3e87;
     *respid = 0x8466;
  }

  if (strcmp("operations",subsys) == 0 ) {
     *cmdid = 0x8154;
     *respid = 0x2eb1;
  }

  if (strcmp("auxscope",subsys) == 0 ) {
     *cmdid = 0x9123;
     *respid = 0xfb02;
  }

  if (strcmp("lasercal",subsys) == 0 ) {
     *cmdid = 0xc2e7;
     *respid = 0xc169;
  }

  if (strcmp("seeing_dimm",subsys) == 0 ) {
     *cmdid = 0x7f20;
     *respid = 0x0b66;
  }

  if (strcmp("seeing_mass",subsys) == 0 ) {
     *cmdid = 0x7456;
     *respid = 0x0c3b;
  }

  if (strcmp("skycam",subsys) == 0 ) {
     *cmdid = 0xf3d1;
     *respid = 0x70d2;
  }

  if (strcmp("environment",subsys) == 0 ) {
     *cmdid = 0x861a;
     *respid = 0x514f;
  }

  if (strcmp("camera",subsys) == 0 ) {
     *cmdid = 0x716b;
     *respid = 0x6385;
  }

  if (strcmp("network",subsys) == 0 ) {
     *cmdid = 0xd170;
     *respid = 0x9cc5;
  }

  if (strcmp("tcs",subsys) == 0 ) {
     *cmdid = 0x0a28;
     *respid = 0xec0c;
  }

  if (cmdid == 0) {
     return SAL__ERR;
  }
  return SAL__OK;
}

