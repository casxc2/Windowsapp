cmake_minimum_required(VERSION 3.10)   # 修正版本号，CMake 没有 4.1
project(Windowsapp C)

set(CMAKE_C_STANDARD 11)

# 1. 添加头文件搜索路径（这样项目里任何地方都能直接 #include "nvml.h"）
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/nvml)

# 2. 可执行文件 + 源文件（头文件不用列进去）
add_executable(Windowsapp
        main.c
        RamLib.c
        RamLib.h
        DiskLib.c
        DiskLib.h
        CPULib.c
        CPULib.h
        GPULib.c                # 如果你已经有 gpu.c，可以直接加在这里
        GPULib.h
)

# 3. 链接 nvml.lib
target_link_libraries(Windowsapp
        ${CMAKE_SOURCE_DIR}/ThirdParty/nvml/nvml.lib
)