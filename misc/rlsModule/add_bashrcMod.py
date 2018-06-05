#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def add_bashrc():
    temp = ""
    ctemp = ""
    with open(os.path.join(os.environ['HOME'], ".bashrc"), "r", encoding="utf-8") as f:
        for line in f:
            if "#" not in line.strip():
                temp += line.strip()
            else:
                ctemp += line.strip()

    if config.PATH in temp:
        print("already passing through in bashrc")
    elif config.PATH in ctemp:
        print("Please remove comment out of path")
    elif config.PATH in ctemp:
        print("Please remove comment out of path")
    else:
        with open(os.path.join(os.environ['HOME'], ".bashrc"), "a", encoding="utf-8") as f:
            f.write(config.n+os.path.join(str("RLSBIN=")+config.RLS_DIR, "bin")+config.n+config.PATH)
        print("add in bashrc")

if __name__ == "__main__":
    add_bashrc()
