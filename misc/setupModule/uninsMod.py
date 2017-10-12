#!/usr/bin/python3

import sys

import config
from myMod import checkUsr
from dataConfigMod import removeDataTree

def uninstall():
    if not checkUsr():
        print("not super user")
        sys.exit()

    cmd=input("uninstall? [y/] ")
    if cmd == "y":
        removeDataTree()

        with open(config.SH, "r", encoding="utf-8") as f:
            for line in f:
                if config.PATH and "RLSBIN" not in line:
                    config.temp += line.rstrip() + config.n

            with open(config.SH, "w", encoding="utf-8") as f:
                f.write(config.temp[:-1])

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
