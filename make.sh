#!/bin/sh

rm main
gcc main.c load.c telnet.c -o main

./main
