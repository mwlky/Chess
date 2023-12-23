#include "Queen.h"

namespace Chess {
    Queen::Queen(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) {
    }

    Queen::~Queen() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Queen::IsValidMove(int newX, int newY) const {
        if(!Piece::IsInsideBoard(newX, newY))
            return false;

        if(newX == m_XPos || m_YPos == newY)
            return true;

        if (abs(newX - m_XPos) == abs(newY - m_YPos)) {
            return true;
        }

        return false;
    }


} // Chess