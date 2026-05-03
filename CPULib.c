
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



/*存储上一次采样到的时间*/
static ULARGE_INTEGER lastIdleTime;     //64位结构体，用来存储数据的，存储空闲时间
static ULARGE_INTEGER lastKernelTime;   //存储内核占用的时间
static ULARGE_INTEGER lastUserTime;     //存储用户占用的时间
static BOOL isFirstRun = TRUE;

/* CPU利用率是（内核时间+用户时间）/总时间
 * 总时间是内核时间+用户时间+空闲时间
 * 使用此函数的时候记得屏蔽掉输出0的情况
 */
float GetCpuUsagePercent(void) {
    FILETIME idleTIme,kernelTime,userTime;      /*FILETIME是存储CPU从开机到现在跑了多长时间的
                                                  结构体，和ULARGE_INTEGER一样，存64位数据*/

    ULARGE_INTEGER curIdleTime,curKernelTime,curUserTime;
    ULONGLONG totalTimeDiff,idleTimeDiff;       //这个数据类型是存储64位无符号整数的
    double cpuusage;

    /* 这个函数会提取出来三个时间，内核时间，用户时间，空闲时间，空闲时间只存在在内核态，用户态没有空闲时间
     * 内核时间包括内核忙碌的时间和内核空闲的时间
     * 所以总时间就是内核时间+用户时间，就不用在加上空闲时间了
     */
    if (!GetSystemTimes(&idleTIme,&kernelTime,&userTime)) {
        printf("Get CPU usage failed！\r\n");
        return -1.0f;
    }

    /*把获取到的各类时间转换成ULARGE_INTEGER*/
    curIdleTime.LowPart = idleTIme.dwLowDateTime;
    curIdleTime.HighPart = idleTIme.dwHighDateTime;
    curKernelTime.LowPart = kernelTime.dwLowDateTime;
    curKernelTime.HighPart = kernelTime.dwHighDateTime;
    curUserTime.LowPart = userTime.dwLowDateTime;
    curUserTime.HighPart = userTime.dwHighDateTime;

    /*判断获取时间是不是第一次运行，如果是的话就把时间存起来并且置标志位*/
    if (isFirstRun) {
        lastIdleTime = curIdleTime;     //相同的结构体可以直接赋值
        lastKernelTime = curKernelTime;
        lastUserTime = curUserTime;
        isFirstRun = FALSE;
        return 0.0f;
    }

    /*计算忙碌的时间*/
    ULONGLONG curtotal = curKernelTime.QuadPart+curUserTime.QuadPart;
    ULONGLONG lasttotal = lastKernelTime.QuadPart+lastUserTime.QuadPart;
    totalTimeDiff = curtotal-lasttotal;     //总时间

    /*计算空闲时间*/
    idleTimeDiff = curIdleTime.QuadPart - lastIdleTime.QuadPart;

    /*计算CPU占用率*/
    if (totalTimeDiff == 0)
        return 0.0f;

    cpuusage = ((totalTimeDiff - idleTimeDiff)/(double)totalTimeDiff)*100;

    return (float)cpuusage;
}

