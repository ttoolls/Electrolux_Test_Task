/**
  ******************************************************************************
  * @file    main.h
  * @author  Anatoly Selivanov
  * @date    02-March-2022
  * @brief   A software module receives and sends messages between two USARTs.
  * 
  * This file contains a software module that uses the public API UART (USART)
  * software module to receive and send messages between two UART hardware
  * blocks (USART) according to the following test task:
  * 
  * Data for hardware block 1 (USART1):
  * 1. Baud rate is 9600;
  * 2. Receives data only (RX line is active);
  *
  * Data for hardware block 2 (USART2):
  * 1. Baud rate is 115200;
  * 2. Transmits data only (TX line is active);
  * 
  * <h2>General data for the second task:</h2>
  * 1. After receiving data via USART1, they must be saved and sent via USART2;
  * 2. Transmission via USART2 is carried out in blocks of 128 bytes, so enough
  *    data must be accumulated before sending via USART2;
  * 3. At the moment of transmission of the data block via USART2, it is
  *    possible to receive new data via USART1, so new / transmitted data should
  *    not be lost or damaged;
  * 4. To check the functionality, a test should be created (the type of the
  *    test is at your discretion);
  ******************************************************************************    
  */ 

/* Includes-------------------------------------------------------------------*/

#include "uart.h"


/* Defines--------------------------------------------------------------------*/

#define DATA_SIZE 128
#define NUMBER_OF_BUFFERS 2


/* Function prototypes--------------------------------------------------------*/

/**
  * @brief  This function implements platform specific initialization.
  * @param  None  
  * @retval None
  */
static void Platform_Specified_Init(void);

/**
  * @brief  This function initializes GPIO module.
  * @param  None  
  * @retval None
  * 
  * Activation of coresponding GPIO ports,
  * pin corresponding to USART1 RX is set as input,
  * pin corresponding to USART2 TX is set as output.
  */
static void GPIO_Init(void);

/**
  * @brief  This function initializes the USART modules.
  * @param  None
  * @retval None
  */
static void USART_Init(void);


/* Functions------------------------------------------------------------------*/

void main(void) {
    Platform_Specified_Init();
    GPIO_Init();
    USART_Init();

    uint8_t input_buffer[NUMBER_OF_BUFFERS][DATA_SIZE];
    uint8_t input_buf_number = 0;
    uint8_t output_buf_number;
    volatile uint32_t bytesReceived = 0;

    Usart_SetEnable(USART1);    
    Usart_ReceiveData(USART1, input_buffer[input_buf_number], DATA_SIZE,
                    &bytesReceived);
    input_buf_number ^= 1;

    while(1) {
        if (bytesReceived == DATA_SIZE) {
            Usart_ReceiveData(USART1, input_buffer[input_buf_number], DATA_SIZE,
                            &bytesReceived);
            output_buf_number = input_buf_number;
            input_buf_number ^= 1;
            Usart_SendData(USART2, input_buffer[output_buf_number], DATA_SIZE);
        }
    }
}

static void USART_Init(void) {
    USART_SETTINGS_STRUCT usartSettings;
    usartSettings.baudRate = 9600;
    usartSettings.mode = USART_RX;
    usartSettings.parityBit = USART_PARITY_NO;
    usartSettings.stopBitDuration = USART_STOP_BIT_1;
    Usart_Init(USART1, &usartSettings);

    usartSettings.baudRate = 115200;
    usartSettings.mode = USART_TX;
    Usart_Init(USART2, &usartSettings);
}