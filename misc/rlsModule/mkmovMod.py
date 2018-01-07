#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config
from myMod import readRegistry

AVCONV = "avconv"
OPTION = " ".join(["-an", "-vcodec", "libx264", "-pix_fmt", "yuv420p"])
VF = " ".join(["-vf", "'scale=trunc(iw/2)*2:trunc(ih/2)*2'"])

def mkmov():
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
        scene = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "src", ind, "scene%08d.png")
        output = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "".join([ind, ".mp4"]))

        avconv = " ".join([AVCONV, "-i", scene, OPTION, output])
        subprocess.call(avconv, shell=True)

    else:
        from argparse import ArgumentParser

        usage = "Usage: [-m model] [-c controller] [-cp composite data name] [-i individual data name] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("-m", "--model", type=str)
        parser.add_argument("-c", "--controller", type=str)
        parser.add_argument("-cp", "--cmp", type=str,)
        parser.add_argument("-i", "--i", type=str, nargs="*")
        parser.add_argument("-f", "--f",
                            action="store_true",
                            help="rescaling")

        args = parser.parse_args()

        if args.model:
            model = args.model
        if args.controller:
            controller = args.controller
        if args.cmp:
            cmp = args.cmp
        if args.i:
            for i in range(len(args.i)):
                scene = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "src", args.i[i], "scene%08d.png")
                output = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "".join([args.i[i], ".mp4"]))

                if args.f:
                    avconv = " ".join([AVCONV, "-i", scene, OPTION, VF, output])
                else:
                    avconv = " ".join([AVCONV, "-i", scene, OPTION, output])

                if os.path.exists(os.path.dirname(scene)):
                    subprocess.call(avconv, shell=True)
                else:
                    print("not found {}".format(os.path.dirname(scene)))

            sys.exit()

        scene = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "src", ind, "scene%08d.png")
        output = os.path.join(config.rgs_dir, "result", ":".join([controller, model]), cmp, "movie", "".join([ind, ".mp4"]))

        if args.f:
            avconv = " ".join([AVCONV, "-i", scene, OPTION, VF, output])
        else:
            avconv = " ".join([AVCONV, "-i", scene, OPTION, output])

        if os.path.exists(os.path.dirname(scene)):
            subprocess.call(avconv, shell=True)
        else:
            print("not found {}".format(os.path.dirname(scene)))

if __name__ == "__main__":
    mkmov()
