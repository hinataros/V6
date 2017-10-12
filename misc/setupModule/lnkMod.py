#!/usr/bin/python3

import os, sys

import config
from myMod import checkUsr

def lnk():
    if not checkUsr():
        print("not super user")
        sys.exit()

    os.makedirs(os.path.join(config.RLS_DIR, "sl"), exist_ok=True)

    try:
        os.symlink(os.path.join(config.src_dir, "data"), os.path.join(config.RLS_DIR, "sl", "data"))
    except FileExistsError:
        print("already exists")
    try:
        os.symlink(os.path.join(config.src_dir, "share"), os.path.join(config.RLS_DIR, "sl", "share"))
    except FileExistsError:
        print("already exists")

    import glob
    config_yaml = glob.glob(os.path.join(config.yaml_dir, "config", "*.yaml"))
    os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "config"), exist_ok=True)
    for temp in config_yaml:
        try:
            os.symlink(temp, os.path.join(config.RLS_DIR, "sl", "yaml", "config", os.path.basename(temp)))
        except FileExistsError:
            print("already exists")

    model_yaml = glob.glob(os.path.join(config.yaml_dir, "model", "*.yaml"))
    os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "model"), exist_ok=True)
    for temp in model_yaml:
        try:
            os.symlink(temp, os.path.join(config.RLS_DIR, "sl", "yaml", "model", os.path.basename(temp)))
        except FileExistsError:
            print("already exists")

    controller_dir = glob.glob(os.path.join(config.yaml_dir, "work", "*"))
    for temp_c in controller_dir:
        os.makedirs(os.path.join(config.RLS_DIR, "sl", "yaml", "work", os.path.basename(temp_c)), exist_ok=True)

        work_yaml = glob.glob(os.path.join(temp_c, "*.yaml"))
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
