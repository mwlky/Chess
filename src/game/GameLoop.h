#ifndef CHESS_GAMELOOP_H
#define CHESS_GAMELOOP_H

#include "../sdl/Window.h"

namespace Chess {

    class GameLoop {
    public:
        GameLoop() = default;

        void Run();
    };

} // Chess

#endif //CHESS_GAMELOOP_H
