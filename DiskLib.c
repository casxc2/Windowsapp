#include "DiskLib.h"
#include <stdio.h>

void GetDiskV(void) {
    ULARGE_INTEGER totalBytes,totalFreeBytes;   //总空间和剩余空间的结构体，这是存64位数据的结构体
    float GFree,Guse;                           //记录总空间和剩余空间

    /*C盘信息的获取*/
    GetDiskFreeSpaceEx("C:\\",NULL,
        &totalBytes,&totalFreeBytes);   //获取磁盘总空间和剩余空间的函数GFree = (float)(totalFreeBytes.QuadPart/(1024.0*1024*1024));
    GFree = totalFreeBytes.QuadPart/(1024.0*1024*1024);
    printf("C: Free :%.1fG, ",GFree);
    Guse = (float)((totalBytes.QuadPart - totalFreeBytes.QuadPart)/(1024.0*1024*1024));
    printf("USe :%.1fG, ",Guse);
    printf("Total :%.1fG\r\n",(float)(totalBytes.QuadPart/(1024.0*1024*1024)));

    /*D盘信息的获取*/
    GetDiskFreeSpaceEx("D:\\",NULL,
        &totalBytes,&totalFreeBytes);   //获取磁盘总空间和剩余空间的函数GFree = (float)(totalFreeBytes.QuadPart/(1024.0*1024*1024));
    GFree = totalFreeBytes.QuadPart/(1024.0*1024*1024);
    printf("D: Free :%.1fG, ",GFree);
    Guse = (float)((totalBytes.QuadPart - totalFreeBytes.QuadPart)/(1024.0*1024*1024));
    printf("USe :%.1fG, ",Guse);
    printf("Total:%.1fG\r\n",(float)(totalBytes.QuadPart/(1024.0*1024*1024)));

}

//
// Created by Administrator on 2026/5/2.
//