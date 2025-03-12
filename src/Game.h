#pragma once
#include <SDL.h>
#include "Scene.h"
#include "Game.h"

class Scene;
class Game{
    public:
    static Game& getInstance(){
        static Game instance;
        return instance;
    };

    void init();
    void run();
    void clean();
    void update(float deltaTime);
    void render();
    void handleEvents(SDL_Event *event);
    void changeScene(Scene* scene);
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;
    SDL_Event* event;
    int score = 0;
    
    //getters
    int getWindowWidth(){
        return WindowWidth;
    };
    int getWindowHeight(){
        return WindowHeight;
    };


    //获取渲染器窗口
    SDL_Renderer* getRenderer(){
        return ren;
    };
    SDL_Window* getWindow(){
        return win;
    };

// 删除拷贝构造函数和赋值运算符
Game(const Game&) = delete;
void operator=(const Game&) = delete;
    private:
    Game();
    ~Game();

    Scene* currentScene = nullptr;
    bool isRunning = true;
    int WindowWidth = 1024;
    int WindowHeight = 760;
    Game* game;
    int FPS = 120;
    Uint32 frameTime;
    float deltaTime;


};