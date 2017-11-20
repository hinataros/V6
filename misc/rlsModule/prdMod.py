#!/usr/bin/python3

import os

import config
from myMod import readRegistry

def prd():
    print("registered dir: " + config.rgs_dir)

if __name__ == "__main__":
    readRegistry()

    prd()

