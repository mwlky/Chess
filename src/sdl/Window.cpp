#include "Window.h"
#include "SDL_render.h"

namespace Chess {

    SDL_Window* Window::CurrentWindow = nullptr; 
    SDL_Renderer* Window::Renderer = nullptr;

    bool Chess::Window::InitWindow(const char *title, int x, int y, int w, int h) {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "SDL Init error: " << SDL_GetError() << std::endl;
            return false;
        }

        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
            std::cerr << "SDL Image error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_Window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED);
        if(!m_Window){

            std::cerr << "Window creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
        if(!m_Renderer){

            std::cerr << "Renderer creation error: " << SDL_GetError() << std::endl;
            return false;
        }

        CurrentWindow = m_Window;
        Renderer = m_Renderer;

        return true;
    }

    Window::~Window() {
        SDL_DestroyWindow(m_Window);
        SDL_DestroyRenderer(m_Renderer);
    }
}


