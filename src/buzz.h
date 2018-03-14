/*
    Author: Barney Wilks
    Date: 05-03-17
    Purpose:
        Provides some common utility functions (such as logging)
        Also defines some global constants such as number of teams or the buzzer
        sound file
        Also provides some logic (such checking for a player to press the a switch or resetting
        all switches)b
*/


#ifndef _BUZZ_H
#define _BUZZ_H

#include <stdio.h>

#define ENABLE_LOGGING

// Utility macros for printing debug messages to STDOUT
#ifdef ENABLE_LOGGING
    #define LOGF(msg, ...) printf(msg, __VA_ARGS__)
    #define LOG(msg) printf(msg)
#else
    #define LOGF(msg ...)
    #define LOG(msg)
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// The GPIO in for the reset switch
#define RESET_SWITCH 11

// How many people that there is in a team
#define HUMAN_NUM 4

// How many teams there are
#define TEAM_NUM 2


#define INVALID_PIN -1

// This would be the GPIO pin that the referee presses if the team got the 
// Correct answer
// Because this is not implemented yet I'll just set it to INVALID_PIN meaning
// that is_pressed will always return false and no logic will happen.
#define CORRECT_ANSWER_PIN INVALID_PIN

typedef struct human_t
{
    int switch_pin;
    int led_pin;
} human_t;

typedef struct team_t
{
    human_t humans[HUMAN_NUM];
    const char *sound_file_path; 
} team_t;

void check_and_handle_buzzer_presses(team_t* teams, int *pressed);

int check_and_handle_reset(team_t* teams, int *pressed);

#define BUZZER_SOUND_FILEPATH "/home/pi/Dev/buzz/dat/buzz.wav"

// The pin states HIGH and LOW are abstracted into these defines for turning an LED on and off
// This is because relays have no regard for human life. R.I.P sanity.
#define LED_ON LOW
#define LED_OFF HIGH

#endif
