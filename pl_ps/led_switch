
//programda run'a bas. mavi işik yanmişsa programlıyor demektir. biraz bekle. program girişinden kabloyu çikart. mavi işik sönmememli. uart girişine tak. hem mavi işik hem de uart girişindeki turuncu işik yanmalı.
//putty ya da tera term u çalıştır. 
//putty için sol tarafta seriala gel bu bilgisayar için com5 yaz 115200 ve 8 bit, 1 stop,none,flow control xon xoff çalıştır.
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"

#define SW_CHANNEL 1
#define LED_CHANNEL 2
#define LED_MASK 0x0F
#define SWITCH_MASK 0x0F





int main(void)
{

    init_platform();
    XGpio Gpio;
    
    int Status;
    u32 switch_value;

    Status = XGpio_Initialize(&Gpio, XPAR_XGPIO_0_BASEADDR);

    if (Status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}

    XGpio_SetDataDirection(&Gpio, SW_CHANNEL, SWITCH_MASK);
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, LED_MASK);




 while (1) {

        switch_value=XGpio_DiscreteRead(&Gpio, SW_CHANNEL);
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, switch_value);
        xil_printf("checked! %x\n\r",switch_value);
 }

    cleanup_platform();
    return 0;
}
