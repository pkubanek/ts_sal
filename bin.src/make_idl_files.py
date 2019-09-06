#!/usr/bin/env python
import argparse

from lsst.ts.sal.make_idl_file import all_component_names, make_idl_file

parser = argparse.ArgumentParser(
    description="Build the IDL file for one or more SAL component")
parser.add_argument("components", nargs='+',
                    help="Names of SAL components, e.g. 'Test'; "
                    "if 'all' then make IDL files for all SAL components")
parser.add_argument("--exclude", nargs="+",
                    help="Names of SAL copmonents to exclude")

args = parser.parse_args()

if args.components == ["all"]:
    components = all_component_names()
else:
    components = args.components
if args.exclude:
    exclude = set(args.exclude)
    components = [name for name in components if name not in exclude]
print(f"Making IDL files for: {', '.join(components)}")
for name in components:
    make_idl_file(name=name)
