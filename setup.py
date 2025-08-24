from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
import pybind11

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

ext_modules = [
    Pybind11Extension(
        "lisptorch_core",
        ["lisptorch_core.cpp"],
        include_dirs=[pybind11.get_include()]
    )
]

setup(
    name="lisptorch",
    version="0.1.9",  # Versiyon numarasını mutlaka artır
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    install_requires=['pybind11'],
    
    long_description=long_description,
    long_description_content_type="text/markdown",
)