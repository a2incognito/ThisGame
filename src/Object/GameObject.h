#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"
#include "SDL_image.h"
#include <string>
// inherit object.h
using namespace std;

struct Properties {
	public:
		string TextureID;
		int width, height;
		float X, Y;
		SDL_RendererFlip flip;

	public: //init
		Properties (string ID, int x, int y, int w, int h, SDL_RendererFlip none = SDL_FLIP_NONE) {
			X = x, Y = y,
			flip = none,
			width = w, height = h,
			TextureID = ID;
		}

};

class GameObject{
	public:
		GameObject (Properties* prop) :
			TextureID (prop -> TextureID),
			width (prop -> width),
			height (prop -> height),
			flip (prop -> flip) {
			Position = new Transform(prop -> X, prop -> Y);
		}
		// push properties for Object (create new Transform* for Transform)
//		virtual void Draw() = 0;
//		virtual void Update(float dt) = 0;
//		virtual void Clean() = 0;
	public:
		Transform* Position;
		int width, height;
		string TextureID;
		SDL_RendererFlip flip;
	private:
};

#endif // GAMEOBJECT_H
