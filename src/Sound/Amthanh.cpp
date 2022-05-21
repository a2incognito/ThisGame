#include "Amthanh.h"

Amthanh* Amthanh::run = nullptr;

using namespace std;

void Amthanh::play(string path, int loops)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
  Mix_PlayChannel(-1, chunk, loops);
}
