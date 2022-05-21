#include "Boss.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Engine.h"
#include "CollisionHandling.h"
#include "Amthanh.h"
//throws something to screen

#include "SDL.h"

Boss::Boss(Properties* prop, Transform p) : Character (prop) {
  HitBox = new Checker();
	HitBoxAttack = new Checker();
	HitBoxFire = new Checker();

  animation = new Animation();

  position = p;

  spawn = 0;
  start = 0;

  hit = 0;
  endHit = 1;
  startHit = 0;

	fire = 0;
  endFire = 1;
  startFire = 0;

  startDeath = 0;

  HP = 100;
  maxHP = 100;
  HitBox ->SetChange(220, 180, 0, 0);
	HitBox ->SetRect(position.X, position.Y, 115, 130);
	HitBoxAttack ->SetChange(0, 0, 0, 0);
	HitBoxAttack ->SetRect(220, 400, 220, 46);
}

void Boss::Update(float dt) {
	animation ->SetProp("summon_", 0, 21, 150);
//	animation ->SetProp("cleave_", 0, 15, 80, SDL_FLIP_HORIZONTAL);
	if (spawn) {
		animation ->SetProp("idle_", 0, 6, 150, SDL_FLIP_HORIZONTAL);
		if (hit) {
			Amthanh::Running() ->play("content/Sound/hit.mp3", 0);
			animation ->SetProp("cleave_", 0, 15, 150, SDL_FLIP_HORIZONTAL);
		}
		if (hit && endHit) {
			hit = 0, startHit = 0;
		}
		if (fire) {
			Amthanh::Running() ->play("content/Sound/fire.mp3", 0);
			animation ->SetProp("fire_", 0, 15, 150);
		}
		if (fire && endFire) {
			fire = 0, startFire = 0;
		}
		if (!hit && !fire && endHit && endFire) {
			if (Delay <= 0) {
				if (!(SDL_GetTicks() % 3)) fire = 1, startFire = 0, endFire = 0;
				else hit = 1, startHit = 0, endHit = 0;
				Delay = DELAY;
			}
			else {
				Delay -= dt;
			}
		}
//		SDL_Log("%d %d", (SDL_GetTicks() / 1000) % 8, hit);
	}
	if (!HP) {
		animation ->SetProp("death_", 0, 22, 200, SDL_FLIP_HORIZONTAL);
	}
	animation ->Update();
	dame = 0;
	if (hit && startHit && !fire && !endHit && 8 < animation ->SpriteFrame && animation ->SpriteFrame < 13) {
		HitBoxAttack ->SetRect(220, 400, 220, 46);
		dame = 1;
	}
	if (fire && startFire && !endFire) {
		dame = 1;
		if (animation ->SpriteFrame == 5) HitBoxAttack ->SetRect(220, 250, 220, 46);
		else if (animation ->SpriteFrame == 9) HitBoxAttack ->SetRect(220, 310, 220, 46);
		else if (animation ->SpriteFrame == 10) HitBoxAttack ->SetRect(220, 340, 220, 46);
		else if (animation ->SpriteFrame == 11) HitBoxAttack ->SetRect(220, 370, 220, 46);
		else if (animation ->SpriteFrame == 12) HitBoxAttack ->SetRect(220, 400, 220, 46);
		else HitBoxAttack ->SetRect(220, 280, 220, 46);
	}

}

void Boss::Clean()
{

}

void Boss::DrawSpawn() {
	if (animation ->SpriteFrame == 20 && start) {
//		LastTime = SDL_GetTicks();
		spawn = 1;
	}
	if (start && !spawn) animation ->DrawFrame(position.X, position.Y, 576, 320);
	if (animation ->SpriteFrame == 0) {
		start = 1;
	}
}

void Boss::Draw() {
	if (!HP) {
//		SDL_Log("%d", startDeath);
		if (startDeath) animation ->DrawFrame(position.X, position.Y, 576, 320);
		else {
			animation ->SetProp("idle_", 0, 6, 150, SDL_FLIP_HORIZONTAL);
			animation ->Update();
			animation ->DrawFrame(position.X, position.Y, 576, 320);
		}
		if (animation ->SpriteFrame == 0) startDeath = 1;
		if (animation ->SpriteFrame == 21 && startDeath) HP = -1;
	}
	else {
		if (animation ->SpriteFrame == 0) {
			startHit = 1;
			startFire = 1;
		}
		if (animation ->SpriteFrame == 14 && startHit && startFire) {
	//		LastTime = SDL_GetTicks();
			endHit = 1;
			endFire = 1;
		}
		if ((startHit && !endHit) || (startFire && !endFire )) animation ->DrawFrame(position.X, position.Y, 576, 320);
		else {
			animation ->SetProp("idle_", 0, 6, 150, SDL_FLIP_HORIZONTAL);
			animation ->Update();
			animation ->DrawFrame(position.X, position.Y, 576, 320);
		}
		SDL_Rect hit_box = HitBox ->Get();
		SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit_box);
		hit_box = HitBoxAttack ->Get();
		if (dame) SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit_box);
	}
}

void Boss::GetHit(float dt) {
	if (GetHitDelay == GET_HIT_DELAY_B) {
		HP -= 1;
		gethit = 1;
	}
	GetHitDelay -= dt;
	if (GetHitDelay < 0) GetHitDelay = GET_HIT_DELAY_B;
}
