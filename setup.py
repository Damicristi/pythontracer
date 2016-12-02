# Written by Eyal Lotem <eyal.lotem+pt@gmail.com>
# Copyright (2007-2008)
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
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from distutils.core import setup
from distutils.extension import Extension

VERSION = "8.10.16"

try:
    from Cython.Distutils import build_ext
except ImportError:
    cmdclass = dict()
    def fixpyx(x):
        return x.replace('.pyx', '.c')
else:
    cmdclass = dict(build_ext=build_ext)
    def fixpyx(x):
        return x

def make_extension(name, filenames):
    return Extension(name, ["graphfile/graphfile.c"] + list(map(fixpyx, filenames)),
                     include_dirs=["graphfile", "graphfile-python", "pyrex-lib"],
                     define_macros=[("PYREX_WITHOUT_ASSERTIONS", "")])
setup(name = "pythontracer", version = VERSION,
      ext_modules = [
          make_extension("graphfile", ["graphfile-python/graphfile.pyx"]),
          make_extension("pytracer", ["tracer/pytracer.pyx", "tracer/rotatingtree.c"],
),
      ],
      py_modules = ["pytracerview"],
      scripts = ["tracer/pytracefile.py"],
      cmdclass = cmdclass)
