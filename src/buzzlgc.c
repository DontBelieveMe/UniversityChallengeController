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
                printf("Switch Pressed %i %i\n", human->switch_pin, human->led_pin);
		        
                // This check was implemnted during a dark time when we didn't
                // have enough GPIO pins. Basically this allows some switches
                // not to have an assosiated pin
                if(human->led_pin > 0)
                {
                    // Turn on that players button LED.
			        digitalWrite(human->led_pin, LED_ON);

                    // Now lock out any other buttons until the reset button
                    // is pressed, setting this flag to FALSE and meaning 
                    // any button can be pressed again.
                    *pressed = TRUE;
                    
                    // Play the teams sound effect -> This is different for each
                    // team, hence why it is stored in the `team_t` struct.
                    // TODO: This sound effect should be able to be customised
                    //       for each player.
                    play_wav(team->sound_file_path);
                }	
            }
        }
    }
}

int check_and_handle_reset(team_t* teams, int *pressed)
{
    // The reset switch input is inverted (i.g LOW when it is pressed)
    // Because of a wiring mistake. Blame oliver. Ta
    if(!is_switch_pressed(RESET_SWITCH))
    {
        LOG(">>> Reseting all switches\n");

        write_to_all_leds(teams, LED_OFF);
        
        // Disable the lock on all the other buttons, reseting the game state so
        // that now all the buttons are in play again (aka can be pressed).
        *pressed = FALSE;

        return TRUE;
    }
    
    return FALSE;
}
