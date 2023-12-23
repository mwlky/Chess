#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const char *sprite, Site site, int x, int y) : Piece(sprite, site, x, y) {
    }

    Pawn::~Pawn() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Pawn::IsValidMove(int newX, int newY) const {
        if(!Piece::IsInsideBoard(newX, newY)){
            return false;
        }

        int direction = (m_Site == Site::WHITE) ? -1 : 1;

        if (newX == m_XPos && newY == m_YPos + direction) {
            return true;
        }

        if (newX == m_XPos && newY == m_YPos + 2 * direction && !HasMoved) {
            return true;
        }

        return false;
    }
}