#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from myMod import checkUsr

def register():
    if not checkUsr():
        print("not super user")
        sys.exit()

    if os.path.exists(os.path.join(config.RLS_DIR, "rls.conf")):
        print("already registered...")

        cmd=input("rewrite? [y/] ")
        if cmd != "y":
            print("interrupted...")
            sys.exit()

    with open(os.path.join(os.path.join(config.RLS_DIR, "rls.conf")), "w", encoding="utf-8") as f:
        f.write("src dir: " + config.src_dir)


if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    register()
