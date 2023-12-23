#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const char *sprite, Chess::Site site, int x, int y) : Piece(sprite, site, x, y) {
    }

    Pawn::~Pawn() {
        SDL_DestroyTexture(m_Texture);
    }

    bool Pawn::IsValidMove(int newX, int newY) const {
        if(!Piece::IsInsideBoard(newX, newY)){
            return false;
        }

        return true;
    }
}