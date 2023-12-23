#include "Knight.h"

namespace Chess {
    Knight::Knight(const char *sprite, Site site, int x, int y) : Piece(sprite, site, x, y) {}

    Knight::~Knight() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Knight::IsValidMove(int newX, int newY) const {
        if(!Piece::IsValidMove(newX, newY))
            return false;

        if((newX == m_XPos + 1 || newX == m_XPos - 1)&& (newY == m_YPos + 2 || newY == m_YPos - 2))
            return true;

        if((newX == m_XPos + 2 || newX == m_XPos - 2)&& (newY == m_YPos + 1 || newY == m_YPos - 1))
            return true;

        return false;
    }
}

