#include "sound.h"

int get_counter(int increase){
    static int counter = 0; 
    if (increase!=NO_CHANGE){
        counter++;
    }
    return counter;
}

int get_set_amplitude(int mode){
    static int amp = 0x0ff;
    
    if (mode==NO_CHANGE){ 
        return amp;
    }

    return amp = mode;




}