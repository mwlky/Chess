#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const char* sprite, Chess::Site site, int x, int y){
        m_Texture = SpriteManager::LoadTexture(sprite, Window::Renderer);
        
        SDL_Rect rect {x * 80 - 2 , y , 90, 90};

        m_Rect = rect;
    }

    Pawn::~Pawn(){

        SDL_DestroyTexture(m_Texture);
    }

    void Pawn::Render(){

        SpriteManager::Draw(m_Texture, m_Rect, Window::Renderer);

    }
}