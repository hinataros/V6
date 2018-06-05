#!/usr/bin/python3

# @author Sho Miyahara 2017

import os

import config

from read_confMod import read_conf

def prd():
    print(read_conf())

if __name__ == "__main__":
    prd()
