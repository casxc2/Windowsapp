cmake_minimum_required(VERSION 4.1)
project(Windowsapp C)

set(CMAKE_C_STANDARD 11)

add_executable(Windowsapp main.c
        RamLib.c
        RamLib.h
        DiskLib.h
        DiskLib.c)
