#!/usr/bin/python3

import os, sys

import config
from myMod import readRegistry
from myMod import readInterface

def setLatexCompile():
    TARGET = "result"
    LATEX = "platex"
    LATEX_OPTION = "-interaction=nonstopmode -output-directory=%s" % config.OUTPUT
    DVIPDFMX = "dvipdfmx"
    DVIPDFMX_OPTION=""

    config.latex_compile = " ".join([
        LATEX,
        "".join(["-interaction=nonstopmode -output-directory=", os.path.join(config.rgs_dir, "misc", "templateTex", config.OUTPUT)]),
        os.path.join(config.rgs_dir, "misc", "templateTex", "src", TARGET) + ".tex",
    ])


    config.dvi2pdf = " ".join([
        DVIPDFMX,
        DVIPDFMX_OPTION,
        "-o %s/%s.pdf" % (os.path.join(config.rgs_dir, "result", config.sim_controller+":"+config.sim_model, config.sim_data, "pdf"), config.sim_sub),
        "%s/%s.dvi" % (os.path.join(config.rgs_dir, "misc", "templateTex", config.OUTPUT), TARGET),
    ])

if __name__ in "__main__":
    readRegistry()
    readInterface()

    setLatexCompile()
