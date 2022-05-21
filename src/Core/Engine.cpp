#include "Engine.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "TextureManager.h"
#include "MapCode.h"
#include "Warrior.h"
#include "EventHandler.h"
#include "CollisionHandling.h"
#include "Timer.h"
#include "Checker.h"
#include "ClientGame.h"
#include "Amthanh.h"


using namespace std;

Engine* Engine::run = nullptr;
Warrior* player = nullptr;

using namespace std;

bool Engine::Init() {
	if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
		//init failed
		SDL_Log("Error: %s", SDL_GetError());
		return false;
	}

	Window = SDL_CreateWindow("ThisGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	// creat window for game, use SDL_CreateWindow (tiele, set position x2, sz_w, sz_h, full scr yes or no)

	if (Window == nullptr) {
		// create window failed
		SDL_Log("Error: %s", SDL_GetError());
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);
	// create renderer SDL_CreateRenderer ( object render, unknown, unknown)

	if (Renderer == nullptr) {
		//create Renderer failed
		SDL_Log("Error: %s", SDL_GetError());
		return false;
	}


	for (int i = 1; i <= 9; ++i) MapCode::Running() ->completed[i] = 0;

	TextureManager::Running() ->Load("idle", "content/Motion/idle.png");
	TextureManager::Running() ->Load("run", "content/Motion/run.png");
	TextureManager::Running() ->Load("jump_1", "content/Motion/jump_1.png");
	TextureManager::Running() ->Load("jump_2", "content/Motion/jump_2.png");
	TextureManager::Running() ->Load("jump_3", "content/Motion/jump_3.png");
	TextureManager::Running() ->Load("shoot", "content/Motion/shoot.png");
	TextureManager::Running() ->Load("bullet", "content/Motion/bullet.png");
	TextureManager::Running() ->Load("attack", "content/Motion/attack.png");
	TextureManager::Running() ->Load("roll", "content/Motion/roll.png");
	TextureManager::Running() ->Load("Map10", "content/Map_png/map_end.png");
	TextureManager::Running() ->Load("Map0", "content/Map_png/map_start.png");
	TextureManager::Running() ->Load("worm_idle", "content/mod/worm_idle.png");
	TextureManager::Running() ->Load("worm_walk", "content/mod/worm_walk.png");
	TextureManager::Running() ->Load("worm_death", "content/mod/worm_death.png");
	TextureManager::Running() ->Load("bat_fly", "content/mod/bat_fly.png");
	TextureManager::Running() ->Load("bat_death", "content/mod/bat_death.png");
	TextureManager::Running() ->Load("lose", "content/lose.png");
	TextureManager::Running() ->Load("start", "content/Client/start.png");
	TextureManager::Running() ->Load("tutorial", "content/Client/tutorial.png");
	TextureManager::Running() ->Load("arrow", "content/Client/arrow.png");
	TextureManager::Running() ->Load("pause", "content/Client/pause.png");
	TextureManager::Running() ->Load("tutorial_move", "content/Client/tutorial_move.png");
	TextureManager::Running() ->Load("tutorial_attack", "content/Client/tutorial_attack.png");
	TextureManager::Running() ->Load("tutorial_roll", "content/Client/tutorial_roll.png");
	TextureManager::Running() ->Load("bgHP", "content/HP/bg.png");
	TextureManager::Running() ->Load("bgHPBoss", "content/HP/bgb.png");
	TextureManager::Running() ->Load("HP", "content/HP/hp.png");
	TextureManager::Running() ->Load("HPBoss", "content/HP/hpb.png");
	TextureManager::Running() ->Load("load0", "content/load/load0.png");
	TextureManager::Running() ->Load("load1", "content/load/load1.png");
	TextureManager::Running() ->Load("load2", "content/load/load2.png");
	TextureManager::Running() ->Load("gate", "content/Client/gate.png");
//	TextureManager::Running() ->Load("1", "content/Map_png/map_1.png");
	for (int i = 1; i <= 9; ++i) { TextureManager::Running() ->Load("Map" + to_string(i), "content/Map_png/map_" + to_string(i) + ".png");}
	for (int i = 1; i <= 15; ++i) {TextureManager::Running() ->Load("cleave_" + to_string(i),"content/boss/attack/demon_cleave_" + to_string(i) + ".png");}
	for (int i = 1; i <= 15; ++i) {TextureManager::Running() ->Load("fire_" + to_string(i),"content/boss/fire/fire_" + to_string(i) + ".png");}
	for (int i = 1; i <= 20; ++i) {TextureManager::Running() ->Load("summon_" + to_string(i),"content/boss/summon/summon_" + to_string(i) + ".png");}
	for (int i = 1; i <= 6; ++i) {TextureManager::Running() ->Load("idle_" + to_string(i),"content/boss/idle/demon_idle_" + to_string(i) + ".png");}
	for (int i = 1; i <= 20; ++i) {TextureManager::Running() ->Load("death_" + to_string(i),"content/boss/death/demon_death_" + to_string(i) + ".png");}

	player = new Warrior(new Properties("idle", 300, 150, 44, 32) );
	StageDelay = STAGE_DELAY;
	play = 1;
	arrow = new Transform(235, 160);
	gate = new Animation();
	gate ->SetProp("gate", 0, 15, 75);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return still = true;
}

bool Engine::Clean() {
	TextureManager::Running() -> Clean();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Quit() {
	still = false;
}

void Engine::Update() {
//	SDL_Log("%d",ClientGame::Running() -> Still());
	//SDL_Log("%d %d", player ->stage, player ->lastStage);
	float dt = Timer::Running() -> GetDeltaTime();
	if (ClientGame::Running() ->Still() == 2) {
		ClientGame::Running() ->Update();
		return ;
	}
	if (ClientGame::Running() -> Still() == 1) {
		MapCode::Running() ->Reset();
		player = new Warrior(new Properties("idle", 300, 150, 44, 32) );
		MapCode::Running() ->boss = new Boss(new Properties("idle", 300, 150, 44, 32), Transform(-80, 128));
		ClientGame::Running() ->Client(0);
	}

	if (EventHandler::Event() ->GetKey(SDL_SCANCODE_ESCAPE) && play) {
		play = 0;
		Amthanh::Running() ->play("content/Sound/click.mp3", 0);
		return ;
	}
	if (!play) {
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_UP)) {
			resume = 1;
			arrow = new Transform(235, 160);
		}
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_DOWN)) {
			resume = 0;
			arrow = new Transform(235, 230);
		}
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_SPACE)) {
				if (resume) play = 1;
				else {
					play = 1;
					ClientGame::Running() ->Client(2);
				}
		}
	}
	if (player ->ChangeStageDelay > 0) {
		player ->ChangeStageDelay -= dt;
		player ->Update(dt);
		return ;
	}

	if (player ->Alive() && play) {
		player -> Update(dt);
		MapCode::Running() ->GetBase(player ->stage);
		MapCode::Running() ->stage = player ->stage;
//		SDL_Log("%d", player ->stage);
//		SDL_Log("%d", MapCode::Running() ->stage);
		if (MapCode::Running() ->stage != 9) {
			if (MapCode::Running() ->stage != player ->lastStage && player ->stage != 10) {
					MapCode::Running() ->amountMod = 0;
					if (!MapCode::Running() ->completed[player ->stage]) {
						MapCode::Running() ->SpawnWorm();
					}
//					player ->lastStage = player ->stage;
			}
			CollisionHandling::Running() ->GetMapCode();
			MapCode::Running() -> Update(dt, player ->stage);
			for (int i = 0; i < int(MapCode::Running() ->worm.size()); ++i) {
				auto v = MapCode::Running() ->worm[i];
				if (MapCode::Running() ->wormDeath[i]) continue;
				Checker* hitbox = v ->GetHitBox();
				SDL_Rect recta = hitbox ->Get();
				SDL_Rect rectb = player ->Hit ->Get();
				bool getdamage = CollisionHandling::Running() ->Check(recta, rectb);
//				SDL_Log("%d", getdamage);
				if (getdamage) v ->GetHit(dt);
				rectb = player ->HitBox ->Get();
				getdamage = CollisionHandling::Running() ->Check(recta, rectb);
				if (getdamage) {
					player ->GetHit(dt);
					v ->GetHit(dt);
				}
//				SDL_Log("%d", v ->HP);
			}
			if (!MapCode::Running() ->amountMod && MapCode::Running() ->completed[player ->stage] == 0) {
				MapCode::Running() ->Completed(player ->stage);
				if (player ->HP < 10) player ->HP ++;
				Amthanh::Running() ->play("content/Sound/complete.mp3", 0);
			}
		}
		else if (MapCode::Running() ->stage == 9 && player ->lastStage == 9){
			if (!MapCode::Running() ->spawn) {
				MapCode::Running() ->spawn = 1;
			}
			CollisionHandling::Running() ->GetMapCode();
			MapCode::Running() -> Update(dt, player ->stage);
			auto v = MapCode::Running() ->boss;
			SDL_Rect b = v ->HitBox ->Get(),
							 ba = v ->HitBoxAttack ->Get(),
							 p = player ->HitBox ->Get(),
							 ph = player ->Hit ->Get();
			if (v ->spawn && v ->HP > 0) {
				bool getdamage = CollisionHandling::Running() ->Check(ph, b); // warrior dame boss
				if (getdamage) v ->GetHit(dt);
				getdamage = 0;
				if (v -> dame) {
					getdamage = CollisionHandling::Running() ->Check(p, ba); // boss dame warrior
				}
				if (getdamage) player ->GetHit(dt);
				getdamage = 0;
				getdamage = CollisionHandling::Running() ->Check(p, b); // Collision of warrior n boss
				if (getdamage) player ->GetHit(dt);
			}
//			SDL_Log("%d", v -> HP);
			if (v -> HP == -1) MapCode::Running() ->Completed(player ->stage);
		}
		if (player ->HP <= 0) Amthanh::Running() ->play("content/Sound/over.mp3", 0);
	}
	else {
		MapCode::Running() ->worm.resize(0);
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_SPACE)) {
			ClientGame::Running() ->Client(2);
		}
	}

	if (player ->stage == 10 && player ->ChangeStageDelay < 0) {
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_SPACE)) {
			ClientGame::Running() ->Client(2);
		}
	}

}

void Engine::Render() {
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);

	if (ClientGame::Running() ->Still()) {
		ClientGame::Running() ->Draw();
		SDL_RenderPresent(Renderer);
		return ;
	}

	if (player ->ChangeStageDelay > 0) {
		TextureManager::Running() ->Draw("load" + to_string(SDL_GetTicks() / 300 % 3), 239, 217, 196 + 23 * (SDL_GetTicks() / 300 % 3), 47);
		SDL_RenderPresent(Renderer);
		return ;
	}

	if (player ->Alive()) {
		string id_map = to_string(player ->stage );
		TextureManager::Running() ->Draw("Map" + id_map, 0, 0, 708, 480, SDL_FLIP_NONE);

		MapCode::Running() ->DrawMod();

		if ((player ->stage == 8 || player ->stage == 9) && MapCode::Running() ->completed[player ->stage]) {
			gate ->Update(); gate ->DrawSprite(256, 144, 192, 192);
		}

		player -> Draw();



		int x = 12, y = 150;

		if (player ->stage != 10) {
			for (int i = 0; i < player ->maxHP; ++i) {
				TextureManager::Running() ->Draw("bgHP", x, y, 18, 35);
				y += 30;
			}

			for (int i = 0; i < player ->HP; ++i) {
				y -= 30;
				TextureManager::Running() ->Draw("HP", x, y, 18, 35);
			}
		}

		x = 60, y = 40;
		if (player ->stage == 9) {
			for (int i = 0; i < MapCode::Running() ->boss ->maxHP; ++i) {
				TextureManager::Running() ->Draw("bgHPBoss", x, y, 6, 9);
				x += 6;
			}
			x = 60;
			for (int i = 0; i < MapCode::Running() ->boss ->HP; ++i) {
				TextureManager::Running() ->Draw("HPBoss", x, y, 6, 9);
				x += 6;
			}
		}

		if (!play) {
			TextureManager::Running() ->Draw("pause", 191, 105, 338, 210);
			TextureManager::Running() ->Draw("arrow", arrow ->X, arrow ->Y, 26, 35);
		}



		SDL_RenderPresent(Renderer);
	}
	else {
		TextureManager::Running() ->Draw("lose", 0, 0, 720, 480, SDL_FLIP_NONE);
		SDL_RenderPresent(Renderer);
	}
}

void Engine::Event() {
	EventHandler :: Event() -> Input();
}


