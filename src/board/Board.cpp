#include "Board.h"

namespace Chess {
void Board::RenderBoard(Squares squares) {

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      squares.squares[i][j].Render();
    }
  }

  m_Pawn.Render();
}

Squares Board::CreateBoard(int screenWidth, int screenHeight) {
  Squares squares;

  bool white = true;

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {

      const char *path = nullptr;

      if (white)
        path = WHITE_SQUARE;

      else
        path = BLACK_SQUARE;

      SDL_Rect rect = {x * screenWidth / 8, y * screenHeight / 8,
                       screenWidth / 8, screenHeight / 8};

      Square square(path, Window::Renderer, rect);
      squares.squares[x][y] = square;

      white = !white;
    }
    white = !white;

    m_Pawn = *new Pawn("../assets/Chess_Pawn_Black.png", Site::BLACK, 0, 0);
  }

  return squares;
}
} // namespace Chess