#pragma once
#include "Piece.h"

namespace Chess {

    class Bishop : public Piece{
    public:
        Bishop() = default;
        Bishop(const char *sprite, Site site, int x, int y);

        ~Bishop() override;

        bool IsValidMove(int newX, int newY) const override;

    private:
        SDL_Texture *m_Texture = nullptr;
    };

} // Chess
