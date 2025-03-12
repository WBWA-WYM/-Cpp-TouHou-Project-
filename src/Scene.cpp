#pragma once
#include "Scene.h"
#include "Game.h"
class Game;

Scene::Scene() : game(Game::getInstance())
{
}

