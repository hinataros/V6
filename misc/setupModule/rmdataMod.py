#!/usr/bin/python3

import sys

from myMod import checkUsr

from dataConfigMod import removeData
from dataConfigMod import removeDataTree

def rmdata():
    if checkUsr():
        print("not nomal user")
        sys.exit()

    if len(sys.argv) == 2:
        if not removeData(sys.argv[1]):
            print("interrupted...")
            sys.exit()

    elif len(sys.argv) == 1:
        if not removeDataTree():
            print("interrupted...")
            sys.exit()
    else:
        print("argument invalid")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    rmdata()
