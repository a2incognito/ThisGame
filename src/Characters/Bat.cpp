#include "Bat.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Engine.h"
#include "CollisionHandling.h"
//throws something to screen

#include "SDL.h"

Bat::Bat(Properties* prop, Transform p) : Character (prop) {
  HitBox = new Checker();

  animation = new Animation();

  left = 0;
  idle = 1;

	HP = 30;
	position = p;
}


void Bat::Draw() {
	animation ->DrawSprite(position.Y, position.X, m_width, m_height);
	SDL_Rect hit_box = HitBox ->Get();
	SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit_box);
}

void Bat::Update(float dt) {
//	SDL_RendererFlip tmp = animation  -> GetFlip();

	HitBox ->SetChange(23, 27, 0, 0);
	m_width = 90, m_height = 90;

	Transform bat = Transform(position.X + 23.0f, position.Y + 27.0f);
	if (bat.Y > player.Y) {
		bat.Y -= 1.0f;
		int i1 = (bat.X + 11) / 32 - 1, j1 = (bat.Y + 17) / 32 - 1, j2 = bat.Y / 32 - 1;
		if (MapCode::Running() ->base[i1][j1] == 1 || MapCode::Running() ->base[i1][j2] == 1) {
			bat.Y += 1.0f;
		}
		animation -> SetProp("bat_fly", 0, 4, 100, SDL_FLIP_HORIZONTAL);
	}
	else {
		bat.Y += 1.0f;
		int i1 = (bat.X + 11) / 32 - 1, j1 = (bat.Y + 17) / 32 - 1, j2 = bat.Y / 32 - 1;
		if (MapCode::Running() ->base[i1][j1] == 1 || MapCode::Running() ->base[i1][j2] == 1) {
			bat.Y -= 1.0f;
		}
		animation ->SetProp("bat_fly", 0, 4, 100, SDL_FLIP_NONE);
	}

	if (bat.X > player.X) {
		bat.X -= 1.0f;
		int i1 = (bat.X + 11) / 32 - 1, j1 = (bat.Y + 17) / 32 - 1, j2 = bat.Y / 32 - 1;
		if (MapCode::Running() ->base[i1][j1] == 1 || MapCode::Running() ->base[i1][j2] == 1) {
			bat.X += 1.0f;
		}
	}
	else {
		bat.X += 1.0f;
		int i1 = (bat.X + 11) / 32 - 1, j1 = (bat.Y + 17) / 32 - 1, j2 = bat.Y / 32 - 1;
		if (MapCode::Running() ->base[i1][j1] == 1 || MapCode::Running() ->base[i1][j2] == 1) {
			bat.X -= 1.0f;
		}
	}

	HitBox ->SetRect(position.Y, position.X, 17, 11);
	animation ->Update();

}

bool Bat::Death() {
	if (HP) return false;
	return true;
}

void Bat::PositionPlayer(Transform p) {
	player = p;
}

void Bat::Clean()
{

}

void Bat::SetSize(int w, int h)
{

}
