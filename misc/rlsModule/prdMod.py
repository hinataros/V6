#!/usr/bin/python3

# @author Sho Miyahara 2017

import os

import config
from myMod import readRegistry

def prd():
    print("registered dir: " + config.rgs_dir)

if __name__ == "__main__":
    readRegistry()

    prd()
