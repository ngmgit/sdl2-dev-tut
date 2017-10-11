OBJS = main.cpp MainGame.cpp Sprite.cpp Errors.cpp GLSLProgram.cpp
SDL_LINK_FLAG = -lSDL2
GLEW_LINK_FLAG = -lGLEW -lGLU -lGL

CC = g++

COMPILER_FLAGS = -g -std=c++17 -Wall

LINKER_FLAGS = $(SDL_LINK_FLAG) $(GLEW_LINK_FLAG)

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME).app
