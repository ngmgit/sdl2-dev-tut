#ifndef MAINGAME_H
#define MAINGAME_H

#include <vector>

#include <Myengine/Window.h>
#include <Myengine/GLSLProgram.h>
#include <Myengine/Camera2D.h>
#include <Myengine/InputManger.h>
#include <Myengine/SpriteBatch.h>

#include "Zombie/Level.h"
#include "Zombie/Player.h"
#include "Zombie/Bullet.h"

class Zombie;

enum class GameState {
    PLAY,
    EXIT
};
class MainGame {
public:
    MainGame();
    ~MainGame();

    // runs the game
    void run();

private:
    // initiaize the core system
    void initSystems();

    // initialze and set level related config
    void initLevel();

    // initialize the shaders
    void initShaders();

    // update agents
    void updateAgents();

    // update bullets
    void updateBullets();

    // Check victory
    void checkVictory();

    // Handle the input processing
    void processInput();
    // Main game loop for the program
    void gameLoop();
    // Render the game
    void drawGame();

    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _fps;

    Myengine::Window      _window;
    Myengine::GLSLProgram _textureProgram;
    Myengine::Camera2D    _camera;
    Myengine::InputManger _inputManger;
    Myengine::SpriteBatch _agentSpriteBatch;

    std::vector<Level*> _levels;
    int _currentLevel;

    Player* _player;
    //vector of all humans
    std::vector<Human*> _humans;
    std::vector<Zombie*> _zombies;

    std::vector<Bullet> _bullets;

    int _numHumansKilled; ///< Humans killed by player
    int _numZombiesKilled; ///< zombies killed by player

};

#endif
