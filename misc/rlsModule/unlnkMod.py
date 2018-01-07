#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from myMod import checkUsr

def unlnk():
    if not checkUsr():
        print("not super user")
        sys.exit()

    cmd=input("unlink? [y/] ")
    if cmd == "y":
        try:
            import shutil
            shutil.rmtree(os.path.join(config.RLS_DIR, "sl"))
            sys.exit()
        except OSError:
            print("already unlinked")

        print("unlinked...")

    else:
        print("interrupted...")

if __name__ == "__main__":
    unlnk()
