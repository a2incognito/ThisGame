#ifndef AMTHANH_H
#define AMTHANH_H

#include "SDL_mixer.h"
#include <iostream>
#include <string>
using namespace std;

class Amthanh
{
	public:
		static Amthanh* Running() {
			return run = (run != nullptr) ? run : new Amthanh();
		}

		void play(string path, int loops);

	private:
		Amthanh() {}
		static Amthanh* run;
};

#endif // AMTHANH_H
