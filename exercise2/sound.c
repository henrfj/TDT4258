#include "sound.h"



int get_counter(int increase){
    static int counter = 0;
    if (increase!=NO_CHANGE){
        counter++;
    }
    return counter;
}

#define LEN(a) (sizeof(a)/sizeof(*a))
#define SONG(id) (id==0? song1 :(id==1? song2 : song3))

int a[] = {10, 1000, 9, 1000, 8, 1000, 7, 1000, 6, 1000, 1000, 1000, 6, 1000,
        1000, 1000, 5, 1000, 5, 1000, 5, 1000, 5, 1000, 6, 1000, 1000, 1000, 1000,
        1000, 7, 1000, 7, 1000, 7, 1000, 7, 1000, 8, 1000, 1000, 1000, 8, 1000,
        1000, 1000, 9, 1000, 9, 1000, 9, 1000, 9, 1000, 10, 1000, 1000, 1000, 1000, 1000};

int b[]= {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

int c[] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};

int d[] = {3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15,3,15};



int get_period(int mode){
    // Mode 1 => soundmodem used by timer interrupt to generate sound i DAC
    // Mode 2, .. 5 => changes the song ID, called by GPIO-button interrupt

    static int current_song_id = 0;

    // Soundmode, playing music
    if (mode == NO_CHANGE){
        static i = 0; //index of array
        static timer = 0; //Return chaning note counter



        SONG(current_song_id);


        
        
        int period = a[i];

        if (timer > 500){
            timer = 0;
            i++;
            if (i == LEN(a)){
                i = 0;
            }
    
    int period = a[i];

        }

        timer++;
        return period;
    }

    //Setting ID
    if (mode > NO_CHANGE){
        current_song_id = mode;
    }

}


int get_set_amplitude(int mode){
    static int amp = 0x0ff;

    if (mode==NO_CHANGE){
        return amp;
    }

    return amp = mode;




}
