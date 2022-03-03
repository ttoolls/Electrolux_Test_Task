# Electrolux_Test_Task

This is my solution for job interview task from Electrolux.

The task is the following:

// ----- Step 1

Write a public API to interact with a hardware UART (USART) block, which should include:

                1. Initialization of the module;

                2. Setting the baud rate;

                3. Setting the parity bit;

                4. Setting the duration of the stop bit;

                5. Setting the callback function for the receiver / transmitter;

                6. Data array transfer function. Data array will be sent by the transmitter;

 

If the requirements described above are not enough to ensure the functionality of the module, then other parameters can be passed at your discretion.

Additionally:

                1. The hardware block only works with interrupts;

                2. The software module must be able to work with several hardware blocks (USART1, USART2, etc.);

                3. Public API should consist of only one header file (platform-specific source files are not needed);

 

// ----- Step 2

 

Based on the first step, write a software module that uses the public API UART (USART) software module to receive and send messages between two UART hardware blocks (USART).

Data for hardware block 1 (USART1):

                1. Baud rate is 9600;

                2. Receives data only (RX line is active);

Data for hardware block 2 (USART2):

                1. Baud rate is 115200;

                2. Transmits data only (TX line is active);

General data for the second task:

                1. After receiving data via USART1, they must be saved and sent via USART2;

                2. Transmission via USART2 is carried out in blocks of 128 bytes, so enough data must be accumulated before sending via USART2;

                3. At the moment of transmission of the data block via USART2, it is possible to receive new data via USART1, so new / transmitted data should not be lost or damaged;

                4. To check the functionality, a test should be created (the type of the test is at your discretion);

 

// ----- General requirements

Modules must be written in C. C99 standard without extensions;

The design, the way how parameters are passed to functions, and the usage of language constructs are important for evaluating a solution.

 

All functions should have a header with a description. These headers in Doxygen style will be a plus.

If the function doesn't have a realization, a description of the possible implementation should be added to the comments.

Adding files for building a project (cmake, make, etc.) will be a plus 
