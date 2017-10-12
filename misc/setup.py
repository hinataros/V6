#!/usr/bin/python3

import os, sys
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "setupModule"))

import setupModule

def setup():
    if not setupModule.myMod.checkUsr():
        print("not super user")
        sys.exit()

    if len(sys.argv) == 2:
        if sys.argv[1] == "install":
            setupModule.insMod.install()
            setupModule.lnkMod.lnk()

        elif sys.argv[1] == "uninstall":
            setupModule.uninsMod.uninstall()

        else:
            print("argument invalid")
    else:
        print("argument invalid")

if __name__ == "__main__":
    setup()
