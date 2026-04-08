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
//#include "../DRIVERS/Switches.h"
int current_mode1 = 0;
int current_mode2 = 0;
extern bool SW1_PRESSED;

extern void forward(void);
extern void backward(void);
extern void off(void);
extern void on(void);

uint8_t speed = 1;

extern void PWM_Duty(unsigned long duty_L, unsigned long duty_R);


enum mode_one_states { 
    IDLE,
    FIGURE8,
    CIRCLE,
    SQUARE,
    ZIGZAG,
//    EXIT_MODE1
};


// states_one demo_mode_fsm[6]={ 
//     {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG, EXIT_MODE1}},
//     {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG, EXIT_MODE1}},
//     {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG, EXIT_MODE1}},
//     {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG, EXIT_MODE1}},
//     {{IDLE,     FIGURE8,CIRCLE, SQUARE, ZIGZAG, EXIT_MODE1}},
//     {{IDLE,     IDLE,   IDLE,   IDLE,   IDLE,   IDLE}}
// };

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
//    EXIT_MODE2 
};


// states_two drive_mode_fsm[8]={ 
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN,EXIT_MODE2}},
//     {{STOP,STOP,   STOP,    STOP,STOP, STOP,   STOP,     STOP}}
// };

states_two drive_mode_fsm[7]={ 
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
    {{STOP,FORWARD,BACKWARD,LEFT,RIGHT,SPEEDUP,SPEEDDOWN}},
};

void mode_one_manager(void){
    
    uint8_t char_input = UART1_InChar();
    
    while(!SW1_PRESSED){

        switch(char_input){ //check for the read char value from the Bluetooth
            case 0x38: // if char '8' in figure 8 state
                current_mode1 = demo_mode_fsm[current_mode1].next[1];
                figure8_operation();
            break;
            case 0x67: // if char 'C' in circle state
                current_mode1 = demo_mode_fsm[current_mode1].next[2];
                circle_operation();
            break;
            case 0x53: // if char 'S' in square state
                current_mode1 = demo_mode_fsm[current_mode1].next[3];
                square_operation();
            break;
            case 0x5A: // if char 'Z' in zigzag state
                current_mode1 = demo_mode_fsm[current_mode1].next[4];
                zigzag_operation();
            break;
            default: // defaulting to an idle state so it does not perform unneccessary operation
                current_mode1 = demo_mode_fsm[current_mode1].next[0];
                off();
            break;
        }
        // reads next input
        
        char_input = UART1_InChar();

    //     while next input isn't valid:
    //    while(char_input != 0x55 || char_input != 0x53 || char_input != 0x46 || char_input != 0x42 || char_input != 0x4C || char_input != 0x52 || char_input != 0x44){
    //        char_input = UART1_InChar(); // keep reading inputs
    //    } 
        
    }
    current_mode1 = demo_mode_fsm[current_mode1].next[0];

}


void mode_two_manager(void){
    
    uint8_t char_input = UART1_InChar();

    // if (!SW1_PRESSED){ //check if SW1_PRESSED if so indication to exit and switch to mode 1
    //     current_mode1 = demo_mode_fsm[current_mode1].next[0];
    //     //other major value resets
    //     return;
    // }

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
                if(speed < 15) {
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
                }
                if (current_mode2 == 3){
                    PWM_Duty(speed * DEFAULT_DUTY/2, speed * DEFAULT_DUTY);
                }
                else if (current_mode2 == 4){
                    PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY/2);
                }
                else{
                    PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY);
                }
            break;            
        }
        // reads next input
        char_input = UART1_InChar();

        // while next input isn't valid:
        while(char_input != 0x55 || char_input != 0x53 || char_input != 0x46 || char_input != 0x42 || char_input != 0x4C || char_input != 0x52 || char_input != 0x44){
            char_input = UART1_InChar(); // keep reading inputs
						if (!SW1_PRESSED){
							return;
						}
        } 
    }
    current_mode2 = demo_mode_fsm[current_mode1].next[0];
}





void figure8_operation(void){
    
    for(int i = 0; i <= 16000000; i++){ 
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){ 
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }


    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();    
    }

    // for(int i = 0; i <= 16000000; i++){ 
    //     PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
    //     on();
    //     forward();    //MOVE FORWARD
    // }

    current_mode1 = demo_mode_fsm[current_mode1].next[0];
}

void circle_operation(void){

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    current_mode1 = demo_mode_fsm[current_mode1].next[0];

}

void square_operation(void){

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }

    for(int i = 0; i <= 8000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }

    for(int i = 0; i <= 8000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }

    for(int i = 0; i <= 8000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();    //MOVE FORWARD
    }

    for(int i = 0; i <= 8000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    current_mode1 = demo_mode_fsm[current_mode1].next[0];
}

void zigzag_operation(void){
    
    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    }

    for(int i = 0; i <= 24000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    }

    for(int i = 0; i <= 24000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed/2 * DEFAULT_DUTY); 
        on();
        forward();   
    }

    for(int i = 0; i <= 16000000; i++){
        PWM_Duty(speed * DEFAULT_DUTY, speed * DEFAULT_DUTY); 
        on();
        forward();
    }

    current_mode1 = demo_mode_fsm[current_mode1].next[0];

}