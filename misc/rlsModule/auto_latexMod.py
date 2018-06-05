#!/usr/bin/python3

# @author Sho Miyahara 2017

import time, os, sys
import subprocess

import config

from read_confMod import read_conf
from read_interfaceMod import read_interface

from set_latex_compileMod import set_latex_compile

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

class ChangeHandler(FileSystemEventHandler):
    # def on_create(self, event):
    #     if event.is_directory:
    #         return
    #     if match(event.src_path):
    #         build()

    def on_modified(self, event):
        if event.is_directory:
            return
        if os.path.basename(event.src_path) == "handler.flag":
            read_interface()
            setLatexCompile()
            subprocess.call(config.latex_compile, shell=True)
            subprocess.call(config.dvi2pdf, shell=True)

    # def on_deleted(self, event):
    #     if event.is_directory:
    #         return
    #     if match(event.src_path):
    #         build()

def auto_latex():
    event_handler = ChangeHandler()
    observer = Observer()
    observer.schedule(event_handler, os.path.join(read_conf(), "result"), recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        observer.stop()
        print("\nauto_latex stop...")
        observer.join()

if __name__ in "__main__":
    auto_latex()
