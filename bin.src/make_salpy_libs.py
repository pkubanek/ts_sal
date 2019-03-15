#!/usr/bin/env python
import argparse

from lsst.ts.sal.make_salpy_lib import make_salpy_lib

parser = argparse.ArgumentParser(
    description="Build SALPY libraries for one or more SAL component")
parser.add_argument("components", nargs='+',
                    help="Names of SAL components, e.g. \"Test\"")
parser.add_argument("--demo", action="store_true",
                    help="Build a demo reader and writer for each topic?")

args = parser.parse_args()
print(f"demo={args.demo}")

for sal_name in args.components:
    make_salpy_lib(sal_name, demo=args.demo)
