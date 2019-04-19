#!/usr/bin/env python
import argparse

from lsst.ts.sal.make_idl_file import make_idl_file

parser = argparse.ArgumentParser(
    description="Build the IDL file for one or more SAL component")
parser.add_argument("components", nargs='+',
                    help="Names of SAL components, e.g. \"Test\"")

args = parser.parse_args()

for name in args.components:
    make_idl_file(name=name)
