#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../sdl/SpriteManager.h"
#include "../sdl/Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Square.h"

#define BLACK_SQUARE "../assets/black.png"
#define WHITE_SQUARE "../assets/white.png"

namespace Chess {

struct Squares {
  Square squares[8][8];
};

class Board {
public:
  Squares CreateBoard(int screenWidth, int screenHeight);

  void RenderBoard(Squares squares);
  void TakePiece(int x, int y);

private:
  Pawn m_Pawn;
};

} // namespace Chess

#endif // CHESS_BOARD_H
