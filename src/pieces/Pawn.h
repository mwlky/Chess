#include "../sdl/SpriteManager.h"
#include "SDL.h"
#include "SDL_image.h"

namespace Chess {

    enum class Site {
        BLACK, WHITE, NONE
    };
    enum class MoveType {
        NORMAL, CASTLE, ENPASSANT, INIT
    };

    class Pawn {
    public:
        Pawn() = default;
        Pawn(const char *sprite, Chess::Site site, int x, int y);
        ~Pawn();

        void Render();
        int GetWidth() const { return m_Rect.w; };
        int GetHeight() const { return m_Rect.h; };

        void SetPosition(int x, int y){
            m_Rect.x = x;
            m_Rect.y = y;
        }

    private:
        SDL_Texture *m_Texture = nullptr;

        SDL_Rect m_Rect;
    };
} // namespace Chess