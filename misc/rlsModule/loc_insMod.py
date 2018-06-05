#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from check_superuserMod import check_superuser

from add_userMod import add_user
from add_bashrcMod import add_bashrc
from ins_confMod import install_conf
from ins_name4texMod import install_name4tex
from add_texMod import add_tex
from lnkMod import lnk

def local_installer():
    print("local install...")

    add_user()
    add_bashrc()
    install_conf()
    install_name4tex()
    add_tex()
    lnk()

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    from check_userMod import check_user
    check_user()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    local_installer()
