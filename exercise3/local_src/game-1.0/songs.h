#ifndef _SONGS_H
#define _SONGS_H

#define SONG(id) (\
		id==0 ? song0 : \
		id==1 ? song1 : \
		id==2 ? song2 : \
		id==3 ? song3 : \
		id==4 ? song4 : \
		id==5 ? song5 : \
		id==6 ? song6 : \
		song0)		//default
#define SONG_AMPL(id) (\
		id==0 ? song0_ampl : \
		id==1 ? song1_ampl : \
		id==2 ? song2_ampl : \
		id==3 ? song3_ampl : \
		id==4 ? song4_ampl : \
		id==5 ? song5_ampl : \
		id==6 ? song6_ampl : \
		song0_ampl)	//default
#define SONG_SPD(id) (\
		id==0 ? song0_spd : \
		id==1 ? song1_spd : \
		id==2 ? song2_spd : \
		id==3 ? song3_spd : \
		id==4 ? song4_spd : \
		id==5 ? song5_spd : \
		id==6 ? song6_spd : \
		song0_spd)	//default

//block
const float song0[6] = {
	5, 391.995, 415.305, 440.0, 466.164, 493.883
};

const uint8_t song0_ampl[6] = {
	0, 15, 1, 1, 1, 15
};

const uint8_t song0_spd[6] = {
	0, 1, 3, 3, 3, 3
};

//coin
const float song1[3] = {
	2, 987.767, 1318.51
};

const uint8_t song1_ampl[3] = {
	0, 15, 1
};

const uint8_t song1_spd[3] = {
	0, 1, 1
};

//flagpole-fanfare
const float song2[47] = {
	46, 195.998, 220.0, 246.942, 261.626, 293.665, 329.628,
	349.228, 391.995, 440.0, 493.883, 523.251, 587.33, 659.255,
	698.456, 783.991, 880.0, 987.767, 1046.502, 1174.659, 1318.51,
	1396.913, 1567.982, 261.626, 329.628, 391.995, 523.251, 659.255,
	783.991, 659.255, 261.626, 311.127, 415.305, 523.251, 622.254,
	830.609, 622.254, 293.665, 349.228, 466.164, 587.33, 698.456,
	932.328, 932.328, 932.328, 932.328, 1046.502
};

const uint8_t song2_ampl[47] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 10, 15, 1, 1, 1, 1, 1, 15, 10,
	1, 1, 1, 1, 1, 15, 10, 1, 1, 1, 1, 1, 15, 1, 1,
	1, 10
};

const uint8_t song2_spd[47] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 19, 3, 3, 3, 3, 3, 1,
	3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 1,
	1, 3
};

//gym
const float song3[98] = {
	97, 329.628, 523.251, 391.995, 523.251, 293.665, 466.164,
	349.228, 466.164, 261.626, 440.0, 261.626, 440.0, 293.665,
	493.883, 523.251, 391.995, 523.251, 587.33, 466.164, 466.164,
	523.251, 391.995, 523.251, 466.164, 466.164, 523.251, 587.33,
	659.255, 587.33, 659.255, 698.456, 587.33, 587.33, 932.328,
	698.456, 698.456, 659.255, 587.33, 659.255, 698.456, 587.33,
	698.456, 932.328, 391.995, 523.251, 391.995, 466.164, 440.0,
	391.995, 349.228, 329.628, 329.628, 349.228, 391.995, 391.995,
	523.251, 391.995, 466.164, 440.0, 391.995, 329.628, 349.228,
	391.995, 523.251, 391.995, 466.164, 440.0, 391.995, 349.228,
	329.628, 329.628, 349.228, 391.995, 391.995, 391.995, 440.0,
	466.164, 523.251, 523.251, 587.33, 659.255, 329.628, 523.251,
	391.995, 523.251, 293.665, 466.164, 349.228, 466.164, 261.626,
	440.0, 261.626, 440.0, 293.665, 493.883, 329.628, 523.251,

};

const uint8_t song3_ampl[98] = {
	0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5
};

const uint8_t song3_spd[98] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

//mushroom
const float song4[7] = {
	6, 659.255, 783.991, 1318.51, 1046.502, 1174.659, 1567.982,

};

const uint8_t song4_ampl[7] = {
	0, 15, 1, 1, 1, 15, 1
};

const uint8_t song4_spd[7] = {
	0, 1, 5, 4, 4, 4, 5
};

//rescue-fanfare
const float song5[26] = {
	25, 523.251, 391.995, 329.628, 523.251, 391.995, 329.628,
	523.251, 554.365, 415.305, 349.228, 554.365, 415.305, 349.228,
	554.365, 622.254, 466.164, 391.995, 622.254, 466.164, 391.995,
	622.254, 698.456, 698.456, 698.456, 783.991
};

const uint8_t song5_ampl[26] = {
	0, 5, 1, 1, 1, 1, 1, 10, 5, 1, 1, 1, 1, 1, 10,
	5, 1, 1, 1, 1, 1, 15, 1, 1, 1, 10
};

const uint8_t song5_spd[26] = {
	0, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3,
	1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 3
};

//trainer
const float song6[739] = {
	738, 880.0, 830.609, 783.991, 739.989, 880.0, 783.991,
	739.989, 698.456, 880.0, 739.989, 698.456, 659.255, 880.0,
	698.456, 659.255, 622.254, 880.0, 659.255, 622.254, 587.33,
	880.0, 622.254, 587.33, 554.365, 880.0, 587.33, 554.365,
	523.251, 880.0, 554.365, 523.251, 493.883, 987.767, 987.767,
	880.0, 493.883, 369.994, 493.883, 369.994, 493.883, 523.251,
	493.883, 369.994, 493.883, 369.994, 493.883, 440.0, 391.995,
	587.33, 391.995, 440.0, 391.995, 659.255, 739.989, 659.255,
	783.991, 880.0, 783.991, 739.989, 659.255, 587.33, 659.255,
	739.989, 783.991, 783.991, 880.0, 783.991, 739.989, 659.255,
	739.989, 830.609, 880.0, 1108.731, 1318.51, 1174.659, 880.0,
	1046.502, 987.767, 1174.659, 880.0, 932.328, 1396.913, 1567.982,
	1318.51, 523.251, 440.0, 523.251, 440.0, 523.251, 466.164,
	698.456, 466.164, 698.456, 587.33, 523.251, 440.0, 523.251,
	659.255, 587.33, 523.251, 659.255, 587.33, 466.164, 698.456,
	783.991, 698.456, 587.33, 698.456, 659.255, 587.33, 659.255,
	1396.913, 1318.51, 1567.982, 1396.913, 659.255, 659.255, 659.255,
	659.255, 659.255, 659.255, 659.255, 659.255, 659.255, 659.255,
	659.255, 659.255, 440.0, 493.883, 391.995, 440.0, 493.883,
	554.365, 659.255, 587.33, 554.365, 493.883, 466.164, 466.164,
	523.251, 698.456, 659.255, 587.33, 523.251, 466.164, 493.883,
	493.883, 554.365, 783.991, 739.989, 659.255, 587.33, 493.883,
	523.251, 659.255, 783.991, 493.883, 369.994, 493.883, 369.994,
	493.883, 523.251, 493.883, 369.994, 493.883, 369.994, 493.883,
	440.0, 391.995, 587.33, 391.995, 440.0, 391.995, 659.255,
	739.989, 659.255, 783.991, 880.0, 783.991, 739.989, 659.255,
	587.33, 659.255, 739.989, 783.991, 783.991, 880.0, 783.991,
	739.989, 659.255, 739.989, 830.609, 880.0, 1108.731, 1318.51,
	1174.659, 880.0, 1046.502, 987.767, 1174.659, 880.0, 932.328,
	1396.913, 1567.982, 1318.51, 523.251, 440.0, 523.251, 440.0,
	523.251, 466.164, 698.456, 466.164, 698.456, 587.33, 523.251,
	440.0, 523.251, 659.255, 587.33, 523.251, 659.255, 587.33,
	466.164, 698.456, 783.991, 698.456, 587.33, 698.456, 659.255,
	587.33, 659.255, 1396.913, 1318.51, 1567.982, 1396.913, 659.255,
	659.255, 659.255, 659.255, 659.255, 659.255, 659.255, 659.255,
	659.255, 659.255, 659.255, 659.255, 440.0, 493.883, 391.995,
	440.0, 493.883, 554.365, 659.255, 587.33, 554.365, 493.883,
	466.164, 466.164, 523.251, 698.456, 659.255, 587.33, 523.251,
	466.164, 493.883, 493.883, 554.365, 783.991, 739.989, 659.255,
	587.33, 493.883, 523.251, 659.255, 783.991, 493.883, 369.994,
	493.883, 369.994, 493.883, 523.251, 493.883, 369.994, 493.883,
	369.994, 493.883, 440.0, 246.942, 261.626, 277.183, 293.665,
	311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.0,
	466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 587.33,
	554.365, 523.251, 493.883, 466.164, 440.0, 415.305, 391.995,
	369.994, 349.228, 329.628, 311.127, 293.665, 277.183, 261.626,
	261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994,
	391.995, 415.305, 440.0, 466.164, 493.883, 523.251, 554.365,
	587.33, 622.254, 659.255, 622.254, 587.33, 554.365, 523.251,
	493.883, 466.164, 440.0, 415.305, 391.995, 369.994, 349.228,
	329.628, 311.127, 293.665, 277.183, 277.183, 293.665, 311.127,
	329.628, 349.228, 369.994, 391.995, 415.305, 440.0, 466.164,
	493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456,
	659.255, 622.254, 587.33, 554.365, 523.251, 493.883, 466.164,
	440.0, 415.305, 391.995, 369.994, 349.228, 329.628, 311.127,
	293.665, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995,
	415.305, 440.0, 466.164, 493.883, 523.251, 554.365, 587.33,
	622.254, 659.255, 698.456, 739.989, 698.456, 659.255, 622.254,
	587.33, 554.365, 523.251, 493.883, 466.164, 493.883, 523.251,
	554.365, 587.33, 622.254, 659.255, 698.456, 987.767, 987.767,
	880.0, 493.883, 369.994, 493.883, 369.994, 493.883, 523.251,
	493.883, 369.994, 493.883, 369.994, 493.883, 440.0, 391.995,
	587.33, 391.995, 440.0, 391.995, 659.255, 739.989, 659.255,
	783.991, 880.0, 783.991, 739.989, 659.255, 587.33, 659.255,
	739.989, 783.991, 783.991, 880.0, 783.991, 739.989, 659.255,
	739.989, 830.609, 880.0, 1108.731, 1318.51, 1174.659, 880.0,
	1046.502, 987.767, 1174.659, 880.0, 932.328, 1396.913, 1567.982,
	1318.51, 523.251, 440.0, 523.251, 440.0, 523.251, 466.164,
	698.456, 466.164, 698.456, 587.33, 523.251, 440.0, 523.251,
	659.255, 587.33, 523.251, 659.255, 587.33, 466.164, 698.456,
	783.991, 698.456, 587.33, 698.456, 659.255, 587.33, 659.255,
	1396.913, 1318.51, 1567.982, 1396.913, 659.255, 659.255, 659.255,
	659.255, 659.255, 659.255, 659.255, 659.255, 659.255, 659.255,
	659.255, 659.255, 440.0, 493.883, 391.995, 440.0, 493.883,
	554.365, 659.255, 587.33, 554.365, 493.883, 466.164, 466.164,
	523.251, 698.456, 659.255, 587.33, 523.251, 466.164, 493.883,
	493.883, 554.365, 783.991, 739.989, 659.255, 587.33, 493.883,
	523.251, 659.255, 783.991, 493.883, 369.994, 493.883, 369.994,
	493.883, 523.251, 493.883, 369.994, 493.883, 369.994, 493.883,
	440.0, 391.995, 587.33, 391.995, 440.0, 391.995, 659.255,
	739.989, 659.255, 783.991, 880.0, 783.991, 739.989, 659.255,
	587.33, 659.255, 739.989, 783.991, 783.991, 880.0, 783.991,
	739.989, 659.255, 739.989, 830.609, 880.0, 1108.731, 1318.51,
	1174.659, 880.0, 1046.502, 987.767, 1174.659, 880.0, 932.328,
	1396.913, 1567.982, 1318.51, 523.251, 440.0, 523.251, 440.0,
	523.251, 466.164, 698.456, 466.164, 698.456, 587.33, 523.251,
	440.0, 523.251, 659.255, 587.33, 523.251, 659.255, 587.33,
	466.164, 698.456, 783.991, 698.456, 587.33, 698.456, 659.255,
	587.33, 659.255, 1396.913, 1318.51, 1567.982, 1396.913, 659.255,
	659.255, 659.255, 659.255, 659.255, 659.255, 659.255, 659.255,
	659.255, 659.255, 659.255, 659.255, 440.0, 493.883, 391.995,
	440.0, 493.883, 554.365, 659.255, 587.33, 554.365, 493.883,
	466.164, 466.164, 523.251, 698.456, 659.255, 587.33, 523.251,
	466.164, 493.883, 493.883, 554.365, 783.991, 739.989, 659.255,
	587.33, 493.883, 523.251, 659.255, 783.991, 493.883, 369.994,
	493.883, 369.994, 493.883, 523.251, 493.883, 369.994, 493.883,
	369.994, 493.883, 440.0, 587.33, 293.665, 329.628, 440.0,
	554.365, 293.665, 329.628, 440.0, 293.665, 329.628, 440.0,
	493.883, 554.365, 440.0, 293.665, 329.628, 587.33, 293.665,
	329.628, 440.0, 554.365, 293.665, 329.628, 440.0, 493.883,
	293.665, 329.628, 440.0, 220.0, 293.665, 329.628, 440.0,
	293.665, 329.628, 440.0, 587.33, 293.665, 329.628, 440.0,
	587.33, 293.665, 329.628, 440.0, 587.33, 293.665, 329.628,
	440.0, 587.33, 293.665, 329.628, 440.0, 587.33, 293.665,
	329.628, 440.0, 587.33, 293.665, 329.628, 440.0, 587.33,
	587.33, 293.665, 329.628, 440.0
};

const uint8_t song6_ampl[739] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15
};

const uint8_t song6_spd[739] = {
	0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 7, 6, 16, 1, 2, 1, 1, 1, 1, 1, 2,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
	1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
	1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7,
	6, 16, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1,
	1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
	1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1,
	4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1
};

#endif
