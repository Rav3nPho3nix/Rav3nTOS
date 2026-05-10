#include <stdint.h>

#include "platform.h"
#include "usart.h"

#include "stm32h743xx.h"

int main(void) {
    platform_init();

    usart_putchar('O');
    usart_putchar('K');
}