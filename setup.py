from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
import pybind11

ext_modules = [
    Pybind11Extension(
        "lisptorch_core",
        ["lisptorch_core.cpp"],
        include_dirs=[pybind11.get_include()],
        extra_compile_args=['-std=c++17'],
        language='c++'
    )
]

setup(
    name="lisptorch",
    version="0.1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    install_requires=['pybind11'] # Bu satırı ekle
)