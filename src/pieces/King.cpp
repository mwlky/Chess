#include "King.h"

namespace Chess{
    King::King(const char *sprite, Piece::Site site, int x, int y) : Piece(sprite, site, x, y) {

    }

    King::~King() {
        SDL_DestroyTexture(m_Texture);
    }

    bool King::IsValidMove(int newX, int newY) const {
        if(!Piece::IsInsideBoard(newX, newY))
            return false;

        if (abs(newX - m_XPos) <= 1 && abs(newY - m_YPos) <= 1) {
            return true;
        }

        return false;
    }
}