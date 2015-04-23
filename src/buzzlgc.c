#include <wiringPi.h>
#include <stdlib.h>
#include "buzz.h"
#include "hdi.h"

void check_and_handle_buzzer_presses(team_t* teams, int *pressed)
{
	int i;
    for(i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(teams[i]);
        
        int x;
        for(x = 0; x < HUMAN_NUM; ++x)
        {
			human_t* human = &(team->humans[x]);
            
            if(is_switch_pressed(human->switch_pin) && !(*pressed))
            {
			    digitalWrite(human->led_pin, HIGH);
                *pressed = TRUE;
                
                // TODO: 
                // 		This works but there is a delay before the sound plays
                // 		This is probably a combination of starting an system process and then the 
                // 		work that the process itself does.
                // 		Ideally we should be able to play the sound from code
                // 		Implement this.
            	system("omxplayer -o local /home/pi/python_games/beep2.ogg --vol 1750");
            }
        }
    }
}

void check_and_handle_reset(team_t* teams, int *pressed)
{
	if(is_switch_pressed(RESET_SWITCH))
    {
        LOG(">>> Reseting all switches\n");

        write_to_all_leds(teams, LOW);

        *pressed = FALSE;
	}

}
