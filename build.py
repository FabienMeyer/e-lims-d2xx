"""Build module."""
from __future__ import annotations

import contextlib
import platform
from distutils.command.build_ext import build_ext
from distutils.errors import CCompilerError, DistutilsExecError, DistutilsPlatformError

from setuptools import Extension


def get_extensions() -> list[Extension]:
    """Get the extension."""
    system = platform.system().lower()
    architecture = platform.machine().lower()

    extensions = "e_lims_d2xx"
    include_dirs = ["e_lims_d2xx/include"]
    library_dirs = []
    libraries = ["ftd2xx"]

    match system:
        case "windows":
            match architecture:
                case "amd64":
                    directory = f"{extensions}/libs/{system}"
                    include_dirs.append(directory)
                    library_dirs = [f"{directory}/{architecture}"]
                    print(include_dirs)
                case _:
                    message = f"Architecture {architecture} is not supported."
                    raise NotImplementedError(message)
        case _:
            message = f"System {system} is not supported."
            raise NotImplementedError(message)

    return [
        Extension(
            'e_lims_d2xx.e_lims_d2xx',
            sources=[
                "e_lims_d2xx/source/pymodule.c",
                "e_lims_d2xx/source/pyclass_device.c",
                "e_lims_d2xx/source/device.c",
            ],
            include_dirs=include_dirs,
            library_dirs=library_dirs,
            libraries=libraries,
        ),
    ]


class BuildFailedError(Exception):

    """Exception raised when the build fails."""


class ExtBuilder(build_ext):

    """Customized `build_ext` command to catch compiler errors."""

    def run(self) -> None:
        """Run the build process."""
        with contextlib.suppress(DistutilsPlatformError, FileNotFoundError):
            build_ext.run(self)

    def build_extension(self, extensions: list[Extension]) -> None:
        """Build the extension."""
        with contextlib.suppress(
            CCompilerError,
            DistutilsExecError,
            DistutilsPlatformError,
            ValueError
        ):
            build_ext.build_extension(self, extensions)


def build(setup_kwargs: dict[str, any]) -> None:
    """Build the extension."""
    setup_kwargs.update(
        {
            "ext_modules": get_extensions(),
            "cmdclass": {"build_ext": ExtBuilder}
        }
    )
