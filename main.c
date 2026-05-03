#include <stdio.h>
#include <windows.h>
#include "RamLib.h"
#include "DiskLib.h"
#include  "CPULib.h"
#include "GPULib.h"

int main(void) {

    while (1) {
        float GPUUsage,GRAMUsage,GPUTemp;
        GPUUsage = GetGPUUsage();
        GRAMUsage = GetGRAMUsage();
        GPUTemp = GetGPUTemp();

        printf("GPU Usage is %.1f%%\r\n",GPUUsage);
        printf("GPU GPU RAM Usage is %.1f%%\r\n",GRAMUsage);
        printf("GPU Temp is %.1f C\r\n",GPUTemp);

        Sleep(2000);
    }
    return 0;
}