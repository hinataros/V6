#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config
from check_superuserMod import check_superuser
from unlnkMod import unlnk
from unins_confMod import uninstall_conf
from del_userMod import del_user

def local_uninstaller():
    print("local uninstall...")

    unlnk()
    uninstall_conf()
    del_user()

if __name__ == "__main__":
    if not check_superuser():
        print("not super user")
        sys.exit()

    from check_userMod import check_user
    check_user()

    local_uninstaller()
