#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from check_superuserMod import check_superuser

def install_path():
    if os.path.exists(config.SH):
        print("already path installed...")

        cmd=input("reinstall path? [y/] ")
        if cmd != "y" and cmd != "":
            print("interrupted...")
            return -1

    with open(config.SH, "w", encoding="utf-8") as f:
        f.write(os.path.join(str("RLS_BIN=")+config.RLS_DIR, "bin")+"\n"+config.PATH)

    print("installed path...")

if __name__ == "__main__":
    if not check_superuser():
        print("not superuser")
        sys.exit()

    install_path()
