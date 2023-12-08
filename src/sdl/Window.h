#ifndef CHESS_WINDOW_H
#define CHESS_WINDOW_H

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

namespace Chess{

    class Window {

    public:
        Window() = default;
        ~Window();

        bool InitWindow(const char* title, int x, int y, int w, int h);

        static SDL_Window* GameWindow;
        static SDL_Renderer* Renderer;
    };

}





#endif //CHESS_WINDOW_H
