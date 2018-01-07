#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "rlsModule"))

import rlsModule

def setup():
    if not rlsModule.myMod.checkUsr():
        print("not super user")
        sys.exit()

    rlsModule.myMod.checkDir()

    if len(sys.argv) == 2:
        if sys.argv[1] == "install":
            rlsModule.insMod.install()
            rlsModule.lnkMod.lnk()

        elif sys.argv[1] == "register":
            rlsModule.registerMod.register()
            rlsModule.lnkMod.lnk()

        elif sys.argv[1] == "uninstall":
            rlsModule.uninsMod.uninstall()

        else:
            print("argument invalid")
    else:
        print("argument invalid")

if __name__ == "__main__":
    setup()
