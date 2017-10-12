#!/usr/bin/python3

import os, sys

import config
from myMod import checkUsr
from myMod import checkDir
from dataConfigMod import removeDataTree

def uninstall():
    if not checkUsr():
        print("not super user")
        sys.exit()

    checkDir()
    cmd=input("uninstall? [y/] ")
    if cmd == "y":
        removeDataTree()

        temp = ""
        with open(config.SH, "r", encoding="utf-8") as f:
            for line in f:
                if config.PATH and "RLSBIN" not in line:
                    temp += line.rstrip() + config.n

            with open(config.SH, "w", encoding="utf-8") as f:
                f.write(temp[:-1])

        temp = ""
        with open(os.path.join(config.home_dir, ".bashrc"), "r", encoding="utf-8") as f:
            for line in f:
                if config.PATH and "RLSBIN" not in line:
                    temp += line.rstrip() + config.n

            with open(os.path.join(config.home_dir, ".bashrc"), "w", encoding="utf-8") as f:
                f.write(temp[:-1])

        try:
            import shutil
            shutil.rmtree(config.RLS_DIR)
        except OSError:
            print("already uninstalled")

        print("uninstalled...")

    else:
        print("interrupted...")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    uninstall()
