#include "GameLoop.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

#define LOG(x) std::cout << x

namespace Chess {
    void GameLoop::Run() {
        Chess::Window window;
        m_IsRunning =
                window.InitWindow("Chess", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

        m_Board.CreateBoard(SCREEN_WIDTH, SCREEN_HEIGHT);

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

            m_Board.RenderBoard();
            m_Board.MoveDraggedPawn();

            SDL_RenderPresent(Window::Renderer);
        }

        SDL_Quit();
        IMG_Quit();
    }

    void GameLoop::HandleEvents() {
        SDL_PollEvent(&m_Event);

        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

        switch (m_Event.type) {

            case SDL_QUIT:
                m_IsRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN: {
                int x = m_Event.button.x / 100;
                int y = m_Event.button.y / 100;
                MovePiece(x, y);
            }
                break;

            case SDL_MOUSEBUTTONUP:
                m_Board.ReleasePiece();
                break;
        }
    }

    void GameLoop::MovePiece(int x, int y) {
        m_Board.TakePiece(x, y);
    }

} // namespace Chess