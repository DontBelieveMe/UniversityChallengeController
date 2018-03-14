cmake_minimum_required(VERSION 2.7)
project(ucc)

set(source
    src/buzzlgc.c
    src/hdi.c
    src/main.c
)

set(headers
    include/buzz/buzz.h
    include/buzz/hdi.h
)

add_definitions(-std=c99)
include_directories(include)

add_executable(ucc ${source} ${headers})

target_link_libraries(ucc wiringPi pthread)
