//hello word2 dosyası
//2. xsa ile yapıldı
//debug olmuyo ila çalışmıyo genel olarak sıkıntılı

#include "xaxidma_hw.h"
#include "xaxidma.h"
#include "xparameters.h"
#include "sleep.h"
#include "xil_cache.h"

u32 checkHalted(u32 baseAddress,u32 offset);

int main(){

	int32_t Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };


   int32_t in[4][4] = {
        { 10,  40,  80, 120},
        { 20,  60, 100, 140},
        { 30,  70, 110, 150},
        { 40,  80, 120, 160}
    };

    int32_t merged[2][2];
    int32_t p[3][3];
    u32 status;

	XAxiDma_Config *myDmaConfig;
	XAxiDma myDma0;     //p  main matrix
    XAxiDma myDma1;     //Gx kernel

	myDmaConfig =  XAxiDma_LookupConfig(XPAR_AXI_DMA_0_BASEADDR);       //BU PROBLEM BÜYÜK İHTİMALLE
	status = XAxiDma_CfgInitialize(&myDma0, myDmaConfig);
	if(status != XST_SUCCESS){
		print("DMA initialization failed\n");
		return -1;
	}


    myDmaConfig = XAxiDma_LookupConfig(XPAR_AXI_DMA_1_BASEADDR);        //BU PROBLEM BÜYÜK İHTİMALLE
	status = XAxiDma_CfgInitialize(&myDma1, myDmaConfig);
	if(status != XST_SUCCESS){
		print("DMA initialization failed\n");
		return -1;
	}
    

	status = checkHalted(XPAR_AXI_DMA_0_BASEADDR,0x4);
	xil_printf("Status before data transfer %0x\n",status);
	Xil_DCacheFlushRange((UINTPTR)p,9*sizeof(int32_t));
    Xil_DCacheFlushRange((UINTPTR)Gx,9*sizeof(int32_t));
    Xil_DCacheFlushRange((UINTPTR)merged, 4*sizeof(int32_t));

    for (int r = 0; r <= 1; r++) {
        for (int c = 0; c <= 1; c++) {
            //int Sx = 0, Sy = 0;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++) {
                    p[i][j] = in[r+i][c+j];

                }
          
            }
            //first 3x3 is defined
            	status = XAxiDma_SimpleTransfer(&myDma0, (UINTPTR)merged, 4*sizeof(int32_t),XAXIDMA_DEVICE_TO_DMA);
                if(status != XST_SUCCESS){
                    print("DMA0 S2MM failed\n");
                    return -1;
                }

	            status = XAxiDma_SimpleTransfer(&myDma0, (UINTPTR)p, 9*sizeof(int32_t),XAXIDMA_DMA_TO_DEVICE);//typecasting in C/C++
                if(status != XST_SUCCESS){
                    print("DMA0 MM2S failed\n");
                    return -1;
                }

                status = XAxiDma_SimpleTransfer(&myDma1, (UINTPTR)Gx, 9*sizeof(int32_t),XAXIDMA_DMA_TO_DEVICE);//typecasting in C/C++
                if(status != XST_SUCCESS){
                    print("DMA1 MM2S failed\n");
                    return -1;
                }

        }
      
    }




	if(status != XST_SUCCESS){
		print("DMA initialization failed\n");
		return -1;
	}
    //DMA0 check
    status = checkHalted(XPAR_AXI_DMA_0_BASEADDR,0x4);
    while(status != 1){
    	status = checkHalted(XPAR_AXI_DMA_0_BASEADDR,0x4);
    }
    status = checkHalted(XPAR_AXI_DMA_0_BASEADDR,0x34);
    while(status != 1){
    	status = checkHalted(XPAR_AXI_DMA_0_BASEADDR,0x34);
    }

    //DMA1 check
    if(status != XST_SUCCESS){
		print("DMA initialization failed\n");
		return -1;
	}
    status = checkHalted(XPAR_AXI_DMA_1_BASEADDR,0x4);
    while(status != 1){
    	status = checkHalted(XPAR_AXI_DMA_1_BASEADDR,0x4);
    }
    


	print("DMA transfer success..\n");
	for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            xil_printf("%0x ",merged[i][j]);
        }
        xil_printf("\n");
    }

}


u32 checkHalted(u32 baseAddress,u32 offset){
	u32 status;
	status = (XAxiDma_ReadReg(baseAddress,offset))&XAXIDMA_HALTED_MASK;
	return status;
}
