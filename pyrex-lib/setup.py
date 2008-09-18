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
      packages = {'_pyrexlib' : '_pyrexlib'},
      ext_modules = [
          Extension("_pyrexlib.%s" % name,
                    [fixpyx("%s.pyx" % name)])
          for name in ["darray", "python", "times"]
      ], cmdclass = cmdclass)
