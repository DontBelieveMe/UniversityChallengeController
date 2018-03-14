cmake_minimum_required(VERSION 2.7)
project(ucc)

set(source
    src/buzzlgc.c
    src/hdi.c
    src/main.c
)

set(headers
    src/buzz.h
    src/hdi.h
)

add_executable(ucc ${source} ${headers})
target_link_libraries(ucc wiringPi pthread)
