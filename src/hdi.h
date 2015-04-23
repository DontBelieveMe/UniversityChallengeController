#ifndef _HDI_H
#define _HDI_H

#include "buzz.h"

void write_to_all_leds(team_t* teams, int state);

int is_switch_pressed(int gpio_pin);

#endif
