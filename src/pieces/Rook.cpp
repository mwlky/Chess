#include "Rook.h"

namespace Chess {
    Rook::Rook(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) {

    }

    Rook::~Rook() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Rook::IsValidMove(int newX, int newY) const {
        if(!Piece::IsInsideBoard(newX, newY))
            return false;

        if(newX == m_XPos || m_YPos == newY)
            return true;

        return false;
    }
} // Chess