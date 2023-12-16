#ifndef CHESS_GAMELOOP_H
#define CHESS_GAMELOOP_H

#include "../board/Board.h"
#include "../sdl/Window.h"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750

namespace Chess {

class GameLoop {
public:
  GameLoop() = default;

  void Run();

private:
  void HandleEvents();
  void MouseEvent();

  Chess::Board m_Board;

  SDL_Event m_Event;

  bool m_IsRunning = false;
};

} // namespace Chess

#endif // CHESS_GAMELOOP_H
