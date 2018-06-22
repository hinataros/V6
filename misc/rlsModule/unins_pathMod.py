#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def uninstall_path():
    if not os.path.exists(config.SH):
        print("already uninstalled path...")
        return -1

    os.remove(config.SH)

if __name__ == "__main__":
    cmd=input("uninstall path? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        sys.exit()

    uninstall_path()
