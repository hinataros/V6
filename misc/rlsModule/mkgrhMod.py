#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config

from check_superuserMod import check_superuser
from read_confMod import read_conf

def mkgrh():
    dir_result = os.path.join(read_conf(), "result")

    with open(os.path.join(dir_result, "interface", "simInfo.tex"), "r", encoding="utf-8") as f:
        for line in f:
            if "\\cmp" in line.strip():
                temp = line.strip().replace("\\def\\cmp{", "")
                cmp = temp.replace("}", "")
            elif "\\ind" in line.strip():
                temp = line.strip().replace("\\def\\ind{", "")
                ind = temp.replace("}", "")

    if len(sys.argv) == 1:
        gp = os.path.join(dir_result, cmp, "gp", ind, "main.gp")

        gnuplot = " ".join(["gnuplot", gp])
        subprocess.call(gnuplot, shell=True)

    else:
        from argparse import ArgumentParser

        usage = "Usage: [-c composite result name] [-i individual result name]  [-gp any gp file] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("-c", "--c", type=str,)
        parser.add_argument("-i", "--i", type=str, nargs="*")
        parser.add_argument("-gp", "--gp", type=str, nargs="*")

        args = parser.parse_args()

        if args.c:
            cmp = args.c

        # ******** case of -i ********
        if args.i:
            for i in range(len(args.i)):
                if args.gp:
                    for j in range(len(args.gp)):
                        gp = os.path.join(dir_result, cmp, "gp", args.i[i], "src", "".join([args.gp[j], ".gp"]))
                        gnuplot = " ".join(["gnuplot", gp])
                        subprocess.call(gnuplot, shell=True)

                else:
                    gp = os.path.join(dir_result, cmp, "gp", args.i[i], "main.gp")
                    gnuplot = " ".join(["gnuplot", gp])
                    subprocess.call(gnuplot, shell=True)

            with open(os.path.join(dir_result, "interface", "handler.flag"), "w", encoding="utf-8") as f:
                f.write("")

            return 0

        # ******** no -i ********
        if args.gp:
            for i in range(len(args.gp)):
                gp = os.path.join(dir_result, cmp, "gp", ind, "src", "".join([args.gp[i], ".gp"]))
                gnuplot = " ".join(["gnuplot", gp])
                subprocess.call(gnuplot, shell=True)

            with open(os.path.join(dir_result, "interface", "handler.flag"), "w", encoding="utf-8") as f:
                f.write("")

            return 0

        # ******** cmp only ********
        gp = os.path.join(dir_result, cmp, "gp", ind, "main.gp")
        gnuplot = " ".join(["gnuplot", gp])
        subprocess.call(gnuplot, shell=True)

        with open(os.path.join(dir_result, "interface", "handler.flag"), "w", encoding="utf-8") as f:
            f.write("")

        return 0

    with open(os.path.join(dir_result, "interface", "handler.flag"), "w", encoding="utf-8") as f:
        f.write("")

if __name__ == "__main__":
    if check_superuser():
        print("not nomal user")
        sys.exit()

    mkgrh()
