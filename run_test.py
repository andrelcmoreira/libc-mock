#!/usr/bin/python

from os import system
from sys import argv

if __name__ == "__main__":
    system('LD_PRELOAD=./lib/libpreload.so {}'.format(argv[1]))
