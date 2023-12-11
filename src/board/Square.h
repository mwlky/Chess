#include "../sdl/SpriteManager.h"
#include "SDL.h"
#include "SDL_render.h"

namespace Chess {

class Square {

public:
  Square() = default;
  Square(const char* path, SDL_Renderer *renderer, SDL_Rect rect) {

    m_Texture = SpriteManager::LoadTexture(path, renderer);
    m_Renderer = renderer;
    m_Rect = rect;
  }

  void Render() {
    SpriteManager::Draw(m_Texture, m_Rect, m_Renderer);
  }

private:
  SDL_Rect m_Rect {};

  SDL_Texture *m_Texture = nullptr;
  SDL_Renderer *m_Renderer = nullptr;
};
} // namespace Chess