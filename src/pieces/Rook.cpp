#include "Rook.h"

namespace Chess {
    Rook::Rook(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) {}

    bool Rook::IsValidMove(int newX, int newY, MoveType type) const {
        if(!Piece::IsValidMove(newX, newY, type))
            return false;

        if(newX == m_XPos || m_YPos == newY)
            return true;

        return false;
    }
} // Chess