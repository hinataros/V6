#!/usr/bin/python3

import os, sys
import subprocess

import config
from myMod import readRegistry
from myMod import readInterface

from commandMod import setLatexCompile

if __name__ in "__main__":
    readRegistry()

    os.makedirs(os.path.join(config.rgs_dir, "misc", "templateTex", config.OUTPUT), exist_ok=True)

    if len(sys.argv) == 2:
        if sys.argv[1] == "start":
            from auto_latexMod import auto_latex

            print("auto_latex start...")
            auto_latex()

        else:
            print("argument invalid...")

    elif len(sys.argv) == 1:
        readInterface()
        setLatexCompile()
        subprocess.call(config.latex_compile, shell=True)
        subprocess.call(config.dvi2pdf, shell=True)

    else:
        print("argument invalid...")
