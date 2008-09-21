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
      ],
      cmdclass = cmdclass)
