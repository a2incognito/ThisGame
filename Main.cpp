#include "Engine.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Timer.h"
#include "TextureManager.h"

using namespace std;

int main(int argc, char** argv) {
	Engine::Running()->Init();

//	while

	while(Engine::Running()->IsRunning()) {
		Engine::Running()->Event();

		Engine::Running()->Update();

		Engine::Running()->Render();

		Timer::Running()->Tick();
	}

	Engine::Running()->Clean();


	return 0;
}
