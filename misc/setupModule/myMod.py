#!/usr/bin/python3

import os
import config

def checkUsr():
    USER = os.environ.get("USER")
    if USER == "root":
        return True
    else:
        return False

def checkDir():
    config.mod_dir = os.path.dirname(os.path.abspath(__file__))
    config.src_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    config.home_dir = os.environ['HOME']

def readRegistry():
    with open(os.path.join(os.path.join(config.RLS_DIR, "rls.conf")), "r", encoding="utf-8") as f:
        for line in f:
            temp = line.strip()
            config.rgs_dir = temp.replace("src dir: ", "")

if __name__ == "__main__":
    print(checkUsr())
    checkDir()
    readRegistry()

