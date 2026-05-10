#include "../includes/types.h"

volatile uint32_t counter = 0;

int main(void) {
    while (1) {
        counter++;
    }
}