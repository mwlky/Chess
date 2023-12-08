cmake_minimum_required(VERSION 3.26)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(SDL2_INCLUDE_DIRS /include/SDL2/Headers)
set(SDL2_LIBRARIES /include/SDL2/Libs)

set(SDL2_IMAGE_INCLUDE_DIRS /include/SDL_Image/Headers)
set(SDL2_IMAGE_LIBRARIES /include/SDL_Image/Libs)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Chess src/main.cpp
        src/sdl/Window.cpp
        src/sdl/Window.h
        src/game/GameLoop.cpp
        src/game/GameLoop.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
