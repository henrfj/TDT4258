#include "sound.h"
#include "songs.h"

int play_song(int mode){
    // Mode 1 => soundmodem used by timer interrupt to generate sound i DAC
    // Mode 2, .. 5 => changes the song ID, called by GPIO-button interrupt

    static uint8_t current_song_id = 0;
    static uint16_t i = 1; //index of array
    static uint16_t timer = 0; //Return chaning note counter
    uint8_t ret = GO_ON;

    // Soundmode, playing music
    if (mode == NO_CHANGE){

        float frequency = SONG(current_song_id)[i];
        uint8_t ampl = SONG_AMPL(current_song_id)[i];
        uint8_t speed = SONG_SPD(current_song_id)[i];

        if (timer == 1) {
            SET_FREQ(frequency); //set the new frequency on the timer
            get_set_amplitude(GET_AMPL(ampl));
        } else if (timer > GET_DURATION(frequency, speed)){
            timer = 0;
            i++;
            int len = SONG(current_song_id)[0];
            if (i > len){
                i = 1;
                ret = STOP_HERE;
                get_set_song_done(SET_DONE, 1);
            }
        }

        timer++;
        return ret;
    }

    //Setting ID
    if (mode > NO_CHANGE){
        if(current_song_id != mode) { //restart the song if new
            i = 1;
            timer = 0;
        }
        current_song_id = mode;
    }

    return 1;

}


int get_set_amplitude(int mode){
    static int amp = BASE_AMPL;

    if (mode==NO_CHANGE){
        return amp;
    }

    return amp = mode;
}


void read_button_value(int button_value){
    if (button_value == LEFT){
		//Clock gating the timer module (turns off sound)
		PAUSE();
	} else if(button_value == UPL){
		//un-gate the timer module and play a tune
		PLAY();
		play_song(NEW_TONE(0)); //setting sound ID = 0
	} else if(button_value == RIGHTL){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(1));
    } else if(button_value == DOWNL){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(2));
    } else if(button_value == LEFTR){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(3));
    } else if(button_value == UPR){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(4));
    } else if(button_value == RIGHT){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(5));
    } else if(button_value == DOWNR){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(6));
    }
}


int get_set_song_done(int mode, int value){
    static int song_done;
    if (mode==GET_DONE){
        return song_done;

    }else if(mode==SET_DONE){
        song_done = value;
        return 0;
    }

}