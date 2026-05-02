#include <stdio.h>
#include <windows.h>
#include "RamLib.h"

int main(void) {
    ULARGE_INTEGER totalBytes,totalFreeBytes;   //总空间和剩余空间
    float GFree,Guse;
    GetDiskFreeSpaceEx("C:\\",NULL,
        &totalBytes,&totalFreeBytes);   //获取磁盘总空间和剩余空间的函数
    GFree = (float)(totalFreeBytes.QuadPart/(1024.0*1024*1024));
    printf("Free :%.1fG\r\n",GFree);
    Guse = (float)((totalBytes.QuadPart - totalFreeBytes.QuadPart)/(1024.0*1024*1024));
    printf("USe :%.1fG\r\n",Guse);
    printf("Total :%.1fG\r\n",(float)(totalBytes.QuadPart/(1024.0*1024*1024)));

    return 0;
}