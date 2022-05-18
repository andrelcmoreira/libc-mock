#!/bin/sh

LD_PRELOAD=./src/libc-mock.so $1
