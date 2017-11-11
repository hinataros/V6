#!/usr/bin/python3

import time, os, sys
import subprocess

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

observed_file_type = (
    ".flag"
)

DATA_DIR = "/usr/local/etc/rls/sl/data"
TARGET = "result"
LATEX = "platex"
OUTPUT = "build"
LATEX_OPTION = "-interaction=nonstopmode -output-directory=%s" % OUTPUT
DVIPDFMX = "dvipdfmx"
DVIPDFMX_OPTION=""

base = os.path.join(DATA_DIR,"eps")

model=""
controller=""
sim=""

latex_compile=""
dvi2pdf=""

def read():
    global base
    global model
    global controller
    global sim

    with open(os.path.join(DATA_DIR, "pdf", "interface.tex"), "r", encoding="utf-8") as f:
        for line in f:
            if "model" in line.strip():
                temp = line.strip().replace("\def\model{", "")
                model = temp.replace("}", "")
            elif "controller" in line.strip():
                temp = line.strip().replace("\def\controller{", "")
                controller = temp.replace("}", "")
            elif "sim" in line.strip():
                temp = line.strip().replace("\def\sim{", "")
                sim = temp.replace("}", "")

def set_command():
    global latex_compile
    global dvi2pdf

    latex_compile = " ".join([
        LATEX,
        LATEX_OPTION,
        os.path.join("src", TARGET) + ".tex",
    ])

    dvi2pdf = " ".join([
        DVIPDFMX,
        DVIPDFMX_OPTION,
        "-o %s/%s.pdf" % (os.path.join(DATA_DIR, "pdf", controller+":"+model), sim),
        "%s/%s.dvi" % (OUTPUT, TARGET),
    ])


def match(path):
    return any([path.endswith(ft) for ft in observed_file_type])


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
            read()
            set_command()

            build()

    # def on_deleted(self, event):
    #     if event.is_directory:
    #         return
    #     if match(event.src_path):
    #         build()


if __name__ in "__main__":
    os.makedirs("build", exist_ok=True)

    if len(sys.argv) == 2:
        if sys.argv[1] == "start":
            print("auto_latex start...")

            event_handler = ChangeHandler()
            observer = Observer()
            observer.schedule(event_handler, base, recursive=True)
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
        read()
        set_command()

        build()

    else:
        print("argument invalid...")
