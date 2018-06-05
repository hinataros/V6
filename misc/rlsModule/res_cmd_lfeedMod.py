#!/usr/bin/python3

# @author Sho Miyahara 2017

#https://qiita.com/kentarosasaki/items/033751ba8b26cc51cf2a
import subprocess
def res_cmd_lfeed(cmd):
  return subprocess.Popen(
      cmd, stdout=subprocess.PIPE,
      shell=True).stdout.readlines()

if __name__ == "__main__":
    print(res_cmd_lfeed("ls -a"))
