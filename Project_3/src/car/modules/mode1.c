// mode1.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: Handles Mode 1 functionality
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
// main contributor: Justin Narciso

#include "mode1.h"

extern int current_mode1;


void figure8_operation(void){
    
    for(int i = 0; i <= 16000000; i++){ 
        forward(15);    //MOVE FORWARD
    }

    for(int i = 0; i <= 16000000; i++){
        right_forward(5); //TURN RIGHT UNTTIL TURN BACKS
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        right_forward(5);
    }

    current_mode1 = 0;
}

void circle_operation(void){

     for(int i = 0; i <= 64000000; i++){
        right_forward(15);
    }

    current_mode1 = 0;

}

void square_operation(void){

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 8000000; i++){
        right_forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 8000000; i++){
        right_forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 8000000; i++){
        right_forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 8000000; i++){
        right_forward(15);
    }

    current_mode1 = 0;
}

void zigzag_operation(void){
    
    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 24000000; i++){
        right_forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    for(int i = 0; i <= 24000000; i++){
        left_forward(15);
    }

    for(int i = 0; i <= 16000000; i++){
        forward(15);
    }

    current_mode1 = 0;

}