#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from check_superuserMod import check_superuser

def add_user():
    os.makedirs(os.path.join(config.RLS_DIR, "user"), exist_ok=True)

    conf = os.path.join(config.home, ".config")
    try:
        os.symlink(conf, os.path.join(config.RLS_DIR, "user", config.uid))
        print("add {}".format(config.user))
    except FileExistsError:
        print("already added {}".format(config.user))

if __name__ == "__main__":
    if not check_superuser():
        print("not superuser")
        sys.exit()

    from check_userMod import check_user
    check_user()

    add_user()
