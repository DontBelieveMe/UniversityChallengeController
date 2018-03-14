/*
    Author: Barney Wilks
    Date: 05-03-17
    Purpose:
        hdi.h -> Human Device Interaction
        Provides a simple interface between the hardware and user code,
        such as getting switch state or playing audio
*/

#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "hdi.h"

void *play_wav_async(void* arg)
{
    char *param = (char*)arg;
    system(param);

    pthread_exit(NULL);
    
    return NULL;
}

void play_wav(const char* file_name) 
{
	char buff[256]; 
	
	// The `-q` means don't output anything to STDOUT (`quiet mode`)
	strcpy(buff, "aplay -q ");
	strcat(buff, file_name);
    
    pthread_t pth;
    pthread_create(&pth, NULL, play_wav_async, buff);
}

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
