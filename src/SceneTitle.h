#pragma once
#include "Scene.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class SceneTitle : public Scene
{
public:
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handleEvents(SDL_Event* event) override;
Mix_Chunk* music = nullptr;
bool xKeyPreviousState = false;
SDL_Texture* bgtexture = nullptr;
TTF_Font* font = nullptr;
private:
};