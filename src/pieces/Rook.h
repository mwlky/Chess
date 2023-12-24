#pragma once

#include "Piece.h"

namespace Chess {

    class Rook : public Piece {
    public:
        Rook() = default;
        Rook(const char *sprite, Site site, int x, int y);

        ~Rook() override;

        bool IsValidMove(int newX, int newY, MoveType type) const override;

    private:
        SDL_Texture *m_Texture = nullptr;
    };
} // Chess
