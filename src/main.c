#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    init_debug_uart0();          // makes printf go to your laptop

    while (1) 
    {
        printf("Hello from our DLL project!\n");
        _delay_ms(1000);      
}
}