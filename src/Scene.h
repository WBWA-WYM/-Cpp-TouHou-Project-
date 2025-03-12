// Scene.h
#pragma once
#include <SDL.h>
class Game;

class Scene {
    public:
    Scene();
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvents(SDL_Event* event) = 0;
    
protected:
    Game& game;
};