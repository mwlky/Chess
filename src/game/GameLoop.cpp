#include "GameLoop.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

namespace Chess {
    void GameLoop::Run() {
        Chess::Window window;
        m_IsRunning =
                window.InitWindow("Chess", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

        m_Board.CreateBoard(SCREEN_WIDTH, SCREEN_HEIGHT);

        Uint32 frameStart;
        double frameTime;

        while (m_IsRunning) {
            frameStart = SDL_GetTicks();

            Tick();

            frameTime = SDL_GetTicks() - frameStart;

            if (FrameDelay > frameTime)
            {
                SDL_Delay(FrameDelay - frameTime);
            }
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
                int x = m_Event.button.x / SQUARE_SIZE;
                int y = m_Event.button.y / SQUARE_SIZE;
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

    void GameLoop::Tick() {
        if (Window::Renderer == nullptr) {
            std::cout << "Renderer is null" << std::endl;
            return;
        }

        if (Window::CurrentWindow == nullptr) {
            std::cout << "Window is null" << std::endl;
            return;
        }

        if (SDL_RenderClear(Window::Renderer)) {
            std::cerr << "Render error!" << SDL_GetError() << std::endl;
            return;
        }

        HandleEvents();

        m_Board.Tick();

        SDL_RenderPresent(Window::Renderer);
    }

} // namespace Chess