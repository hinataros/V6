#!/usr/bin/python3

import os, sys

import config

def makeData(arg):
    import glob

    controller_dir = glob.glob(os.path.join(config.rgs_dir, "yaml", "work", "*"))
    for temp_c in controller_dir:
        model_yaml = glob.glob(os.path.join(config.rgs_dir, "yaml", "model", "*.yaml"))
        for temp_m in model_yaml:
            name, ext = os.path.splitext(temp_m)
            temp = os.path.basename(temp_c) + str(":") + os.path.basename(name)
            os.makedirs(os.path.join(config.rgs_dir, "data", "dat", temp, arg, "model"), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "dat", temp, arg, "controller"), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "dat", temp, arg, "gif"), exist_ok=True)

            os.makedirs(os.path.join(config.rgs_dir, "data", "eps", temp, arg, "model"), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "eps", temp, arg, "controller"), exist_ok=True)
            f = open(os.path.join(config.rgs_dir, "data", "eps", "eps.flag"),'w')
            f.close()

            os.makedirs(os.path.join(config.rgs_dir, "data", "gif", temp, arg), exist_ok=True)

            os.makedirs(os.path.join(config.rgs_dir, "data", "gp", temp, arg, "library"), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "gp", temp, arg, "model"), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "gp", temp, arg, "controller"), exist_ok=True)

            os.makedirs(os.path.join(config.rgs_dir, "data", "pdf", temp, "src", arg), exist_ok=True)
            os.makedirs(os.path.join(config.rgs_dir, "data", "movie", temp), exist_ok=True)

def removeData(arg):
    cmd=input("delete {0} directory? [y/] ".format(arg))

    if cmd == "y":
        for root, dirs, files in os.walk(os.path.join(config.rgs_dir, "data")):
            for dir in dirs:
                if dir == arg:
                    import shutil
                    shutil.rmtree(os.path.join(root, dir))
                    print("{0} deleted...".format(os.path.join(root, dir)))
        return True
    else:
        return False

def removeDataTree():
    cmd=input("delete data tree? [y/] ")

    if cmd == "y":
        try:
            import shutil
            shutil.rmtree(os.path.join(config.rgs_dir, "data"))
            print("{0} deleted...".format(os.path.join(config.rgs_dir, "data")))
        except OSError:
            print("already deleted")

        return True
    else:
        return False

if __name__ == "__main__":
    from myMod import checkDir
    checkDir()

    from myMod import readRegistry
    readRegistry()

    if len(sys.argv) == 3:
        if sys.argv[1] == "makeData":
            makeData(sys.argv[2])
            print("created {0} data tree...".format(sys.argv[2]))

        elif sys.argv[1] == "removeData":
            removeData(sys.argv[2])

        else:
            print("argument invalid")

    if len(sys.argv) == 2:
        if sys.argv[1] == "removeDataTree":
                removeDataTree()

        else:
            print("argument invalid")
    else:
        print("argument invalid")
