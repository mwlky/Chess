cmake_minimum_required(VERSION 3.26)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Chess src/main.cpp
        src/sdl/Window.cpp
        src/sdl/Window.h
        src/game/GameLoop.cpp
        src/game/GameLoop.h
        src/sdl/SpriteManager.h
        src/board/Board.cpp
        src/board/Board.h
        src/pieces/Pawn.cpp
        src/pieces/Pawn.h
        src/pieces/Piece.cpp
        src/pieces/Piece.h
        src/pieces/Knight.cpp
        src/pieces/Knight.h
        src/pieces/Rook.cpp
        src/pieces/Rook.h
        src/pieces/Bishop.cpp
        src/pieces/Bishop.h
        src/pieces/Queen.cpp
        src/pieces/Queen.h
        src/pieces/King.cpp
        src/pieces/King.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
