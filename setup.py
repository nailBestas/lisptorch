from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

setup(
    name="superframe",
    version="0.1.0",
    ext_modules=[
        Pybind11Extension(
            "superframe_core",
            ["superframe_core.cpp"],
        ),
    ],
    cmdclass={"build_ext": build_ext},
)