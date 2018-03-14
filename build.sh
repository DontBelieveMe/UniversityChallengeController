# To build the program use `sh build.sh` in the root directory
# Run's CMake to generate the project files (aka makefiles most likely) and then uses CMake
# to build the code.

cmake -H. -Bbuild
cmake --build build
