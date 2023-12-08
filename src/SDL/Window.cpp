#include "Window.h"

namespace Chess{

    bool Chess::Window::InitWindow() {

        if (SDL_Init(SDL_INIT_VIDEO) != 0){
            std::cerr << "SDL Init error: " << SDL_GetError() << std::endl;
            return false;
        }


        return true;
    }

    Window::~Window() {

    }

}


