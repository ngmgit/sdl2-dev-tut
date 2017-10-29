cmake_minimum_required(VERSION 3.4)

project (sdl2-dev-tut)
set (CMAKE_CXX_STANDARD 17)

set(source_files
        MainGame.cpp
        Bullet.cpp
    )

set(output_name "game.app")


# *** include folders path here ***
include_directories ("${PROJECT_SOURCE_DIR}")


# *** include library path here ***
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/Myengine)


# *** add directories here ***
add_subdirectory(Myengine)


# *** set library constants ***
set(MY_LIBS_LINK_FLAGS "myengine")
set(SDL_LINK_FLAGS "-lSDL2")
set(GLEW_LINK_FLAGS "-lGLEW -lGLU -lGL")


# *** set compile and link flag ***
set(COMPILER_FLAGS "-Wall")
set(LINKER_FLAGS "${SDL_LINK_FLAGS} ${GLEW_LINK_FLAGS}")


# *** add the executable ***
add_executable(${output_name} main.cpp ${source_files})


# *** set cmake linker and compiler flags ***
add_compile_options(${COMPILER_FLAGS})
target_link_libraries(${output_name} ${MY_LIBS_LINK_FLAGS} ${LINKER_FLAGS})
