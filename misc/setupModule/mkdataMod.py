#!/usr/bin/python3

import sys

import config
from myMod import checkUsr

from dataConfigMod import makeData
from dataConfigMod import removeData
from dataConfigMod import removeDataTree

def mkdata():
    if checkUsr():
        print("not nomal user")
        sys.exit()

    if len(sys.argv) == 2 or len(sys.argv) == 3:
        if len(sys.argv) == 3:
            if sys.argv[1] == "-re":
                if not removeData(sys.argv[2]):
                    print("interrupted...")
                    sys.exit()

            elif sys.argv[1] == "-re0":
                if not removeDataTree():
                    print("interrupted...")
                    sys.exit()
            else:
                print("argument invalid")

            makeData(sys.argv[2])
            print("created {0} data tree...".format(sys.argv[2]))

        else:
            makeData(sys.argv[1])
            print("created {0} data tree...".format(sys.argv[1]))

    else:
        print("argument invalid")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    mkdata()
