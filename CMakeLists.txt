cmake_minimum_required(VERSION 3.4)

project (sdl2-dev-tut)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(source_files
        MainGame.cpp
        Zombie/Level.cpp
        Zombie/Agent.cpp
        Zombie/Human.cpp
        Zombie/Player.cpp
        Zombie/Zombie.cpp
        Zombie/Gun.cpp
        Zombie/Bullet.cpp
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

# To add assets symlinks and add target dependecy to make it execute before ${output_name} target is built
if (${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    message("Build directory is same as source directory: not using symlink for assets")
else()
    message("Please make sure the assets are symlinked properly in the build directory, else errors like 'File not found' maybe encountered")
    ADD_CUSTOM_TARGET(symlink_assets ALL
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/shaders ./shaders
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/levels ./levels
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/textures ./textures)
    add_dependencies(${output_name} symlink_assets)
endif()


# *** set cmake linker and compiler flags ***
add_compile_options(${COMPILER_FLAGS})
target_link_libraries(${output_name} ${MY_LIBS_LINK_FLAGS} ${LINKER_FLAGS})
