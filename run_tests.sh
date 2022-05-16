#!/bin/sh

LD_PRELOAD=./lib/libc-mock.so $1
