#ifndef CHESS_BOARD_H

#include "../sdl/SpriteManager.h"
#include "../sdl/Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Square.h"

#define PAWN_BLACK "../assets/Chess_Pawn_Black.png"
#define BLACK_SQUARE "../assets/black.png"
#define ROCK_BLACK "../assets/Chess_Rock_Black.png"
#define KING_BLACK "../assets/Chess_King_Black.png"
#define QUEEN_BLACK "../assets/Chess_Hetman_Black.png"
#define KNIGHT_BLACK "../assets/Chess_Knight_Black.png"
#define BISHOP_BLACK "../assets/Chess_Bishop_Black.png"

#define WHITE_SQUARE "../assets/white.png"
#define KING_WHITE "../assets/Chess_King_White.png"
#define PAWN_WHITE "../assets/Chess_Pawn_White.png"
#define ROCK_WHITE "../assets/Chess_Rock_White.png"
#define QUEEN_WHITE "../assets/Chess_Queen_White.png"
#define KNIGHT_WHITE "../assets/Chess_Knight_White.png"
#define BISHOP_WHITE "../assets/Chess_Bishop_White.png"

namespace Chess {

    struct Squares {
      Square squares[8][8];
    };

    class Board {
    public:
      void CreateBoard(int screenWidth, int screenHeight);
      void MoveDraggedPawn();
      void ReleasePiece();
      void TakePiece(int x, int y);
      void RenderBoard();

    private:
        std::shared_ptr<Piece> m_DraggedPawn = nullptr;

        void SetPieces();

        Squares m_Squares;
};

} // namespace Chess

#endif // CHESS_BOARD_H
