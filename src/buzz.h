#ifndef _BUZZ_H
#define _BUZZ_H

#define RESET_SWITCH 4

#define TRUE 1
#define FALSE 0

typedef struct human_t
{
    int switch_pin;
    int led_pin;
} human_t;

#define HUMAN_NUM 2

typedef struct team_t
{
    human_t humans[HUMAN_NUM];
} team_t;

#define TEAM_NUM 2

#endif
