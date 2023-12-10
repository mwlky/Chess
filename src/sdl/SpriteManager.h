#ifndef CHESS_SPRITEMANAGER_H
#define CHESS_SPRITEMANAGER_H

#include <iostream>

#include "SDL.h"
#include "Window.h"
#include "SDL_image.h"

namespace Chess {

    class SpriteManager {
    public:
        static SDL_Texture *LoadTexture(const char *filePath, SDL_Renderer* renderer) {

            SDL_Surface *tempSurface = IMG_Load(filePath);

            if (!tempSurface) {
                std::cerr << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError()
                          << std::endl;
                return nullptr;
            }

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

            if (!texture) {
                std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError()
                          << std::endl;
                return nullptr;
            }
            SDL_FreeSurface(tempSurface);

            return texture;
        }

        static void Draw(SDL_Texture *texture, SDL_Rect destinationPosition, SDL_Renderer* renderer) {
            if(texture != nullptr){
                SDL_RenderCopy(renderer, texture, NULL, &destinationPosition);
            } else{
                std::cerr << "No texture find to draw" << std::endl;
            }
        }

    };

}

#endif //CHESS_SPRITEMANAGER_H
