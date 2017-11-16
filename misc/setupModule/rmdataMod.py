#!/usr/bin/python3

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

        usage = "Usage: DATA_NAME [-option] [-sub simulation name] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("data", type=str, help="data name")
        parser.add_argument("-sub", "--sub", nargs="*")

        args = parser.parse_args()

        if args.sub:
            removeSubData(args.data, args.sub)

    else:
        if not removeDataTree():
            print("interrupted...")
            sys.exit()

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    rmdata()
