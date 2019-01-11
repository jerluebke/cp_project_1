# -*- coding: utf-8 -*-

import os
from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import numpy

# when compiling with MSVS on windows
#  os.environ["CFLAGS"] = "-std=c11"

exclude_1 = ["search.c"]
exclude_2 = ["cvisualise.c"]
libs = ["m", "gvc", "cgraph", "cdt"] if not os.name == 'nt' else None

ext = Extension(
        "visualise",
        sources = ["./visualise.pyx", *[os.path.join("..", "src", d) for d in
                                        os.listdir("../src") if d not in
                                        exclude_1]],
        include_dirs = ["../include", numpy.get_include(),
                        "/usr/include/graphviz"],
        libraries = libs
        #  extra_compile_args = ["-std=c11"]
    )

setup(
    cmdclass = {"build_ext" : build_ext},
    ext_modules = cythonize(ext) #, gdb_debug=True
)
