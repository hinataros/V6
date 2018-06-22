#!/usr/bin/python3

# @author Sho Miyahara 2018

import os, sys
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "rlsModule"))

import rlsModule

def setup():
    if len(sys.argv) == 2:
        if sys.argv[1] == "install":
            if not rlsModule.check_superuserMod.check_superuser():
                print("not super user")
                return -1

            rlsModule.check_src_dirMod.check_src_dir()
            rlsModule.glob_insMod.global_installer()

            rlsModule.check_userMod.check_user()
            rlsModule.loc_insMod.local_installer()

        elif sys.argv[1] == "insmod":
            if not rlsModule.check_superuserMod.check_superuser():
                print("not super user")
                return -1

            rlsModule.check_src_dirMod.check_src_dir()
            from rlsModule.ins_modMod import install_module
            install_module()

        elif sys.argv[1] == "useradd":
            if not rlsModule.check_superuserMod.check_superuser():
                print("not super user")
                return -1

            rlsModule.check_userMod.check_user()
            rlsModule.check_src_dirMod.check_src_dir()
            rlsModule.loc_insMod.local_installer()

        elif sys.argv[1] == "chdir":
            rlsModule.check_userMod.check_user()
            rlsModule.check_src_dirMod.check_src_dir()
            rlsModule.chdirMod.chdir()

        elif sys.argv[1] == "userdel":
            if not rlsModule.check_superuserMod.check_superuser():
                print("not super user")
                return -1

            rlsModule.check_userMod.check_user()
            from rlsModule.loc_uninsMod import local_uninstaller
            local_uninstaller()

        elif sys.argv[1] == "uninstall":
            if not rlsModule.check_superuserMod.check_superuser():
                print("not super user")
                return -1

            rlsModule.loc_rec_uninsMod.local_recursive_uninstaller()
            rlsModule.glob_uninsMod.global_uninstaller()

        else:
            print("argument invalid")
    else:
        print("argument invalid")

if __name__ == "__main__":
    setup()
