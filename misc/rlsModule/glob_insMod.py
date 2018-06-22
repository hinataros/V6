#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from check_superuserMod import check_superuser
from ins_modMod import install_module
from ins_pathMod import install_path

def global_installer():
    print("global install...")

    install_module()
    install_path()

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    global_installer()
