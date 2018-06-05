#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys
import shutil

import config

from check_superuserMod import check_superuser

from res_cmd_lfeedMod import res_cmd_lfeed

def local_recursive_uninstaller():
    cmd=input("_/_/ all user _/_/ uninstall? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        return -1

    dir = os.path.join(config.RLS_DIR, "user")
    if not os.path.exists(dir):
        print("already unsintalled all user...")
        return -1

    for line_user in os.listdir(dir):
        dir_local = os.path.join(dir,line_user, "rlsSimulator")
        if os.path.exists(dir_local):
            shutil.rmtree(dir_local)
        for line_passwd in res_cmd_lfeed("cat /etc/passwd"):
            if os.path.basename(line_user) == str(line_passwd).split(":")[2]:
                home = str(line_passwd).split(":")[5].replace("b'", "")

        temp = ""
        with open(os.path.join(home, ".bashrc"), "r", encoding="utf-8") as f:
            for line in f:
                if config.PATH and "RLSBIN" not in line:
                    temp += line.rstrip() + config.n

            with open(os.path.join(home, ".bashrc"), "w", encoding="utf-8") as f:
                f.write(temp[:-1])

        os.unlink(os.path.join(dir,line_user))

    print("uninstalled all user...")

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    local_recursive_uninstaller()
