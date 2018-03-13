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
            
            printf("%i %i\n", human->switch_pin, is_switch_pressed(human->switch_pin));
            
            
            if(is_switch_pressed(human->switch_pin) && !(*pressed))
            
            {
                if(human->led_pin > 0)
                {
                digitalWrite(human->led_pin, LED_ON);
                *pressed = TRUE;

                play_wav(BUZZER_SOUND_FILEPATH);
            }
            
            }
        }
    }
}

int check_and_handle_reset(team_t* teams, int *pressed)
{
    if(!is_switch_pressed(RESET_SWITCH))
    {
        LOG(">>> Reseting all switches\n");

        write_to_all_leds(teams, LED_OFF);

        *pressed = FALSE;
        return TRUE;
    }
    
    return FALSE;
}
