#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def install_conf():
    local = os.path.join(config.home, ".config", "rlsSimulator")
    os.makedirs(local, exist_ok=True)
    os.chown(local, int(config.uid), int(config.gid))

    path = os.path.join(local, "rls.conf")

    if os.path.exists(path):
        print("already installed conf...")
        cmd=input("{} reconfigure? [y/] ".format(config.user))
        if cmd != "y" and cmd != "":
            print("interrupted...")
            sys.exit()

        print("{} rewrote...".format(path))

    with open(path, "w", encoding="utf-8") as f:
        f.write("src dir: " + config.src_dir +"\n")

    os.chown(path, int(config.uid), int(config.gid))

    path = os.path.join(local, "name.tex")
    with open(path, "w", encoding="utf-8") as f:
        f.write("\\def\\name{" + config.name +"}\n")

    os.chown(path, int(config.uid), int(config.gid))

    print("install conf...")

if __name__ == "__main__":
    from check_userMod import check_user
    check_user()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    install_conf()
