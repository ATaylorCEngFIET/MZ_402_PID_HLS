// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xpid.h"

extern XPid_Config XPid_ConfigTable[];

XPid_Config *XPid_LookupConfig(u16 DeviceId) {
	XPid_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XPID_NUM_INSTANCES; Index++) {
		if (XPid_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XPid_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XPid_Initialize(XPid *InstancePtr, u16 DeviceId) {
	XPid_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XPid_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XPid_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

