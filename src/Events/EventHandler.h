#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SDL.h"

class EventHandler
{
	public:
		static EventHandler* Event() {
				return check = (check != nullptr) ? check : new EventHandler();
		}

		void Input();
		bool GetKey(SDL_Scancode key);
		bool GetKeyClient(SDL_Scancode key);

	private:
		EventHandler();
		void Up();
		void Down();
		bool press;
		const Uint8 *m_KeyStates = SDL_GetKeyboardState(NULL); //states of key
		static EventHandler* check; // create iterator of EventHandler
		Uint32 buttons;
};

#endif // EVENTHANDLER_H
