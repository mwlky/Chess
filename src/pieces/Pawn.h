#pragma once

#include "SDL.h"
#include "Piece.h"
#include "SDL_image.h"
#include "../sdl/SpriteManager.h"

namespace Chess {

class Pawn : public Piece {
    public:
        Pawn() = default;
        Pawn(const char *sprite, Site site, int x, int y);
        ~Pawn() override;

        bool IsValidMove(int newX, int newY, MoveType type) const override;

    private:
        SDL_Texture *m_Texture = nullptr;
    };
} // namespace Chess