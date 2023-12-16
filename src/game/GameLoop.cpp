#include "GameLoop.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

#define LOG(x) std::cout << x

namespace Chess {
void GameLoop::Run() {
  Chess::Window window;

  m_IsRunning =
      window.InitWindow("Chess", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

  Squares squares = m_Board.CreateBoard(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (m_IsRunning) {

    if (Window::Renderer == nullptr) {
      std::cout << "Renderer is null" << std::endl;
      break;
    }

    if (Window::CurrentWindow == nullptr) {
      std::cout << "Window is null" << std::endl;
      break;
    }

    if (SDL_RenderClear(Window::Renderer)) {
      std::cerr << "Render error!" << SDL_GetError() << std::endl;
      break;
    }

    HandleEvents();
    m_Board.RenderBoard(squares);

    SDL_RenderPresent(Window::Renderer);
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