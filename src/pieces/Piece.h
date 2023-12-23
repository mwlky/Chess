#include "SDL.h"
#include "SDL_image.h"
#include "../sdl/SpriteManager.h"

namespace Chess {
    enum class Site {
        BLACK, WHITE, NONE
    };
    enum class MoveType {
        NORMAL, CASTLE, ENPASSANT, INIT
    };

    class Piece {
    public:
        Piece() = default;
        Piece(const char *sprite, Chess::Site site, int x, int y);

        virtual ~Piece();

        void Render();

        SDL_Rect GetRect() const;

        void SetGlobalPosition(int x, int y);
        void SetBoardPosition(int x, int y);

        virtual bool IsValidMove(int x, int y) const;

        bool HasMoved;

    protected:
        bool IsInsideBoard(int newX, int newY) const;

        // Position on board
        int m_XPos;
        int m_YPos;

        Site m_Site {};

    private:
        SDL_Texture *m_Texture = nullptr;

        SDL_Rect m_Rect;
    };
};


