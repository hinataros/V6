#!/usr/bin/python3

import os, sys

import config
from myMod import checkUsr
from myMod import readRegistry

def lnk():
    if not checkUsr():
        print("not super user")
        sys.exit()

    if os.path.exists(os.path.join(config.RLS_DIR, "sl")):
        print("already linked...")

        cmd=input("rewrite? [y/] ")
        if cmd == "y":
            import shutil
            shutil.rmtree(os.path.join(config.RLS_DIR, "sl"))
        else:
            print("interrupted...")
            sys.exit()

    os.makedirs(os.path.join(config.RLS_DIR, "sl"), exist_ok=True)

    readRegistry()

    try:
        os.symlink(os.path.join(config.rgs_dir, "result"), os.path.join(config.RLS_DIR, "sl", "result"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.rgs_dir, "share"), os.path.join(config.RLS_DIR, "sl", "share"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.rgs_dir, "yaml"), os.path.join(config.RLS_DIR, "sl", "yaml"))
    except FileExistsError:
        print("already exists")

    print("linked...")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    lnk()
