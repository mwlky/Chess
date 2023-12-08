#include "GameLoop.h"

namespace Chess {
    void GameLoop::Run() {
        Chess::Window window;

        bool he = window.InitWindow("Chess", 100,100, 256, 256);

        while (true){
            if(he){
                std::cout << "Sucesfully\n" << std::endl;
            }
            else{

                std::cout << "Problemo" << std::endl;
            }

        }

    }
} // Chess