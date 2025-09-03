#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xbram.h"


#define LED_CHANNEL 1
#define SWITCH_CHANNEL 2
#define LEDS_MASK 0x0F   // 4 leds
#define SWITCHES_MASK 0x0F   // 4 switches
#define XPAR_BRAM_0_BASEADDR  XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR


int main()
{


    init_platform();

 XGpio Gpio; /* The Instance of the GPIO Driver */
 XBram Bram; /* The Instance of the BRAM Driver */

 XBram_Config *ConfigPtr;

 int Status;

 /* Initialize the GPIO driver */
 Status = XGpio_Initialize(&Gpio, XPAR_XGPIO_0_BASEADDR);
 if (Status != XST_SUCCESS) {
  xil_printf("Gpio Initialization Failed\r\n");
  return XST_FAILURE;
 }


 ConfigPtr = XBram_LookupConfig(XPAR_XBRAM_0_BASEADDR);
 if (ConfigPtr == (XBram_Config *) NULL) {
  return XST_FAILURE;
 }

 Status = XBram_CfgInitialize(&Bram, ConfigPtr,
         ConfigPtr->CtrlBaseAddress);
 if (Status != XST_SUCCESS) {
  return XST_FAILURE;
 }


 /* Set the direction for all signals  */
 XGpio_SetDataDirection(&Gpio, LED_CHANNEL, ~LEDS_MASK); // output
 XGpio_SetDataDirection(&Gpio, SWITCH_CHANNEL, SWITCHES_MASK); // input



    printf("Hello World\n\r");
    printf("Successfully ran Hello World application");


    for (int i = 0; i < 16*4; i=i+4){
     XBram_WriteReg(XPAR_XBRAM_0_BASEADDR,i,i);

    }

    int out_data;

    for (int i = 0; i < 16*4; i=i+4){
     out_data = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR,i);
  xil_printf("%d: %d\n\r",i, out_data);

    }

    while(1){
     u32 switches = XGpio_DiscreteRead(&Gpio,SWITCH_CHANNEL);
  XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, switches);
  xil_printf("checked! %x\n\r",switches);
  sleep(1);
    }


    cleanup_platform();
    return 0;
}
