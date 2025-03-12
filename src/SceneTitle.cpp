#pragma once
#include "SceneTitle.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include "Game.h"
#include <iostream>
#include "SceneMain.h"

void SceneTitle::init() 
{   //载入背景图片
    bgtexture = IMG_LoadTexture(game.getRenderer(), "assets/image/th08logo.jpg");
    //载入标题字体
    font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
    //载入标题音乐
    music = Mix_LoadWAV("assets/music/titlemusic.mp3");
    Mix_PlayChannel(25, music, 0);
}

void SceneTitle::handleEvents(SDL_Event* event)
{
    bool xKeyCurrentState = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Z] != 0);
        {   if((xKeyCurrentState) && (!xKeyPreviousState))
            {   
                auto scene = new SceneMain();
                game.changeScene(scene);
            }
        }
    xKeyPreviousState = xKeyCurrentState;
}

void SceneTitle::update(float deltaTime)
{

}

void SceneTitle::render()
{   
    //背景
    SDL_Rect bgRect = {0, 0, game.getWindowWidth(), game.getWindowHeight()};
    SDL_RenderCopy(game.getRenderer(), bgtexture, NULL, &bgRect);
    //字体提示
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Press Z to Start", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game.getRenderer(), surface);
    SDL_Rect textRect = {game.getWindowWidth() / 2 - surface->w / 2, game.getWindowHeight() / 2 - surface->h / 2, surface->w*3, surface->h*3};
    SDL_RenderCopy(game.getRenderer(), texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void SceneTitle::clean()
{   //清理背景图片
    SDL_DestroyTexture(bgtexture);
    TTF_CloseFont(font);
    //清理标题音乐
    Mix_FreeChunk(music);
}

