#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Running = nullptr;

void Timer::Tick() {
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (FPS / 1000.0f);

	if (m_DeltaTime > DELTATIME) {
		m_DeltaTime = DELTATIME;
	}

	m_LastTime = SDL_GetTicks();
}
