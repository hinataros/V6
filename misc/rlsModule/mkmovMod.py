#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config

from check_superuserMod import check_superuser
from read_confMod import read_conf

AVCONV = "avconv"
OPTION = " ".join(["-an", "-vcodec", "libx264", "-pix_fmt", "yuv420p"])
VF = " ".join(["-vf", "'scale=trunc(iw/2)*2:trunc(ih/2)*2'"])

def mkmov():
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
        scene = os.path.join(dir_result, cmp, "movie", ind, "src", "scene%08d.png")
        output = os.path.join(dir_result, cmp, "movie", ind, "".join([ind, ".mp4"]))

        avconv = " ".join([AVCONV, "-i", scene, OPTION, output])
        subprocess.call(avconv, shell=True)

    else:
        from argparse import ArgumentParser

        usage = "Usage: [-n movie name] [-c composite result name] [-i individual result name] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("-n", "--n", type=str,)
        parser.add_argument("-c", "--c", type=str,)
        parser.add_argument("-i", "--i", type=str, nargs="*")
        parser.add_argument("-f", "--f",
                            action="store_true",
                            help="rescaling")

        args = parser.parse_args()

        if args.c:
            cmp = args.c
        if args.i:
            for i in range(len(args.i)):
                if args.n:
                    scene = os.path.join(dir_result, cmp, "movie", args.i[i], "src", args.n, "scene%08d.png")
                    output = os.path.join(dir_result, cmp, "movie", args.i[i], "".join([args.n, ".mp4"]))
                else:
                    scene = os.path.join(dir_result, cmp, "movie", args.i[i], "src", "scene%08d.png")
                    output = os.path.join(dir_result, cmp, "movie", "".join([args.i[i], ".mp4"]))

                if args.f:
                    avconv = " ".join([AVCONV, "-i", scene, OPTION, VF, output])
                else:
                    avconv = " ".join([AVCONV, "-i", scene, OPTION, output])

                if os.path.exists(os.path.dirname(scene)):
                    subprocess.call(avconv, shell=True)
                else:
                    print("not found {}".format(os.path.dirname(scene)))

            return 0

        if args.n:
            scene = os.path.join(dir_result, cmp, "movie", ind, "src", args.n, "scene%08d.png")
            output = os.path.join(dir_result, cmp, "movie", ind, "".join([args.n, ".mp4"]))
        else:
            scene = os.path.join(dir_result, cmp, "movie", ind, "src", "scene%08d.png")
            output = os.path.join(dir_result, cmp, "movie", ind, "".join([ind, ".mp4"]))

        if args.f:
            avconv = " ".join([AVCONV, "-i", scene, OPTION, VF, output])
        else:
            avconv = " ".join([AVCONV, "-i", scene, OPTION, output])

        if os.path.exists(os.path.dirname(scene)):
            subprocess.call(avconv, shell=True)
        else:
            print("not found {}".format(os.path.dirname(scene)))

if __name__ == "__main__":
    if check_superuser():
        print("not nomal user")
        sys.exit()

    mkmov()
