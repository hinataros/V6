#!/usr/bin/python3

import os, sys

import config
from myMod import checkUsr
from myMod import checkDir

def install():
    if not checkUsr():
        print("not super user")
        sys.exit()

    checkDir()
    os.makedirs(os.path.join(config.RLS_DIR, "bin"), exist_ok=True)

    with open(config.SH, "r", encoding="utf-8") as f:
        for line in f:
            if "#" not in line.strip():
                config.temp += line.strip()
            else:
                config.ctemp += line.strip()

    if config.PATH in config.temp:
        print("Already passing through")
    elif config.PATH in config.ctemp:
        print("Please remove comment out of path")
    else:
        with open(config.SH, "a", encoding="utf-8") as f:
            f.write(config.n+os.path.join(str("RLSBIN=")+config.RLS_DIR, "bin")+config.n+config.PATH)

    try:
        os.symlink(os.path.join(config.misc_dir, "lnkMod.py"), os.path.join(config.RLS_DIR, "bin", "lnk"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.misc_dir, "unlnkMod.py"), os.path.join(config.RLS_DIR, "bin", "unlnk"))
    except FileExistsError:
        print("already exists")

    try:
        os.symlink(os.path.join(config.misc_dir, "mkdataMod.py"), os.path.join(config.RLS_DIR, "bin", "mkdata"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.misc_dir, "rmdataMod.py"), os.path.join(config.RLS_DIR, "bin", "rmdata"))
    except FileExistsError:
        print("already exists")

    print("installed...")

if __name__ == "__main__":
    install()
