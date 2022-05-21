#ifndef COLLISIONHANDLING_H
#define COLLISIONHANDLING_H

#include "SDL.h"
//#include "Map.h"
#include <vector>
#include "MapCode.h"
#include "Warrior.h"

using namespace std;

class CollisionHandling
{
	public:
		bool MapCollision (SDL_Rect a);
		bool Check (SDL_Rect a, SDL_Rect b);
		bool CheckNextMap (SDL_Rect a);

		void GetMapCode();

		static CollisionHandling* Running() {
			return run = (run != nullptr) ? run : new CollisionHandling();
		}

	private:
		CollisionHandling() {}
		static CollisionHandling* run;
		int base[30][30];

};

#endif // COLLISIONHANDLING_H
