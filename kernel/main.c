#include <stdint.h>

#include "platform.h"
#include "log.h"
#include "clock.h"

#define CLOCK_FREQUENCY 32000000
#define TICK_FREQUENCY 1000

int main(void) {
    platform_init();

    if (clock_init(CLOCK_FREQUENCY / TICK_FREQUENCY) != 0U) {
        while(1);
    }

    // Kernel body
    while(1) {
        log_info("This is printed every second !");
        clock_wait(1000);
    }
}