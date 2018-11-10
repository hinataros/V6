#!/usr/bin/python3

# @author Sho Miyahara 2017

import os, sys

from read_confMod import read_conf

def make_result(arg_cmp, arg_ind):
    dir_result = os.path.join(read_conf(), "result")

    os.makedirs(os.path.join(dir_result, "interface"), exist_ok=True)
    f = open(os.path.join(dir_result, "interface", "handler.flag"),'w')
    f.close()

    for i in range(len(arg_ind)):
        if os.path.exists(os.path.join(dir_result, arg_cmp, "dat", arg_ind[i])):
            print("already exists '{}'".format(arg_ind[i]))
            cmd=input("overwrite '{}': '{}' directory? [n/] ".format(arg_cmp,  arg_ind[i]))
            if cmd == "y":
                import shutil
                # ****************************************************************
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "dat", arg_ind[i]))
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "eps", arg_ind[i]))
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "gp", arg_ind[i]))
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "gif", arg_ind[i]))
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "pdf", "src", arg_ind[i]))
                shutil.rmtree(os.path.join(dir_result, arg_cmp, "movie", arg_ind[i]))
                print("'{}' deleted...".format(arg_ind[i]))
            else:
                print("interrupted...")

        # ****************************************************************
        os.makedirs(os.path.join(dir_result, arg_cmp, "dat", arg_ind[i]), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "eps", arg_ind[i]), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "gp", arg_ind[i], "library"), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "gp", arg_ind[i], "src"), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "gif", arg_ind[i]), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "pdf", "src", arg_ind[i]), exist_ok=True)
        os.makedirs(os.path.join(dir_result, arg_cmp, "movie", arg_ind[i], "src"), exist_ok=True)

def remove_sub_result(arg_cmp, arg_ind):
    dir_result = os.path.join(read_conf(), "result")

    for root_cmp, dirs_cmp, files_cmp in os.walk(dir_result):
        for dir_result in dirs_cmp:
            if dir_result == arg_cmp:
                root = root_cmp

                for i in range(len(arg_ind)):
                    cmd=input("delete '{}': '{}' directory? [y/] ".format(arg_cmp,  arg_ind[i]))
                    if cmd == "y" or cmd == "":
                        for root_ind, dirs_ind, files_ind in os.walk(os.path.join(root)):
                            for dir_ind in dirs_ind:
                                if dir_ind == arg_ind[i]:
                                    import shutil
                                    shutil.rmtree(os.path.join(root_ind, dir_ind))
                                    print("'{}' deleted...".format(os.path.join(root_ind, dir_ind)))

def remove_sub_result_tree(arg_cmp):
    dir_result = os.path.join(read_conf(), "result")

    for root, dirs, files in os.walk(dir_result):
        for dir in dirs:
            if dir == arg_cmp:
                cmd=input("delete '{}' directory? [y/] ".format(arg_cmp))
                if cmd == "y" or cmd == "":
                    import shutil
                    shutil.rmtree(os.path.join(root, dir))
                    print("'{}' deleted...".format(os.path.join(root, dir)))

def remove_result_tree():
    cmd=input("delete 'result' tree? [y/] ")

    if cmd == "y" or cmd == "":
        dir_result = os.path.join(read_conf(), "result")
        try:
            import shutil
            shutil.rmtree(dir_result)
            print("'{0}' deleted...".format(dir_result))
        except OSError:
            print("already deleted")

        return True
    else:
        return False
