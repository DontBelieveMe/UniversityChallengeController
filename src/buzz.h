/*
	Author: Barney Wilks
	Date: 05-03-17
	Purpose:
		Provides some common utility functions (such as logging)
		Also defines some global constants such as number of teams or the buzzer
		sound file
		Also provides some logic (such checking for a player to press the a switch or resetting
		all switches)
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


#define TRUE 1
#define FALSE 0

// The GPIO in for the reset switch
#define RESET_SWITCH 24

// How many people that there is in a team
#define HUMAN_NUM 3

// How many teams there are
#define TEAM_NUM 2

typedef struct human_t
{
    int switch_pin;
    int led_pin;
} human_t;

typedef struct team_t
{
    human_t humans[HUMAN_NUM];
} team_t;

void check_and_handle_buzzer_presses(team_t* teams, int *pressed);

void check_and_handle_reset(team_t* teams, int *pressed);

#define BUZZER_SOUND_FILEPATH "/home/pi/python_games/match0.wav"

#endif
