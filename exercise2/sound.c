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

// POLLING UNDER HERE

void polling_solution(){
    int button_value;
    while(1){ //Polling forever
        button_value = *GPIO_PC_DIN;
        if (button_value == LEFT){
            __asm__("nop");
        }else if(button_value == UPL){
            polling_play_sound(0);
        }else if(button_value == RIGHTL){
            polling_play_sound(1);
        }else if(button_value == DOWNL){
            polling_play_sound(2);
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
    int cond;
    int timer;
    float frequency;
    uint8_t ampl;
    uint8_t amplitude;
    uint8_t speed;
    float period;
    float clk_duration;

    for (int i = 1; i < len; i++){
        //get frequenct
        frequency = SONG(current_song_id)[i];
        period = 1/frequency; //in seconds

        //get amplitude
        ampl = SONG_AMPL(current_song_id)[i];
        amplitude = BASE_AMPL + (ampl<<2);  //amplitude is way too low

        //get duration
        speed = SONG_SPD(current_song_id)[i];
        clk_duration = 0.25*frequency/speed; // duration of a note in clks
        
        //Playing note with frequency and ampl, over duration.
        cond = 0;
        timer = 0;
        while(!cond){	//Duration
            if (timer < clk_duration){
                polling_one_period(amplitude, period);
                timer++;
            }else   //timer has reached condition
            {
                cond = 1;
            }
        }
    
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


void my_sleep_1(int secs) {
  unsigned int i,s;
  for (s=0; s < secs; s++) {
    for (i=0; i < CPU_FREQ; i++) {
       // skip CPU cycle or any other statement(s) for making loop 
       // untouched by C compiler code optimizations
       __asm__("nop");
    }
  }
}

void my_sleep_2(float secs) {
  	*TIMER1_TOP = secs*CPU_FREQ; //#Cycles to reach "secs"
	while(*TIMER1_CNT <= *TIMER1_TOP - 4){
		__asm__("nop");
	}
}