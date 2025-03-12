#pragma once
#include "Game.h"
#include <SDL.h>
#include <iostream>
#include "SceneMain.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SceneTitle.h"
#include "Scene.h"
 
Game::Game() {

}

Game::~Game()
{   
    
}

void Game::init()
{   SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    frameTime = 1000/FPS;
    //初始化SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    //创建窗口
    win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,getWindowWidth(),
                            getWindowHeight(), SDL_WINDOW_SHOWN);
    //创建渲染器
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if(ren == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return;
    }
    //初始化SDL_image
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
    {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return;
    }
    //初始化SDL_mixer
    if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        std::cout << "Mix_Init Error: " << Mix_GetError() << std::endl;
        return;
    }
    //初始化Mix_OpenAudio
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
    }
    //分配频道
    Mix_AllocateChannels(32);
    //设置音乐音量
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
    //设置音效音量
    Mix_Volume(-1, MIX_MAX_VOLUME/25);
    //设置符卡音量
    Mix_Volume(6, MIX_MAX_VOLUME/15);
    Mix_Volume(5, MIX_MAX_VOLUME/15);
    //玩家射击音量
    Mix_Volume(7, MIX_MAX_VOLUME/30);
    //敌人射击音量
    Mix_Volume(0, MIX_MAX_VOLUME/35);
    Mix_Volume(1, MIX_MAX_VOLUME/35);
    Mix_Volume(2, MIX_MAX_VOLUME/35);
    //card get volumn
    Mix_Volume(3, MIX_MAX_VOLUME/10);
    //health get volumn
    Mix_Volume(4, MIX_MAX_VOLUME/10);
    //Boss战斗music
    Mix_Volume(20, MIX_MAX_VOLUME/3);
    //标题music
    Mix_Volume(25, MIX_MAX_VOLUME/3);
    //初始化SDL_ttf
    if(TTF_Init() == -1)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return;
    }

    currentScene = new SceneTitle(); 
    if(currentScene == nullptr)
    {
        std::cout << "Scene Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    currentScene->init();
}

void Game::run()
{
    while(isRunning)
    {   
        
            Uint32 frameStart = SDL_GetTicks();
            SDL_Event event;
            handleEvents(&event);
            update(deltaTime);
            render();      
            Uint32 frameEnd = SDL_GetTicks();
            Uint32 diff = frameEnd-frameStart;
            if(diff < frameTime)
            {
                SDL_Delay(frameTime-diff);
                deltaTime = frameTime/1000.0f;
            }
            else
            {
                deltaTime = diff/1000.0f;
            }
        }

    }




void Game::clean()
{
    //清理SDL资源
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    //清理SDL_image资源
    IMG_Quit();
    //清理SDL_mixer资源
    Mix_CloseAudio();
    Mix_Quit();
    //清理SDL_ttf资源
    TTF_Quit();
}

void Game::update(float deltaTime)
{
    currentScene->update(deltaTime);
}

void Game::render()
{   //清空
    SDL_RenderClear(ren);
    currentScene->render();
    //显示
    SDL_RenderPresent(ren);
}

void Game::handleEvents(SDL_Event *event)
{   
    if(SDL_PollEvent(event))
    {
        if(event->type == SDL_QUIT)
        {
            isRunning = false;
        }
        
    }
    currentScene->handleEvents(event);
}

void Game::changeScene(Scene *scene)
{
    if(currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}
