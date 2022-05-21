#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MapCode.h"
#include "TextureManager.h"
#include <bits/stdc++.h>
#include "SDL.h"

MapCode* MapCode::run = nullptr;

using namespace std;

void MapCode::GetBase(int stage)
{
  string path = "content/Map_code/" + to_string(stage) + ".txt";

  ifstream inp(path.c_str());

  for (int i = 0; i < 15; ++i)
    for (int j = 0; j < 22; ++j)
    {
      inp >> base[i][j];
    }
}

void MapCode::SpawnWorm() {
	if (stage == 0) return;
	int amount = SDL_GetTicks() % 3;
	amount = 3;
	amountMod += amount;
	while (worm.size()) {
		worm.pop_back();
		wormDeath.pop_back();
	}
	while (amount--) {
		while(1) {
			int _i = SDL_GetTicks() % 15 + 1;
			int _j = SDL_GetTicks() % 22 + 1;
			if (base[_i][_j] == 2) {
				base[_i][_j] = 0;
				Worm* New = new Worm(new Properties("idle", 300, 150, 44, 32),
															new	Transform(float(1) * (_i + 1) * 32 - 60, float(1) * (_j + 1) * 32 - 60));
				worm.push_back(New);
				wormDeath.push_back(0);
				break;
			}
		}
	}
}



void MapCode::Update(float dt, int currently_stage) {
	if (stage != currently_stage) return ;
	for (int i = 0; i < worm.size(); ++i) {
		worm[i] ->Update(dt);
		if (worm[i] ->Death() && !wormDeath[i]) {
			--amountMod;
			wormDeath[i] = 1;
		}
	}

	if (stage == 9) {
		boss ->Update(dt);
	}
}

void MapCode::DrawMod() {
	for (int i = 0; i < worm.size(); ++i) {
		if (!wormDeath[i]) worm[i] ->Draw();
	}
	if (MapCode::Running() ->stage == 9) {
		if (!boss ->spawn) {
			boss ->DrawSpawn();
		}
		else {
			if (boss ->Alive()) boss ->Draw();
		}
	}
}

void MapCode::Completed(int stage) {
	completed[stage] = 1;
}

void MapCode::Reset()
{
	for (int i = 0; i < 12; ++i) completed[i] = 0;
	for (int i = 0; i < 28; ++i) for (int j = 0; j < 28; ++j) base[i][j] = 0;
}



