#ifndef	_P_PL011_UART_H
#define	_P_PL011_UART_H

#include "peripherals/base.h"

#define UART_BASE (PBASE+0x00201000)

#define UART0 (UART_BASE)
#define UART2 (UART_BASE+0x400)
#define UART3 (UART_BASE+0x600)
#define UART4 (UART_BASE+0x800)
#define UART5 (UART_BASE+0xA00)

// FOR UART0 but changing to whichever UARTx will work
#define UART_DR         (UART0)
#define UART_RSRECR     (UART0+0x04)
#define UART_FR         (UART0+0x18)
#define UART_ILPR       (UART0+0x20)
#define UART_IBRD       (UART0+0x24)
#define UART_FBRD       (UART0+0x28)
#define UART_LCRH       (UART0+0x2C)
#define UART_CR         (UART0+0x30)
#define UART_IFLS       (UART0+0x34)
#define UART_IMSC       (UART0+0x38)
#define UART_RIS        (UART0+0x3C)
#define UART_MIS        (UART0+0x40)
#define UART_ICR        (UART0+0x44)
#define UART_DMACR      (UART0+0x48)
#define UART_ITCR       (UART0+0x80)
#define UART_ITIP       (UART0+0x84)
#define UART_ITOP       (UART0+0x88)
#define UART_TDR        (UART0+0x8C)

#endif  /*_P_PL011_UART_H */