#include "GameLoop.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

#define LOG(x) std::cout << x

namespace Chess {
void GameLoop::Run() {
  Chess::Window window;

  m_IsRunning =
      window.InitWindow("Chess", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer *renderer = window.GetRenderer();

  Squares squares = m_Board.CreateBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  while (m_IsRunning) {

    if (window.GetRenderer() == nullptr) {
      std::cout << "Renderer is null" << std::endl;
      break;
    }

    if (window.GetWindow() == nullptr) {
      std::cout << "Window is null" << std::endl;
      break;
    }

    if (SDL_RenderClear(window.GetRenderer())) {
      std::cerr << "Render error!" << SDL_GetError() << std::endl;
      break;
    }

    HandleEvents();
    m_Board.RenderBoard(renderer, squares);

    SDL_RenderPresent(window.GetRenderer());
  }

  SDL_Quit();
  IMG_Quit();
}

void GameLoop::HandleEvents() {
  SDL_WaitEvent(&m_Event);

  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

  switch (m_Event.type) {

  case SDL_QUIT:
    m_IsRunning = false;
    break;

  case SDL_MOUSEBUTTONDOWN:
      MouseEvent();
    break;
  }
}

void GameLoop::MouseEvent() {
  int mouseX = 0;
  int mouseY = 0;

  SDL_GetMouseState(&mouseX, &mouseY);

  LOG("x:");
  LOG(mouseX / 80);
  LOG("\n");

LOG("y:");
  LOG(mouseY / 80);
  LOG("\n");
}
} // namespace Chess