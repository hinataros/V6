#!/usr/bin/python3

import time, os, sys
import subprocess

import config
from myMod import readRegistry
from myMod import readInterface

from commandMod import setLatexCompile

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
            readInterface()
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
    observer.schedule(event_handler, os.path.join(config.rgs_dir, "result"), recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        observer.stop()
        print("\nauto_latex stop...")
        observer.join()

if __name__ in "__main__":
    readRegistry()

    auto_latex()
