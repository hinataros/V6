#!/usr/bin/python3

# @author Sho Miyahara 2017

import sys

from check_superuserMod import check_superuser

from resultMod import remove_sub_result
from resultMod import remove_sub_result_tree
from resultMod import remove_result_tree

def rmrslt():
    if len(sys.argv) != 1:
        from argparse import ArgumentParser

        usage = "Usage: COMPOSITE_RESULT_NAME [-option] [-i individual result name] [--help]"\
                .format(__file__)
        parser = ArgumentParser(usage=usage)
        parser.add_argument("cmp", type=str, help="composite data name")
        parser.add_argument("-i", "--i", nargs="*")

        args = parser.parse_args()

        if args.i:
            remove_sub_result(args.cmp, args.i)
            return 0

        remove_sub_result_tree(args.cmp)

    else:
        if not remove_result_tree():
            print("interrupted...")
            return -1

if __name__ == "__main__":
    if check_superuser():
        print("not nomal user")
        sys.exit()

    rmrslt()
