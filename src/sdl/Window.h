#pragma once

#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace Chess{

class Window {

public:
  Window();
  ~Window();

  bool InitWindow() {
    bool quit = false;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        std::cout << "Failed SDL init" << SDL_GetError() <<std::endl;
        return false;
    }
    
    SDL_Window *window =
        SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if(!window){

      std::cout << "Failed window init!" << SDL_GetError() << std::endl;

      return false;
    }


    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){

      std::cout << "Failed init renderer! " << SDL_GetError() << std::endl;
      return false;
    }

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

    return true;
  }

  static SDL_Renderer* Renderer;
  static SDL_Window* GameWindow;

private:
};
} // namespace Chess::SDL