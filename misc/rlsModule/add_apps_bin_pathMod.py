#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from check_superuserMod import check_superuser

def add_apps_bin_path():
    temp = ""
    ctemp = ""
    with open(config.SH, "r", encoding="utf-8") as f:
        for line in f:
            if "#" not in line.strip():
                temp += line.strip()
            else:
                ctemp += line.strip()

    if config.PATH in temp:
        print("already passing through in apps_bin_path")
    elif config.PATH in ctemp:
        print("Please remove comment out of path")
    elif config.PATH in ctemp:
        print("Please remove comment out of path")
    else:
        with open(config.SH, "a", encoding="utf-8") as f:
            f.write(config.n+os.path.join(str("RLSBIN=")+config.RLS_DIR, "bin")+config.n+config.PATH)
        print("add in add_apps_bin_path")

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    add_apps_bin_path()
