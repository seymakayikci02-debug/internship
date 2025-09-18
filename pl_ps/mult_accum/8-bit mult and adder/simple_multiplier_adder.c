#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xil_printf.h"

//////////////////////////////////////////////////////////////////////////
Prepared by     :  Seyma Kayıkcı
Date            : [09 18 2025]
////////////////////////////////////////////////////////////////////////////

// Base addresses of our custom IPs (defined in xparameters.h)
unsigned *ip_custom_mult  = XPAR_SIMPLE_MULT_0_BASEADDR;
unsigned *ip_custom_adder = XPAR_SIMPLE_ADDER_0_BASEADDR;

int main()
{
    init_platform();
    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    // ---------------------------
    // 1. WHAT DOES ip_custom_mult MEAN?
    // ---------------------------
    // XPAR_SIMPLE_MULT_0_BASEADDR is just a number like 0x40000000
    // We cast it as "unsigned *" → a pointer to an unsigned int
    // So: ip_custom_mult points to the start of the multiplier's registers
    //
    // Registers are mapped like this:
    //   ip_custom_mult + 0 --> register 0 (operand A)
    //   ip_custom_mult + 1 --> register 1 (operand B)
    //   ip_custom_mult + 2 --> register 2 (result)

    short a, b;

    // ---- First multiplication ----
    a = 10;
    b = 45;

    *(ip_custom_mult + 0) = a;  // Write "a" into register 0 (operand A)
    *(ip_custom_mult + 1) = b;  // Write "b" into register 1 (operand B)
    int c = *(ip_custom_mult + 2); // Read result from register 2
    xil_printf("\n\rFirst multiplication: %d", c);

    // ---- Second multiplication ----
    a = 2;
    b = 20;

    *(ip_custom_mult + 0) = a;  // Register 0 again (new operand A)
    *(ip_custom_mult + 1) = b;  // Register 1 again (new operand B)
    int d = *(ip_custom_mult + 2); // Register 2 again (new result)
    xil_printf("\n\rSecond multiplication: %d", d);

    // ---------------------------
    // 2. SAME IDEA FOR THE ADDER
    // ---------------------------
    // ip_custom_adder points to the adder's base address
    //   ip_custom_adder + 0 --> register 0 (operand A)
    //   ip_custom_adder + 1 --> register 1 (operand B)
    //   ip_custom_adder + 2 --> register 2 (result)

    a = c;  // First multiplication result
    b = d;  // Second multiplication result

    *(ip_custom_adder + 0) = a;   // Write c into adder operand A
    *(ip_custom_adder + 1) = b;   // Write d into adder operand B
    int final = *(ip_custom_adder + 2); // Read sum from result register
    xil_printf("\n\rFirst multiplication + Second multiplication: %d", final);

    cleanup_platform();
    return 0;
}
