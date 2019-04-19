# This file is part of ts_idl.
#
# Developed for the LSST Telescope and Site Systems.
# This product includes software developed by the LSST Project
# (https://www.lsst.org).
# See the COPYRIGHT file at the top-level directory of this distribution
# for details of code ownership.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

__all__ = ["make_idl_file"]

import glob
import os
import pathlib
import shutil
import subprocess


def get_env_dir(name, err_msg):
    path = os.environ.get(name)
    if path is None:
        raise RuntimeError(err_msg)
    path = pathlib.Path(path)
    if not path.is_dir():
        raise RuntimeError(f"{path} is not a directory")
    print(f"${name} = {path}")
    return path


class MakeIdlFile:
    """Make the IDL file for a specified SAL component.

    Parameters
    ----------
    name : `str`
        Name of SAL component, e.g. ``"ScriptQueue"``.
    """
    def __init__(self, name):
        self.name = name
        self.xml_dir = get_env_dir("TS_XML_DIR", "ts_xml not setup")
        pkg_dir = get_env_dir("TS_IDL_DIR", "ts_idl not setup")
        self.sal_work_dir = get_env_dir("SAL_WORK_DIR", "$SAL_WORK_DIR must be defined")
        idl_file_name = f"sal_revCoded_{self.name}.idl"
        self.idl_file_from_path = self.sal_work_dir / "idl-templates" / "validated" / "sal" / idl_file_name
        self.idl_file_to_path = pkg_dir / "idl" / idl_file_name

    def copy_xml_files(self):
        interfaces_dir = os.path.join(self.xml_dir, "sal_interfaces")
        std_xml_paths = [os.path.join(interfaces_dir, f"{n}.xml") for n in ("SALGenerics", "SALSubsystems")]
        sal_xml_paths = glob.glob(os.path.join(interfaces_dir, self.name, "*.xml"))
        if not sal_xml_paths:
            raise RuntimeError(f"Could not find any XML files for SAL component {self.name}")
        for xmlpath in std_xml_paths + sal_xml_paths:
            shutil.copy(xmlpath, self.sal_work_dir)

    def delete_files(self):
        """Delete unwanted files for this SAL component.
        """
        xmlfiles = glob.glob(os.path.join(self.sal_work_dir, "*.xml"))
        for f in xmlfiles:
            os.remove(f)

        for subdir in ["idl-templates"]:
            print(f"Remove subdir {subdir}")
            shutil.rmtree(os.path.join(self.sal_work_dir, subdir), ignore_errors=True)

    def make_idl_file(self):
        """Make the IDL file."""
        for command in ("validate", "sal pydds",):
            full_cmd = f"salgenerator {self.name} {command}"
            print(f"***** {full_cmd}")
            subprocess.run(full_cmd, check=True, cwd=self.sal_work_dir, shell=True)

    def run(self):
        """Make the IDL file and move it to the idl directory."""
        print(f"* Make {self.name} IDL file ***")

        print(f"*** Copy {self.name} XML files ***")
        self.copy_xml_files()

        print(f"*** Validate and generate {self.name} libraries ***")
        self.make_idl_file()

        print(f"*** Move {self.name} IDL file into place ***")
        os.rename(self.idl_file_from_path, self.idl_file_to_path)

        print(f"*** Cleanup {self.name} files ***")
        self.delete_files()

        print(f"*** Done generating SALPY_{self.name} ***")


def make_idl_file(name):
    """Make the SALPY library for a specified SAL component.

    Parameters
    ----------
    name : `str`
        Name of SAL component, e.g. ``"ScriptQueue"``.
    """
    maker = MakeIdlFile(name)
    maker.run()
