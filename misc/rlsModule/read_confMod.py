#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

def read_conf():
    path = os.path.join(os.environ['HOME'], ".config", "rlsSimulator", "rls.conf")

    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            if "src dir:" in line:
                dir = line.strip().split(":")[1].strip()

    return dir

if __name__ == "__main__":
    read_conf()
