#!/usr/bin/python3

import os, sys

import config

def makeData(arg_data, arg_sub):
    import glob

    os.makedirs(os.path.join(config.rgs_dir, "result", "interface"), exist_ok=True)
    f = open(os.path.join(config.rgs_dir, "result", "interface", "handler.flag"),'w')
    f.close()

    for i in range(len(arg_sub)):
        controller_dir = glob.glob(os.path.join(config.rgs_dir, "yaml", "work", "*"))
        for temp_c in controller_dir:
            model_yaml = glob.glob(os.path.join(config.rgs_dir, "yaml", "model", "*.yaml"))
            for temp_m in model_yaml:
                name, ext = os.path.splitext(temp_m)
                temp = os.path.basename(temp_c) + str(":") + os.path.basename(name)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "dat", arg_sub[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "dat", arg_sub[i], "controller"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "dat", arg_sub[i], "gif"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "eps", arg_sub[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "eps", arg_sub[i], "controller"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "gif", arg_sub[i]), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "gp", arg_sub[i], "library"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "gp", arg_sub[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "gp", arg_sub[i], "controller"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "pdf", "src", arg_sub[i]), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_data, "movie", "src", arg_sub[i]), exist_ok=True)

def removeSubData(arg_data, arg_sub):
    for root_data, dirs_data, files_data in os.walk(os.path.join(config.rgs_dir, "result")):
        for dir_data in dirs_data:
            if dir_data == arg_data:
                root = root_data

                for i in range(len(arg_sub)):
                    cmd=input("delete <{}>:{}:{} directory? [y/] ".format(os.path.basename(root), arg_data,  arg_sub[i]))
                    if cmd == "y":
                        for root_sub, dirs_sub, files_sub in os.walk(os.path.join(root)):
                            for dir_sub in dirs_sub:
                                if dir_sub == arg_sub[i]:
                                    import shutil
                                    shutil.rmtree(os.path.join(root_sub, dir_sub))
                                    print("{} deleted...".format(os.path.join(root_sub, dir_sub)))

def removeSubDataTree(arg_data):
    for root, dirs, files in os.walk(os.path.join(config.rgs_dir, "result")):
        for dir in dirs:
            if dir == arg_data:
                cmd=input("delete <{}>:{} directory? [y/] ".format(os.path.basename(root), arg_data))
                if cmd == "y":
                    import shutil
                    shutil.rmtree(os.path.join(root, dir))
                    print("{} deleted...".format(os.path.join(root, dir)))

def removeDataTree():
    cmd=input("delete data tree? [y/] ")

    if cmd == "y":
        try:
            import shutil
            shutil.rmtree(os.path.join(config.rgs_dir, "result"))
            print("{0} deleted...".format(os.path.join(config.rgs_dir, "result")))
        except OSError:
            print("already deleted")

        return True
    else:
        return False
