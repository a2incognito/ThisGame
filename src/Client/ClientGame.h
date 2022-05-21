#ifndef CLIENTGAME_H
#define CLIENTGAME_H
#include "SDL.h"
#include "Animation.h"
#include <string>
#include "Transform.h"

using namespace std;


class ClientGame
{
	public:
		static ClientGame* Running() {
			return run = (run != nullptr) ? run : new ClientGame();
		}

		const  SDL_Rect
			buttonPlay = {65, 175, 136, 47},
			buttonTutorial = {65, 239, 197, 47},
			buttonQuit = {65, 298, 106, 47},
			buttonBack = {582, 422, 103, 40};

		void Update();
		void Draw();

		int Still() {return still;}
		void Client(int change) {still = change;}

	private:
		ClientGame() {}
		static ClientGame* run;
		int still = 2;
		string type = "start";
		SDL_Window* window;
		SDL_Renderer* renderer;
		Animation* animation;
		Transform* arrow = new Transform(37, 184);
		int order = 1;
};

#endif // CLIENTGAME_H
