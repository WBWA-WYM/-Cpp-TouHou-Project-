#pragma once
#include <SDL.h>


struct Player{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    int speed = 0;
    int speedNormalMode = 550;
    int speedSlowMode = 235;
    int currenthealth = 1;
    int maxhealth = 35;
    int currentFrame=0;
    int totalFrame=0;
    Uint32 startTime = 0;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isStill = true;
    SDL_Texture *texturestill = NULL;
    SDL_Texture *textureleft = NULL;
    SDL_Texture *textureright = NULL;
    Uint32 lastShootTime = 0;
    Uint32 coolDownTime = 100;
    bool isSlowMode = false;
    int fukaMax = 8;
    int fukaCurrent = 3;
    bool isDead = false;
    bool isRecovering = false;
};

struct EnemyA{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 2;
    int currenthealth = 3;
    int maxhealth = 10;
    int currentFrame=0;
    int totalFrame=0;
    Uint32 lastTime = 0;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isStill = true;
    SDL_Texture *texturestill = NULL;
    SDL_Texture *textureleft = NULL;
    SDL_Texture *textureright = NULL;
    SDL_Texture *currentTexture = NULL;
    bool isRunningInto = false;
    float animationTime = 0.1f;
    float timer = 0;
    int movementType = 0; // 0: down, 1: random, 2: circle
    float angle =0;
    float initalX;
    bool startMoveInit = false;
    int moveStep = 0;
    float radius;
    bool startCircling = false;
    float lastShootingTime = 0;
    float coolDownTime = 400;
    int health = 20;
    float movementTypeFloat = 0;

};
struct EnemyB{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 2;
    int currenthealth = 3;
    int maxhealth = 10;
    int currentFrame=0;
    int totalFrame=0;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isStill = true;
    Uint32 lastTime = 0;
    SDL_Texture *texturestill = NULL;
    SDL_Texture *textureleft = NULL;
    SDL_Texture *textureright = NULL;
    SDL_Texture *currentTexture = NULL;
    bool isRunningInto = false;
    float animationTime = 0.1f;
    float timer = 0;
    int movementType = 0; // 0: down, 1: random, 2: circle
    float angle =0;
    float initalX;
    bool startMoveInit = false;
    int moveStep = 0;
    bool startCircling = false;
    float radius = 0;
    float lastShootingTime = 0;
    float coolDownTime = 400;
    int health = 20;
    float movementTypeFloat = 0;
};
struct EnemyC{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 2;
    int currenthealth = 3;
    int maxhealth = 10;
    int currentFrame=0;
    int totalFrame=0;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isStill = true;
    Uint32 lastTime = 0;
    SDL_Texture *texturestill = NULL;
    SDL_Texture *currentTexture = NULL;
    bool isRunningInto = false;
    float timer = 0;
    float lastShootingTime = 0;
    float coolDownTime = 800;
    int health = 20;
};

struct TaMaRight{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
};
struct TaMaLeft{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
};
struct HitBox{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
};

struct PlayerProjectileA{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    int speed = 800;
    SDL_Texture *texture = NULL;
    bool hit = false;
    int damage = 2;
};
struct MinDistanceEnemy{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    float distance = 5000;
    int chasestep = 0;
};
struct FukaBullet{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 400;
    SDL_Texture *texture = NULL;
    bool hit = false;
    int damage = 5;
    MinDistanceEnemy minDistanceEnemy;//只有一个的minenemy
};
struct PlayerProjectileB{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 800;
    SDL_Texture *texture = NULL;
    MinDistanceEnemy minDistanceEnemy;//只有一个的minenemy
    bool hit = false;
    int damage = 2;
};
struct EnemyProjectileA{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 500;
    SDL_Texture *texture = NULL;
    bool hit = false;
};
struct EnemyProjectileB{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 500;
    SDL_Texture *texture = NULL;
    bool hit = false;
};
struct EnemyProjectileC{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int speed = 500;
    SDL_Texture *texture = NULL;
    bool hit = false;
    float timer;
};
struct FukaEffect{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    bool active = false;
    int damage = 10;
    float timer = 0;
};
struct MoveBackground1{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    float speed = 50;
    float offset = 0;
};
struct StillBackground{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;

};
struct MoveBackground2{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    float speed = 50;
    SDL_Texture *texture = NULL;
    float offset = 0;
};
struct MoveBackground3{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    float speed = 50;
    SDL_Texture *texture = NULL;
    float offset = 0;
};
struct MoveBackground4{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    float speed = 50;
    SDL_Texture *texture = NULL;
    float offset = 0;
};
struct SpawnEvent
{
    Uint32 triggerTime;
    int enemyType; //0：敌人A 1：敌人B 2：敌人C 3:Boss
    int count; //生成数量
    float spawnArea [2]; //生成地点，格式为[x1, y1]
    int movementType;//0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
};
struct ItemA{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,1};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    bool active = false;
};
struct ItemB{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,1};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    bool active = false;
};
struct ItemC{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,1};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    bool active = false;
};
struct Title02{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
};
struct Logo01{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    float alpha = 0;
    bool isFadingIn = false;
    bool isFadingOut = false;
    Uint32 fadeStarTime = 20000;
    Uint32 fadeDuration = 15000;
};
struct Logo02{
    SDL_FPoint position = {0,0};
    int width = 50;
    int height = 50;
    SDL_Texture *texture = NULL;
    float alpha = 0;
    bool isFadingIn = false;
    bool isFadingOut = false;
    Uint32 fadeStarTime = 20000;
    Uint32 fadeDuration = 15000;
};
struct Boss{
    SDL_FPoint position = {0,0};
    SDL_FPoint direction = {0,0};
    int width = 50;
    int height = 50;
    int currenthealth = 2500;
    int currentFrame=0;
    int totalFrame=0;
    float timer = 0;
    SDL_Texture *textureStill = NULL;
    SDL_Texture *currentTexture = NULL;
    SDL_Texture *textureLeft = NULL;
    SDL_Texture *textureRight = NULL;
    bool still = true;
    bool rollingLeft = false;
    bool rollingRight = false;
    Uint32 lastShootingTime = 0;
    Uint32 coolDownTime = 500;
    bool isRunningInto = false;
    int speed = 20;
};
