#!/usr/bin/python3

import os, sys

import config

def makeData(arg_cmp, arg_ind):
    import glob

    os.makedirs(os.path.join(config.rgs_dir, "result", "interface"), exist_ok=True)
    f = open(os.path.join(config.rgs_dir, "result", "interface", "handler.flag"),'w')
    f.close()

    for i in range(len(arg_ind)):
        controller_dir = glob.glob(os.path.join(config.rgs_dir, "yaml", "work", "*"))
        for temp_c in controller_dir:
            model_yaml = glob.glob(os.path.join(config.rgs_dir, "yaml", "model", "*.model"))
            for temp_m in model_yaml:
                name, ext = os.path.splitext(temp_m)
                temp = os.path.basename(temp_c) + str(":") + os.path.basename(name)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "dat", arg_ind[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "dat", arg_ind[i], "controller"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "dat", arg_ind[i], "gif"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "eps", arg_ind[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "eps", arg_ind[i], "controller"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "gif", arg_ind[i]), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "gp", arg_ind[i], "library"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "gp", arg_ind[i], "model"), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "gp", arg_ind[i], "controller"), exist_ok=True)

                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "pdf", "src", arg_ind[i]), exist_ok=True)
                os.makedirs(os.path.join(config.rgs_dir, "result", temp, arg_cmp, "movie", "src", arg_ind[i]), exist_ok=True)

def removeSubData(arg_cmp, arg_ind):
    for root_cmp, dirs_cmp, files_cmp in os.walk(os.path.join(config.rgs_dir, "result")):
        for dir_data in dirs_cmp:
            if dir_data == arg_cmp:
                root = root_cmp

                for i in range(len(arg_ind)):
                    cmd=input("delete <{}>:{}:{} directory? [y/] ".format(os.path.basename(root), arg_cmp,  arg_ind[i]))
                    if cmd == "y":
                        for root_ind, dirs_ind, files_ind in os.walk(os.path.join(root)):
                            for dir_ind in dirs_ind:
                                if dir_ind == arg_ind[i]:
                                    import shutil
                                    shutil.rmtree(os.path.join(root_ind, dir_ind))
                                    print("{} deleted...".format(os.path.join(root_ind, dir_ind)))

def removeSubDataTree(arg_cmp):
    for root, dirs, files in os.walk(os.path.join(config.rgs_dir, "result")):
        for dir in dirs:
            if dir == arg_cmp:
                cmd=input("delete <{}>:{} directory? [y/] ".format(os.path.basename(root), arg_cmp))
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
