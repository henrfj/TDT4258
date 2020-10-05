#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

void setupGPIO();
void setupDAC();
void setupNVIC();
void polling_solution();

int main(void){



    setupDAC();
    setupGPIO();
    polling_solution();




}

void polling_solution(){
    int button_value = *GPIO_PC_DIN;
    uint8_t playing = 0;
    while(1){
        if(playing){

        }else{
            read_button_value(button_value);
            printf("%d", button_value);
        }

    }

}
