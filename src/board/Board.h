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

        Square* m_SquareThatPawnIsDraggedFrom = nullptr;
        std::shared_ptr<Piece> m_DraggedPawn = nullptr;

        void SetPieces();
        void SwitchSite();
        void CancelMove();
        void DoCastle(const int& newX);
        void DoNormalMove(const int& newX, const int& newY);
        void CheckProcedures(const int &newX, const int &newY);

        bool HasTriedToSaveKing(const int& newX, const int& newY);
        bool SimulateMoveAndCheckForCheck(const int& newX, const int& newY);

        bool CheckCheck() const;
        bool CheckSite(const Piece &piece) const;
        bool IsTryingToCastle(const int& newX, const int& newY) const;
        bool IsSquareUnderAttack(const int& x, const int& y, const Piece::Site& site) const;
        bool CheckIfPathIsClear(const Piece &piece, const int& newX, const int& newY) const;
        bool CheckIfMoveIsProper(const int& newX, const int& newY,const std::shared_ptr<Piece> &piece) const;
        bool IsPathUnderAttack(const int& xStart, const int& xEnd, const int& y, const Piece::Site& site) const;

        Piece* FindKingOfSite(Piece::Site site) const;
    };

} // namespace Chess

#endif // CHESS_BOARD_H
