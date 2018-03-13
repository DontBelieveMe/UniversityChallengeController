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
//      { 27 -> Switch, 10 -> LED }

// Red Leds (as of writing 05-03-18)

// 23, 18, 15, 14
team_t _team1 = 
{
    {
        { 14, -1 },
        { 15, 25 },  
        { 18, 8  },
        { 23, 7  }
    }
};

//2,3,4,17
// Yellow Leds (as of writing 05-03-18)
team_t _team2 = 
{
    {
        { 4,  -1  }, //2,25
        { 17, 10  }, //3,24
        { 21, 22  },
        { 24, 9 }
    }
};

static team_t _teams[TEAM_NUM];

int _pressed = FALSE;   

static void step(void)
{
    int has_reset = check_and_handle_reset(_teams, &_pressed);
    
    if(!has_reset) {
        check_and_handle_buzzer_presses(_teams, &_pressed);
    }
    
    delay(16);
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
    
            // Configure 
            pullUpDnControl(human->switch_pin, PUD_DOWN);
        }
    }

    write_to_all_leds(_teams, LED_OFF);
    
    pinMode(RESET_SWITCH, INPUT);
}

static void end(void)
{
    write_to_all_leds(_teams, LED_OFF);
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
