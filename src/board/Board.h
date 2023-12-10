#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "SDL.h"
#include "SDL_image.h"
#include "../sdl/Window.h"

namespace Chess {

    class Board {
    public:
        void RenderBoard(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    };

} // Chess

#endif //CHESS_BOARD_H
