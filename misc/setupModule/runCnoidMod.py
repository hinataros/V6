#!/usr/bin/python3

import os, sys
import subprocess

import config
from myMod import readRegistry

command = "bin/choreonoid"

def runCnoid():
    readRegistry()

    if len(sys.argv) == 2:
        path_cnoid = os.path.join(config.rgs_dir, "share", "project", "".join([sys.argv[1], ".cnoid"]))
        run = " ".join([command, path_cnoid])
        try:
            subprocess.call(run, shell=True)
        except KeyboardInterrupt:
            print("keyboard interupt...")
            # import traceback
            # traceback.print_exc()
    else:
        print("argument invalid...")

if __name__ == "__main__":
    runCnoid()
