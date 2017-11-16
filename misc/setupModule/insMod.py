#!/usr/bin/python3

import os, sys

import config
from registerMod import register

from myMod import checkUsr

def install():
    if not checkUsr():
        print("not super user")
        sys.exit()

    if os.path.isdir(config.RLS_DIR):
        print("already installed...")
    else:
        import shutil
        os.makedirs(os.path.join(config.RLS_DIR, "bin"), exist_ok=True)

        try:
            shutil.copytree(config.mod_dir, os.path.join(config.RLS_DIR, "module", "setupModule"))
        except FileExistsError:
            print("already installed setup module...")

        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "lnkMod.py"), os.path.join(config.RLS_DIR, "bin", "lnk"))
        except FileExistsError:
            print("already exists")
        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "unlnkMod.py"), os.path.join(config.RLS_DIR, "bin", "unlnk"))
        except FileExistsError:
            print("already exists")

        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "mkdataMod.py"), os.path.join(config.RLS_DIR, "bin", "mkdata"))
        except FileExistsError:
            print("already exists")
        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "rmdataMod.py"), os.path.join(config.RLS_DIR, "bin", "rmdata"))
        except FileExistsError:
            print("already exists")

        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "auto_latexMod.py"), os.path.join(config.RLS_DIR, "bin", "atex"))
        except FileExistsError:
            print("already exists")
        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "mkmovMod.py"), os.path.join(config.RLS_DIR, "bin", "mkmov"))
        except FileExistsError:
            print("already exists")

        try:
            os.symlink(os.path.join(config.RLS_DIR, "module", "setupModule", "prdMod.py"), os.path.join(config.RLS_DIR, "bin", "prd"))
        except FileExistsError:
            print("already exists")

        temp = ""
        ctemp = ""
        with open(config.SH, "r", encoding="utf-8") as f:
            for line in f:
                if "#" not in line.strip():
                    temp += line.strip()
                else:
                    ctemp += line.strip()

        if config.PATH in temp:
            print("Already passing through")
        elif config.PATH in ctemp:
            print("Please remove comment out of path")
        else:
            with open(config.SH, "a", encoding="utf-8") as f:
                f.write(config.n+os.path.join(str("RLSBIN=")+config.RLS_DIR, "bin")+config.n+config.PATH)

        temp = ""
        ctemp = ""
        with open(os.path.join(config.home_dir, ".bashrc"), "r", encoding="utf-8") as f:
            for line in f:
                if "#" not in line.strip():
                    temp += line.strip()
                else:
                    ctemp += line.strip()

        if config.PATH in temp:
            print("Already passing through")
        elif config.PATH in ctemp:
            print("Please remove comment out of path")
        else:
            with open(os.path.join(config.home_dir, ".bashrc"), "a", encoding="utf-8") as f:
                f.write(config.n+os.path.join(str("RLSBIN=")+config.RLS_DIR, "bin")+config.n+config.PATH)

    register()

    print("installed...")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    install()
