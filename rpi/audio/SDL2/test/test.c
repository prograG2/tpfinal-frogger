#include <SDL2/SDL.h>
#include "../audio.h"

#define S2WAIT 30

#define DOOR1 "../sounds/door1.wav"
#define DOOR2 "../sounds/door2.wav"
#define HIGHLANDS "../music/highlands.wav"
#define ROAD "../music/road.wav"

void memory_fun(Audio * memorySound);
void disk_fun(void);

int main(void)
{
    /* Init SDL2-Audio */
    if ( initAudio() == NO_INIT)
    {
        fprintf(stderr, "Audio not initilized.\n");
	endAudio();
	return 1;
    }

    /* Play music and a sound reading them from disk */
    /* This method is slow and needs lots of I/O from disk. 
       A better approach is explained below. */
    playMusic(HIGHLANDS, SDL_MIX_MAXVOLUME);

    printf("Showcase\n");
    if ( playerStatus() == READY && musicStatus() == PLAYING)
    {
        printf("Music playing ok.\n");
    }
    
    disk_fun();

    SDL_Delay(500);
    
    /* We can stop our music */
    printf("Pausing and waiting 1.5 seconds\n");
    pauseAudio();
    if ( musicStatus() == PAUSED )
    {
        printf("Music paused.\n");
    }

    SDL_Delay(1500);

    /* And play it back again for a second */
    printf("Continuing...\n");
    unpauseAudio();
    SDL_Delay(1000);

    if ( musicStatus() == PLAYING )
    {
        printf("Music unpaused.\n");
    }

    /* We're also able to read a whole music file once and load it in RAM */
    /* This is far better than reading every byte from disk all time. 
       Specially if we're going to play the same song over and over again */
    printf("Loading new audio in memory.\n");

    Audio * sound = createAudio(DOOR2, 0, SDL_MIX_MAXVOLUME / 2);
    Audio * music = createAudio(ROAD, 1, SDL_MIX_MAXVOLUME);

    printf("Loaded.\n");

    /* Change music track */
    printf("Playing new music!\n");
    playMusicFromMemory(music, SDL_MIX_MAXVOLUME);

    memory_fun(sound);

    printf("Bye bye!\n");

    /* End Simple-SDL2-Audio */
    endAudio();

    /* It's VERY important to free all audio samples after ending 
       Simple-SDL2-Audio because they might be referenced still */
    freeAudio(sound);
    freeAudio(music);

    return 0;
}


/* Play some sound loaded in memory every 5 seconds. */
void memory_fun(Audio * memorySound)
{
    int i = 1;

    for (i = 1; i < S2WAIT; i++)
    {
        printf("%d ",i);
        fflush(stdout);
        if (i % 5 == 0)
        {
            printf("Door\n");
            playSoundFromMemory(memorySound, SDL_MIX_MAXVOLUME / 2);
        }

        SDL_Delay(1000);

    }
    putchar('\n');
}

/* Play some sound in disk every 5 seconds. */
void disk_fun(void)
{
    int i;
    for (i = 1; i <= S2WAIT/3; i++)
    {
        printf("%d ",i);
        fflush(stdout);
        if (i % 5 == 0)
        {
            printf("Door\n");
            playSound(DOOR1, SDL_MIX_MAXVOLUME / 2);
        }

        SDL_Delay(1000);

    }
    putchar('\n');
}
