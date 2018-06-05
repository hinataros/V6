#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config

from read_confMod import read_conf
from read_interfaceMod import read_interface

from set_latex_compileMod import set_latex_compile

def actex():
    os.makedirs(os.path.join(read_conf(), "misc", "templateTex", config.OUTPUT), exist_ok=True)

    if len(sys.argv) == 2:
        if sys.argv[1] == "start":
            from auto_latexMod import auto_latex

            print("auto_latex start...")
            auto_latex()

            return 0

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
        set_latex_compile()

        subprocess.call(config.latex_compile, shell=True)
        subprocess.call(config.dvi2pdf, shell=True)

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

            set_latex_compile()
            subprocess.call(config.latex_compile, shell=True)
            subprocess.call(config.dvi2pdf, shell=True)

            return 0

    if args.c:
        config.def_cmp = args.c
    if args.i:
        for i in range(len(args.i)):
            config.def_ind = args.i[i]

            # smiyahara: ind毎に聞かれるのが億劫
            # *************************************
            # cmd=input("rewrite simInfo? [y/] ")
            # if cmd == "y":
            #     with open(os.path.join(config.rgs_dir, "result", "interface", "simInfo.tex"), "w", encoding="utf-8") as f:
            #         f.write("\def\cmp{"+config.def_cmp+"}\n")
            #         f.write("\def\ind{"+config.def_ind+"}\n")

            #         print("{} rewrote...".format(os.path.join(config.rgs_dir, "result", "interface", "simInfo.tex")))

            # else:
            #     readInterface()

            # without confirmation
            # *************************************
            with open(path_simInfo, "w", encoding="utf-8") as f:
                f.write("\\def\\title{"+config.def_title+"}\n")
                f.write("\\def\\cmp{"+config.def_cmp+"}\n")
                f.write("\\def\\ind{"+config.def_ind+"}\n")
            # *************************************

            set_latex_compile()
            subprocess.call(config.latex_compile, shell=True)
            subprocess.call(config.dvi2pdf, shell=True)

        return 0

    print("Please select individual result name by -i option")

if __name__ in "__main__":
    read_interface()

    actex()
