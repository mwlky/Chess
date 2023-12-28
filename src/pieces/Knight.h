#pragma once

#include "Piece.h"

namespace Chess{

    class Knight : public Piece{
    public:
        Knight() = default;
        Knight(const char *sprite, Site site, int x, int y);
        ~Knight() override = default;

        bool IsValidMove(int newX, int newY, MoveType type) const override;
    };
}


