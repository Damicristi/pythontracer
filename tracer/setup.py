from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(name = "pythontracer", version = "1.0",
      ext_modules = [Extension("pygraphfile", ["graphfile/graphfile.c", "graphfile/python/pygraphfile.pyx"]),
                     Extension("pytracer", ["graphfile/graphfile.c", "pytracer.pyx"])],
      scripts = ["pytracerview.py", "pytracefile.py"],
      cmdclass = dict(build_ext=build_ext))
