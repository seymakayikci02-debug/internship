#include <stdio.h>
#include <xstatus.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"
#include "xparameters.h"
#include "sleep.h"

XGpioPs gpio;

void gpioInit()
{
    XGpioPs_Config *gpioConfig;
    gpioConfig = XGpioPs_LookupConfig(XPAR_GPIO0_BASEADDR);
    if(gpioConfig==NULL) xil_printf("GPIO Config Error...");
    int status =XGpioPs_CfgInitialize(&gpio, gpioConfig, gpioConfig->BaseAddr);
    if (status==XST_SUCCESS) xil_printf("GPIO initialization Successful...\r\n");
    XGpioPs_SetDirectionPin(&gpio, 7, 1);
    XGpioPs_SetOutputEnablePin(&gpio, 7, 1);
}

int main()
{
    gpioInit();
    while(1)
    {
        XGpioPs_WritePin(&gpio, 7, 1);
        sleep(1);
        XGpioPs_WritePin(&gpio, 7, 0);
        sleep(1);
    }
    return 0;
}
