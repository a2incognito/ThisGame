#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL_image.h"
#include "SDL.h"
#include <string>

using namespace std;


class Animation
{
	public:
		Animation() {}

		void Update();
		void DrawSprite (float x, float y, int width, int height);
		void DrawSpriteClient (float x, float y, int width, int height);
		void DrawFrame (float x, float y, int width, int height);
		void SetProp (string ID, int spriteRow, int framecount, int animationspeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
		SDL_RendererFlip GetFlip();

	public:
		int Frame, SpriteFrame;

	public:
		int SpriteRow;
		int AnimationSpeed, FrameCount;
		string TextureID;
		SDL_RendererFlip Flip;
};

#endif // ANIMATION_H

/***
variable
*/
