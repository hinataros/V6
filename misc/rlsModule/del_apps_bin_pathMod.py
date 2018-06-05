#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from check_superuserMod import check_superuser

def del_apps_bin_path():
    temp = ""
    with open(config.SH, "r", encoding="utf-8") as f:
        for line in f:
            if config.PATH and "RLSBIN" not in line:
                temp += line.rstrip() + config.n

        with open(config.SH, "w", encoding="utf-8") as f:
            f.write(temp[:-1])

    print("deleted in apps_bin_path...")

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    del_apps_bin_path()
