#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from check_superuserMod import check_superuser

def del_user():
    sl = os.path.join(config.RLS_DIR, "user", config.uid)
    if not os.path.exists(sl):
        print("already deleted {}".format(config.user))
        return -1

    os.unlink(sl)
    print("delete {}".format(config.user))

if __name__ == "__main__":
    if not check_superuser():
        print("not superuser")
        sys.exit()

    cmd=input("delete user? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        sys.exit

    from check_userMod import check_user
    check_user()

    del_user()
