#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Transform.h"
#include "Animation.h"

using namespace std;

#define SCREEN_WIDTH 704
#define SCREEN_HEIGHT 480

#define STAGE_DELAY 20.0f

class Engine
{
	public:
		static Engine* Running() {
				return run = (run != nullptr) ? run : new Engine();
		}

		bool Init();
		bool Clean();
		void Quit();

		void Update();
		void Render();
		void Event();

		inline bool IsRunning() {return still;}
		inline SDL_Renderer* GetRenderer(){return Renderer;}

	private:
		Engine(){}
		bool still;
		bool play;
		bool resume;
		float StageDelay;
		SDL_Window* Window;
		SDL_Renderer* Renderer;
		Transform* arrow;
		Animation* gate;
		static Engine* run;
};

#endif // ENGINE_H

