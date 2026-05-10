#include <stdint.h>

#include "platform.h"

#include "stm32h743xx.h"

int main(void) {
    platform_init();

    usart_write_string("OK !!");
}