#include "RamLib.h"
#include "stdio.h"

float GetRamPercent(void) {
    float Usage;
    MEMORYSTATUSEX RamUsage;    //内存相关的结构体
    RamUsage.dwLength = sizeof(RamUsage);   //在使用内存相关的结构体的时候，必须进行初始化
    GlobalMemoryStatusEx(&RamUsage);        //获取当前内存信息的函数
    Usage = (float)(RamUsage.ullTotalPhys-RamUsage.ullAvailPhys)/RamUsage.ullTotalPhys;
    Usage *= 100; //换算成百分比
    return Usage;
}

//
// Created by Administrator on 2026/5/2.
//

