cmake_minimum_required(VERSION 3.10)
project(Windowsapp C)

set(CMAKE_C_STANDARD 11)

# 头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/nvml)

# 可执行文件及源文件
add_executable(Windowsapp
        main.c
        RamLib.c
        DiskLib.c
        CPULib.c
        GPULib.c
)

# 链接库
target_link_libraries(Windowsapp
        ${CMAKE_SOURCE_DIR}/ThirdParty/nvml/nvml.lib
)