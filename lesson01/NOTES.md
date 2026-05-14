> RTS (Request to Send) on a Raspberry Pi is a hardware flow control signal used in serial (UART) communication to manage data flow between the Pi and a peripheral. It tells the other device that the Pi is ready to receive data, preventing buffer overflows, typically on GPIO31 (ALT3) or other assignable pins, working alongside CTS (Clear to Send).Key Aspects of RTS on Raspberry PiFunction: RTS is an output signal from the Raspberry Pi indicating its readiness to receive data. It works with CTS (an input to the Pi) to ensure data isn't sent when buffers are full.


> ENABLING PL011 UART (UART0) WHAT FAILED INITIALLY THEN WHAT SUCCEEDED AFTERWARDS?
- INITIALLY THERE WAS A FAILURE IN BIT SETTING ESPECIALLY in the uart register parts
- not enabling FIFO was not a major issue, although you can see a gibberish in the beginning
- not clearing interrupts was not an issue
- get32(UART_DR&0xFF) in the pl_uart_recv function although it is still displaying hello world, it causes burst of weird buffer displaying on the terminal on you start typing on it
- it got fixed after changed to get32(UART_DR)&0xFF. Why the difference? 
```c
while (1) {
	pl_uart_send(pl_uart_recv());
}
```
- in the earlier case, get32(UART_DR&0xFF) - FF is 1111 1111 - @ is 0100 0000 - so not sure why @ kept displayed indefinitely, but we are definitely sending that value continuously
- let's just call it undefined behavior ;)
- the correct way to read it is get32 bits from UART_DR register and extract the 8 bits with 0xFF. get32(0) does not make any sense from the point of raspberry pi or bcm2711. it's random value, 
- my question is, for the correct way, how come recv function is waiting.. while the other isn't. 
- this is the important bit, if(get32(AUX_MU_LSR_REG)&0x20)
- in mini_uart, i misunderstood how the loop was used above, this is important, if the transmitter is empty hence, fifo can accept a byte, we break this loop 
- hence, i needed some kind of mechanism to break the loop WHEN the buffer is available for use as opposed to flag with error message. 
- now i get it why recv is being waited, program is constantly checking

