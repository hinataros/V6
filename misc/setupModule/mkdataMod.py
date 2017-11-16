#!/usr/bin/python3

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

    usage = "Usage: DATA_NAME [-option] [-sub simulation name] [--help]"\
            .format(__file__)
    parser = ArgumentParser(usage=usage)
    parser.add_argument("data", type=str,
                           help="data name")
    parser.add_argument("-re", "--re",
                           action="store_true",
                           help="remove")
    parser.add_argument("-re0", "--re0",
                           action="store_true",
                           help="remove")
    parser.add_argument("-sub", "--sub", required=True, nargs="*")

    args = parser.parse_args()

    if args.re0:
        if not removeDataTree():
            print("interrupted...")
            sys.exit()

    if args.re:
        removeSubData(args.data, args.sub)

    makeData(args.data, args.sub)

if __name__ == "__main__":
    mkdata()
