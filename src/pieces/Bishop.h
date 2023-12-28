#pragma once
#include "Piece.h"

namespace Chess {

    class Bishop : public Piece{
    public:
        Bishop() = default;
        Bishop(const char *sprite, Site site, int x, int y);

        ~Bishop() override = default;

        bool IsValidMove(int newX, int newY, MoveType type) const override;
    };

} // Chess
