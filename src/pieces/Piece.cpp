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

    SDL_Rect Piece::GetRect() const {
        return m_Rect;
    }

    void Piece::SetPosition(int x, int y) {
        m_Rect.x = x;
        m_Rect.y = y;
    }

    bool Piece::IsValidMove(int x, int y) const{
        if(!IsInsideBoard(x, y))
            return false;

        return true;
    }

    bool Piece::IsInsideBoard(int newX, int newY) const {
        if(newX >= 8 || newX < 0){
            return false;
        }

        if(newY < 0 || newY >= 8){
            return false;
        }

        return true;
    }
}

