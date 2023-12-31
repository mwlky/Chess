#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const char *sprite, Site site, int x, int y) : Piece(sprite, site, x, y) {}

    bool Pawn::IsValidMove(int newX, int newY, MoveType type) const {
        if(!Piece::IsValidMove(newX, newY, type))
            return false;

        int direction = (m_Site == Site::WHITE) ? -1 : 1;

        if(type == MoveType::TAKE || type == MoveType::EN_PASSANT){

            bool isDiagnal = abs(newX - m_XPos) == abs(newY - m_YPos);

            if ( isDiagnal && newX - m_XPos <= direction && newY - m_YPos <= direction) {
                return true;
            }

            return false;
        }

        if (newX == m_XPos && newY == m_YPos + direction)
            return true;


        if (newX == m_XPos && newY == m_YPos + 2 * direction && !HasMoved)
            return true;


        return false;
    }
}