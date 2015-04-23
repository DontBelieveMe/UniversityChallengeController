/*
	Author: Barney Wilks
	Date: 05-03-17
	Purpose:
		Contains entry point ( main() ) and the central response
		loop. E.g every check or input/output comes back to this file.
		Also contains the GPIO pins that describes each team/player.
		This function sets up the switch pins for INPUT and the led pins for output.
		Also checks for exit and will reset the leds.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "buzz.h"
#include "hdi.h"

// The order is the switch pin and then the LED. e.g 
//		{ 27 -> Switch, 10 -> LED }

// Red Leds (as of writing 05-03-18)
team_t _team1 = 
{
	{
		{ 27, 10 },
		{ 25, 9  },
		{ 14, 9 }
	}
};

// Yellow Leds (as of writing 05-03-18)
team_t _team2 = 
{
	{
		{ 17, 8 },
		{ 22, 11 },
		{ 15, 11 }
	}
};

static team_t _teams[TEAM_NUM];

int _pressed = FALSE;	

static void step(void)
{
	check_and_handle_buzzer_presses(_teams, &_pressed);
	check_and_handle_reset(_teams, &_pressed);

	delay(10);
}

static void run(void)
{
    LOG(">>> Running setup\n");

	while(1)
    {
		step();
	}
}

static void setup(void)
{
	wiringPiSetupGpio();
	
	_teams[0] = _team1;
	_teams[1] = _team2;
	
    int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(_teams[i]);
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
            human_t* human = &(team->humans[x]);
			
            pinMode(human->switch_pin, INPUT);
            pinMode(human->led_pin, OUTPUT);
        }
    }

	write_to_all_leds(_teams, LOW);
    
	pinMode(RESET_SWITCH, INPUT);
}

static void end(void)
{
    write_to_all_leds(_teams, LOW);
}

void sigint_handler(int num)
{
	end();
	exit(0);
}

int main()
{
	// When Ctrl-C is pressed we want to correctly handle it by resetting all
	// LEDs to LOW before terminating.
	signal(SIGINT, sigint_handler);
	
	setup();
	run();

	return 0;
}
