"""e-lims-d2xx Top-level."""

__author__ = """Fabien Meyer"""
__email__ = 'fabien-meyer@outlook.com'
__version__ = '0.0.1'

import os
import platform
import sys

if platform.system() == 'Windows':
    from pathlib import Path

    extra_dll_dir = Path(__file__).parent / 'libs' / 'windows' / 'amd64'

    if sys.version_info >= (3, 9):
        os.add_dll_directory(str(extra_dll_dir))

    os.environ.setdefault('PATH', '')
    os.environ['PATH'] += os.pathsep + str(extra_dll_dir)

# from .e_lims_d2xx import *

__all__ = ['Ftd2xxDevice', 'Ftd2xxError']

del os, sys, platform
