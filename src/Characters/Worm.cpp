#include "Worm.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Engine.h"
#include "CollisionHandling.h"
//throws something to screen

#include "SDL.h"

Worm::Worm(Properties* prop, Transform *p) : Character (prop) {
  HitBox = new Checker();

	left = 0;
	idle = 1;

  animation = new Animation();
  Position = new Transform();
	HP = 5;
  Position = p;
  IdleTime = IDLE_TIME;
  GetHitDelay = GET_HIT_DELAY;
}

void Worm::Draw() {
	animation ->DrawSprite(Position ->Y, Position ->X, width, height);
//	SDL_Log("%f %f %d %d", Position ->X, Position ->Y, width, height);
	SDL_Rect hit_box = HitBox ->Get();
	SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit_box);
}

void Worm::Update(float dt) {
	SDL_RendererFlip tmp = animation  -> GetFlip();
	animation -> SetProp("worm_idle", 0, 9, 100, tmp);
	HitBox ->SetChange(23, 27, 0, 0);
	width = 90, height = 90;

	if (gethit) {
		IdleDelay -= dt;
		if (IdleDelay < 0) {
			IdleDelay = GET_HIT_DELAY / 2;
			gethit = 0;
		}
	}
	else {
		if (idle) {
			IdleTime -= dt;
			if (IdleTime < 0) {
				IdleTime = IDLE_TIME;
				idle = 0;
			}
		}
		else if (!left) {
		// move right
			animation -> SetProp("worm_walk", 0, 9, 100, SDL_FLIP_NONE);
			Position ->TransY (2.0f);
		}
		else {
			animation -> SetProp("worm_walk", 0, 9, 100, SDL_FLIP_HORIZONTAL);
			Position ->TransY (-2.0f);
		}

		int i = (Position ->X + 60) / 32 - 1,
				j = (Position ->Y + 60) / 32 - 1;
		if (i < 0 || j < 0) HP = 0;
	//	SDL_Log("%f %f %d %d", Position ->X, Position ->Y, i, j);
		if (!left && (MapCode::Running() -> base[i][j + 1] == 1 || !MapCode::Running() ->base[i + 1][j + 1])) {
			idle = 1;
			left = 1;
		}

		if (left && (MapCode::Running() -> base[i][j - 1] == 1 || !MapCode::Running() ->base[i + 1][j - 1])) {
			idle = 1;
			left = 0;
		}
	}

	HitBox ->SetRect(Position ->Y, Position ->X, 30, 30);
	animation ->Update();
}

bool Worm::Death() {
	if (HP > 0) return false;
	return true;
}

void Worm::Clean() {

}

void Worm::SetSize(int w, int h)
{

}

Checker* Worm::GetHitBox() {
	return HitBox;
}

void Worm::GetHit(float dt) {
//	SDL_Log("%f", GetHitDelay);
	if (GetHitDelay == GET_HIT_DELAY) {
		HP -= 1;
		gethit = 1;
	}
	GetHitDelay -= dt;
	if (GetHitDelay < 0) GetHitDelay = GET_HIT_DELAY;
}

