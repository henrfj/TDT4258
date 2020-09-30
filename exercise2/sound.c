#include "sound.h"



int get_counter(int increase){
    static int counter = 0;
    if (increase!=NO_CHANGE){
        counter++;
    }
    return counter;
}

#define LEN(a) (sizeof(a)/sizeof(*a))
#define SONG(id) (id==0? song0 :(id==1? song1 : (id==2? song2 : song3)))

int song0[] = {60, 10, 1000, 9, 1000, 8, 1000, 7, 1000, 6, 1000, 1000, 1000, 6, 1000,
        1000, 1000, 5, 1000, 5, 1000, 5, 1000, 5, 1000, 6, 1000, 1000, 1000, 1000,
        1000, 7, 1000, 7, 1000, 7, 1000, 7, 1000, 8, 1000, 1000, 1000, 8, 1000,
        1000, 1000, 9, 1000, 9, 1000, 9, 1000, 9, 1000, 10, 1000, 1000, 1000, 1000, 1000};

int song1[]= {7, 10, 10, 10, 10, 10, 10, 10};

int song2[] = {7, 10, 10, 10, 10, 10, 10, 10};

int song3[] = {8, 3, 15, 3, 15, 3, 15, 3, 15};



int get_period(int mode){
    // Mode 1 => soundmodem used by timer interrupt to generate sound i DAC
    // Mode 2, .. 5 => changes the song ID, called by GPIO-button interrupt

    static int current_song_id = 0;

    // Soundmode, playing music
    if (mode == NO_CHANGE){
        static int i = 1; //index of array
        static int timer = 0; //Return chaning note counter

        int period =  SONG(current_song_id)[i];

        if (timer > 500){
            timer = 0;
            i++;
            int len = SONG(current_song_id)[0];
            if (i > len){
                i = 1;
            }
        }

        timer++;
        return period;
    }

    //Setting ID
    if (mode > NO_CHANGE){
        current_song_id = mode;
    }

    return 1;

}


int get_set_amplitude(int mode){
    static int amp = 0x0ff;

    if (mode==NO_CHANGE){
        return amp;
    }

    return amp = mode;




}


void read_button_value(int button_value){
    if (button_value == LEFT){
		//Clock gating the timer module (turns off sound)
		*CMU_HFPERCLKEN0 &= ~(1 << 6);

	}else if(button_value == RIGHT){

		//un-gate the timer module and play a tune
		*CMU_HFPERCLKEN0 |= (1 << 6);
		get_period(0); //setting sound ID = 0

	}else if(button_value == DOWNR){
        //un-gate the timer module and play a tune
		*CMU_HFPERCLKEN0 |= (1 << 6);
        get_period(1);

    }else if(button_value == DOWNL){
        //un-gate the timer module and play a tune
		*CMU_HFPERCLKEN0 |= (1 << 6);
        get_period(2);

    }else if(button_value == UPR){
        //un-gate the timer module and play a tune
		*CMU_HFPERCLKEN0 |= (1 << 6);
        get_period(3);

    }
    
}