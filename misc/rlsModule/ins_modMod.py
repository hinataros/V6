#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
import shutil

from check_superuserMod import check_superuser

def install_module():
    dir_rlsmod = os.path.join(config.RLS_DIR, "module", "rlsModule")

    if os.path.exists(dir_rlsmod):
        print("already module installed...")

        cmd=input("reinstall module? [y/] ")
        if cmd != "y" and cmd != "":
            print("interrupted...")
            return -1

        shutil.rmtree(dir_rlsmod)
        print("{} deleted...".format(dir_rlsmod))

    # try:
    shutil.copytree(config.mod_dir, dir_rlsmod)
    # except FileExistsError:
    #     print("already installed module...")

    if not os.path.exists(os.path.join(config.RLS_DIR, "bin")):
        os.makedirs(os.path.join(config.RLS_DIR, "bin"), exist_ok=True)
    else:
        shutil.rmtree(os.path.join(config.RLS_DIR, "bin"))
        os.makedirs(os.path.join(config.RLS_DIR, "bin"))

    os.symlink(os.path.join(dir_rlsmod, "mkrsltMod.py"), os.path.join(config.RLS_DIR, "bin", "mkrslt"))
    os.symlink(os.path.join(dir_rlsmod, "rmrsltMod.py"), os.path.join(config.RLS_DIR, "bin", "rmrslt"))

    os.symlink(os.path.join(dir_rlsmod, "runcnoidMod.py"), os.path.join(config.RLS_DIR, "bin", "runcnoid"))

    os.symlink(os.path.join(dir_rlsmod, "mkgrhMod.py"), os.path.join(config.RLS_DIR, "bin", "mkgrh"))
    os.symlink(os.path.join(dir_rlsmod, "actexMod.py"), os.path.join(config.RLS_DIR, "bin", "actex"))
    os.symlink(os.path.join(dir_rlsmod, "mkmovMod.py"), os.path.join(config.RLS_DIR, "bin", "mkmov"))

    os.symlink(os.path.join(dir_rlsmod, "rwhoMod.py"), os.path.join(config.RLS_DIR, "bin", "rwho"))
    os.symlink(os.path.join(dir_rlsmod, "prdMod.py"), os.path.join(config.RLS_DIR, "bin", "prd"))

    print("installed module...")

if __name__ == "__main__":
    if not check_superuser():
        print("not superuser")
        sys.exit()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    install_module()
