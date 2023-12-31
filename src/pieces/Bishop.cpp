#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) { }

    bool Bishop::IsValidMove(int newX, int newY, MoveType type) const {
        if(!Piece::IsValidMove(newX, newY, type))
            return false;

        if (abs(newX - m_XPos) == abs(newY - m_YPos))
            return true;


        return false;
    }
} // Chess