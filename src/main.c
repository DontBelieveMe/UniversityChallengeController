#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "buzz.h"
#include "hdi.h"


// switch, led
// red
team_t _team1 = 
{
	{
		{ 27, 10 },
		{ 25, 9  }
	}
};

// yellow
team_t _team2 = 
{
	{
		{ 17, 8 },
		{ 22, 11 }
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
