#include "ClientGame.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Engine.h"
#include "Amthanh.h"

ClientGame* ClientGame::run = nullptr;



void ClientGame::Update() {
	if (type == "start") {
		animation = new Animation();
		animation -> SetProp("idle", 0, 4, 300, SDL_FLIP_HORIZONTAL);
		animation ->Update();

		if (EventHandler::Event() ->GetKeyClient(SDL_SCANCODE_UP) && order > 1) {
			arrow = new Transform(arrow ->X, arrow ->Y - 58);
			Amthanh::Running() ->play("content/Sound/change.mp3", 0);
			order --;
		}
		if (EventHandler::Event() ->GetKeyClient(SDL_SCANCODE_DOWN) && order < 3) {
			arrow = new Transform(arrow ->X, arrow ->Y + 58);
			Amthanh::Running() ->play("content/Sound/change.mp3", 0);
			order ++;
		}
		if (EventHandler::Event() ->GetKeyClient(SDL_SCANCODE_J)) {
				Amthanh::Running() ->play("content/Sound/click.mp3", 0);
			if (order == 1) still = 1;
			else if (order == 2) type = "tutorial";
			else Engine::Running() ->Quit();
		}
		return;
	}

	if (EventHandler::Event() ->GetKeyClient(SDL_SCANCODE_L)) {
		Amthanh::Running() ->play("content/Sound/click.mp3", 0);
		type = "start";
	}

}

void ClientGame::Draw() {
	if (type == "start") {
		TextureManager::Running() ->Draw(type, 0, 0, 720, 480);
		TextureManager::Running() ->Draw("arrow", arrow ->X, arrow ->Y, 26, 35);
		animation ->DrawSprite(523, 285, 44, 32);
		return;
	}
	else {
		TextureManager::Running() ->Draw(type, 0, 0, 720, 480);
		animation = new Animation();
		animation -> SetProp("tutorial_move", 0, 6, 200);
		animation ->Update();
		animation ->DrawSprite(500, 100, 100, 106);
		animation = new Animation();
		animation -> SetProp("tutorial_attack", 0, 8, 80);
		animation ->Update();
		animation ->DrawSprite(500, 210, 167, 66);
		animation = new Animation();
		animation -> SetProp("tutorial_roll", 0, 5, 100);
		animation ->Update();
		animation ->DrawSprite(500, 270, 96, 62);
	}
}
