#!/usr/bin/python3

# @author Sho Miyahara 2017

import os

def check_superuser():
    USER = os.environ.get("USER")
    if USER == "root":
        return True
    else:
        return False

if __name__ == "__main__":
    print(check_superuser())
