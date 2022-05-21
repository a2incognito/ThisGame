#include "CollisionHandling.h"

#include "Engine.h"
#include "SDL.h"
#include <iostream>

//SDL_Rect with x, y, w, h (x, y) upper left

CollisionHandling* CollisionHandling::run = nullptr;

bool CollisionHandling::Check(SDL_Rect a, SDL_Rect b) {
	return (a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y < b.y + b.h) && (a.y + a.h > b.y);
	// check rect a n b with overlap
}

bool CollisionHandling::MapCollision(SDL_Rect a) {
	int tileSize = 32;
	int	row = 15,
			column = 22; // w, h -> r, c -> x, y
	pair <int, int> point_top = {0, 0}, point_down = {0, 0};
	point_top = {(a.y - 1) / tileSize, (a.x - 1) / tileSize};
	point_down = {(a.y + a.h - 1) / tileSize, (a.x + a.w - 1) / tileSize};
	if (point_top.first < 0) point_top.first = 0;
	if (point_top.second < 0) point_top.second = 0;

	if (point_down.first >= 15) point_down.first = 14;
	if (point_down.second >= 22) point_down.second = 21;
//	SDL_Log("%d %d %d %d", point_top.first, point_top.second, point_down.first, point_down.second);
//	SDL_Log("hit_box %d %d %d %d", a.y / tileSize, a.x / tileSize, a.y / tileSize, (a.x + a.w)  / tileSize);

	for (int i = point_top.first; i <= point_down.first; ++i)
		for (int j = point_top.second; j <= point_down.second; ++j) {
			if (base[i][j] == 1) {
				return true;
			}
		}

	return false;
}

void CollisionHandling::GetMapCode() {
	for (int i = 0; i < 15; ++i)
    for (int j = 0; j < 22; ++j)
    {
      base[i][j] = MapCode::Running() ->base[i][j];
//      SDL_Log("Error: i j %d %d %d", i, j, base[i][j]);
    }
}




