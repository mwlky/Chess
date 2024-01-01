#include <memory>
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

        Board() = default;

        void Tick();
        void ReleasePiece();

        void TakePiece(int x, int y);
        void CreateBoard(int screenWidth, int screenHeight);

    private:
        Squares m_Squares{};

        Piece::Site m_CurrentMove = Piece::Site::WHITE;

        Pawn* m_PawnToPromote = nullptr;
        Pawn* m_LastMovedPawn = nullptr;
        Square* m_SquareThatPawnIsDraggedFrom = nullptr;
        std::shared_ptr<Piece> m_DraggedPawn = nullptr;

        Piece* FindKingOfSite(Piece::Site site) const;

        Piece::MoveType GetMoveType(int newX, int newY, const std::shared_ptr<Piece>& piece);

        void SetPieces();
        void SwitchSite();
        void CancelMove();
        void RenderBoard();
        void PromotionLogic();
        void MoveDraggedPawn();
        void CheckForPromotion();

        void DoCastle(int newX);
        void DoNormalMove(int newX, int newY);
        void CheckProcedures(int newX, int newY);
        void EnPassantLogic(int newX, int newY, const std::shared_ptr<Piece>& piece);

        bool CheckCheck() const;
        bool CheckSite(const Piece &piece) const;
        bool IsTryingToCastle(int newX, int newY) const;
        bool IsSquareUnderAttack(int x, int y, Piece::Site site) const;
        bool CheckIfPathIsClear(const Piece &piece, int newX, int newY) const;
        bool IsPathUnderAttack(int xStart, int xEnd, int y, Piece::Site site) const;

        bool CheckCheckmate(Piece::Site site);
        bool HasTriedToSaveKing(int newX, int newY);
        bool IsEnPassant(int newX, int newY, const std::shared_ptr<Piece>& piece);
        bool CheckIfMoveIsProper(int newX, int newY, const std::shared_ptr<Piece> &piece);
        bool SimulateMoveAndCheckForCheck(std::shared_ptr<Piece> piece, int newX, int newY);
    };

} // namespace Chess

#endif // CHESS_BOARD_H
