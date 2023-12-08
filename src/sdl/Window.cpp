#include "Window.h"

namespace Chess {

    SDL_Renderer* Chess::Window::Renderer = nullptr;
    SDL_Window* Chess::Window::GameWindow = nullptr;

    bool Chess::Window::InitWindow(const char *title, int x, int y, int w, int h) {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "sdl Init error: " << SDL_GetError() << std::endl;
            return false;
        }

        GameWindow = SDL_CreateWindow(title, x, y, w, h, SDL_RENDERER_ACCELERATED);
        if(!GameWindow){

            std::cerr << "Window creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        Renderer = SDL_CreateRenderer(GameWindow, 0, 0);
        if(!Renderer){

            std::cerr << "Renderer creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    Window::~Window() {
        SDL_DestroyWindow(GameWindow);
        SDL_DestroyRenderer(Renderer);
    }
}


