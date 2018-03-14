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

#include <buzz/hdi.h>

// The function callback that will play the sound effect in another thread
void *play_wav_async(void* arg)
{
    char *command_string = (char*)arg;

    system(command_string);
    
    // Now that the system has finished playing the audio, close this thread.
    pthread_exit(NULL);
    
    return NULL;
}

void play_wav(const char* file_name) 
{
	char buff[256]; 
    
    // Here we construct the command string.  
	// The `-q` means don't output anything to STDOUT (`quiet mode`)
	strcpy(buff, "aplay -q ");
	strcat(buff, file_name);
    
    // Play the sound effect in another thread.
    // This is because `system(...)` is a blocking call, meaning
    // The next line of code will not be executed until it has finished.
    // As a result of this, the app will not read the reset button until the audio
    // has finished playing -> Specifically if you press the reset button whilst
    // the buzzer sound is playing then it will not actually reset.
    // Running the audio in a background thread solves this issue.
    pthread_t audio_thread;
    pthread_create(&audio_thread, NULL, play_wav_async, buff);
}

void write_to_all_leds(team_t* teams, int state)
{
    for(int i = 0; i < TEAM_NUM; ++i)
    {
        team_t* team = &(teams[i]);

        for(int x = 0; x < HUMAN_NUM; ++x)
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
