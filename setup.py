from distutils.core import setup
from distutils.extension import Extension

VERSION = "8.10.16"

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
def make_extension(name, filenames):
    return Extension(name, ["graphfile/graphfile.c"] +
                     map(fixpyx, filenames),
                     include_dirs=["graphfile", "graphfile-python", "pyrex-lib"],
                     define_macros=[("PYREX_WITHOUT_ASSERTIONS", "")])
setup(name = "pythontracer", version = VERSION,
      ext_modules = [
          make_extension("graphfile", ["graphfile-python/graphfile.pyx"]),
          make_extension("pytracer", ["tracer/pytracer.pyx", "tracer/rotatingtree.c"],
),
      ],
      scripts = ["tracer/pytracerview.py", "tracer/pytracefile.py"],
      cmdclass = cmdclass)
