#ifndef CHESS_GAMELOOP_H
#define CHESS_GAMELOOP_H

#include "../board/Board.h"
#include "../sdl/Window.h"

namespace Chess {

    class GameLoop {
    public:
        GameLoop() = default;

        void Run();

    private:
        void HandleEvents();
        void MovePiece(int x, int y);
        void Tick();

        Chess::Board m_Board;

        SDL_Event m_Event;

        bool m_IsRunning = false;

        const int FPS = 120;
        const int FrameDelay = 1000 / FPS;
    };

} // namespace Chess

#endif // CHESS_GAMELOOP_H
