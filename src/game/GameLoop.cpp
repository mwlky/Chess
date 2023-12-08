#include "GameLoop.h"

namespace Chess {
    void GameLoop::Run() {
        Chess::Window window;

        m_IsRunning = window.InitWindow("Chess", 100, 100, 256, 256);

        while (m_IsRunning) {
            HandleEvents();
        }

        SDL_Quit();
    }

    void GameLoop::HandleEvents() {
        SDL_PollEvent(&m_Event);

        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);


        switch (m_Event.type) {

            case SDL_QUIT:
                m_IsRunning = false;
                break;

        }
    }
}