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

#include "ring_buffer.h"
RingBuffer ringBuffer_PC;
RingBuffer *rb_PC = &ringBuffer_PC;

RingBuffer ringBuffer_MCU;
RingBuffer *rb_MCU = &ringBuffer_MCU;

bool userFinished = false;
bool EOL = false;

//initialize Ring Buffer
void rb_init(RingBuffer *rb) {
    rb->head = rb->tail = 0;
}

//detect buffer empty
bool rb_empty(RingBuffer *rb){
    return rb->head == rb->tail;
}

//detect buffer is full
bool rb_full(RingBuffer *rb){
    return (uint16_t)((rb->head + 1) % BUFFER_SIZE) == rb->tail;
}

void UART5_Handler(void){
    char c = UART5_DR_R;
    uint16_t next = (rb_MCU->head + 1) % BUFFER_SIZE;  
    if(next != rb_MCU->tail) {
      rb_MCU->buf[rb_MCU->head] = c;
            rb_MCU->head = next;
    }
        UART5_ICR_R = UART_ICR_RXIC;        // acknowledge RX FIFO
}

void UART7_Handler(void){
    char c = UART7_DR_R;
    uint16_t next = (rb_MCU->head + 1) % BUFFER_SIZE;  
    if(next != rb_MCU->tail) {
        rb_MCU->buf[rb_MCU->head] = c;
        rb_MCU->head = next;
    }
		UART7_ICR_R = UART_ICR_RXIC;        // acknowledge RX FIFO
}

void UART0_Handler(void){
    char c = UART0_DR_R;
		if(c == CR){
            userFinished = true;
            return;
        }

        if(c == LF){
            return;
        }
    
    uint16_t next = (rb_PC->head + 1) % BUFFER_SIZE;  
    if(next != rb_PC->tail) {
        rb_PC->buf[rb_PC->head] = c;
        rb_PC->head = next;
    }
    if(rb_PC->head == rb_PC->tail) {
        EOL = true;
				rb_PC->buf[rb_PC->head] = '\0';
		}
}

int UART_ReadChar(RingBuffer *rb) {
    if(rb->head == rb->tail) return -1;
    char c = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    return c;
}

void ClearBuffer(RingBuffer *rb){
	if(rb_empty(rb)) return;
	rb->tail = rb->head = 0;
	rb->buf[rb->tail] = (char) UNUSED_CHAR;
	userFinished = false;
}
