// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xpid.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPid_CfgInitialize(XPid *InstancePtr, XPid_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPid_Start(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL) & 0x80;
    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XPid_IsDone(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XPid_IsIdle(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XPid_IsReady(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XPid_EnableAutoRestart(XPid *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XPid_DisableAutoRestart(XPid *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XPid_Get_return(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_AP_RETURN);
    return Data;
}
void XPid_Set_set_point(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_SET_POINT_DATA, Data);
}

u32 XPid_Get_set_point(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_SET_POINT_DATA);
    return Data;
}

void XPid_Set_KP(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KP_DATA, Data);
}

u32 XPid_Get_KP(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KP_DATA);
    return Data;
}

void XPid_Set_KI(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KI_DATA, Data);
}

u32 XPid_Get_KI(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KI_DATA);
    return Data;
}

void XPid_Set_KD(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KD_DATA, Data);
}

u32 XPid_Get_KD(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_KD_DATA);
    return Data;
}

void XPid_Set_sample(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_SAMPLE_DATA, Data);
}

u32 XPid_Get_sample(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_SAMPLE_DATA);
    return Data;
}

void XPid_Set_ts(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_TS_DATA, Data);
}

u32 XPid_Get_ts(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_TS_DATA);
    return Data;
}

void XPid_Set_pmax(XPid *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_PMAX_DATA, Data);
}

u32 XPid_Get_pmax(XPid *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_PMAX_DATA);
    return Data;
}

void XPid_InterruptGlobalEnable(XPid *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_GIE, 1);
}

void XPid_InterruptGlobalDisable(XPid *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_GIE, 0);
}

void XPid_InterruptEnable(XPid *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_IER);
    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_IER, Register | Mask);
}

void XPid_InterruptDisable(XPid *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_IER);
    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_IER, Register & (~Mask));
}

void XPid_InterruptClear(XPid *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPid_WriteReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_ISR, Mask);
}

u32 XPid_InterruptGetEnabled(XPid *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_IER);
}

u32 XPid_InterruptGetStatus(XPid *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPid_ReadReg(InstancePtr->Control_BaseAddress, XPID_CONTROL_ADDR_ISR);
}

