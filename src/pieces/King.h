#pragma once

#include "Piece.h"

namespace Chess{

    class King : public Piece {
    public:
        King() = default;
        King(const char *sprite, Site site, int x, int y);

        ~King() override;

        bool IsValidMove(int newX, int newY, MoveType type) const override;

    private:
        SDL_Texture *m_Texture = nullptr;
    };
}

