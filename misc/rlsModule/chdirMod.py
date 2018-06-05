#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from ins_confMod import install_conf
from add_texMod import add_tex
from lnkMod import lnk

def chdir():
    print("change directory...")

    install_conf()
    lnk()

if __name__ == "__main__":
    from check_userMod import check_user
    check_user()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    chdir()
