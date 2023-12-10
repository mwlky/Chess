#include "GameLoop.h"

namespace Chess {
    void GameLoop::Run() {
        Chess::Window window;

        m_IsRunning = window.InitWindow("Chess", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_Renderer* renderer = window.GetRenderer();
        Chess::Board board;

        while (m_IsRunning) {

            if(window.GetRenderer() == nullptr){
                std::cout << "Renderer is null" << std::endl;
                break;
            }

            if (window.GetWindow() == nullptr){
                std::cout << "Window is null" << std::endl;
                break;
            }

            if(SDL_RenderClear(window.GetRenderer())){
                std::cerr << "Render error!" << SDL_GetError() << std::endl;
                break;
            }

            HandleEvents();
            board.RenderBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            SDL_RenderPresent(window.GetRenderer());
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

        }
    }
}