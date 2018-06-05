#!/usr/bin/python3

# @author Sho Miyahara 2017

import os
import config

from check_superuserMod import check_superuser

from res_cmd_lfeedMod import res_cmd_lfeed

def check_user():
    if os.path.exists(os.path.join("/etc/lsb-release")):
        if check_superuser():
            config.user = os.environ.get("SUDO_USER")
            config.uid = os.environ.get("SUDO_UID")
            config.gid = os.environ.get("SUDO_GID")
        else:
            config.user = os.environ.get("USER")
            config.uid = os.getuid()
            config.gid = os.getgid()

        for line in res_cmd_lfeed("cat /etc/passwd"):
            if config.user in str(line):
                config.name = str(line).split(":")[4].replace(",", "")
                config.home = str(line).split(":")[5]

        if config.name == "":
            print("no such user name...")
            return False

    else:
        flag = -1
        config.user=input("user name: ")
        for line in res_cmd_lfeed("cat /etc/passwd"):
            if user in str(line):
                config.uid = str(line).split(":")[2]
                config.gid = str(line).split(":")[3]
                config.name = str(line).split(":")[4].replace(",", "")
                config.home = str(line).split(":")[5]
                flag = 0

        if flag == -1:
            print("no such user name...")
            return False

    return True
if __name__ == "__main__":
    print(check_user())
    if(check_user()):
        print(config.user)
        print(config.uid)
        print(config.gid)
        print(config.name)
        print(config.home)
