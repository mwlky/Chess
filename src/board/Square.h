#include <memory>
#include "../sdl/SpriteManager.h"
#include "SDL.h"
#include "../pieces/Piece.h"

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
            if (m_Piece == nullptr)
                return;

            m_Piece->Render();
        }

        void AssignPiece(const std::shared_ptr<Piece> &pawn, bool isMoveValid) {
            m_Piece = pawn;
            int pawnX = m_Rect.x + (m_Rect.w - m_Piece->GetRect().w) / 2;
            int pawnY = m_Rect.y + (m_Rect.h - m_Piece->GetRect().h) / 2;

            m_Piece->SetGlobalPosition(pawnX, pawnY);
            m_Piece->SetBoardPosition(m_Rect.x / 100, m_Rect.y / 100);

            if (!m_Piece->HasMoved && isMoveValid)
                m_Piece->HasMoved = isMoveValid;
        }

        void UnassignPiece(){
            m_Piece = nullptr;
        }

        SDL_Rect GetPosition() const { return m_Rect; }

        std::shared_ptr<Piece> GetAssignedPawn() const { return m_Piece; }

    private:
        std::shared_ptr<Piece> m_Piece = nullptr;
        SDL_Rect m_Rect{};

        SDL_Texture *m_Texture = nullptr;
        SDL_Renderer *m_Renderer = nullptr;
    };
} // namespace Chess