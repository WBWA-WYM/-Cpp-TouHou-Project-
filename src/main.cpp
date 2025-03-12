#pragma once
#include <iostream>
#include <SDL.h>
#include "Game.h"




int main(int argc,char* argv[]) {
    Game& game = Game::getInstance();
    std::cout << "Hello, from TOUHOU!\n";
    game.init();
    game.run();
    return 0;
}
