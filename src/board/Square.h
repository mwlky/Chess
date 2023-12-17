#include <memory>
#include "../sdl/SpriteManager.h"
#include "../pieces/Pawn.h"
#include "SDL.h"

namespace Chess {

    class Square {

    public:
        Square() = default;

        Square(const char *path, SDL_Renderer *renderer, SDL_Rect rect) {

            m_Texture = SpriteManager::LoadTexture(path, renderer);
            m_Renderer = renderer;
            m_Rect = rect;
        }

        void Render() {
            SpriteManager::Draw(m_Texture, m_Rect, m_Renderer);
            if (m_Pawn == nullptr)
                return;

            int pawnX = m_Rect.x + (m_Rect.w - m_Pawn->GetWidth()) / 2;
            int pawnY = m_Rect.y + (m_Rect.h - m_Pawn->GetHeight()) / 2;

            // Set the position for the pawn
            m_Pawn->SetPosition(pawnX, pawnY);
            m_Pawn->SetPosition(pawnX, pawnY);
            m_Pawn->Render();
        }

        void AssignPawn(const std::shared_ptr<Pawn> &pawn) { m_Pawn = pawn; }

        std::shared_ptr<Pawn> GetAssignedPawn() const { return m_Pawn; }

    private:
        std::shared_ptr<Pawn> m_Pawn = nullptr;
        SDL_Rect m_Rect{};

        SDL_Texture *m_Texture = nullptr;
        SDL_Renderer *m_Renderer = nullptr;
    };
} // namespace Chess