#include "hdi.h"

#include <wiringPi.h>

void write_to_all_leds(team_t* teams, int state)
{
	int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(teams[i]);
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
            human_t* human = &(team->humans[x]);
            digitalWrite(human->led_pin, state);
        }
    }
}

int is_switch_pressed(int gpio_pin)
{
	return digitalRead(gpio_pin) == HIGH;
}
