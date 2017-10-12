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
    config.misc_dir = os.path.dirname(os.path.abspath(__file__))
    config.src_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    config.yaml_dir = os.path.join(config.src_dir, "yaml")

if __name__ == "__main__":
    print(checkUsr())
    checkDir()

