#!/bin/sh

rm main
gcc main.c load.c static.c telnet.c -o main

./main
