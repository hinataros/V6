#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def install_name4tex():
    path = os.path.join(config.home, ".config", "rlsSimulator", "name.tex")

    with open(path, "w", encoding="utf-8") as f:
        f.write("\\def\\name{" + config.name +"}\n")

    os.chown(path, int(config.uid), int(config.gid))

    print("install name for tex...")

if __name__ == "__main__":
    from check_userMod import check_user
    check_user()

    from check_src_dirMod import check_src_dir
    check_src_dir()

    install_name4tex()
