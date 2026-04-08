// FSM.h
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: FSM of mode 1 and mode 2
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// main contributor: Justin Narciso

#include <stdint.h>
#include <stdbool.h>
#include "../../tm4c123gh6pm.h"
#include "../../common/drivers/UART1.h"

struct State_Mode1 {
    uint8_t next[5];
};
typedef const struct State_Mode1 states_one;


struct State_Mode2 {
    uint8_t next[7];
};
typedef const struct State_Mode2 states_two;

#define DEFAULT_DUTY 15

void mode_one_manager(void);
void mode_two_manager(void);

void figure8_operation(void);
void circle_operation(void);
void square_operation(void);
void zigzag_operation(void);