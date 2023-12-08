#include "Window.h"

namespace Chess {

    bool Chess::Window::InitWindow(const char *title, int x, int y, int w, int h) {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "sdl Init error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, SDL_RENDERER_ACCELERATED);
        if(!window){

            std::cerr << "Window creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
        if(!renderer){

            std::cerr << "Renderer creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    Window::~Window() {

    }
}


