cmake_minimum_required(VERSION 3.30)
project(ARCANEGAME)

set(CMAKE_CXX_STANDARD 20)
set(SDL2_INCLUDE_DIR C:/libs/SDL2/include)
set(SDL2_LIB_DIR C:/libs/SDL2/lib/x64)
set(SDL2_IMAGE_INCLUDE_DIR C:/libs/SDL2_image/include)
set(SDL2_IMAGE_DIR C:/libs/SDL2_image/lib/x64)
set(SDL2_TTF_INCLUDE_DIR C:/libs/SDL2_ttf/include)
set(SDL2_TTF_DIR C:/libs/SDL2_ttf/lib/x64)
set(SDL2_MIXER_INCLUDE_DIR C:/libs/SDL2_mixer/include)
set(SDL2_MIXER_DIR C:/libs/SDL2_mixer/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_IMAGE_DIR})
link_directories(${SDL2_TTF_DIR})
link_directories(${SDL2_MIXER_DIR})

add_executable(${PROJECT_NAME}
        main.cpp
        Menu.cpp
        Menu.h
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        Globals.cpp
        Globals.h
        Bullet.cpp
        Bullet.h
        Entity.cpp
        Entity.h
        Enemy.cpp
        Enemy.h
        Boss.cpp
        Boss.h
        BossLaze.cpp
        BossLaze.h
        Health.cpp
        Health.h


)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)



