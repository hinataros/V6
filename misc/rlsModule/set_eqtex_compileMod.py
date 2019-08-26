#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from read_confMod import read_conf

from read_interfaceMod import read_interface

def set_eqtex_compile():
    TARGET = "equation"
    LATEX = "platex"
    BIBTEX = "bibtex"
    LATEX_OPTION = "-interaction=nonstopmode -output-directory=%s" % config.OUTPUT
    DVIPDFMX = "dvipdfmx"
    DVIPDFMX_OPTION=""

    config.eqtex_compile = " ".join([
        LATEX,
        "".join(["-interaction=nonstopmode -output-directory=", os.path.join(read_conf(), "misc", "templateEqTex", "src")]),
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".tex",
    ])
    # amiyata
    config.eqtex_compile_extract = " ".join([
        LATEX,
        "".join(["-interaction=nonstopmode -output-directory=", os.path.join(read_conf(), "misc", "templateEqTex", config.OUTPUT)]),
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".tex",
    ])
    config.bibtex_compile = " ".join([
        BIBTEX,
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".aux",
    ])
    config.remove_datas = " ".join([
        "rm -rf",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".aux",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".dvi",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".log",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".out",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".bbl",
        os.path.join(read_conf(), "misc", "templateEqTex", "src", TARGET) + ".blg",
    ])

    config.dvi2pdf = " ".join([
        DVIPDFMX,
        DVIPDFMX_OPTION,
        "-o %s/%s.pdf" % (os.path.join(read_conf(), "result", config.def_cmp, "eq"), config.def_ind),
        "%s/%s.dvi" % (os.path.join(read_conf(), "misc", "templateEqTex", config.OUTPUT), TARGET),
    ])

if __name__ in "__main__":
    read_interface()

    set_eqtex_compile()

    print(config.eqtex_compile)
    print(config.eqtex_compile_extract)
    print(config.remove_datas)
    print(config.bibtex_compile)
    print(config.dvi2pdf)
