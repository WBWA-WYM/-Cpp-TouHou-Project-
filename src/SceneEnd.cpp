#pragma once 
#include "SceneEnd.h"
#include <iostream>
#include "SceneTitle.h"
#include <string>
#include "SceneMain.h"

void SceneEnd::init()
{
    //载入字体
    font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
}
void SceneEnd::handleEvents(SDL_Event* event)
{
    bool xKeyCurrentState = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_X] != 0);
    {   if((xKeyCurrentState) && (!xKeyPreviousState))
        {   
            auto scene = new SceneTitle();
            game.changeScene(scene);
        }
    }
xKeyPreviousState = xKeyCurrentState;   
}
void SceneEnd::update(float deltaTime)
{
}
void SceneEnd::render()
{   
    //需要将整型score转换为字符串
    std::string scoreText =std::to_string(game.score);
    std::string fullText = "Score: " + scoreText + " Press X to return to menu";
    //渲染字体
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, fullText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game.getRenderer(), surface);
    SDL_Rect rect = {game.getWindowWidth() / 2 - surface->w / 2, game.getWindowHeight() / 2 - surface->h / 2, 
                     surface->w, surface->h };


    SDL_RenderCopy(game.getRenderer(), texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void SceneEnd::clean()
{
    //清理字体
    TTF_CloseFont(font);
}