#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "../sdl/SpriteManager.h"

namespace Chess {
    class Piece {
    public:
        enum class Site {
            BLACK, WHITE, NONE
        };
        enum class MoveType {
            NORMAL, CASTLE, ENPASSANT, TAKE
        };

        Piece() = default;
        Piece(const char *sprite, Site site, int x, int y);

        virtual ~Piece();
        virtual bool IsValidMove(int x, int y, MoveType type) const;

        Site GetSite() const;
        SDL_Rect GetRect() const;
        int GetBoardXPosition() const { return m_XPos; }
        int GetBoardYPosition() const { return m_YPos; }

        void Render();
        void SetGlobalPosition(int x, int y);
        void SetBoardPosition(int x, int y);

        bool HasMoved = false;

    protected:
        bool IsInsideBoard(int newX, int newY) const;

        // Position on board
        int m_XPos;
        int m_YPos;

        Site m_Site{};

    private:
        SDL_Texture *m_Texture = nullptr;

        SDL_Rect m_Rect;
    };
};


