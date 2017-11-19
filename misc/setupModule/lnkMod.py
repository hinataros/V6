#!/usr/bin/python3

import os, sys

import config
from myMod import checkUsr
from myMod import readRegistry

def lnk():
    if not checkUsr():
        print("not super user")
        sys.exit()

    if os.path.exists(os.path.join(config.RLS_DIR, "sl")):
        print("already linked...")

        cmd=input("rewrite? [y/] ")
        if cmd == "y":
            import shutil
            shutil.rmtree(os.path.join(config.RLS_DIR, "sl"))
        else:
            print("interrupted...")
            sys.exit()

    os.makedirs(os.path.join(config.RLS_DIR, "sl"), exist_ok=True)

    readRegistry()

    try:
        os.symlink(os.path.join(config.rgs_dir, "result"), os.path.join(config.RLS_DIR, "sl", "result"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.rgs_dir, "share"), os.path.join(config.RLS_DIR, "sl", "share"))
    except FileExistsError:
        print("already exists")

    import glob
    config_yaml = glob.glob(os.path.join(config.rgs_dir, "yaml", "config", "*.conf"))
    os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "config"), exist_ok=True)
    for temp in config_yaml:
        try:
            os.symlink(temp, os.path.join(config.RLS_DIR, "sl", "yaml", "config", os.path.basename(temp)))
        except FileExistsError:
            print("already exists")

    model_yaml = glob.glob(os.path.join(config.rgs_dir, "yaml", "model", "*.model"))
    os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "model"), exist_ok=True)
    for temp in model_yaml:
        try:
            os.symlink(temp, os.path.join(config.RLS_DIR, "sl", "yaml", "model", os.path.basename(temp)))
        except FileExistsError:
            print("already exists")

    controller_dir = glob.glob(os.path.join(config.rgs_dir, "yaml", "work", "*"))
    for temp_c in controller_dir:
        os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "work", os.path.basename(temp_c)), exist_ok=True)

        work_yaml = glob.glob(os.path.join(temp_c, "*.work"))
        for temp_w in work_yaml:
            try:
                os.symlink(temp_w, os.path.join(config.RLS_DIR, "sl", "yaml", "work", os.path.basename(temp_c), os.path.basename(temp_w)))
            except FileExistsError:
                print("already exists")

    print("linked...")

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    lnk()
