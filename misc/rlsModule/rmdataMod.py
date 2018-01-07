#!/usr/bin/python3

# @author Sho Miyahara 2017

import sys

from myMod import checkUsr

from dataConfigMod import removeSubData
from dataConfigMod import removeSubDataTree
from dataConfigMod import removeDataTree
from myMod import readRegistry

def rmdata():
    if checkUsr():
        print("not nomal user")
        sys.exit()

    readRegistry()

    if len(sys.argv) != 1:
        from argparse import ArgumentParser

        usage = "Usage: COMPOSITE_DATA_NAME [-option] [-i individual data name] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("cmp", type=str, help="composite data name")
        parser.add_argument("-i", "--i", nargs="*")

        args = parser.parse_args()

        if args.i:
            removeSubData(args.cmp, args.i)
            sys.exit()

        removeSubDataTree(args.cmp)

    else:
        if not removeDataTree():
            print("interrupted...")
            sys.exit()

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    rmdata()
