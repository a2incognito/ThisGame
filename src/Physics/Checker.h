#ifndef CHECKER_H
#define CHECKER_H

#include "SDL.h"

class Checker
{
	public:
		inline SDL_Rect Get() {
			return Rect;
		}

		inline void SetChange (int x, int y, int w, int h) {
			Buffer = {x, y, w, h};
		}

		void SetRect (int x, int y, int w, int h) {
//			Rect = {x, y, w, h};
			Rect = {x + Buffer.x, y + Buffer.y, w - Buffer.w, h - Buffer.h};
		}

		void Print() {
			SDL_Log("%d %d", Rect.x, Rect.y);
		}

	private:
		SDL_Rect Rect;
		SDL_Rect Buffer;
};

#endif // CHECKER_H
