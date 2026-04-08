// ring_buffer.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Temporary Circular storage array used to store and hold data before data could be used
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

    #include "../tm4c123gh6pm.h"
    #include <stdbool.h> 
    #include <stdint.h>
    #include <stdio.h>
		#include "../config.h"
	
    #define BUFFER_SIZE 31
    #define CR   0x0D
    #define LF   0x0A
    #define UNUSED_CHAR 0xFE

    typedef struct {
            uint16_t head;
            uint16_t tail;
            uint8_t buf[BUFFER_SIZE];
    } RingBuffer; 

    // ---------- rb_init ---------- //
    // Initializes ring buffer head and tail to 0
    // Input: pointer to which ring buffer to initialize
    // Output: none
    void rb_init(RingBuffer *rb);

     // ---------- rb_empty ---------- //
     // Checks if ring buffer is empty
     // Input: pointer to which ring buffer to check if empty
     // Output: boolean
    bool rb_empty(RingBuffer *rb);

     // ---------- rb_full ---------- //
     // Checks if ring buffer is full
     // Input: pointer to which ring buffer to check if full
     // Output: boolean
    bool rb_full(RingBuffer *rb);

     // ---------- UART5_Handler ---------- //
     // Handles input recieved into UART 5 (MCU 1)
     // Input: nothing
     // Output: nonthing
    void UART5_Handler(void);

     // ---------- UART7_Handler ---------- //
     // Handles input recieved into UART 7 (MCU 2)
     // Input: nothing
     // Output: nothing
    void UART7_Handler(void);

     // ---------- UART_ReadChar ---------- //
     // Reads char from selected ring buffer and moves the tail up one to signifiy it's been read
     // Input: A pointer of which ring buffer to read from
     // Output: the value inside of the ring buffer (int, but is a uint8_t)
    int UART_ReadChar(RingBuffer *rb);

     // ---------- ClearBuffer ---------- //
     // Clears the ring buffer
     // Input: A pointer of which ring buffer to clear
     // Output: none
		void ClearBuffer(RingBuffer *rb);

#endif /* RING_BUFFER_H */