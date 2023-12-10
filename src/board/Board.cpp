#include "Board.h"

namespace Chess {
    void Board::RenderBoard(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
        bool white = true;

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                if (white)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0, 76, 153, 255);
                }
                white = !white;
                SDL_Rect rectangle = {x * screenWidth / 8,
                                      y * screenHeight / 8,
                                      screenWidth + 1/ 8,
                                      screenHeight + 1/ 8};
                SDL_RenderFillRect(renderer, &rectangle);
            }
            white = !white;
        }
    }
} // Chess