#ifndef CHESS_BOARD_H

#include "../sdl/SpriteManager.h"
#include "../sdl/Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Square.h"

#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"
#include "../pieces/King.h"
#include "../pieces/Queen.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../Macros.h"

namespace Chess {

    struct Squares {
        Square squares[8][8];
    };

    class Board {
    public:

        void RenderBoard();
        void ReleasePiece();
        void MoveDraggedPawn();
        void TakePiece(int x, int y);
        void CreateBoard(int screenWidth, int screenHeight);

    private:
        Squares m_Squares{};

        Piece::Site m_CurrentMove = Piece::Site::WHITE;

        Square *m_SquareThatPawnIsDraggedFrom{};
        std::shared_ptr<Piece> m_DraggedPawn = nullptr;

        void SetPieces();
        void SwitchSite();
        void CancelMove();
        void DoCastle(int newX);
        void DoNormalMove(int newX, int newY);

        bool CheckCheck();
        bool IsCheckmate(Piece::Site site);
        bool IsPathUnderAttack(int xStart, int xEnd, int y, Piece::Site site) const;
        bool CheckSite(const Piece &piece);
        bool IsTryingToCastle(int newX, int newY);
        bool IsSquareUnderAttack(int x, int y, Piece::Site site) const;
        bool CheckIfPathIsClear(const Piece &piece, int newX, int newY) const;
        bool CheckIfMoveIsProper(int newX, int newY,
                                 const std::shared_ptr<Piece> &piece) const;

        Piece* FindKingOfSite(Piece::Site site);

    };

} // namespace Chess

#endif // CHESS_BOARD_H
