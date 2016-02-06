from distutils.core import setup, Extension

module = Extension("fast_combination", sources=["src/fast_combinationmodule.c"])

setup(name = "fast_combination",
      version = '0.1',
      description = "Fast nCk combinations via the multiplicative method",
      ext_modules = [module])
