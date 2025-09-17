/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xil_printf.h"

unsigned *ip_simple_mult=XPAR_SIMPLE_MULT_0_BASEADDR;

int main()
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    short a;
    short b;
    a=2;
    b=45;
    *(ip_simple_mult+0)=(a<<16)+b;
    int c=*(ip_simple_mult+1);
    xil_printf("%d",c);

    cleanup_platform();
    return 0;
}
