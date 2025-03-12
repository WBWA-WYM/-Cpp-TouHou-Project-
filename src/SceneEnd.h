#pragma once
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include "Game.h"
#include <iostream>
#include "SceneMain.h"


class SceneEnd : public Scene{
    public:
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handleEvents(SDL_Event* event) override;
    TTF_Font* font;
    bool xKeyPreviousState = false;
};