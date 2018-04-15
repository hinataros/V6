#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import subprocess

import config
from myMod import readRegistry

def runCnoid():
    readRegistry()

    if len(sys.argv) == 1:
        print("argument invalid...")
        sys.exit()

    elif len(sys.argv) == 2:
        path_cnoid = os.path.join(config.rgs_dir, "share", "project", "".join([sys.argv[1], ".cnoid"]))
        run = " ".join([config.run_cnoid, path_cnoid])

    else:
        from argparse import ArgumentParser

        usage = "Usage: cnoid name [-t max time] [-g gravity] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("cnoid", type=str,
                            help="cnoid name")
        parser.add_argument("-t", "--t", type=str)
        parser.add_argument("-g", "--g", type=str)

        args = parser.parse_args()
        path_cnoid = os.path.join(config.rgs_dir, "share", "project", "".join([args.cnoid, ".cnoid"]))
        run = " ".join([config.run_cnoid, path_cnoid])

        if not os.path.exists(os.path.join(path_cnoid)):
            print("Not found {}.cnoid".format(args.cnoid))
            sys.exit()

        if args.t or args.g:
            cmd=input("rewrite? [y/] ")
            if cmd != "y":
                print("interrupted...")
                sys.exit()

            temp=""
            with open(path_cnoid, "r", encoding="utf-8") as f:
                for line in f:
                    if "maxTime:" in line:
                        temp1 = line.strip()
                        temp2 = line
                        time = temp1.replace("maxTime: ","")
                        if args.t:
                            hoge = temp2.replace(time, args.t)
                            temp += hoge
                        else:
                            temp += line
                    elif "gravity: [" in line:
                        temp1 = line.strip()
                        temp2 = line
                        gravity = temp1.replace("gravity: ","")
                        if args.g:
                            hoge = temp2.replace(gravity, "[ 0, 0, "+args.g+" ]")
                            temp += hoge
                        else:
                            temp += line
                    else:
                        temp += line

        with open(path_cnoid, "w", encoding="utf-8") as f:
            f.write(temp)

    try:
        subprocess.call(run, shell=True)
    except KeyboardInterrupt:
        print("keyboard interupt...")
        # import traceback
        # traceback.print_exc()

if __name__ == "__main__":
    runCnoid()
