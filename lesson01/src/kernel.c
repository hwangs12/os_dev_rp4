#include "pl011_uart.h"

void kernel_main(void)
{
	pl_uart_init();
	pl_uart_send_string("Hello, world!\n");
    // pl_uart_send('Q');

	while (1) {
		pl_uart_send(pl_uart_recv());
	}
}
