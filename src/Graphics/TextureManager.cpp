#include "TextureManager.h"
#include "Engine.h"
#include "SDL.h"
#include "SDL_image.h"


TextureManager* TextureManager::run = nullptr;


bool TextureManager::Load(string id, string file_name)
{
	SDL_Surface* surface = IMG_Load(file_name.c_str());
	// create surface by IMG_Load (char only)
	if (surface == nullptr) {
		SDL_Log("Can't load: %s %s", file_name, SDL_GetError());
		return false;
	} // cant load to fail

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Running() -> GetRenderer(), surface);
	// creat texture
	if (surface == nullptr) {
		SDL_Log("Can't Creat Texture: %s", SDL_GetError());
		return false;
	}
	if (id == "lose") SDL_Log("can load");
	TextureMap[id] = texture;
	// mapping id -> texture
	return true;
}

void TextureManager::Remove(string id)
{
	SDL_DestroyTexture(TextureMap[id]);
	// texture u want remove
	TextureMap.erase(id);
	// erase texture was drop
}

void TextureManager::Clean()
{
	map<string, SDL_Texture*> :: iterator it;
	for (it = TextureMap.begin(); it != TextureMap.end(); it++)
		SDL_DestroyTexture(it -> second);
	TextureMap.clear();
	// for all member in map, remove Texture, clear map
	SDL_Log("cleaned!");
}


void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{ // draw id_texture to scr with the origin at (x, y), width n height is size of rectangle
	SDL_Rect srcRect = {0, 0, width, height}; // part of image to show
	SDL_Rect desRect = {x, y, width, height}; // where on screen we want show
//	id = "lose";
	SDL_RenderCopyEx(Engine::Running() -> GetRenderer(), TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
	// renderer (use renderer of Engine), texture, srcRect, desRect, angel (degrees), a pointer to a point dstrect will be rotate (nullptr to center), flip)
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = {width * frame, height * row, width, height};
	SDL_Rect desRect = {x, y, width, height};
//	if (width == 192) SDL_Log("%d", row);
	SDL_RenderCopyEx(Engine::Running() -> GetRenderer(), TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}


