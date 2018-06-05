#!/usr/bin/python3

# @author Sho Miyahara 2017

import os
import config

from read_confMod import read_conf

def read_interface():
    path_simInfo = os.path.join(read_conf(), "result", "interface", "simInfo.tex")

    with open(path_simInfo, "r", encoding="utf-8") as f:
        for line in f:
            if "\\title" in line.strip():
                temp = line.strip().replace("\\def\\title{", "")
                config.def_title = temp.replace("}", "")
            elif "\\cmp" in line.strip():
                temp = line.strip().replace("\\def\\cmp{", "")
                config.def_cmp = temp.replace("}", "")
            elif "\\ind" in line.strip():
                temp = line.strip().replace("\\def\\ind{", "")
                config.def_ind = temp.replace("}", "")

if __name__ == "__main__":
    read_interface()

    print(config.def_title)
    print(config.def_cmp)
    print(config.def_ind)
