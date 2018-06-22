#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from check_superuserMod import check_superuser
from unins_pathMod import uninstall_path
# not implement
# from unins_modMod import uninstall_module

def global_uninstaller():
    cmd=input("uninstall core? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        return -1

    print("global uninstall...")

    uninstall_path()

    # uninstall_module()
    if not os.path.exists(config.RLS_DIR):
        print("already uninstalled module...")
        return -1

    import shutil
    shutil.rmtree(config.RLS_DIR)
    print("uninstall module...")

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    global_uninstaller()
