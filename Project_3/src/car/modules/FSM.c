// FSM.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: FSM of mode 1 and mode 2
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
// main contributor: Justin Narciso

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 

#include "FSM.h"
int current_mode1 = 0;
int current_mode2 = 0;
extern bool SW1_PRESSED;

extern void forward(void);
extern void backward(void);
extern void off(void);
extern void on(void);
extern void pivot_left(void);
extern void pivot_right(void);

uint8_t speed = 4;

extern void PWM_Duty(uint16_t  duty_L, uint16_t duty_R);


enum mode_one_states { 
    IDLE,
    FIGURE8,
    CIRCLE,
    SQUARE,
    ZIGZAG,
};

states_one demo_mode_fsm[5]={ 
    {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG}},
    {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG}},
    {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG}},
    {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG}},
    {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG}},
};

enum mode_two_states { 
    STOP,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    SPEEDUP,
    SPEEDDOWN,
};

states_two drive_mode_fsm[7]={ 
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
};

// @brief: Handles how mode 1 handles inputs (State machine)
// Loops inside the function (Based on mode 1 or mode 2)
void mode_one_manager(void){
    
    uint8_t char_input = UART1_InChar();
    
    while(!SW1_PRESSED){

        switch(char_input){ //check for the read char value from the Bluetooth
					 case 0x5A: // if char 'Z' in zigzag state
                current_mode1 = demo_mode_fsm[current_mode1].next[4];
								speed=2;
								zigzag_operation();
            break;
            case 0x38: // if char '8' in figure 8 state
                current_mode1 = demo_mode_fsm[current_mode1].next[1];
								speed = 7;
                figure8_operation();
            break;
            case 0x43: // if char 'C' in circle state
                current_mode1 = demo_mode_fsm[current_mode1].next[2];
                speed=7;
                circle_operation();
            break;
            case 0x53: // if char 'S' in square state
                current_mode1 = demo_mode_fsm[current_mode1].next[3];
						speed = 2;
                square_operation();
					
            break;
								
            
        }
				//change_LED(BLUE);
				current_mode1 = demo_mode_fsm[current_mode1].next[0];
				off();
        // reads next input
        speed =4;
        char_input = UART1_InChar();
        
    }
    current_mode1 = demo_mode_fsm[current_mode1].next[0];

}

// @brief: Handles the way mode 2 handles inputs (State machine)
// Loops inside the function (Based on mode 1 or mode 2)
void mode_two_manager(void){
    
    uint8_t char_input = UART1_InChar();

    while(SW1_PRESSED){
        switch(char_input){ //check for the read char value from the Bluetooth
            case 0x53: // if char 'S' in stop state
                current_mode2 = drive_mode_fsm[current_mode2].next[0];
                off();
            break;
            case 0x46: // if char 'F' in forward state 
                current_mode2 = drive_mode_fsm[current_mode2].next[1];
                PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
                on();
                forward();
            break;
            case 0x42: // if char 'B' in backward state
                current_mode2 = drive_mode_fsm[current_mode2].next[2];
                PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
                on();
                backward();
            break;
            case 0x4C: // if char 'L' in left state
                PWM_Duty(speed * DEFAULT_DUTY/2, speed * DEFAULT_DUTY);
                // check if previous state backwards
                if(current_mode2 == 2){
                    backward();
                }else{
                    forward();
                }
                current_mode2 = drive_mode_fsm[current_mode2].next[3];
            break;
            case 0x52: // if char 'R' in right state
                PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY/2);
                // check if previous state backwards
                if(current_mode2 == 2){
                    backward();
                }else{
                    forward();
                }
                current_mode2 = drive_mode_fsm[current_mode2].next[4];
            break;
            case 0x55: // if char 'U' in speed up state
                current_mode2 = drive_mode_fsm[current_mode2].next[5];
                if(speed < 6) {
                    speed++;
                    }
                    if (current_mode2 == 3) {
                        PWM_Duty(speed * DEFAULT_DUTY/2, speed * DEFAULT_DUTY);
                    }
                    else if (current_mode2 == 4){
                        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY/2);
                    }
                    else{
                        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY);
                    }
            break;
            case 0x44: // if char 'D' in speed down state
                current_mode2 = drive_mode_fsm[current_mode2].next[6];
                if(speed > 1){
                   speed--;
                
									if (current_mode2 == 3){
											PWM_Duty(speed * DEFAULT_DUTY/2, speed * DEFAULT_DUTY);
									}
									else if (current_mode2 == 4){
											PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY/2);
									}
									else{
											PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY);
									}
								}
            break;            
        }
        // reads next input
        char_input = UART1_InChar();
    }
    current_mode2 = demo_mode_fsm[current_mode1].next[0];
}

// @brief: does an 8 on the floor
void figure8_operation(void){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    		for(unsigned long long i = 0; i <= 1210000; i++){}



        PWM_Duty(speed/2 * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    
    		for(unsigned long long i = 0; i <= 1210000; i++){}

    current_mode1 = demo_mode_fsm[current_mode1].next[0];
}

// @brief: Does a circle (ends where it starts)
void circle_operation(void){
		PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
		on();
		forward();   
		for(unsigned long long i = 0; i <= 1210000; i++){}

    current_mode1 = demo_mode_fsm[current_mode1].next[0];
		off();
}

// @brief: Does a square shape (ends where it starts)
void square_operation(void){
		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		forward();    //MOVE FORWARD
		for(unsigned long long i = 0; i <= 1800000/2; i++){}

		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		pivot_left();   
		for(unsigned long long i = 0; i <= 1800000/7; i++){}
    
		
		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		forward();    //MOVE FORWARD
		for(unsigned long long i = 0; i <= 1800000/2; i++){}

		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		pivot_left();   
		for(unsigned long long i = 0; i <= 1800000/7; i++){}

		
		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		forward();    //MOVE FORWARD
		for(unsigned long long i = 0; i <= 1800000/2; i++){}

		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		pivot_left();  
		for(unsigned long long i = 0; i <= 1800000/7; i++){}

		
		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
		on();
		forward();    //MOVE FORWARD
		for(unsigned long long i = 0; i <= 1800000/2; i++){}


		PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
			on();
		pivot_left();  
		for(unsigned long long i = 0; i <= 1800000/7; i++){}

    current_mode1 = demo_mode_fsm[current_mode1].next[0];
}

// @brief: Does a Z shape
void zigzag_operation(void){
    
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    for(unsigned long long i = 0; i <= 1800000/2; i++){}

        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        pivot_left();   
    for(unsigned long long i = 0; i <= 1800000/7; i++){}

        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    for(unsigned long long i = 0; i <= 1800000/2; i++){}

        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        pivot_right();   
    for(unsigned long long i = 0; i <= 1800000/7; i++){}

        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    for(unsigned long long i = 0; i <= 1800000/2; i++){}

    current_mode1 = demo_mode_fsm[current_mode1].next[0];

}