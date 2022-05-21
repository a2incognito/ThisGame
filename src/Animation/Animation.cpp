#include "Animation.h"
#include "TextureManager.h"

using namespace std;

void Animation::Update() {
	SpriteFrame = (SDL_GetTicks()/AnimationSpeed) % FrameCount;
//	SDL_Log("can load %d", SpriteFrame);
}

void Animation::DrawSprite(float x, float y, int width, int height)
{
	TextureManager::
		Running() ->
			DrawFrame(TextureID, x, y, width, height, SpriteRow, SpriteFrame, Flip);
}

void Animation::DrawFrame(float x, float y, int width, int height) {
	string id = TextureID + to_string(SpriteFrame + 1);
	TextureManager::Running()->Draw(id, x, y, width, height, Flip);
}


void Animation::SetProp(string ID, int spriteRow, int framecount, int animationspeed, SDL_RendererFlip flip) {
	TextureID = ID,
	SpriteRow = spriteRow,
	FrameCount = framecount,
	AnimationSpeed = animationspeed,
	Flip = flip;
}

SDL_RendererFlip Animation::GetFlip() {
	return Flip;
}
