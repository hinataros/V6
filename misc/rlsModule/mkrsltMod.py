#!/usr/bin/python3

# @author Sho Miyahara 2017

import sys

import config

from check_superuserMod import check_superuser

from resultMod import make_result
from resultMod import remove_sub_result
from resultMod import remove_result_tree

def mkrslt():
    from argparse import ArgumentParser

    usage = "Usage: COMPOSITE_RESULT_NAME [-option] [-i individual result name] [--help]"\
            .format(__file__)
    parser = ArgumentParser(usage=usage)
    parser.add_argument("cmp", type=str,
                           help="composite result name")
    parser.add_argument("-re", "--re",
                           action="store_true",
                           help="remove")
    parser.add_argument("-re0", "--re0",
                           action="store_true",
                           help="remove")
    parser.add_argument("-i", "--i", required=True, nargs="*")

    args = parser.parse_args()

    if args.re0:
        if not remove_result_tree():
            print("interrupted...")
            return -1

    if args.re:
        remove_sub_result(args.cmp, args.i)

    make_result(args.cmp, args.i)

    print("generated result tree...")

if __name__ == "__main__":
    if check_superuser():
        print("not nomal user")
        sys.exit()

    mkrslt()
