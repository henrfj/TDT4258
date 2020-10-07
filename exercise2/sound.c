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
		//un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(0));
	} else if(button_value == UPL){
		//un-gate the timer module and play a tune
		PLAY();
		play_song(NEW_TONE(1)); //setting sound ID = 0
	} else if(button_value == RIGHTL){
        //un-gate the timer module and play a tune
		PLAY();
        play_song(NEW_TONE(2));
    } else if(button_value == DOWNL){
        //Clock gating the timer module (turns off sound)
		PAUSE();
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

// POLLING UNDER HERE

void polling_solution(){
    int button_value = 0xff;
    while(1){ //Polling forever
        button_value = *GPIO_PC_DIN;
        if (button_value == LEFT){
            polling_play_sound(0);
        }else if(button_value == UPL){
            polling_play_sound(1);
        }else if(button_value == RIGHTL){
            polling_play_sound(2);
        }else if(button_value == DOWNL){
            __asm__("nop");
        }else if(button_value == LEFTR){
            polling_play_sound(3);
        }else if(button_value == UPR){
            polling_play_sound(4);
        }else if(button_value == RIGHT){
            polling_play_sound(5);
        }else if(button_value == DOWNR){
            polling_play_sound(6);
        }

    }   

}

void polling_play_sound(int current_song_id){
    int len = SONG(current_song_id)[0];
    float frequency;
    uint8_t ampl;
    uint8_t amplitude;
    uint8_t speed;
    float period;
    double duration;
    double compond_timer;

    for (int i = 1; i < len + 1; i++){
        //get frequenct
        frequency = SONG(current_song_id)[i];
        period = 1.0/(frequency); //in seconds

        //get amplitude
        ampl = SONG_AMPL(current_song_id)[i];
        amplitude = GET_AMPL(ampl);  //amplitude is way too low

        //get duration. "1/speed" is no. 1/16 of a beat
        speed = SONG_SPD(current_song_id)[i];
        duration = (BEAT / speed) * frequency; //duartion in num_periods
        
        //duration = (BEAT / speed); //duartion in seconds (BEAT = seconds/beat)
        //clk_duration = duration * CPU_FREQ; // shoul be multiplied by CPU_FREQ

        compond_timer = 0;
        while(compond_timer < duration){
            polling_one_period(amplitude, period);
            compond_timer++;
        }
        
        
        
        /*
        cond = 0;
        //Reset timer
        *TIMER1_CNT = 0;  
        while (!cond){
            compond_timer += *TIMER1_CNT;
            *TIMER1_CNT = 0;
            polling_one_period(amplitude, period);
            if (compond_timer > clk_duration){
                cond = 1;
            }
        }
        */
        
    }

}

void polling_one_period(uint8_t amplitude, float period){
	//12-bit registers, dont forget
	*DAC0_CH0DATA = amplitude;
	*DAC0_CH1DATA = amplitude;
	my_sleep_2(period/2);
	*DAC0_CH0DATA = 0x000;
	*DAC0_CH1DATA = 0x000;	
	my_sleep_2(period/2);
}

void test_timer(){
    //Find the scalar for timer 2
    int button_value;
    while(1){
        button_value = *GPIO_PC_DIN;
        if (button_value == LEFT){
            my_sleep_2(2);
        }
        polling_one_period(0x5f, 0.005);
        
    }
}


void my_sleep_1(float secs) {
  //Uses timer module timer to sleep.
  //Haven't worked so far.
}

void my_sleep_2(float secs) {
    //TODO: test accuracy of sleep
    float scalar = 11.5;
    float scaled = secs/scalar;
  	int roof = scaled*CPU_FREQ; //#Cycles to reach "secs"
    int i = 0;
	while(i < roof){
		__asm__("nop");
        i++;
	}
}