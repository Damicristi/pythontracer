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
def make_extension(name, filename):
    return Extension(name, ["graphfile/graphfile.c", fixpyx(filename)],
                     include_dirs=["graphfile", "../pyrex-lib"],
                     define_macros=[("PYREX_WITHOUT_ASSERTIONS", "")])
setup(name = "pythontracer", version = "8.9.21",
      ext_modules = [
          make_extension("graphfile", "graphfile-python/graphfile.pyx"),
          make_extension("pytracer", "pytracer.pyx"),
      ],
      scripts = ["pytracerview.py", "pytracefile.py"],
      cmdclass = cmdclass)
