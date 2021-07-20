// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of ap_return
//        bit 31~0 - ap_return[31:0] (Read)
// 0x18 : Data signal of set_point
//        bit 31~0 - set_point[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of KP
//        bit 31~0 - KP[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of KI
//        bit 31~0 - KI[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of KD
//        bit 31~0 - KD[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of sample
//        bit 31~0 - sample[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of ts
//        bit 31~0 - ts[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of pmax
//        bit 31~0 - pmax[31:0] (Read/Write)
// 0x4c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XPID_CONTROL_ADDR_AP_CTRL        0x00
#define XPID_CONTROL_ADDR_GIE            0x04
#define XPID_CONTROL_ADDR_IER            0x08
#define XPID_CONTROL_ADDR_ISR            0x0c
#define XPID_CONTROL_ADDR_AP_RETURN      0x10
#define XPID_CONTROL_BITS_AP_RETURN      32
#define XPID_CONTROL_ADDR_SET_POINT_DATA 0x18
#define XPID_CONTROL_BITS_SET_POINT_DATA 32
#define XPID_CONTROL_ADDR_KP_DATA        0x20
#define XPID_CONTROL_BITS_KP_DATA        32
#define XPID_CONTROL_ADDR_KI_DATA        0x28
#define XPID_CONTROL_BITS_KI_DATA        32
#define XPID_CONTROL_ADDR_KD_DATA        0x30
#define XPID_CONTROL_BITS_KD_DATA        32
#define XPID_CONTROL_ADDR_SAMPLE_DATA    0x38
#define XPID_CONTROL_BITS_SAMPLE_DATA    32
#define XPID_CONTROL_ADDR_TS_DATA        0x40
#define XPID_CONTROL_BITS_TS_DATA        32
#define XPID_CONTROL_ADDR_PMAX_DATA      0x48
#define XPID_CONTROL_BITS_PMAX_DATA      32

