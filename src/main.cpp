#include <iostream>
#include "SDL/Window.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Chess::Window window;

    bool he = window.InitWindow();

    if(he){
        std::cout << "Sucesfully\n" << std::endl;
    }
    else{

        std::cout << "Problemo" << std::endl;
    }

    return 0;
}
