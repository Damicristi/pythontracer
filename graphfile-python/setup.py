from distutils.core import setup
from distutils.extension import Extension
try:
    from Pyrex.Distutils import build_ext
except ImportError:
    cmdclass = dict()
    def fixpyx(x):
        return x.replace('.pyx', '.c')
else:
    cmdclass = dict(build_ext=build_ext)
    def fixpyx(x):
        return x
setup(name = "graphfile-python", version = "1.4",
      ext_modules = [
          Extension("graphfile", ["../graphfile/graphfile.c", fixpyx("graphfile.pyx")],
                    include_dirs=["../graphfile", "../pyrex-lib"]),
          Extension("_pyrexlib.memory", [fixpyx("../pyrex-lib/memory.pyx")], include_dirs=["../pyrex-lib"]),
          Extension("_pyrexlib.memory", [fixpyx("../pyrex-lib/memory.pyx")], include_dirs=["../pyrex-lib"]),
      ],
      cmdclass = cmdclass)
  -rw-r--r-- 1 eyal users   264 2008-09-18 19:06 darray.pxd
  -rw-r--r-- 1 eyal users   757 2008-09-18 19:10 darray.pyx
  -rw-r--r-- 1 eyal users   332 2008-09-18 20:00 memory.pxd
  -rw-r--r-- 1 eyal users   349 2008-09-18 20:01 memory.pyx
  -rw-r--r-- 1 eyal users   192 2008-09-18 19:20 posix.pxd
  -rw-r--r-- 1 eyal users   638 2008-09-18 19:20 python.pxd
  -rw-r--r-- 1 eyal users   165 2008-09-18 19:11 python.pyx
  -rw-r--r-- 1 eyal users   598 2008-09-18 18:53 times.pyx
