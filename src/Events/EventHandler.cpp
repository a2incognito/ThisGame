#include "EventHandler.h"
#include "Engine.h"
#include "SDL.h"
//#include <bits/stdc++.h>

EventHandler* EventHandler::check = nullptr;

//EventHandler ::

EventHandler::EventHandler(){
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::Input() {
	// know currently pending event is press or not
	SDL_Event event;

	while (SDL_PollEvent(&event)) { // poll for currently pending event
		switch (event.type) {
			case SDL_QUIT: Engine :: Running() -> Quit(); break;
			case SDL_KEYDOWN: Down(); break; // player press
			case SDL_KEYUP: Up(); break; // player put
		}
	}
}

bool EventHandler::GetKey(SDL_Scancode key) {
//	m_KeyStates[key] = false;
	if(m_KeyStates[key] == 1) {
		return true;
	}
	return false;
}

bool EventHandler::GetKeyClient(SDL_Scancode key) {
//	m_KeyStates[key] = false;
//SDL_Log("%d", press);
	if(m_KeyStates[key] == 1 && !press) {
		press = 1;
		return true;
	}
	return false;
}

void EventHandler::Up() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
	// SDL_GetKeyboardState(nullptr) return what u press on keyboard (a pointer)
}

void EventHandler::Down() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
	press = 0;
}
