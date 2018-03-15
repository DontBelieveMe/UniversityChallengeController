/*
    Author: Barney Wilks
    Date: 05-03-17
    Purpose:
        hdi.h -> Human Device Interaction
        Provides a simple interface between the hardware and user code,
        such as getting switch state or playing audio
*/

#ifndef _HDI_H
#define _HDI_H

#include "buzz.h"

// Write the specified state (HIGH or LOW) to all LED's
void write_to_all_leds(team_t* teams, int state);

// Utility function to see if the button at the specified
// GPIO pin is being pressed
int is_switch_pressed(int gpio_pin);

// Play the specified Wave (.wav) audio file
void play_wav(const char* file_name);
#endif
