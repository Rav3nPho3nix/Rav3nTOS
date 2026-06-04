// Implementation for USART driver for STM32h743 using USART1

#include <stddef.h>

#include "usart.h"
#include "usart_types.h"
#include "stm32h743xx.h"

void usart_init(uint32_t baudrate) {
    // Enable USART1 clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    // Enable GPIO A clock
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;

    // Configure TX = PA9 and RX = PA10 and AF7 alternate function
    // Clear bits
    GPIOA->MODER &= ~(GPIO_MODER_MODE9 | GPIO_MODER_MODE10);
    // Set to alternate function mode
    GPIOA->MODER |= (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1);

    // Set alternate function to AF7 for PA9 and PA10
    // Clear bits
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10);  
    // Set alternate function
    GPIOA->AFR[1] |= (7 << GPIO_AFRH_AFSEL9_Pos) | (7 << GPIO_AFRH_AFSEL10_Pos);

    // Set up BBR
    // 200 Mhz of frequency
    // BBR = (200,000,000) / (16 * BaudRate)
    USART1->BRR = 200000000U / (16 * baudrate);

    // Enable USART1
    USART1->CR1 = USART_CR1_UE;
    // Enable transmitter and receiver
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

usart_status_t usart_write_char(char c) {
    // If TX FIFO is full
    if ((USART1->ISR & USART_ISR_TXE_TXFNF) == 0U) {
        return USART_STATUS_TX_FULL;
    }
    USART1->TDR = (uint8_t)(c);
    return USART_STATUS_OK;
}

usart_status_t usart_read_char(char* ptr_c) {
    // If ptr_c is NULL
    if (ptr_c == NULL) {
        return USART_STATUS_ERROR;
    }

    // If RX FIFO is empty
    if ((USART1->ISR & USART_ISR_RXNE_RXFNE) == 0U) {
        return USART_STATUS_RX_EMPTY;
    }

    *ptr_c = (char)(USART1->RDR & 0xFFU);
    return USART_STATUS_OK;
}

usart_status_t usart_write_string(const char* str) {
    // If bad pointer
    if (str == NULL) {
        return USART_STATUS_ERROR;
    }

    // While the string is not empty
    while (*str != '\0') {
        usart_status_t status = usart_write_char(*str);

        // Propagating the error
        if (status != USART_STATUS_OK) {
            return status;
        }
        str++;
    }

    return USART_STATUS_OK;
}