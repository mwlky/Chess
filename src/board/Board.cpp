#include "Board.h"

namespace Chess {
    void Board::RenderBoard() {

      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          m_Squares.squares[i][j].Render();
        }
      }
    }

    void Board::CreateBoard(int screenWidth, int screenHeight) {
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
      }

      m_Squares = squares;
      SetPieces();
    }

    void Board::TakePiece(int x, int y) {
        m_DraggedPawn = m_Squares.squares[x][y].GetAssignedPawn();
    }

    void Board::SetPieces() {
        const char* blackPieces[] = {ROCK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, QUEEN_BLACK, KING_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROCK_BLACK};
        const char* whitePieces[] = {ROCK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, QUEEN_WHITE, KING_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROCK_WHITE};

        // Spawn Black Pieces
        for (int file = 0; file < 8; ++file) {
            auto pawn = std::make_shared<Pawn>(blackPieces[file], Site::BLACK, file, 0);
            m_Squares.squares[file][0].AssignPawn(pawn);
        }

        // Spawn White Pieces
        for (int file = 0; file < 8; ++file) {
            auto pawn = std::make_shared<Pawn>(whitePieces[file], Site::WHITE, file, 0);
            m_Squares.squares[file][7].AssignPawn(pawn);
        }

        // Spawn White Pawns
        for (int i = 0; i < 8; ++i) {
            auto whitePawn = std::make_shared<Pawn>(PAWN_WHITE, Site::WHITE, i, 0);
            m_Squares.squares[i][6].AssignPawn(whitePawn);
        }

        // Spawn Black Pawns
        for (int i = 0; i < 8; ++i) {
            auto blackPawn = std::make_shared<Pawn>(PAWN_BLACK, Site::BLACK, i, 0);
            m_Squares.squares[i][1].AssignPawn(blackPawn);
        }
    }

    void Board::MoveDraggedPawn() {
        if(m_DraggedPawn == nullptr)
            return;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int pawnX = mouseX - m_DraggedPawn->GetWidth() / 2;
        int pawnY = mouseY - m_DraggedPawn->GetHeight() / 2;

        m_DraggedPawn->SetPosition(pawnX, pawnY);
    }

    void Board::ReleasePiece() {
        if(m_DraggedPawn == nullptr)
            return;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int newX = mouseX / 100;
        int newY = mouseY / 100;

        m_Squares.squares[newX][newY].AssignPawn(m_DraggedPawn);
        m_DraggedPawn = nullptr;
    }
} // namespace Chess