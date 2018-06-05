#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from read_confMod import read_conf

from read_interfaceMod import read_interface

def set_latex_compile():
    TARGET = "result"
    LATEX = "platex"
    LATEX_OPTION = "-interaction=nonstopmode -output-directory=%s" % config.OUTPUT
    DVIPDFMX = "dvipdfmx"
    DVIPDFMX_OPTION=""

    config.latex_compile = " ".join([
        LATEX,
        "".join(["-interaction=nonstopmode -output-directory=", os.path.join(read_conf(), "misc", "templateTex", config.OUTPUT)]),
        os.path.join(read_conf(), "misc", "templateTex", "src", TARGET) + ".tex",
    ])

    config.dvi2pdf = " ".join([
        DVIPDFMX,
        DVIPDFMX_OPTION,
        "-o %s/%s.pdf" % (os.path.join(read_conf(), "result", config.def_cmp, "pdf"), config.def_ind),
        "%s/%s.dvi" % (os.path.join(read_conf(), "misc", "templateTex", config.OUTPUT), TARGET),
    ])

if __name__ in "__main__":
    read_interface()

    set_latex_compile()

    print(config.latex_compile)
    print(config.dvi2pdf)
