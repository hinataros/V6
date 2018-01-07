#!/usr/bin/python3

# @author Sho Miyahara 2017

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

            sys.exit()

    from argparse import ArgumentParser
    usage = "Usage: [-m model] [-c controller] [-cp composite data name] [-i individual data name] [--help]"\
            .format(__file__)
    parser = ArgumentParser(usage=usage)
    parser.add_argument("-m", "--model", type=str)
    parser.add_argument("-c", "--controller", type=str)
    parser.add_argument("-cp", "--cmp", type=str,)
    parser.add_argument("-i", "--ind", type=str, nargs="*")
    parser.add_argument("-f", "--f",
                        action="store_true",
                        help="rescaling")

    args = parser.parse_args()

    readInterface()
    if len(sys.argv) == 1:
        setLatexCompile()
        subprocess.call(config.latex_compile, shell=True)
        subprocess.call(config.dvi2pdf, shell=True)

    else:
        if args.model:
            config.sim_model = args.model
        if args.controller:
            config.sim_controller = args.controller
        if args.cmp:
            config.sim_cmp = args.cmp
        if args.ind:
            for i in range(len(args.ind)):
                config.sim_ind = args.ind[i]
                setLatexCompile()
                subprocess.call(config.latex_compile, shell=True)
                subprocess.call(config.dvi2pdf, shell=True)

            sys.exit()

        setLatexCompile()
        subprocess.call(config.latex_compile, shell=True)
        subprocess.call(config.dvi2pdf, shell=True)
