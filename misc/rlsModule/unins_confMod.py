#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def uninstall_conf():
    # local = os.path.join("/home/"+str(config.sudo_user), ".config", "rlsSimulator")
    local = os.path.join(os.environ['HOME'], ".config", "rlsSimulator")

    if not os.path.exists(local):
        print("already uninstalled conf...")
        return -1

    import shutil
    shutil.rmtree(local)

if __name__ == "__main__":
    cmd=input("uninstall conf? [y/] ")
    if cmd != "y" and cmd != "":
        print("interrupted...")
        sys.exit()

    uninstall_conf()
