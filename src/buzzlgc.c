#include <wiringPi.h>
#include <stdlib.h>

#include <buzz/buzz.h>
#include <buzz/hdi.h>

int _reset_once = FALSE;

void check_and_handle_buzzer_presses(team_t* teams, int *pressed)
{
    for(int i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(teams[i]);
        
        for(int x = 0; x < HUMAN_NUM; ++x)
        {
            human_t* human = &(team->humans[x]);
                      
            if(is_switch_pressed(human->switch_pin) && !(*pressed)) 
            {
                printf("Please press the reset button. Ta\n");
		        
                // This check was implemnted during a dark time when we didn't
                // have enough GPIO pins. Basically this allows some switches
                // not to have an assosiated LED
                if(human->led_pin > 0)
                {
                    // Turn on that players button LED.
                    digitalWrite(human->led_pin, LED_ON);

                    // Now lock out any other buttons until the reset button
                    // is pressed, setting this flag to FALSE and meaning 
                    // any button can be pressed again.
                    *pressed = TRUE;
                    
                    _reset_once = FALSE;

                    // Play the teams sound effect -> This is different for each
                    // team, hence why it is stored in the `team_t` struct.
                    // TODO: This sound effect should be able to be customised
                    //       for each player.
                    //printf("%i %i\n", i, x);
                    if(i == 1 && x == 3) play_wav("/home/pi/Dev/buzz/dat/dave.wav");
                    else play_wav(team->sound_file_path);
                }	
            }
        }
    }
}

int check_and_handle_reset(team_t* teams, int *pressed)
{
    if(is_switch_pressed(RESET_SWITCH) && !_reset_once)
    {
        printf("Buttons have been RESET!\n");

        write_to_all_leds(teams, LED_OFF);
        
        // Disable the lock on all the other buttons, reseting the game state so
        // that now all the buttons are in play again (aka can be pressed).
        *pressed = FALSE;
        play_wav("/home/pi/Dev/buzz/dat/reset.wav");
        
        // This means the reset logic only triggers once. Even if the switch is
        // held down
        _reset_once = TRUE;
        return TRUE;
    }
    
    return FALSE;
}
