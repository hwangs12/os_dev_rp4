#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"

#define BAUD_RATE 115200
#define CLOCK_FREQ 500000000

void pl_uart_send ( char c )
{
    // is my UART_DR correct?
	while (get32(UART_FR) & (1 << 5));     // Wait until the Transmit FIFO is NOT full (Bit 5 of UART_FR is 0)

        // if(get32(UART_DR)&0x400)
        //     break;
        // if(get32(UART_DR)&0x200)
        //     break;
        // if(get32(UART_DR)&0x100)
        //     break;
	put32(UART_DR,c);
}

char pl_uart_recv ( void )
{
	// Wait while the Receive FIFO is EMPTY (Bit 4 of UART_FR is 1)
    while (get32(UART_FR) & (1 << 4));
	return (get32(UART_DR)&0xFF);
}

void pl_uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		pl_uart_send((char)str[i]);
	}
}

void pl_uart_init ( void )
{
	unsigned int selector;
	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15
	put32(GPFSEL1,selector);

    /* FOR PI 3 */
	// put32(GPPUD,0);
	// delay(150);
	// put32(GPPUDCLK0,(1<<14)|(1<<15));
	// delay(150);
	// put32(GPPUDCLK0,0);

    /* FOR PI 4 */
    // 2. NEW Pi 4 Pull-up/down Logic (replaces GPPUD)
    // GPIO 14 & 15 are bits 28-31 of REG0. Setting to 00 = No pull.
    selector = get32(GPIO_PUP_PDN_CNTRL_REG0);
    selector &= ~(0xF << 28); 
    put32(GPIO_PUP_PDN_CNTRL_REG0, selector);

	put32(UART_CR,0);                                   //disable uart (this also enables access to its registers) to program LCRH
	// put32(AUX_MU_CNTL_REG,0);                        //Disable auto flow control and disable receiver and transmitter (for now)
	put32(UART_ICR,0x7FF);                                  //Disable receive and transmit interrupts
	put32(UART_LCRH, 0x70);                             //Enable 8 bit mode and enable FEN, disable parity and BRK
	put32(UART_IBRD,CLOCK_FREQ/(16*BAUD_RATE));         //Set baud rate to 115200
    put32(UART_CR, 0x0301);                              //Enable uart, rxe, txe, disable rts
}

