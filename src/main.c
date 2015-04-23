#include <wiringPi.h>
#include <stdio.h>

#include "buzz.h"

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
    #define LOGF(msg, ...) printf(msg, __VA_ARGS__)
    #define LOG(msg) printf(msg)
#else
    #define LOGF(msg ...)
    #define LOG(msg)
#endif
// switch, led
team_t _team1 = 
{
	{
		{ /*17*/ 3, 10},
		{ /*22*/ 7, 9 }
	}
};

team_t _team2 = 
{
	{
		{ 27, 11 },
		{ 2, 25   }
	}
};

static team_t _teams[TEAM_NUM];

static int is_pressed(int pin)
{
	return digitalRead(pin) == LOW;
}

int _pressed = FALSE;

static void write_to_all_leds(int state)
{
    int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(_teams[i]);
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
            human_t* human = &(team->humans[x]);
            digitalWrite(human->led_pin, state);
        }
    }
}

static void check_teams(void)
{
    int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(_teams[i]);
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
			human_t* human = &(team->humans[x]);
            printf("%i %i\n", human->switch_pin, is_pressed(human->switch_pin));
			
            if(is_pressed(human->switch_pin) && !_pressed)
            {
                digitalWrite(human->led_pin, HIGH);
                _pressed = TRUE;
            }
        }
    }
}

static void step(void)
{
	check_teams();
	
	if(is_pressed(RESET_SWITCH))
    {
        LOG(">>> Reseting all switches\n");

        write_to_all_leds(LOW);

        _pressed = FALSE;
	}
	
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

	write_to_all_leds(LOW);
    //digitalWrite(10, LOW);
	pinMode(RESET_SWITCH, INPUT);
}

static void end(void)
{
    int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(_teams[i]);
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
            human_t* human = &(team->humans[x]);
            digitalWrite(human->led_pin, LOW);
        }
    }
}

int main()
{
	setup();
	run();

	return 0;
}
