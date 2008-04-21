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
setup(name = "pythontracer", version = "1.3",
      ext_modules = [Extension("pygraphfile", ["graphfile/graphfile.c", fixpyx("graphfile/python/pygraphfile.pyx")]),
                     Extension("pytracer", ["graphfile/graphfile.c", fixpyx("pytracer.pyx")])],
      scripts = ["pytracerview.py", "pytracefile.py"],
      cmdclass = cmdclass)
