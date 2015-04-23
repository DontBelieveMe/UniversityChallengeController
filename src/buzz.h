#ifndef _BUZZ_H
#define _BUZZ_H

#include <stdio.h>

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
    #define LOGF(msg, ...) printf(msg, __VA_ARGS__)
    #define LOG(msg) printf(msg)
#else
    #define LOGF(msg ...)
    #define LOG(msg)
#endif

#define RESET_SWITCH 24

#define TRUE 1
#define FALSE 0

#define HUMAN_NUM 2
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
