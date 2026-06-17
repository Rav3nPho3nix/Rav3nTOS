// Implementation of USART driver for STM32H533 using USART2

#include <stddef.h>

#include "usart.h"
#include "usart_types.h"
#include "stm32h533xx.h"

void usart_init(uint32_t baudrate) {
    // Enable USART2 clock
    RCC->APB1LENR |= RCC_APB1LENR_USART2EN;
    // Enable GPIO A clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Configure TX = PA2 and RX = PA3 and AF7 alternate function
    // Clear bits
    GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
    // Set to alternate function mode
    GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);

    // Set alternate function to AF7 for PA2 and PA3
    // Clear bits
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2 | GPIO_AFRL_AFSEL3);  
    // Set alternate function
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

    // Set up BBR
    // 32 Mhz of frequency by default
    // BBR = (32,000,000) / BaudRate
    USART2->BRR = 32000000U / baudrate;

    // Enable USART2
    USART2->CR1 = USART_CR1_UE;
    // Enable transmitter and receiver
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

usart_status_t usart_write_char(char c) {
    // Wait until TX is not full
    while ((USART2->ISR & USART_ISR_TXE_TXFNF) == 0U);
    
    USART2->TDR = (uint8_t)(c);
    return USART_STATUS_OK;
}

usart_status_t usart_read_char(char* ptr_c) {
    // If ptr_c is NULL
    if (ptr_c == NULL) {
        return USART_STATUS_ERROR;
    }

    // Wait until RX is not empty
    while ((USART2->ISR & USART_ISR_RXNE_RXFNE) == 0U);

    *ptr_c = (char)(USART2->RDR & 0xFFU);
    return USART_STATUS_OK;
}

usart_status_t usart_write_string(const char* str) {
    // If bad pointer
    if (str == NULL) {
        return USART_STATUS_ERROR;
    }

    // Write each character
    while (*str != '\0') {
        usart_write_char(*(str++));
    }

    return USART_STATUS_OK;
}