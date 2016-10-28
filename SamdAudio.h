/*
 * Copyright Theo Meyer (c) 2016
 *
 * Audio library for Arduino Zero.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
	
#ifndef SAMDAUDIO_H
#define SAMDAUDIO_H

#include "Arduino.h"
#include "Print.h"

#include <SdFat.h>
extern SdFat SD;


class SamdAudio{
public:

    SamdAudio(){};
	void begin(uint32_t sampleRate);
    void play(const char *fname, uint8_t channel) ;
    //void play(const char *fname) ;
    void stopChannel(uint8_t c);
    void loopChannel(uint8_t c, bool loopEnable);
    
    bool isPlaying(uint8_t c);
    void setGain(uint8_t v);
    void gainUp();
    void gainDown();
    
    void setChannelVolume(uint8_t c, uint8_t v);
	void end();

    void criticalON();
    void criticalOFF();
    

private:
	void dacConfigure(void);
    
    //The first timer is used to feed the DAC with data every 1/sampleRate sec
	void configurePlayerTimer(uint32_t sampleRate);
	bool syncPlayerTimer(void);
	void resetPlayerTimer(void);
	void enablePlayerTimer(void);
	void disablePlayerTimer(void);
    
    //the second timer is used to read audio data from the SD card every 15.6ms
    void configureReaderTimer();
    void enableReaderTimer();
    void disableReaderTimer();

    void updaterConfigure();
    
    bool alonePlaying(uint8_t channel);
    bool someonePlaying();
    

};
#endif //SAMDAUDIO_H