#include "platform.h"

#include "usart.h"

void platform_init(void) {
    usart_init(115200U);
}