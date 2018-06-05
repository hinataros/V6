#!/usr/bin/python3

# @author Sho Miyahara 2017

import os
import config

def check_src_dir():
    config.src_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    config.mod_dir = os.path.dirname(os.path.abspath(__file__))

if __name__ == "__main__":
    check_src_dir()

    print(config.src_dir)
    print(config.mod_dir)
