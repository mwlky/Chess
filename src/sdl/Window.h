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

        SDL_Window* GetWindow() const {
            return m_Window;
        }

        SDL_Renderer* GetRenderer() const {
            return m_Renderer;
        }

    private:
        SDL_Window* m_Window = nullptr;
        SDL_Renderer* m_Renderer = nullptr;
    };

}





#endif //CHESS_WINDOW_H
