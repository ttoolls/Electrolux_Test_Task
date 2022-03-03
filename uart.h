/**
  ******************************************************************************
  * @file    usart.h
  * @author  Anatoly Selivanov
  * @date    01-March-2022
  * @brief   This file contains public API to interact with 
  *          a hardware UART (USART) block.
  * 
  * <h2>This file contains public API to interact with 
  *     a hardware UART (USART) block accordint to the following task:</h2>
  * Write a public API to interact with a hardware UART (USART) block,
  * which should include:
  * 1. Initialization of the module;
  * 2. Setting the baud rate;
  * 3. Setting the parity bit;
  * 4. Setting the duration of the stop bit;
  * 5. Setting the callback function for the receiver / transmitter;
  * 6. Data array transfer function. Data array will be sent by the transmitter;
  * 
  * If the requirements described above are not enough to ensure 
  * the functionality of the module, then other parameters can be passed 
  * at your discretion.
  * 
  * <h2>Additionally:</h2>
  * 1. The hardware block only works with interrupts;
  * 2. The software module must be able to work with several 
  *     hardware blocks (USART1, USART2, etc.);
  * 3. Public API should consist of only one header file 
  *     (platform-specific source files are not needed);
  ******************************************************************************    
  */ 


#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes-------------------------------------------------------------------*/

#include <stdint.h>

/* Definess-------------------------------------------------------------------*/

#define USART_STATUS_OK     ((uint16_t)0x0000)
#define USART_STATUS_ERROR  ((uint16_t)0x0001)

#define USART_PARITY_NO   ((uint16_t)0x0000)
#define USART_PARITY_ODD  ((uint16_t)0x0001)
#define USART_PARITY_EVEN ((uint16_t)0x0002)

#define USART_STOP_BIT_1   ((uint16_t)0x0001)
#define USART_STOP_BIT_2   ((uint16_t)0x0002)

#define USART_RX ((uint16_t)0x0001)
#define USART_TX ((uint16_t)0x0002)

/* Typedefs-------------------------------------------------------------------*/

extern struct USART_HDL;

typedef void(* usart_callback_t)(USART_HDL* USARTx, uint8_t status, void *userData);

typedef struct {
    uint32_t baudRate;
    uint16_t parityBit;
    uint16_t stopBitDuration;
    uint16_t mode;
} USART_SETTINGS_STRUCT;


/* Function prototypes---------------------------------------------------------*/

/**
  * @brief  This function initializes the USARTx module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @param  usartSettings: pointer to structure containing configuration
  *         information for the UART  module.
  * @retval None
  */
void Usart_Init(USART_HDL* USARTx, const USART_SETTINGS_STRUCT* usartSettings);

/**
  * @brief  This function deinitializes the USARTx module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.  *
  * @retval None
  */
void Usart_Deinit(USART_HDL* USARTx);

/**
  * @brief  Setting baud rate to the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @param  baudRate: baud rate to be set.
  * @retval None
  */
void Usart_SetBaudRate(USART_HDL* USARTx, const uint32_t baudRate);

/**
  * @brief  Setting baud rate to the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @param  callback: callback function for the receiver / transmitter.
  * @retval None
  */
void Usart_SetCallback(USART_HDL* USARTx, usart_callback_t callback);

/**
  * @brief  Enabling the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @retval None
  */
void Usart_SetEnable(USART_HDL* USARTx);

/**
  * @brief  Disabling the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @retval None
  */
void Usart_SetDisable(USART_HDL* USARTx);

/**
  * @brief  Sending data array via the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @param  data: pointer to array of data to be transmitted.
  * @param  size: number of bytes to be transmitted.
  * @retval None
  */
void Usart_SendData(USART_HDL* USARTx, const uint8_t* data, const uint32_t size);

/**
  * @brief  Nonblocking receiving data array via the UART module.
  * @param  USARTx: heandler of UARTx hardware block, it is defined in platform-
  *         specific source files, possible values are USART1, USART2, etc.
  * @param  data: pointer to a buffer where data will be saved.
  * @param  size: number of bytes to be received.
  * @param  received: amount of received data.
  * @retval None
  */
void Usart_ReceiveData(USART_HDL* USARTx, const uint8_t* data, const uint32_t size, uint32_t* received);


#ifdef __cplusplus
}
#endif

#endif /* __USART_H */