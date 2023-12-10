#ifndef CHESS_GAMELOOP_H
#define CHESS_GAMELOOP_H

#include "../sdl/Window.h"
#include "../board/Board.h"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750

namespace Chess {

    class GameLoop {
    public:
        GameLoop() = default;

        void Run();

    private:

        void HandleEvents();

        SDL_Event m_Event;

        bool m_IsRunning = false;
    };

} // Chess

#endif //CHESS_GAMELOOP_H
