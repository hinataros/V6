#!/usr/bin/python3

import time, os, sys
import subprocess

import config
from myMod import readRegistry

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

observed_file_type = (
    ".flag"
)

TARGET = "result"
LATEX = "platex"
OUTPUT = "build"
LATEX_OPTION = "-interaction=nonstopmode -output-directory=%s" % OUTPUT
DVIPDFMX = "dvipdfmx"
DVIPDFMX_OPTION=""

readRegistry()
with open(os.path.join(config.rgs_dir, "result", "interface", "simInfo.tex"), "r", encoding="utf-8") as f:
    for line in f:
        if "model" in line.strip():
            temp = line.strip().replace("\def\model{", "")
            model = temp.replace("}", "")
        elif "controller" in line.strip():
            temp = line.strip().replace("\def\controller{", "")
            controller = temp.replace("}", "")
        elif "data" in line.strip():
            temp = line.strip().replace("\def\data{", "")
            data = temp.replace("}", "")
        elif "sub" in line.strip():
            temp = line.strip().replace("\def\sub{", "")
            sub = temp.replace("}", "")

latex_compile = " ".join([
    LATEX,
    "".join(["-interaction=nonstopmode -output-directory=", os.path.join(config.rgs_dir, "misc", "templateTex", OUTPUT)]),
    os.path.join(config.rgs_dir, "misc", "templateTex", "src", TARGET) + ".tex",
])


dvi2pdf = " ".join([
    DVIPDFMX,
    DVIPDFMX_OPTION,
    "-o %s/%s.pdf" % (os.path.join(config.rgs_dir, "result", controller+":"+model, data, "pdf"), sub),
    "%s/%s.dvi" % (os.path.join(config.rgs_dir, "misc", "templateTex", OUTPUT), TARGET),
])

def match(path):
    return os.path.basename(path) == "handler.flag"
    # return any([path.endswith(ft) for ft in observed_file_type])


def build():
    subprocess.call(latex_compile, shell=True)
    subprocess.call(dvi2pdf, shell=True)


class ChangeHandler(FileSystemEventHandler):
    # def on_create(self, event):
    #     if event.is_directory:
    #         return
    #     if match(event.src_path):
    #         build()

    def on_modified(self, event):
        if event.is_directory:
            return
        if match(event.src_path):
            build()

    # def on_deleted(self, event):
    #     if event.is_directory:
    #         return
    #     if match(event.src_path):
    #         build()


if __name__ in "__main__":
    os.makedirs(os.path.join(config.rgs_dir, "misc", "templateTex", OUTPUT), exist_ok=True)

    if len(sys.argv) == 2:
        if sys.argv[1] == "start":
            print("auto_latex start...")

            event_handler = ChangeHandler()
            observer = Observer()
            observer.schedule(event_handler, os.path.join(config.rgs_dir, "result"), recursive=True)
            observer.start()
            try:
                while True:
                    time.sleep(0.1)
            except KeyboardInterrupt:
                observer.stop()
                print("\nauto_latex stop...")
                observer.join()
        else:
            print("argument invalid...")

    elif len(sys.argv) == 1:
        build()

    else:
        print("argument invalid...")
