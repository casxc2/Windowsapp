#include "GPULib.h"
#include "nvml.h"
#include <stdio.h>

static nvmlDevice_t g_device = {0};  //定义设备句柄
static int g_initialized = 0;

//初始化NVML并获取GPU句柄
static int EnsureNvmlReady(void) {
    if (g_initialized)  return 0;   //证明已经初始化好了

    nvmlReturn_t ret = nvmlInit();  //nvmlReturn_t是nvml库返回值类型，用来存放nvm
                                    //相关函数的返回值
    if (ret != NVML_SUCCESS) {
        printf("NVML Init Failed!:%s\n",nvmlErrorString(ret));
        return -1;
    }

    ret = nvmlDeviceGetHandleByIndex(0,&g_device);  //获取文件句柄
    if (ret != NVML_SUCCESS) {
        printf("Get GPU Handle Failed!:%s\n",nvmlErrorString(ret));
        nvmlShutdown();
        return -1;
    }

    g_initialized = 1;
    return 0;
}

/*获取GPU利用率*/
float GetGPUUsage(void) {
    if (EnsureNvmlReady()!=0)   return -1.0f;   //没初始化好nvml直接退出

    nvmlUtilization_t utilization;  //显卡利用率结构体，里面存显卡核心的利用率和显存的利用率
    nvmlReturn_t ret = nvmlDeviceGetUtilizationRates(g_device,&utilization); //获取利用率
    if (ret != NVML_SUCCESS) {
        printf("Get GPU Usage Failed!:%s",nvmlErrorString(ret));
        return -1.0f;
    }

    return (float)utilization.gpu;      //返回的是百分比
}

//获得显存利用率
float GetGRAMUsage(void) {
    if (EnsureNvmlReady()!=0)   return -1.0f;   //没初始化好nvml直接退出

    nvmlUtilization_t utilization;  //显卡利用率结构体，里面存显卡核心的利用率和显存的利用率
    nvmlReturn_t ret = nvmlDeviceGetUtilizationRates(g_device,&utilization); //获取利用率
    if (ret != NVML_SUCCESS) {
        printf("Get GPU RAM Usage Failed!:%s",nvmlErrorString(ret));
        return -1.0f;
    }

    return (float)utilization.memory;       //返回的是百分比
}

//获取GPU温度
float GetGPUTemp(void){
    if (EnsureNvmlReady()!=0)   return -1.0f;   //没初始化好nvml直接退出

    unsigned int temp;
    nvmlReturn_t ret = nvmlDeviceGetTemperature(g_device,NVML_TEMPERATURE_GPU,&temp);
    if (ret != NVML_SUCCESS) {
        printf("GET GPU Temperture Failed!%s",nvmlErrorString(ret));
        return -1.0f;
    }

    return (float)temp;
}

//非阻塞运行的话，需要执行这个nvml终止程序
void ShutdownNvml(void) {
    if (g_initialized) {
        nvmlShutdown();
        g_initialized = 0;
    }
}
//
// Created by Administrator on 2026/5/3.
//