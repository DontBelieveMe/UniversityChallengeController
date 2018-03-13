# This is the main build file, because I cannot be bothered to write a proper makefile
# To build the program use `sh build.sh` in the root directory

cmake -H. -Bbuild
cmake --build build
