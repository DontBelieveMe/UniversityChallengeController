# This is the main build file, because I cannot be bothered to write a proper makefile
# To build the program use `sh build.sh` in the root directory

/usr/bin/c99 src/main.c src/hdi.c src/buzzlgc.c -obin/a.out -lwiringPi
