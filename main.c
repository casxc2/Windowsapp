#include <stdio.h>
#include <windows.h>
#include "RamLib.h"
#include "DiskLib.h"
#include "CPULib.h"
#include "GPULib.h"

int main(void) {

    while (1) {
        /************GPU监控代码*************/
        float GPUUsage,GRAMUsage,GPUTemp;
        GPUUsage = GetGPUUsage();       //获取GPU利用率
        GRAMUsage = GetGRAMUsage();     //获取显存利用率
        GPUTemp = GetGPUTemp();         //获取GPU温度

        printf("GPU Usage is %.1f%%, ",GPUUsage);           //获取GPU利用率
        printf("GPU GPU RAM Usage is %.1f%%, ",GRAMUsage);  //获取显存利用率
        printf("GPU Temp is %.1f C\r\n",GPUTemp);           //获取GPU温度

        /************CPU监控代码*************/
        float CPUUsage = GetCpuUsagePercent();
        printf("CPU usage is %.1f%%\r\n",CPUUsage);

        /************RAM监控代码*************/
        float RAMUsage = GetRamPercent();
        printf("RAM usage is %.1f%%\r\n",RAMUsage);

        /************DISK监控代码*************/
        GetDiskV();

        Sleep(2000);
    }
    return 0;
}