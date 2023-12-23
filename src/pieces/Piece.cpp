#include "Piece.h"
namespace Chess{

    Piece::Piece(const char *sprite, Chess::Site site, int x, int y) {
        m_Texture = SpriteManager::LoadTexture(sprite, Window::Renderer);

        SDL_Rect rect {x * 80 - 2 , y , 100, 100};

        m_Rect = rect;
    }

    Piece::~Piece() {
        SDL_DestroyTexture(m_Texture);
    }

    void Piece::Render() {
        SpriteManager::Draw(m_Texture, m_Rect, Window::Renderer);

    }
}

