#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

from read_confMod import read_conf

def lnk():
    sl = os.path.join(os.environ['HOME'], ".config", "rlsSimulator", "sl")

    if os.path.exists(sl):
        print("already linked...")

        cmd=input("relink? [y/] ")
        if cmd != "y" and cmd != "":
            print("interrupted...")
            return -1

        os.unlink(sl)

    os.symlink(read_conf(), os.path.join(sl))

    from check_superuserMod import check_superuser
    if check_superuser():
        import config
        from check_userMod import check_user
        check_user()
        os.chown(sl, int(config.uid), int(config.gid), follow_symlinks=False)

    print("linked...")

if __name__ == "__main__":
    lnk()
