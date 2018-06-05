#!/usr/bin/python3

# @author Sho Miyahara 2017

import os

import config

from res_cmd_lfeedMod import res_cmd_lfeed

def rwho():
    for line_user in os.listdir(os.path.join(config.RLS_DIR, "user")):
        for line_passwd in res_cmd_lfeed("cat /etc/passwd"):
            if line_user == str(line_passwd).split(":")[2]:
                print(str(line_passwd).split(":")[0].replace("b'", ""))

if __name__ == "__main__":
    rwho()
