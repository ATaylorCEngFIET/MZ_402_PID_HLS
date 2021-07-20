// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XPID_H
#define XPID_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xpid_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XPid_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XPid;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPid_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPid_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPid_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPid_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XPid_Initialize(XPid *InstancePtr, u16 DeviceId);
XPid_Config* XPid_LookupConfig(u16 DeviceId);
int XPid_CfgInitialize(XPid *InstancePtr, XPid_Config *ConfigPtr);
#else
int XPid_Initialize(XPid *InstancePtr, const char* InstanceName);
int XPid_Release(XPid *InstancePtr);
#endif

void XPid_Start(XPid *InstancePtr);
u32 XPid_IsDone(XPid *InstancePtr);
u32 XPid_IsIdle(XPid *InstancePtr);
u32 XPid_IsReady(XPid *InstancePtr);
void XPid_EnableAutoRestart(XPid *InstancePtr);
void XPid_DisableAutoRestart(XPid *InstancePtr);
u32 XPid_Get_return(XPid *InstancePtr);

void XPid_Set_set_point(XPid *InstancePtr, u32 Data);
u32 XPid_Get_set_point(XPid *InstancePtr);
void XPid_Set_KP(XPid *InstancePtr, u32 Data);
u32 XPid_Get_KP(XPid *InstancePtr);
void XPid_Set_KI(XPid *InstancePtr, u32 Data);
u32 XPid_Get_KI(XPid *InstancePtr);
void XPid_Set_KD(XPid *InstancePtr, u32 Data);
u32 XPid_Get_KD(XPid *InstancePtr);
void XPid_Set_sample(XPid *InstancePtr, u32 Data);
u32 XPid_Get_sample(XPid *InstancePtr);
void XPid_Set_ts(XPid *InstancePtr, u32 Data);
u32 XPid_Get_ts(XPid *InstancePtr);
void XPid_Set_pmax(XPid *InstancePtr, u32 Data);
u32 XPid_Get_pmax(XPid *InstancePtr);

void XPid_InterruptGlobalEnable(XPid *InstancePtr);
void XPid_InterruptGlobalDisable(XPid *InstancePtr);
void XPid_InterruptEnable(XPid *InstancePtr, u32 Mask);
void XPid_InterruptDisable(XPid *InstancePtr, u32 Mask);
void XPid_InterruptClear(XPid *InstancePtr, u32 Mask);
u32 XPid_InterruptGetEnabled(XPid *InstancePtr);
u32 XPid_InterruptGetStatus(XPid *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
