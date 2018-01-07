#!/usr/bin/python3

# @author Sho Miyahara 2017

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

def readInterface():
    with open(os.path.join(config.rgs_dir, "result", "interface", "simInfo.tex"), "r", encoding="utf-8") as f:
        for line in f:
            if "model" in line.strip():
                temp = line.strip().replace("\def\model{", "")
                config.sim_model = temp.replace("}", "")
            elif "controller" in line.strip():
                temp = line.strip().replace("\def\controller{", "")
                config.sim_controller = temp.replace("}", "")
            elif "cmp" in line.strip():
                temp = line.strip().replace("\def\cmp{", "")
                config.sim_cmp = temp.replace("}", "")
            elif "ind" in line.strip():
                temp = line.strip().replace("\def\ind{", "")
                config.sim_ind = temp.replace("}", "")

if __name__ == "__main__":
    print(checkUsr())
    checkDir()
    readRegistry()
    readInterface()
