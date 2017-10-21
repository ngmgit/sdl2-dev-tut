cmake_minimum_required(VERSION 3.4)

project (sdl2-dev-tut)

set(source_files
        MainGame.cpp
        Sprite.cpp
        Errors.cpp
        GLSLProgram.cpp
        ImageLoader.cpp
        IOManager.cpp
        picoPNG.cpp
        TextureCache.cpp
        ResourceManager.cpp
    )

set(output_name "game.app")

#set library constants
SET(SDL_LINK_FLAGS "-lSDL2")
SET(GLEW_LINK_FLAGS "-lGLEW -lGLU -lGL")

# set compile and link flag
SET(COMPILER_FLAGS "-g -std=c++17 -Wall" )
SET(LINKER_FLAGS "${SDL_LINK_FLAGS} ${GLEW_LINK_FLAGS}")

# add the executable
add_executable(${output_name} main.cpp ${source_files})

# set cmake linker and compiler flags
add_compile_options(${COMPILER_FLAGS})
target_link_libraries(${output_name} ${LINKER_FLAGS})
