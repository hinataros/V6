#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config
from myMod import readRegistry

def mkgrh():
    readRegistry()

    with open(os.path.join(config.rgs_dir, "result", "interface", "simInfo.tex"), "r", encoding="utf-8") as f:
        for line in f:
            if "model" in line.strip():
                temp = line.strip().replace("\def\model{", "")
                model = temp.replace("}", "")
            elif "controller" in line.strip():
                temp = line.strip().replace("\def\controller{", "")
                controller = temp.replace("}", "")
            elif "cmp" in line.strip():
                temp = line.strip().replace("\def\cmp{", "")
                cmp = temp.replace("}", "")
            elif "ind" in line.strip():
                temp = line.strip().replace("\def\ind{", "")
                ind = temp.replace("}", "")

    if len(sys.argv) == 1:
        mgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "model.gp")
        cgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "controller.gp")

        gnuplot = " ".join(["gnuplot", mgp])
        subprocess.call(gnuplot, shell=True)
        gnuplot = " ".join(["gnuplot", cgp])
        subprocess.call(gnuplot, shell=True)

    else:
        from argparse import ArgumentParser

        usage = "Usage: [-m model] [-c controller] [-cp composite data name] [-i individual data name]  [-mgp model gp file] [-cgp controller gp file] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("-m", "--model", type=str)
        parser.add_argument("-c", "--controller", type=str)
        parser.add_argument("-cp", "--cmp", type=str,)
        parser.add_argument("-i", "--i", type=str, nargs="*")
        parser.add_argument("-mgp", "--mgp", type=str, nargs="*")
        parser.add_argument("-cgp", "--cgp", type=str, nargs="*")

        args = parser.parse_args()

        if args.model:
            model = args.model
        if args.controller:
            controller = args.controller
        if args.cmp:
            cmp = args.cmp
        if args.i:
            for i in range(len(args.i)):
                if args.mgp:
                    if len(args.mgp) == 1 and args.mgp[0] == "all":
                        mgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", args.i[i], "model.gp")
                        gnuplot = " ".join(["gnuplot", mgp])
                        subprocess.call(gnuplot, shell=True)

                    else:
                        for j in range(len(args.mgp)):
                            mgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", args.i[i], "model", "".join([args.mgp[j], ".gp"]))
                            gnuplot = " ".join(["gnuplot", mgp])
                            subprocess.call(gnuplot, shell=True)

                if args.cgp:
                    if len(args.cgp) == 1 and args.cgp[0] == "all":
                        cgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", args.i[i], "controller.gp")
                        gnuplot = " ".join(["gnuplot", cgp])
                        subprocess.call(gnuplot, shell=True)

                    else:
                        for j in range(len(args.cgp)):
                            cgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", args.i[i], "controller", "".join([args.cgp[j], ".gp"]))
                            gnuplot = " ".join(["gnuplot", cgp])
                            subprocess.call(gnuplot, shell=True)

            with open(os.path.join(config.rgs_dir, "result", "interface", "handler.flag"), "w", encoding="utf-8") as f:
                f.write("")

            sys.exit()

        if args.mgp:
            if len(args.mgp) == 1 and args.mgp[0] == "all":
                mgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "model.gp")
                gnuplot = " ".join(["gnuplot", mgp])
                subprocess.call(gnuplot, shell=True)

            else:
                for j in range(len(args.mgp)):
                    mgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "model", "".join([args.mgp[j], ".gp"]))
                    gnuplot = " ".join(["gnuplot", mgp])
                    subprocess.call(gnuplot, shell=True)

        if args.cgp:
            if len(args.cgp) == 1 and args.cgp[0] == "all":
                cgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "controller.gp")
                gnuplot = " ".join(["gnuplot", cgp])
                subprocess.call(gnuplot, shell=True)

            else:
                for j in range(len(args.cgp)):
                    cgp = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "gp", ind, "controller", "".join([args.cgp[j], ".gp"]))
                    gnuplot = " ".join(["gnuplot", cgp])
                    subprocess.call(gnuplot, shell=True)

    with open(os.path.join(config.rgs_dir, "result", "interface", "handler.flag"), "w", encoding="utf-8") as f:
        f.write("")

if __name__ == "__main__":
    mkgrh()
