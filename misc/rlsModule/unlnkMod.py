#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def unlnk():
    sl = os.path.join(os.environ['HOME'], ".config", "rlsSimulator", "sl")

    if not os.path.exists(sl):
        print("already unlinked")
        return -1

    os.unlink(sl)

    print("unlinked...")

if __name__ == "__main__":
    cmd=input("unlink? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        sys.exit()

    unlnk()
