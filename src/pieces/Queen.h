#pragma once
#include "Piece.h"

namespace Chess {

    class Queen : public Piece {
    public:
        Queen() = default;
        Queen(const char *sprite, Site site, int x, int y);

        ~Queen() override = default;

        bool IsValidMove(int newX, int newY, MoveType type) const override;
    };

} // Chess

