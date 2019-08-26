#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config

from read_confMod import read_conf
from read_interfaceMod import read_interface

from set_eqtex_compileMod import set_eqtex_compile

def eqtex():
    os.makedirs(os.path.join(read_conf(), "misc", "templateEqTex", config.OUTPUT), exist_ok=True)

    from argparse import ArgumentParser
    usage = "Usage: [-t title name] [-c composite result name] [-i individual result name] [--help]"\
            .format(__file__)
    parser = ArgumentParser(usage=usage)
    parser.add_argument("-t", "--t", type=str,)
    parser.add_argument("-c", "--c", type=str,)
    parser.add_argument("-i", "--i", type=str, nargs="*")
    parser.add_argument("-f", "--f",
                        action="store_true",
                        help="rescaling")

    args = parser.parse_args()

    if len(sys.argv) == 1:
        set_eqtex_compile()
        subprocess.call(config.eqtex_compile, shell=True)
        subprocess.call(config.bibtex_compile, shell=True)
        subprocess.call(config.eqtex_compile, shell=True)
        subprocess.call(config.eqtex_compile_extract, shell=True)
        subprocess.call(config.dvi2pdf, shell=True)
        subprocess.call(config.remove_datas, shell=True)

        return 0

    path_simInfo = os.path.join(read_conf(), "result", "interface", "simInfo.tex")

    if args.t:
        config.def_title = args.t

        # ******** only -t ********
        if not args.i:
            with open(path_simInfo, "w", encoding="utf-8") as f:
                f.write("\\def\\title{"+config.def_title+"}\n")
                f.write("\\def\\cmp{"+config.def_cmp+"}\n")
                f.write("\\def\\ind{"+config.def_ind+"}\n")

            set_eqtex_compile()
            subprocess.call(config.eqtex_compile, shell=True)
            subprocess.call(config.bibtex_compile, shell=True)
            subprocess.call(config.eqtex_compile, shell=True)
            subprocess.call(config.eqtex_compile_extract, shell=True)
            subprocess.call(config.dvi2pdf, shell=True)
            subprocess.call(config.remove_datas, shell=True)

            return 0

    if args.c:
        config.def_cmp = args.c
    if args.i:
        for i in range(len(args.i)):
            config.def_ind = args.i[i]

            with open(path_simInfo, "w", encoding="utf-8") as f:
                f.write("\\def\\title{"+config.def_title+"}\n")
                f.write("\\def\\cmp{"+config.def_cmp+"}\n")
                f.write("\\def\\ind{"+config.def_ind+"}\n")
            # *************************************

            set_eqtex_compile()
            subprocess.call(config.eqtex_compile, shell=True)
            subprocess.call(config.bibtex_compile, shell=True)
            subprocess.call(config.eqtex_compile, shell=True)
            subprocess.call(config.eqtex_compile_extract, shell=True)
            subprocess.call(config.dvi2pdf, shell=True)
            subprocess.call(config.remove_datas, shell=True)

        return 0

    print("Please select individual result name by -i option")

if __name__ in "__main__":
    read_interface()

    eqtex()
