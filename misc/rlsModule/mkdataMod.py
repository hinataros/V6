#!/usr/bin/python3

# @author Sho Miyahara 2017

import sys

import config
from myMod import checkUsr
from myMod import readRegistry

from dataConfigMod import makeData
from dataConfigMod import removeSubData
from dataConfigMod import removeSubDataTree
from dataConfigMod import removeDataTree

def mkdata():
    if checkUsr():
        print("not nomal user")
        sys.exit()

    readRegistry()

    from argparse import ArgumentParser

    usage = "Usage: COMPOSITE_DATA_NAME [-option] [-i individual data name] [--help]"\
            .format(__file__)
    parser = ArgumentParser(usage=usage)
    parser.add_argument("cmp", type=str,
                           help="composite data name")
    parser.add_argument("-re", "--re",
                           action="store_true",
                           help="remove")
    parser.add_argument("-re0", "--re0",
                           action="store_true",
                           help="remove")
    parser.add_argument("-i", "--i", required=True, nargs="*")

    args = parser.parse_args()

    if args.re0:
        if not removeDataTree():
            print("interrupted...")
            sys.exit()

    if args.re:
        removeSubData(args.cmp, args.i)

    makeData(args.cmp, args.i)

    print("generated data tree...")

if __name__ == "__main__":
    mkdata()
