#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) {
    }

    Bishop::~Bishop() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Bishop::IsValidMove(int newX, int newY, MoveType type) const {
        if(!Piece::IsInsideBoard(newX, newY))
            return false;

        if (abs(newX - m_XPos) == abs(newY - m_YPos)) {
            return true;
        }

        return false;
    }
} // Chess