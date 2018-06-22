#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

from read_confMod import read_conf

def add_tex():
    tex = os.path.join(read_conf(), "misc", "templateTex", "src", "result.tex")

    temp = ""
    with open(tex, "r", encoding="utf-8") as f:
        for line in f:
            if "\\def\\user" in line:
                temp += "\\def\\user{"+str(config.uid)+"}"+"\n"
            else:
                temp += line

        with open(tex, "w", encoding="utf-8") as f:
            f.write(temp)

    print("add in template tex...")

if __name__ == "__main__":
    from check_userMod import check_user
    check_user()

    add_tex()
