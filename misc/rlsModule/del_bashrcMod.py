#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

import config

def del_bashrc():
    temp = ""
    with open(os.path.join(os.environ['HOME'], ".bashrc"), "r", encoding="utf-8") as f:
        for line in f:
            if config.PATH and "RLSBIN" not in line:
                temp += line.rstrip() + config.n

        with open(os.path.join(os.environ['HOME'], ".bashrc"), "w", encoding="utf-8") as f:
            f.write(temp[:-1])

    print("deleted in bashrc...")

if __name__ == "__main__":
    del_bashrc()
