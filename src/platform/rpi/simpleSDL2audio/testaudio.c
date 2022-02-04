#include <unistd.h>
#include "audio.h"

int main(){
  SDL_Init(SDL_INIT_AUDIO);
  initAudio();

  Audio *musica = createAudio("../../../../res/sounds/streams/ranking_theme.wav", 1, SDL_MIX_MAXVOLUME);
  playMusicFromMemory(musica, SDL_MIX_MAXVOLUME);

  SDL_Delay(10000);
  freeAudio(musica);
  endAudio();
  SDL_Quit();
}