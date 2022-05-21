#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL.h"
#include <string>
#include <map>

using namespace std;

class TextureManager
{
	public:
		static TextureManager* Running() {
			return run = (run != nullptr) ? run : new TextureManager();
		}

		bool Load (string id, string file_name);
		void Remove (string id);
		void Clean();
		void Draw (string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void DrawFrame (string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void DrawFrameClient (string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void SetBase();
	private:
		TextureManager() {}
		static TextureManager* run;
		map<string, SDL_Texture*> TextureMap;
		int base[30][30][30];
		//id -> SDL_Texture
};

#endif // TEXTUREMANAGER_H
