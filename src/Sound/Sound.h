#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <iostream>
#include <string>
using namespace std;

class Sound
{
	public:
		static Sound* Running() {
			return run = (run != nullptr) ? run : new Sound();
		}

		//void play(string path, int loops);

	private:
		Sound() {}
		static Sound* run;
};

#endif // SOUND_H
