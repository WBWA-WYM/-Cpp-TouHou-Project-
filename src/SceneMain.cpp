#pragma once
#include "SceneMain.h"
#include "Scene.h"
#include <SDL_image.h>
#include "Game.h"
#include <iostream>
#include "Object.h"
#include <cstdlib>
#include <time.h>
#include <random>
#include "SceneEnd.h"
#include <SDL_ttf.h>
#include <string>
SceneMain::SceneMain() 
{   
}

SceneMain::~SceneMain()
{
    
}

void SceneMain::init()
{   
std::cout<<"init"<<std::endl;
gameStartTime = SDL_GetTicks();
//时间轴初始化
float RightArea = screenLeftOffset + WindowplayWidth - 100; 
float LeftArea = screenLeftOffset - 200;
float DownArea = (screenUpOffset + WindowplayHeight/2);
float UpArea = (screenUpOffset);

//秒数 | 种类 0A 1B 2C | 数量 | 位置 | 运动 0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
//3-6秒时第一波AB左右横穿
for(Uint32 i = 3000; i < 6000; i += 300)
{
    timeline.push_back({i,0,1,{RightArea,UpArea},3});
    timeline.push_back({i,1,1,{LeftArea,UpArea},3});
}
//10-20秒持续的随机移动和转圈AB敌人
for(Uint32 i = 10000; i < 20000; i += 3000)
{   
timeline.push_back({i,0,1,{RightArea,UpArea},1});
timeline.push_back({i,1,1,{RightArea,UpArea},1});
 
timeline.push_back({i,0,1,{LeftArea,UpArea},2});
timeline.push_back({i,1,1,{RightArea,UpArea},2});
}
//20 - 35秒展示标题

//35-60秒转圈搭配敌人C
 for(Uint32 i = 35000; i < 60000; i += 1000)
 {   //敌人A
     timeline.push_back({i,0,1,{RightArea,UpArea},2});
     timeline.push_back({i,0,1,{LeftArea,UpArea},2});
     //敌人B
     timeline.push_back({i,1,1,{RightArea,UpArea},2});
     timeline.push_back({i,1,1,{LeftArea,UpArea},2});
 } for(Uint32 i = 45000; i < 50000; i += 1500)
 {   //敌人C
     timeline.push_back({i,2,1,{RightArea,UpArea},4});
 }

 //65-90秒群魔乱舞
 for(Uint32 i = 65000; i < 90000; i += 1500)
 {   
 timeline.push_back({i,0,1,{RightArea,UpArea},1});
 timeline.push_back({i,0,1,{LeftArea,UpArea},0});
 timeline.push_back({i,1,1,{RightArea,UpArea},2});
 timeline.push_back({i,1,1,{LeftArea,UpArea},3});

 timeline.push_back({i,0,1,{RightArea,UpArea},4});
 timeline.push_back({i,0,1,{LeftArea,UpArea},0});
 timeline.push_back({i,1,1,{RightArea,UpArea},2});
 timeline.push_back({i,1,1,{LeftArea,UpArea},3});
 }
 //90-120秒持续随机敌人,转圈敌人,
 for(Uint32 i = 90000; i < 120000; i += 3000)
 {
     timeline.push_back({i,1,1,{RightArea,UpArea},1});
     timeline.push_back({i,0,1,{RightArea,UpArea},0});
     timeline.push_back({i,1,1,{RightArea,UpArea},2});
     timeline.push_back({i,0,1,{RightArea,UpArea},0}); 
 }
 //135-150秒持续向下敌人 横穿敌人
 for(Uint32 i = 125000; i < 150000; i += 500)
 {
     timeline.push_back({i,1,1,{RightArea,UpArea},0});
     timeline.push_back({i,0,1,{LeftArea,UpArea},0});

 }

 //155-180随机弹道敌人，敌人C
 for(Uint32 i = 155000; i < 180000; i += 500)
 {
     timeline.push_back({i,0,1,{RightArea,UpArea},1});
     timeline.push_back({i,1,1,{LeftArea,UpArea},1});
     timeline.push_back({i,2,1,{RightArea,UpArea},0});
 }
//200秒Boss战
timeline.push_back({200000,3,1,{screenLeftOffset + 400.0f,UpArea},0});

    std::srand(static_cast<unsigned int>(time(NULL)));
    //载入灵梦图像
    player.texturestill = IMG_LoadTexture(game.getRenderer(),"assets/image/reimuStill.png");
    if(player.texturestill == NULL)
    {
        std::cout<<"Failed to load player texture!"<<std::endl;
    }
    player.textureleft = IMG_LoadTexture(game.getRenderer(),"assets/image/reimuLeft.png");
    player.textureright = IMG_LoadTexture(game.getRenderer(),"assets/image/reimuRight.png");
    SDL_QueryTexture(player.texturestill, NULL, NULL, &player.width, &player.height);
    player.position.x = screenLeftOffset + WindowplayWidth / 2 - player.width / 2;
    player.position.y = screenUpOffset + WindowplayHeight - player.height;
    player.width /= 2;
    player.width /= 4;
    //灵梦帧动画初始化
    player.totalFrame = player.width / player.height;
    //初始化敌人ABC模板
    enemyATemplate.texturestill = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyAStill.png");
    enemyBTemplate.texturestill = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyBStill.png");
    enemyCTemplate.texturestill = IMG_LoadTexture(game.getRenderer(),"assets/image/C.png");
    SDL_QueryTexture(enemyATemplate.texturestill, NULL, NULL, &enemyATemplate.width, &enemyATemplate.height);
    SDL_QueryTexture(enemyBTemplate.texturestill, NULL, NULL, &enemyBTemplate.width, &enemyBTemplate.height);
    SDL_QueryTexture(enemyCTemplate.texturestill, NULL, NULL, &enemyCTemplate.width, &enemyCTemplate.height);
    if(player.textureleft == NULL)
    if(enemyATemplate.texturestill == NULL)
    {
        std::cout<<"Failed to load enemyA texture!"<<std::endl;
    }
    if(enemyBTemplate.texturestill == NULL) 
    {
        std::cout<<"Failed to load enemyBStill texture!"<<std::endl;
    }
    if(enemyCTemplate.texturestill == NULL) 
    {
        std::cout<<"Failed to load enemyB texture!"<<std::endl;
    }
    enemyATemplate.textureleft = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyAleft.png");
    enemyBTemplate.textureleft = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyBleft.png");
    SDL_QueryTexture(enemyATemplate.textureleft, NULL, NULL, &enemyATemplate.width, &enemyATemplate.height);
    SDL_QueryTexture(enemyBTemplate.textureleft, NULL, NULL, &enemyBTemplate.width, &enemyBTemplate.height);
    if(player.textureleft == NULL)
    if(enemyATemplate.textureleft == NULL)
    {
        std::cout<<"Failed to load enemyA texture!"<<std::endl;
    }
    if(enemyBTemplate.textureleft == NULL) 
    {
        std::cout<<"Failed to load enemyBLeft texture!"<<std::endl;
    }
    enemyATemplate.textureright = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyAright.png");
    enemyBTemplate.textureright = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyBRight.png");
    SDL_QueryTexture(enemyATemplate.textureright, NULL, NULL, &enemyATemplate.width, &enemyATemplate.height);
    SDL_QueryTexture(enemyBTemplate.textureright, NULL, NULL, &enemyBTemplate.width, &enemyBTemplate.height);
    if(player.textureleft == NULL)
    if(enemyATemplate.textureright == NULL)
    {
        std::cout<<"Failed to load enemyA texture!"<<std::endl;
    }
    if(enemyBTemplate.textureright == NULL) 
    {
        std::cout<<"Failed to load enemyB texture!"<<std::endl;
    }
    //阴阳玉初始化
    taMaRight.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/yinyangyu2.png");
    SDL_QueryTexture(taMaRight.texture, NULL, NULL, &taMaRight.width, &taMaRight.height);
    taMaLeft.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/yinyangyu2.png");
    SDL_QueryTexture(taMaLeft.texture, NULL, NULL, &taMaLeft.width, &taMaLeft.height);
    //HitBox初始化
    hitBox.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/HitBox.png");
    SDL_QueryTexture(hitBox.texture, NULL, NULL, &hitBox.width, &hitBox.height);
    hitBox.height /=2.35;
    hitBox.width = hitBox.height;  
    //载入子弹图像
    playerProjectileATemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/card_red.png");
    SDL_QueryTexture(playerProjectileATemplate.texture, NULL, NULL,
                     &playerProjectileATemplate.width, &playerProjectileATemplate.height);
    playerProjectileATemplate.width /= 1.5;
    playerProjectileATemplate.height /= 1.5;  
    playerProjectileBTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/qiudaoyu.png");
    if(playerProjectileBTemplate.texture == NULL)
    {
        std::cout<<"Failed to load playerProjectileB texture!"<<std::endl;
    }
    SDL_QueryTexture(playerProjectileBTemplate.texture, NULL, NULL,
                     &playerProjectileBTemplate.width, &playerProjectileBTemplate.height);
    playerProjectileBTemplate.width /= 4;
    playerProjectileBTemplate.height /= 4;         
    //随机
    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<float>(0.0f,1.0f);  
    //初始化敌人子弹模板 A
    enemyProjectileATemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyprojectileB.png");
    if(enemyProjectileATemplate.texture == NULL)
    {
        std::cout<<"Failed to load enemyProjectileA texture!"<<std::endl;
    }
    SDL_QueryTexture(enemyProjectileATemplate.texture, NULL, NULL,
                     &enemyProjectileATemplate.width, &enemyProjectileATemplate.height);
    //B
    enemyProjectileBTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/enemyprojectileA.png");
    if(enemyProjectileBTemplate.texture == NULL )
    {
        std::cout<<"Failed to load enemyProjectileB texture!"<<std::endl;
    }
    SDL_QueryTexture(enemyProjectileBTemplate.texture, NULL, NULL,
                     &enemyProjectileBTemplate.width, &enemyProjectileBTemplate.height);
    //C
    enemyProjectileCTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/projectileC.png");
    if(enemyProjectileCTemplate.texture == NULL)
    {
        std::cout<<"Failed to load enemyProjectileA texture!"<<std::endl;
    }
    SDL_QueryTexture(enemyProjectileCTemplate.texture, NULL, NULL,
                     &enemyProjectileCTemplate.width, &enemyProjectileCTemplate.height);
    enemyProjectileCTemplate.width *= 1.5;
    enemyProjectileCTemplate.height *= 1.5;
    //初始化符卡相关内容
    fukaBulletTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/fukabullet.png");
    if(fukaBulletTemplate.texture == NULL)
    {
        std::cout<<"Failed to load fuka texture!"<<std::endl;
    }
    SDL_QueryTexture(fukaBulletTemplate.texture, NULL, NULL,
                     &fukaBulletTemplate.width, &fukaBulletTemplate.height);
    fukaeffect.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/fukaeffect.png");
    if(fukaeffect.texture == NULL)
    {
        std::cout<<"Failed to load fukaeffect texture!"<<std::endl;
    }
    SDL_QueryTexture(fukaeffect.texture, NULL, NULL,
                     &fukaeffect.width, &fukaeffect.height); 
    fukaeffect.width *= 0.45;
    fukaeffect.height *= 0.45;
    fukaBulletTemplate.width *= 2.5;
    fukaBulletTemplate.height *= 2.5;

    //载入音效
    sounds["playerDied"] = Mix_LoadWAV("assets/music/se_pldead00.wav");
    sounds["shoot"] = Mix_LoadWAV("assets/music/se_plst00.wav");
    sounds["fuka"] = Mix_LoadWAV("assets/music/fuka.wav");
    sounds["fuka2"] = Mix_LoadWAV("assets/music/fuka2.wav");
    sounds["tan0"] = Mix_LoadWAV("assets/music/se_tan00.wav");
    sounds["tan1"] = Mix_LoadWAV("assets/music/se_tan01.wav");
    sounds["tan2"] = Mix_LoadWAV("assets/music/se_tan02.wav");
    sounds["cardget"] = Mix_LoadWAV("assets/music/se_cardget.wav");
    sounds["healthget"] = Mix_LoadWAV("assets/music/se_extend.wav");

    //载入背景图像
    stillbackground.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/title00a.png");
    if(stillbackground.texture == NULL)
    {
        std::cout<<"Failed to load background texture!"<<std::endl;
    }
    SDL_QueryTexture(stillbackground.texture, NULL, NULL,
                     &stillbackground.width, &stillbackground.height);
    //载入Logo01
    logo01.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/logo1.png");
    if(logo01.texture == NULL)
    {
        std::cout<<"Failed to load logo01 texture!"<<std::endl;
    }
    SDL_QueryTexture(logo01.texture, NULL, NULL,
                     &logo01.width, &logo01.height);
    logo01.width *= 2;
    logo01.height *= 2;
    //载入Logo02
    logo02.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/logo2.png");
    if(logo02.texture == NULL)
    {
        std::cout<<"Failed to load logo02 texture!"<<std::endl;
    }
    SDL_QueryTexture(logo02.texture, NULL, NULL
                     ,&logo02.width, &logo02.height);
    logo02.width *= 2;
    logo02.height *= 2;
    //移动背景1
    movebackground1.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/bg1.png");
    if(movebackground1.texture == NULL)
    {
        std::cout<<"Failed to load background1 texture!"<<std::endl;
    }
    SDL_QueryTexture(movebackground1.texture, NULL, NULL,
                     &movebackground1.width, &movebackground1.height);
                     movebackground1.width = movebackground1.height;
    //移动背景2
    movebackground2.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/bg2.png");
    if(movebackground2.texture == NULL)
    {
        std::cout<<"Failed to load background2 texture!"<<std::endl;
    }
    SDL_QueryTexture(movebackground2.texture, NULL, NULL,
                     &movebackground2.width, &movebackground2.height);
movebackground1.height = WindowplayHeight;  
movebackground1.width = WindowplayWidth;
//载入音乐
music = Mix_LoadMUS("assets/music/bgm1.mp3");
bossmusic = Mix_LoadWAV("assets/music/BOSS.mp3");
Mix_PlayMusic(music, -1);
//初始化物品
itemATemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/itemA.png");
if(itemATemplate.texture == NULL)
{
    std::cout<<"Failed to load itemA texture!"<<std::endl;
}
SDL_QueryTexture(itemATemplate.texture, NULL, NULL,&itemATemplate.width,&itemATemplate.height);


itemBTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/itemB.png");
if(itemBTemplate.texture == NULL)
{
    std::cout<<"Failed to load itemB texture!"<<std::endl;
}
SDL_QueryTexture(itemBTemplate.texture, NULL, NULL,&itemBTemplate.width,&itemBTemplate.height);

itemCTemplate.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/itemC.png");
if(itemCTemplate.texture == NULL)
{
    std::cout<<"Failed to load itemC texture!"<<std::endl;
}
SDL_QueryTexture(itemCTemplate.texture, NULL, NULL,&itemCTemplate.width,&itemCTemplate.height);
//UI图像初始化
title02.texture = IMG_LoadTexture(game.getRenderer(),"assets/image/title02.png");
if(title02.texture == NULL)
{
    std::cout<<"Failed to load title texture!"<<std::endl;
}
SDL_QueryTexture(title02.texture, NULL, NULL,
                     &title02.width, &title02.height);
//载入字体
font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
//初始化Logo透明度
logo01.alpha = 0;
logo02.alpha = 0;
//初始化Boss
boss.textureStill= IMG_LoadTexture(game.getRenderer(),"assets/image/bossstill.png");
if(boss.textureStill == NULL)
{
    std::cout<<"Failed to load boss texture!"<<std::endl;
}
SDL_QueryTexture(boss.textureStill, NULL, NULL,
                     &boss.width, &boss.height);
                     boss.position.x = screenLeftOffset + WindowplayWidth/2 - 50;
                     boss.position.y = screenUpOffset - boss.height;
}

void SceneMain::handleEvents(SDL_Event *event)
{   
    if(player.isDead)
    {
        auto scene = new SceneEnd();
        game.changeScene(scene);
    }
    else if(player.isRecovering)
    {   
        static float timer = 0;
        timer += 0.008;
        if(timer >= 3)
        {   
            player.isRecovering = false;
            player.position.x = screenLeftOffset + WindowplayWidth / 2 - player.width / 2;
            player.position.y = screenUpOffset + WindowplayHeight - player.height;
            timer = 0;
        }
    }
}
void SceneMain::update(float deltaTime)
{   
    if(bossIsAlive)
    {//更新Boss
    updateBoss(deltaTime);}
    //更新logo动画
    updateLogo(deltaTime);
    //更新Item
    updateItem(deltaTime);
    //更新背景
    updateBackground(deltaTime);
    gameCurrentTime = SDL_GetTicks();
    if((!player.isDead)&&(!player.isRecovering))
    {
        updateKeyBoard(deltaTime);
        updatereimu(deltaTime);
        //更新符卡 
        playerFukaUpdate(deltaTime);
    }
    updateEnemy(deltaTime);
    //更新子弹
    updatePlayerProjectile(deltaTime);
    updateEnemyProjectile(deltaTime);
    //更新时间轴
    //只要没执行完所有事件就继续生成
    if(currentEventIndex < timeline.size())
    {   //当前事件
        SpawnEvent& e = timeline[currentEventIndex];
        //生成时间点过了就生成
        if(gameCurrentTime >= e.triggerTime)
        {   //生成当前事件对应数量
            for(int i = 0;i < e.count; i++)
            {
                //生成坐标
                float x = e.spawnArea[0];
                float y = e.spawnArea[1];
                //生成敌人
                if(e.enemyType == 3)
                {   
                    spawnBoss(x,y);
                }
                else
                {
                    spawnEnemy(x,y,e.enemyType,e.movementType);
                }
            }
            //下一个事件
            currentEventIndex++;
        }

    }
}

void SceneMain::updatereimu(float deltaTime)
{   
    //灵梦移动动画逻辑
    player.totalFrame = 6;
    Uint32 currentTime= SDL_GetTicks();
    player.currentFrame = 24*(currentTime - player.startTime)*deltaTime*FPS/1000;
    //判断是否在移动
    if((!player.isMovingLeft)&&(!player.isMovingRight)){
        player.isStill = true;
    }
    else{
        player.isStill = false;
    }
    //帧动画播放选择
    if(player.isStill){
        if(player.currentFrame >= player.totalFrame)
        {
            player.currentFrame = 0;
            player.startTime = currentTime;
        }
    }
    else if((player.isMovingLeft)||(player.isMovingRight)){
        if(player.currentFrame >= player.totalFrame)
        {
            player.currentFrame = player.totalFrame;
            player.startTime = currentTime;
        }
    }
    //更新hitBox位置
    if((!player.isRecovering)&&(!fukaeffect.active))
    {hitBox.position.x = player.position.x + player.width/2 - hitBox.width - 1;
    hitBox.position.y = player.position.y + player.height/2 - hitBox.height/2;}
    else{
        hitBox.position.x = -10000;
        hitBox.position.y = -10000;
    }
    //更新hitBox大小
}

void SceneMain::render()
{   
    //渲染静态窗口
    renderStillBackground();
    //渲染UI
    renderUI();
    //开始限制
    SDL_Rect viewport = {screenLeftOffset,screenUpOffset,WindowplayWidth,WindowplayHeight};
    SDL_RenderSetViewport(game.getRenderer(), &viewport);
    //渲染背景
    renderMoveBackground();
    //渲染灵梦
    if(!player.isRecovering)
    {
    renderReimu();
    }
    //渲染Item
    renderItem();
    //渲染符卡效果
    playerFukaRender();
    //渲染敌人
    renderEnemy();
    //渲染HitBox；
    if(player.isSlowMode)
    {renderHitBox();}
    //渲染子弹
    renderPlayerProjectile();
    renderEnemyProjectile();
    //渲染Logo
    renderLogo();
    if(bossIsAlive)
    {//渲染Boss
    renderBoss();}
    //解除视口限制
    SDL_RenderSetViewport(game.getRenderer(), NULL);
}

void SceneMain::clean()
{
    //清理灵梦图像
    SDL_DestroyTexture(player.texturestill);
    //清理阴阳玉
    SDL_DestroyTexture(taMaLeft.texture);
    SDL_DestroyTexture(taMaRight.texture);
    //清理HitBox
    SDL_DestroyTexture(hitBox.texture);
    //清理敌人图像
    SDL_DestroyTexture(enemyATemplate.texturestill);
    SDL_DestroyTexture(enemyBTemplate.texturestill);
    SDL_DestroyTexture(enemyCTemplate.texturestill);
    SDL_DestroyTexture(enemyATemplate.textureleft);
    SDL_DestroyTexture(enemyBTemplate.textureleft);
    SDL_DestroyTexture(enemyATemplate.textureright);    
    SDL_DestroyTexture(enemyBTemplate.textureright);
    //清理子弹图像
    SDL_DestroyTexture(playerProjectileATemplate.texture);
    SDL_DestroyTexture(enemyProjectileATemplate.texture);
    SDL_DestroyTexture(enemyProjectileBTemplate.texture);
    //清理容器
    for(auto it = enemyAs.begin(); it != enemyAs.end(); )
    {   auto enemyA = *it;
        delete enemyA;
        it = enemyAs.erase(it);
    }
    enemyAs.clear();
    for(auto it = enemyBs.begin(); it != enemyBs.end(); )
    {   auto enemyB = *it;
        delete enemyB;
        it = enemyBs.erase(it);
    }
    enemyBs.clear();
    for(auto it = enemyCs.begin(); it != enemyCs.end(); )
    {   auto enemyC = *it;
        delete enemyC;
        it = enemyCs.erase(it);
    }
    enemyCs.clear();
    //清理子弹容器
    for(auto it = playerProjectileAs.begin(); it != playerProjectileAs.end(); )
    {   auto playerProjectileA = *it;
        delete playerProjectileA;
        it = playerProjectileAs.erase(it);
    }
    playerProjectileAs.clear();
    for(auto it = playerProjectileBs.begin(); it != playerProjectileBs.end(); )
    {   auto playerProjectileB = *it;
        delete playerProjectileB;
        it = playerProjectileBs.erase(it);
    }
    playerProjectileBs.clear(); 
    for(auto it = enemyProjectileAs.begin(); it != enemyProjectileAs.end(); )
    {   auto enemyProjectileA = *it;
        delete enemyProjectileA;
        it = enemyProjectileAs.erase(it);
    }
    
    enemyProjectileAs.clear();
    for(auto it = enemyProjectileBs.begin(); it != enemyProjectileBs.end(); )
    {   auto enemyProjectileB = *it;
        delete enemyProjectileB;
        it = enemyProjectileBs.erase(it);
    }
    enemyProjectileBs.clear();
    for(auto it = enemyProjectileCs.begin(); it != enemyProjectileCs.end(); )
    {   auto enemyProjectileC = *it;
        delete enemyProjectileC;
        it = enemyProjectileCs.erase(it);
    }
    enemyProjectileCs.clear();
    //清理符卡资源
    SDL_DestroyTexture(fukaBulletTemplate.texture);
    for(auto it = fukaBullets.begin(); it != fukaBullets.end(); )
    {   auto fukaBullet = *it;
        delete fukaBullet;
        it = fukaBullets.erase(it);
    }
    fukaBullets.clear();
    //清理背景
    SDL_DestroyTexture(stillbackground.texture);
    SDL_DestroyTexture(movebackground1.texture);
    SDL_DestroyTexture(movebackground2.texture);
    SDL_DestroyTexture(movebackground3.texture);
    //清理bgm
    Mix_FreeMusic(music);
    //关闭音乐
    Mix_CloseAudio();
    //清理物品素材
    SDL_DestroyTexture(itemATemplate.texture);
    SDL_DestroyTexture(itemBTemplate.texture);
    SDL_DestroyTexture(itemCTemplate.texture);
    //清理物品容器
    for(auto it = itemAs.begin(); it != itemAs.end(); )
    {   auto item = *it;
        delete item;
        it = itemAs.erase(it);
    }
    itemAs.clear();
    for(auto it = itemBs.begin(); it != itemBs.end(); )
    {   auto item = *it;
        delete item;
        it = itemBs.erase(it);
    }
    itemBs.clear();
    for(auto it = itemCs.begin(); it != itemCs.end(); )
    {   auto item = *it;
        delete item;
        it = itemCs.erase(it);
    }
    itemCs.clear();
    //清理UI图像
    SDL_DestroyTexture(title02.texture);
    TTF_CloseFont(font);
    //清理Logo
    SDL_DestroyTexture(logo01.texture);
    SDL_DestroyTexture(logo02.texture);
    //清理Boss资源
    SDL_DestroyTexture(boss.textureStill);
}

void SceneMain::updateKeyBoard(float deltaTime)
{
    auto keyboardState = SDL_GetKeyboardState(NULL);
    bool xKeyCurrentState = (keyboardState[SDL_SCANCODE_X] != 0);//按下x为true，松开为false
    player.isSlowMode = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LSHIFT] != 0);
    if(keyboardState[SDL_SCANCODE_LEFT])
    {
        player.position.x -= player.speed*deltaTime;
        player.isMovingLeft = true;
    }
    if(keyboardState[SDL_SCANCODE_RIGHT])
    {
        player.position.x += player.speed*deltaTime;
        player.isMovingRight = true;
    }
    if(keyboardState[SDL_SCANCODE_UP])
    {
        player.position.y -= player.speed *deltaTime;
    }
    if(keyboardState[SDL_SCANCODE_DOWN])
    {
        player.position.y += player.speed*deltaTime;
    }
    if((xKeyCurrentState) && (!xKeyPreviousState) && (player.fukaCurrent != 0) && (fukaeffect.active != true))//现在按下同时上一帧没按下
    {
        fukaeffect.active = true;
        playerFuka();
    }
    xKeyPreviousState = xKeyCurrentState;//记录上一次x键的状态
    //普通状态
    if(!player.isSlowMode)                                    
    {   player.speed = player.speedNormalMode;
        if((keyboardState[SDL_SCANCODE_Z])&&((gameCurrentTime-player.lastShootTime)>=player.coolDownTime))
        {
            playerNormalShoot();//普通状态射击
            player.lastShootTime = gameCurrentTime;
        } 
    }
    //低速状态
    if(player.isSlowMode)
    {   
        player.speed = player.speedSlowMode;
        if((keyboardState[SDL_SCANCODE_Z])&&((gameCurrentTime-player.lastShootTime)>=player.coolDownTime*0.65))
        {
            playerNormalShoot();
            player.lastShootTime = gameCurrentTime;
        }
    }
    if(keyboardState[SDL_SCANCODE_Z])
    {
        Mix_PlayChannel(7, sounds["shoot"], 0);
    }

    if((!keyboardState[SDL_SCANCODE_LEFT])&&(!keyboardState[SDL_SCANCODE_RIGHT]))
    {   
        player.isMovingLeft = false;
        player.isMovingRight = false;
    }
    //边界检测
    if(player.position.x < screenLeftOffset)
    {
        player.position.x = screenLeftOffset;
    }
    if(player.position.x > WindowplayWidth - player.width)
    {
        player.position.x = WindowplayWidth - player.width;
    }
    if(player.position.y < screenUpOffset)
    {
        player.position.y = screenUpOffset;
    }
    if(player.position.y > WindowplayHeight - player.height)
    {
        player.position.y = WindowplayHeight - player.height;
    }

}
void SceneMain::renderReimu()
{
    SDL_Texture* texture = NULL;
    SDL_Rect srcRect = {player.currentFrame * player.width, 0, player.width, player.height};
    SDL_Rect dstRect = {player.position.x, player.position.y, player.width*0.8, player.height*0.8};
    if(player.isStill){
        texture = player.texturestill;
    }
    else if(player.isMovingLeft){
        texture = player.textureleft;
    }
    else if(player.isMovingRight){
        texture = player.textureright;
    }
    // 设置灵梦透明度
    Uint8 originalAlpha = 255;
    if((player.isSlowMode) || (fukaeffect.active)) {
        SDL_SetTextureAlphaMod(texture, 128);// 设置为半透明（128）
    }
    if((!player.isSlowMode) && (!fukaeffect.active)) {
        SDL_SetTextureAlphaMod(texture, originalAlpha);
    }
    SDL_RenderCopy(game.getRenderer(), texture, &srcRect, &dstRect);

    //渲染阴阳玉(左)
    SDL_Rect dst2Rect = {player.position.x - taMaLeft.width + 15, player.position.y + 20, taMaLeft.width/1.5,taMaLeft.height/1.5};
    //渲染阴阳玉(右)
    SDL_Rect dst3Rect = {player.position.x + player.width - 20, player.position.y + 20, 
                         taMaRight.width/1.5,taMaRight.height/1.5};
    SDL_RenderCopy(game.getRenderer(), taMaLeft.texture, NULL, &dst2Rect);
    SDL_RenderCopy(game.getRenderer(), taMaRight.texture, NULL, &dst3Rect);
}
void SceneMain::updateItem(float deltaTime)
{  
    for(auto it = itemAs.begin(); it != itemAs.end();)
    {  
        //位置更新
        auto item = *it;
        item->position.y += item->direction.y*1.5;
        //碰撞检测
        SDL_Rect playerRect = {player.position.x, player.position.y, player.width, player.height};
        SDL_Rect itemRect = {item->position.x, item->position.y, item->width, item->height};
        if(SDL_HasIntersection(&playerRect, &itemRect))
        {
            game.score++;
            delete item;
            it = itemAs.erase(it);
            continue;
        }
        //边界检测
        if((item->position.y > WindowplayHeight + screenUpOffset + 100)||(item->position.y < screenUpOffset))
            {   
                delete item;
                it = itemAs.erase(it);
                continue;    
            }      
        it++;
    }
    for(auto it = itemBs.begin(); it != itemBs.end();)
    {   
        //位置更新
        auto item = *it;
        item->position.y += item->direction.y*1.5;
        //碰撞检测
        SDL_Rect playerRect = {player.position.x, player.position.y, player.width, player.height};
        SDL_Rect itemRect = {item->position.x, item->position.y, item->width, item->height};
        if(SDL_HasIntersection(&playerRect, &itemRect))
        {
            player.fukaCurrent++;
            Mix_PlayChannel(3, sounds["cardget"], 0);
            delete item;
            it = itemBs.erase(it);
            continue;
        }
        //边界检测
        if((item->position.y > WindowplayHeight + screenUpOffset + 100)||(item->position.y < screenUpOffset))
            {   
                delete item;
                it = itemBs.erase(it);
                continue;    
            }   
        it++;
    }
    for(auto it = itemCs.begin(); it != itemCs.end();)
    {   
        //位置更新
        auto item = *it;
        item->position.y += item->direction.y*1.5;
        //碰撞检测
        SDL_Rect playerRect = {player.position.x, player.position.y, player.width, player.height};
        SDL_Rect itemRect = {item->position.x, item->position.y, item->width, item->height};
        if(SDL_HasIntersection(&playerRect, &itemRect))
        {
            player.currenthealth++;
            Mix_PlayChannel(4, sounds["healthget"], 0);
            delete item;
            it = itemCs.erase(it);
            continue;
        }
        //边界检测
        if((item->position.y > WindowplayHeight + screenUpOffset + 100)||(item->position.y < screenUpOffset))
            {   
                delete item;
                it = itemCs.erase(it);
                continue;    
            }   
        it++;
    }
}
void SceneMain::updateLogo(float deltaTime)
{   if(gameCurrentTime < fadeStarTime)
    {return;}
    float progress = (gameCurrentTime - fadeStarTime) / (float)fadeDuration;
    progress = SDL_clamp(progress, 0.0f, 1.0f);
    isFadingIn = true;
    if(gameCurrentTime > fadeStarTime + fadeDuration)
    {
        isFadingIn = false;
        isFadingOut = true;
    }
    if(isFadingIn)
    {
        logo01.alpha = (progress * 255);
        logo02.alpha = (progress * 255);
    }
    else if((!isFadingIn) && (isFadingOut))
    {
        logo01.alpha = (255 - progress * 255);
        logo02.alpha = (255 - progress * 255);
    }
}
void SceneMain::spawnEnemy(float x, float y, int enemyType, int movementType)
{   
        if(enemyType == 0)//敌人A
        {  
            SDL_Texture * texture = enemyATemplate.textureright;  
            auto enemy = new EnemyA(enemyATemplate);
            enemy->position.x = x; 
            enemy->position.y = y;
            enemy->currentTexture = texture;
            enemy->speed = 10;
            enemy->direction.x = 30;
            enemy->direction.y = 10;
            enemy->isRunningInto = true;
            enemy->movementTypeFloat = movementType; //0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
            enemy->movementType = movementType;
            enemyAs.push_back(enemy);
            enemyNumber++;
            lastEnemySpawnTime = gameCurrentTime;
        }
        else if(enemyType == 1)//敌人B
        {   
            SDL_Texture * texture = enemyBTemplate.textureright;  
            auto enemy = new EnemyB(enemyBTemplate);
            enemy->position.x = x; 
            enemy->position.y = y;
            enemy->currentTexture = texture;
            enemy->speed = 10;
            enemy->direction.x = 30;
            enemy->direction.y = 10;
            enemy->isRunningInto = true;
            enemy->movementTypeFloat = movementType; //0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
            enemy->movementType = movementType;
            enemyBs.push_back(enemy);
            enemyNumber++;
            lastEnemySpawnTime = gameCurrentTime;
        }
    else if(enemyType == 2)//敌人C
    {  
        SDL_Texture * texture = enemyCTemplate.texturestill;  
        auto enemy = new EnemyC(enemyCTemplate);
        if(enemyCs.size() != 0){
            enemy->position.x = enemyCs.back()->position.x + 200;
        }
        else{
            enemy->position.x = screenLeftOffset+50;
        }
        enemy->position.y = screenUpOffset+10;
        enemy->currentTexture = texture;
        enemy->speed = 10;
        enemy->direction.x = 30;
        enemy->direction.y = 30;
        enemy->isRunningInto = true;
        enemyCs.push_back(enemy);
        enemyNumber++;
        lastEnemySpawnTime = gameCurrentTime;
    }
}
void SceneMain::spawnBoss(float x, float y)
{   
    BossSpawnTime = gameCurrentTime;
    bossIsAlive = true;
    boss.isRunningInto = true;
    boss.direction.y = 10;
    Mix_HaltMusic();
    Mix_PlayChannel(20,bossmusic, -1);
}
void SceneMain::updateEnemy(float deltaTime)
{   //敌人A状态更新
    for(auto it = enemyAs.begin(); it != enemyAs.end();)
    {
         auto enemyA = (*it);
        //Running Into
         if(enemyA->isRunningInto)
         {  
             enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/3;
             enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/3;
             enemyA->direction.x *= 0.999;
             enemyA->direction.y *= 0.999;
             if( ((enemyA->position.x >= screenLeftOffset+enemyA->width)&&(enemyA->direction.x > 0)) ||
                 ((enemyA->position.x <= screenLeftOffset+WindowplayWidth-enemyA->width-50)&&(enemyA->direction.x < 0)) )
             {  
                enemyA->isRunningInto = false;
                enemyA->startMoveInit = true;
             }
         }

        //场内运动初始化
            if((enemyA->startMoveInit)&&(!enemyA->isRunningInto)){
                switch(enemyA->movementType){
                case 0: //向下移动到出屏幕
                    enemyA->direction.x =0;
                    enemyA->direction.y = 60;
                    enemyA->startMoveInit = false;
                    break;
                case 1: //随机移动
                    enemyA->direction.x = rand()%60-20;
                    enemyA->direction.y = rand()%60-20;
                    enemyA->startMoveInit = false;
                    break;
                case 2: //转圈运动
                    enemyA->radius = enemyA->width*3;
                    //先向内运动
                    if(enemyA->position.x <= screenLeftOffset+(WindowplayWidth/2))
                    {
                    enemyA->direction.x = 80;
                    enemyA->direction.y = 30;
                    enemyA->startMoveInit = false;
                    }
                    else
                    {
                    enemyA->direction.x = -80;
                    enemyA->direction.y = 30;
                    enemyA->startMoveInit = false;
                    }
                case 3: //快速横穿
                    if(enemyA->position.x <= screenLeftOffset+(WindowplayWidth/2))
                    {
                        enemyA->direction.x = 80;
                    }
                    else if (enemyA->position.x > screenLeftOffset+(WindowplayWidth/2))
                    {
                        enemyA->direction.x = -80;
                    }
                    enemyA->direction.y = 0;
                    enemyA->startMoveInit = false;
                    break;
                case 4: //快速交叉穿过
                    if(enemyA->position.x <= screenLeftOffset+(WindowplayWidth/2))
                    {
                        enemyA->direction.x = 65;
                    }
                    else if (enemyA->position.x > screenLeftOffset+(WindowplayWidth/2))
                    {
                        enemyA->direction.x = -65;
                    }
                    enemyA->direction.y = 25;
                    enemyA->startMoveInit = false;
                }
            }

        //场内运动更新
            if(!enemyA->isRunningInto)
            {

            switch(enemyA->movementType)
            {
            case 0: //向下移动到出屏幕
                enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/2;
                enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/2;
                enemyA->direction.x *= 0.999;
                break;
            case 1: //随机移动
                //步数后改变方向
                if(enemyA->moveStep >=200)
                {
                    enemyA->direction.x = rand()%60-20;
                    enemyA->direction.y = rand()%60-20;
                    enemyA->moveStep = 0;
                }
                enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/3;
                enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/3;
                enemyA->direction.x *= 0.999;
                enemyA->direction.y *= 0.999;
                enemyA->moveStep++;
                break;
            case 2: //转圈运动
                    //先向内移动40步
                    if(enemyA->moveStep <= 40)
                    {
                        enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/2;
                        enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/2;
                        enemyA->direction.x *= 0.99;
                        enemyA->direction.y *= 0.99;
                        enemyA->moveStep++;
                    }
                    //转圈数据初始化
                    else if((enemyA->moveStep >= 40)&&(!enemyA->startCircling))
                    {   
                        enemyA->direction.x = 50;
                        enemyA->direction.y = 50;
                        enemyA->initalX = enemyA->position.x;
                        enemyA->radius = enemyA->width;
                        enemyA->startCircling = true;
                    }
                //开始转圈
                if(enemyA->startCircling)
                {
                enemyA->angle += 0.125/2;
                enemyA->direction.x = enemyA->radius*cos(enemyA->angle);
                enemyA->direction.y = enemyA->radius*sin(enemyA->angle);
                enemyA->position.x += enemyA->speed *enemyA->direction.x* deltaTime/3.75;
                enemyA->position.y += enemyA->speed *enemyA->direction.y* deltaTime/3.75;
                break;
                }
            case 3: //快速横穿
                enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/2.25;
                enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/2.25;
                enemyA->direction.x *= 0.999;
                break;
            case 4: //快速交叉运动
                enemyA->position.x += enemyA->direction.x * enemyA->speed * deltaTime/1.5;
                enemyA->position.y += enemyA->direction.y * enemyA->speed * deltaTime/1.5;
                enemyA->direction.x *= 0.999;
                enemyA->direction.y *= 0.999;
                break;
            }
        }
         //飞行状况判断
         if(enemyA->direction.x > 0)
         {
             enemyA->isMovingRight = true;
             enemyA->isMovingLeft = false;
             enemyA->isStill = false;
             enemyA->totalFrame = 7;
         }
         else if(enemyA->direction.x < 0)
         {
            enemyA->isMovingRight = false;
             enemyA->isMovingLeft = true;
             enemyA->isStill = false;
             enemyA->totalFrame = 7;
         }
         else if((enemyA->direction.x == 0))
         {
             enemyA->isMovingRight = false;
             enemyA->isMovingLeft = false;
             enemyA->isStill = true;
             enemyA->totalFrame = 5;
         }
         //当前材质比例更新
         if(enemyA->isMovingRight)
         {  
            enemyA->width = enemyA->height+3.5;
         }
         else if(enemyA->isMovingLeft)
         {
            enemyA->width = enemyA->height+3.5;
         }
         else
         {
            enemyA->width = enemyA->height+2.5;
         }
        //非灵梦7帧移动逻辑
        enemyA->timer += deltaTime;
        if(enemyA->timer >= 0.142857142857/1.5)
        {  enemyA->currentFrame += 1;
           enemyA->timer = 0;}
        if((enemyA->isStill) && (enemyA->currentFrame >= enemyA->totalFrame))
        {
            enemyA->currentFrame = 0;
            enemyA->lastTime = gameCurrentTime;
        }
        else if((enemyA->isMovingRight) || (enemyA->isMovingLeft))
        {   if(enemyA->currentFrame >= enemyA->totalFrame)
            enemyA->currentFrame = 0;
            enemyA->lastTime = gameCurrentTime;
        }
        //在RunningInto之后出屏幕的删除
        if(enemyA->isRunningInto == false)
        {
            if((enemyA->position.x < screenLeftOffset - 300)||(enemyA->position.x > screenLeftOffset+WindowplayWidth + 300))
            {   enemyNumber--;
                delete enemyA;
                it = enemyAs.erase(it);
                continue;
            }
            else if((enemyA->position.y > WindowplayHeight + screenUpOffset + 300)||(enemyA->position.y < screenUpOffset - 300))
            {   enemyNumber--;
                delete enemyA;
                it = enemyAs.erase(it);
                continue;    
            }       
        }
        //敌人射击
        if((!player.isRecovering)&&(!fukaeffect.active))
        {
            if((gameCurrentTime - enemyA->lastShootingTime) > enemyA->coolDownTime)
            {
                enemyAShoot(enemyA);
                enemyA->lastShootingTime = gameCurrentTime;
            }
        }
        //死亡更新
        if(enemyA->health <=0)
        {   //概率下生成物品
            float i = 10*dis(gen);
            //生成A
            if((i>0)&&(i<=3))
            {   
                auto item = new ItemA(itemATemplate);
                item->position.x = enemyA->position.x + enemyA->width/2 - item->width/2;
                item->position.y = enemyA->position.y + enemyA->height/2 - item->height/2;
                itemAs.push_back(item);
            }
            //生成B
            else if((i>3)&&(i<=4))
            {
                auto item = new ItemB(itemBTemplate);
                item->position.x = enemyA->position.x + enemyA->width/2 - item->width/2;
                item->position.y = enemyA->position.y + enemyA->height/2 - item->height/2;
                itemBs.push_back(item);
            }
            //生成C
            else if((i>5)&&(i<=6))
            {
                auto item = new ItemC(itemCTemplate);
                item->position.x = enemyA->position.x + enemyA->width/2 - item->width/2;
                item->position.y = enemyA->position.y + enemyA->height/2 - item->height/2;
                itemCs.push_back(item);
            }
            Mix_PlayChannel(-1, sounds["enemyDied"], 0);
            enemyNumber--;
            delete enemyA;
            it = enemyAs.erase(it);
            continue;
            
        }
        it++;
    }
    //敌人B状态更新
    for(auto it = enemyBs.begin(); it != enemyBs.end();)
    {
        auto enemyB = (*it);
        //Running Into
        if(enemyB->isRunningInto)
        {
            enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime/3;
            enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime/3;
            enemyB->direction.x *= 0.999;
            enemyB->direction.y *= 0.999;
            if( ((enemyB->position.x >= screenLeftOffset+enemyB->width)&&(enemyB->direction.x > 0)) ||
                ((enemyB->position.x <= screenLeftOffset+WindowplayWidth-enemyB->width-50)&&(enemyB->direction.x < 0)) )
            {  
               enemyB->direction.x = 0;
               enemyB->direction.y = 0;
               enemyB->isRunningInto = false;
               enemyB->startMoveInit = true;
            }
        }
               //场内运动初始化
if ((enemyB->startMoveInit) && (!enemyB->isRunningInto)) 
{
    switch (enemyB->movementType) 
    {
    case 0: // 向下移动到出屏幕
        enemyB->direction.x = 0;
        enemyB->direction.y = 80;
        enemyB->startMoveInit = false;
        break;
    case 1: // 随机移动
        enemyB->direction.x = rand() % 60 - 20;
        enemyB->direction.y = rand() % 60 - 20;
        enemyB->startMoveInit = false;
        break;
    case 2: // 转圈运动
        enemyB->radius = enemyB->width * 3;
        // 先向内运动
        if (enemyB->position.x <= screenLeftOffset + (WindowplayWidth / 2)) 
        {
            enemyB->direction.x = 80;
            enemyB->direction.y = 30;
            enemyB->startMoveInit = false;
        } 
        else 
        {
            enemyB->direction.x = -80;
            enemyB->direction.y = 30;
            enemyB->startMoveInit = false;
        }
        break;
    case 3: // 快速横穿
        if (enemyB->position.x <= screenLeftOffset + (WindowplayWidth / 2)) 
        {
            enemyB->direction.x = 80;
        } 
        else if (enemyB->position.x > screenLeftOffset + (WindowplayWidth / 2)) 
        {
            enemyB->direction.x = -80;
        }
        enemyB->direction.y = 0;
        enemyB->startMoveInit = false;
        break;
    case 4: // 快速交叉穿过
        if (enemyB->position.x <= screenLeftOffset + (WindowplayWidth / 2)) 
        {
            enemyB->direction.x = 65;
        } 
        else if (enemyB->position.x > screenLeftOffset + (WindowplayWidth / 2)) 
        {
            enemyB->direction.x = -65;
        }
        enemyB->direction.y = 25;
        enemyB->startMoveInit = false;
        break;
    }
}

// 场内运动更新
if (!enemyB->isRunningInto) 
{
    switch (enemyB->movementType) 
    {
    case 0: // 向下移动到出屏幕
        enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime/2;
        enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime/2;
        enemyB->direction.x *= 0.999;
        break;
    case 1: // 随机移动
        if (enemyB->moveStep >= 200) 
        {
            enemyB->direction.x = rand() % 60 - 20;
            enemyB->direction.y = rand() % 60 - 20;
            enemyB->moveStep = 0;
        }
        enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime/3 ;
        enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime/3 ;
        enemyB->direction.x *= 0.999;
        enemyB->direction.y *= 0.999;
        enemyB->moveStep++;
        break;
    case 2: // 转圈运动
        if (enemyB->moveStep <= 40) 
        {
            enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime /1.5;
            enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime /1.5;
            enemyB->direction.x *= 0.99;
            enemyB->direction.y *= 0.99;
            enemyB->moveStep++;
        } 
        else if ((enemyB->moveStep >= 40) && (!enemyB->startCircling)) 
        {
            enemyB->direction.x = 50;
            enemyB->direction.y = 50;
            enemyB->initalX = enemyB->position.x;
            enemyB->radius = enemyB->width;
            enemyB->startCircling = true;
        }
        if (enemyB->startCircling) 
        {
            enemyB->angle += 0.125 / 2;
            enemyB->direction.x = enemyB->radius * cos(enemyB->angle);
            enemyB->direction.y = enemyB->radius * sin(enemyB->angle);
            enemyB->position.x += enemyB->speed * enemyB->direction.x * deltaTime / 3.75;
            enemyB->position.y += enemyB->speed * enemyB->direction.y * deltaTime / 3.75;
        }
        break;
    case 3: // 快速横穿
        enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime/2.25;
        enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime/2.25;
        enemyB->direction.x *= 0.999;
        break;
    case 4: // 快速交叉运动
        enemyB->position.x += enemyB->direction.x * enemyB->speed * deltaTime/1.5;
        enemyB->position.y += enemyB->direction.y * enemyB->speed * deltaTime/1.5;
        enemyB->direction.x *= 0.999;
        enemyB->direction.y *= 0.999;
        break;
    }
}
        //飞行状况判断
        if(enemyB->direction.x > 0)
        {
            enemyB->isMovingRight = true;
            enemyB->isMovingLeft = false;
            enemyB->isStill = false;
            enemyB->totalFrame = 7;
        }
        else if(enemyB->direction.x < 0)
        {
            enemyB->isMovingRight = false;
            enemyB->isMovingLeft = true;
            enemyB->isStill = false;
            enemyB->totalFrame = 7;
        }
        else if((enemyB->direction.x == 0))
        {
            enemyB->isMovingRight = false;
            enemyB->isMovingLeft = false;
            enemyB->isStill = true;
            enemyB->totalFrame = 5;
        }
        //当前材质比例更新
        if(enemyB->isMovingRight)
        {  
           enemyB->width = enemyB->height+5;
        }
        else if(enemyB->isMovingLeft)
        {
           enemyB->width = enemyB->height+5;
        }
        else
        {
           enemyB->width = enemyB->height+4;
        }
         //非灵梦7帧移动逻辑
         enemyB->timer += deltaTime;
         if(enemyB->timer >= 0.142857142857/1.5)
         {  enemyB->currentFrame += 1;
            enemyB->timer = 0;}
         if((enemyB->isStill) && (enemyB->currentFrame >= enemyB->totalFrame))
         {
             enemyB->currentFrame = 0;
             enemyB->lastTime = gameCurrentTime;
         }
         else if((enemyB->isMovingRight) || (enemyB->isMovingLeft))
         {   if(enemyB->currentFrame >= enemyB->totalFrame)
             enemyB->currentFrame = 0;
             enemyB->lastTime = gameCurrentTime;
         }
         //在RunningInto之后出屏幕的删除
        if(enemyB->isRunningInto == false)
        {
            if((enemyB->position.x < screenLeftOffset)||(enemyB->position.x > screenLeftOffset+WindowplayWidth))
            {   enemyNumber--;
                delete enemyB;
                it = enemyBs.erase(it);
                continue;
            }
            else if((enemyB->position.y > WindowplayHeight + screenUpOffset) || (enemyB->position.y < screenUpOffset))
            {   enemyNumber--;
                delete enemyB;
                it = enemyBs.erase(it);
                continue;    
            }       
        }
        //敌人射击
        if(!player.isRecovering&&(!fukaeffect.active)){
            if(gameCurrentTime - enemyB->lastShootingTime > enemyB->coolDownTime)
            {
                enemyBShoot(enemyB);
                enemyB->lastShootingTime = gameCurrentTime;
            }
        }
        //死亡更新
        if(enemyB->health <=0)
        {   
            //概率下生成物品
            float i = 10*dis(gen);
            //生成A
            if((i>0)&&(i<=3))
            {   
                auto item = new ItemA(itemATemplate);
                item->position.x = enemyB->position.x + enemyB->width/2 - item->width/2;
                item->position.y = enemyB->position.y + enemyB->height/2 - item->height/2;
                itemAs.push_back(item);
            }
            //生成B
            else if((i>3)&&(i<=5))
            {
                auto item = new ItemB(itemBTemplate);
                item->position.x = enemyB->position.x + enemyB->width/2 - item->width/2;
                item->position.y = enemyB->position.y + enemyB->height/2 - item->height/2;
                itemBs.push_back(item);
            }
            //生成C
            else if((i>5)&&(i<=7))
            {
                auto item = new ItemC(itemCTemplate);
                item->position.x = enemyB->position.x + enemyB->width/2 - item->width/2;
                item->position.y = enemyB->position.y + enemyB->height/2 - item->height/2;
                itemCs.push_back(item);
            }
            Mix_PlayChannel(-1, sounds["enemyDied"], 0);
            enemyNumber--;
            delete enemyB;
            it = enemyBs.erase(it);
            continue;
        }
        it++;
    }
    //敌人C状态更新
    for(auto it = enemyCs.begin(); it != enemyCs.end();)
    {
        auto enemyC = (*it);
        //Running Into
        if(enemyC->isRunningInto)
        {
            enemyC->position.y += enemyC->direction.y * enemyC->speed * deltaTime/5;
            enemyC->direction.y *= 0.999;
            if((enemyC->position.y >= screenUpOffset+enemyC->height -65))
            {   
                enemyC->speed = 0;
                enemyC->isRunningInto = false;
            }
        }
        enemyC->isMovingRight = false;
        enemyC->isMovingLeft = false;
        enemyC->isStill = true;
        enemyC->totalFrame = 5;
        //当前材质更新
        enemyC->currentTexture = enemyC->texturestill;
        enemyC->width = enemyC->height+25;
        //非灵梦7帧移动逻辑
         enemyC->timer += deltaTime;
         if(enemyC->timer >= 0.041666666667)
         {  enemyC->currentFrame += 1;
            enemyC->timer = 0;}
         if((enemyC->isStill) && (enemyC->currentFrame >= enemyC->totalFrame))
         {
             enemyC->currentFrame = 0;
             enemyC->lastTime = gameCurrentTime;
         }
         //在RunningInto之后出屏幕的删除
        if(enemyC->isRunningInto == false)
        {
            if((enemyC->position.x < screenLeftOffset)||(enemyC->position.x > screenLeftOffset+WindowplayWidth))
            {   enemyNumber--;
                delete enemyC;
                it = enemyCs.erase(it);
                continue;
            }
            else if((enemyC->position.y > WindowplayHeight) || (enemyC->position.y < screenUpOffset))
            {   enemyNumber--;
                delete enemyC;
                it = enemyCs.erase(it);
                continue;    
            }       
        }
          //敌人射击
        if(!player.isRecovering&&(!fukaeffect.active)){
            if(gameCurrentTime - enemyC->lastShootingTime > enemyC->coolDownTime)
            {
                enemyCShoot(enemyC);
                enemyC->lastShootingTime = gameCurrentTime;
            }
        }
          //死亡更新
        if(enemyC->health <=0)
        {
            //概率下生成物品
            float i = 10*dis(gen);
            //生成A
            if((i>0)&&(i<=3))
            {   
                auto item = new ItemA(itemATemplate);
                item->position.x = enemyC->position.x + enemyC->width/2 - item->width/2;
                item->position.y = enemyC->position.y + enemyC->height/2 - item->height/2;
                itemAs.push_back(item);
            }
            //生成B
            else if((i>3)&&(i<=5))
            {
                auto item = new ItemB(itemBTemplate);
                item->position.x = enemyC->position.x + enemyC->width/2 - item->width/2;
                item->position.y = enemyC->position.y + enemyC->height/2 - item->height/2;
                itemBs.push_back(item);
            }
            //生成C
            else if((i>5)&&(i<=7))
            {
                auto item = new ItemC(itemCTemplate);
                item->position.x = enemyC->position.x + enemyC->width/2 - item->width/2;
                item->position.y = enemyC->position.y + enemyC->height/2 - item->height/2;
                itemCs.push_back(item);
            }
            Mix_PlayChannel(-1, sounds["enemyDied"], 0);
            enemyNumber--;
            delete enemyC;
            it = enemyCs.erase(it);
            continue;
        }
    it++;
    }
}
void SceneMain::renderEnemy()
{     //渲染A
    for(auto it = enemyAs.begin(); it != enemyAs.end();++it)
    {   
        auto enemyA = (*it);
    if((enemyA->position.x > screenLeftOffset) && (enemyA->position.x<screenLeftOffset+WindowplayWidth) &&
        (enemyA->position.y > screenUpOffset) &&  (enemyA->position.y<WindowplayHeight + screenUpOffset)) 
    {
        if(enemyA->isStill)
        {
            enemyA->currentTexture = enemyA->texturestill;
        }
        if(enemyA->isMovingLeft)
        {
            enemyA->currentTexture = enemyA->textureleft;
        }
        if(enemyA->isMovingRight)
        {
            enemyA->currentTexture = enemyA->textureright;
        }
            SDL_Rect srcrect = {enemyA->width*enemyA->currentFrame, 0, enemyA->width, enemyA->height};
            SDL_Rect dstrect = {enemyA->position.x, enemyA->position.y, enemyA->width*0.75, enemyA->height*0.75};
            SDL_RenderCopy(game.getRenderer(), enemyA->currentTexture, &srcrect, &dstrect);
    }
    }
    //渲染B
    for(auto it = enemyBs.begin(); it != enemyBs.end();++it)
    {
        auto enemyB = (*it);
    if((enemyB->position.x > screenLeftOffset) && (enemyB->position.x<screenLeftOffset+WindowplayWidth) &&
    (enemyB->position.y > screenUpOffset) &&  (enemyB->position.y<WindowplayHeight + screenUpOffset))
    {
        if(enemyB->isStill)
        {
            enemyB->currentTexture = enemyB->texturestill;
        }
        if(enemyB->isMovingLeft)
        {
            enemyB->currentTexture = enemyB->textureleft;
        }
        if(enemyB->isMovingRight)
        {
            enemyB->currentTexture = enemyB->textureright;
        }
            SDL_Rect srcrect = {enemyB->width*enemyB->currentFrame, 0, enemyB->width, enemyB->height};
            SDL_Rect dstrect = {enemyB->position.x,enemyB->position.y, enemyB->width*0.75, enemyB->height*0.75};
            SDL_RenderCopy(game.getRenderer(), enemyB->currentTexture, &srcrect, &dstrect);
    }
    }
    //渲染C
    for(auto it = enemyCs.begin(); it != enemyCs.end();++it)
    {
        auto enemyC = (*it);
        SDL_Rect srcrect = {enemyC->width*enemyC->currentFrame, 0, enemyC->width, enemyC->height};
        SDL_Rect dstrect = {enemyC->position.x,enemyC->position.y, enemyC->width*0.75, enemyC->height*0.75};
        SDL_RenderCopy(game.getRenderer(), enemyC->currentTexture, &srcrect, &dstrect);
    }
}

void SceneMain::playerNormalShoot()
{
    //子弹A
    auto projectileLeftA = new PlayerProjectileA(playerProjectileATemplate);
    projectileLeftA->position.x = player.position.x - projectileLeftA->width/2 + 10;
    projectileLeftA->position.y = player.position.y;
    playerProjectileAs.push_back(projectileLeftA);
    auto projectileRightA = new PlayerProjectileA(playerProjectileATemplate);
    projectileRightA->position.x = player.position.x + player.width/2 - projectileRightA->width/2 + 10;
    projectileRightA->position.y = player.position.y;
    playerProjectileAs.push_back(projectileRightA);
    //子弹B
    auto projectileLeftB = new PlayerProjectileB(playerProjectileBTemplate);
    projectileLeftB->position.x = player.position.x - player.width + 15;
    projectileLeftB->position.y = player.position.y + 20;
    projectileLeftB->direction.x = -1.25;
    projectileLeftB->direction.y = -1;
    playerProjectileBs.push_back(projectileLeftB);
    auto projectileRightB = new PlayerProjectileB(playerProjectileBTemplate);
    projectileRightB->position.x = player.position.x + player.width + projectileRightB->width - 20;
    projectileRightB->position.y = player.position.y + 10;
    projectileRightB->direction.x = 1.25;
    projectileRightB->direction.y = -1;
    playerProjectileBs.push_back(projectileRightB);
}

void SceneMain::playerDiedEffect()
{   
    Mix_PlayChannel(-1, sounds["playerDied"], 0);
    if(player.currenthealth <= 0)
    {
        player.isDead = true;
    }
    else if(player.currenthealth > 0)
    {
        player.isRecovering = true;
    }
}

void SceneMain::enemyAShoot(EnemyA *enemy)
{   //0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
    if((enemy->movementType == 0) || (enemy->movementType == 3) || (enemy->movementType == 4))
    {   //五发跟踪弹
        for(int i = 0; i < 5; i++)
        {Mix_PlayChannel(0, sounds["tan0"], 0);
        auto projectile = new EnemyProjectileA(enemyProjectileATemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        float distance = sqrt(pow(player.position.x - projectile->position.x,2)+pow(player.position.y - projectile->position.y,2));
        projectile->direction.x = (player.position.x - projectile->position.x)/(distance);
        projectile->direction.y = (player.position.y - projectile->position.y)/(distance);
        enemyProjectileAs.push_back(projectile);
        }
    }
    if(enemy->movementType == 1)
    {   
        //敌人面朝方向的慢速弹(非圆)
        static int shootCount = 0;
        if(shootCount != 10)
        {Mix_PlayChannel(1, sounds["tan1"], 0);
            shootCount++;
        }
        if(shootCount == 10)
        { 
        auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        projectile->direction.x = enemy->direction.x/1000;
        projectile->direction.y = enemy->direction.y/1000;
        enemyProjectileBs.push_back(projectile);
        shootCount == 0;
        }
    }
    if((enemy->movementType == 2) && (enemy->startCircling))
    {   //敌人面朝方向的慢速弹(圆)
        for(int i = 0; i < 3; i++)
        {Mix_PlayChannel(1, sounds["tan1"], 0);
        auto projectile = new EnemyProjectileA(enemyProjectileATemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        projectile->direction.x = enemy->direction.x/1000;
        projectile->direction.y = enemy->direction.y/1000;
        enemyProjectileAs.push_back(projectile);}
    }
}

void SceneMain::enemyBShoot(EnemyB *enemy)
{
    //0:进入后向下快速移动 1:随机飞行 2: 转圈运动 3:快速横穿 4：快速交叉穿过
    if((enemy->movementType == 0) || (enemy->movementType == 3) || (enemy->movementType == 4))
    {   //五发跟踪弹
        for(int i = 0; i < 5; i++)
        {Mix_PlayChannel(0, sounds["tan0"], 0);
        auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        float distance = sqrt(pow(player.position.x - projectile->position.x,2)+pow(player.position.y - projectile->position.y,2));
        projectile->direction.x = (player.position.x - projectile->position.x)/(distance);
        projectile->direction.y = (player.position.y - projectile->position.y)/(distance);
        enemyProjectileBs.push_back(projectile);
        }
    }
    if(enemy->movementType == 1)
    {   
        //敌人面朝方向的慢速弹(非圆)
        static int shootCount = 0;
        if(shootCount != 10)
        {  
            shootCount++;
        }
        if(shootCount == 10)
        {Mix_PlayChannel(1, sounds["tan1"], 0);
        auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        projectile->direction.x = enemy->direction.x/1000;
        projectile->direction.y = enemy->direction.y/1000;
        enemyProjectileBs.push_back(projectile);
        shootCount == 0;
        }
    }
    if((enemy->movementType == 2) && (enemy->startCircling))
    {   //敌人面朝方向的慢速弹(圆)
        for(int i = 0; i < 3; i++)
        {Mix_PlayChannel(1, sounds["tan1"], 0);
        auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
        projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
        projectile->position.y = enemy->position.y + enemy->height;
        projectile->direction.x = enemy->direction.x/1000;
        projectile->direction.y = enemy->direction.y/1000;
        enemyProjectileBs.push_back(projectile);}
    }
}

void SceneMain::enemyCShoot(EnemyC *enemy)
{   static float baseAngle = 0;
    const int bulletCount = 15;
    for(int i = 0; i < bulletCount; i++)
    {Mix_PlayChannel(2, sounds["tan2"], 0);
    auto projectile = new EnemyProjectileC(enemyProjectileCTemplate);
    projectile->position.x = enemy->position.x + enemy->width/2 - projectile->width/2;
    projectile->position.y = enemy->position.y + enemy->height;
    float angle = baseAngle + (180.0f/bulletCount)*i;
    projectile->direction.x = cos((angle/(2*3.1415926535)));
    projectile->direction.y = fabs(sin((angle/(2*3.1415926535))));
    enemyProjectileCs.push_back(projectile);
    }
}

void SceneMain::playerFuka()
{   
    Mix_PlayChannel(6, sounds["fuka"],0);
    Mix_PlayChannel(5, sounds["fuka2"],2);
    playerFukashoot();
}

void SceneMain::playerFukashoot()
{
    static float baseAngle = 0;
    const int bulletCount = 15;
    for(int i = 0; i < bulletCount; i++)
    {
    auto projectile = new FukaBullet(fukaBulletTemplate);
    projectile->position.x = player.position.x + player.width/2 - projectile->width/2;
    projectile->position.y = player.position.y - player.height;
    float angle = baseAngle + (180.0f/bulletCount)*i;
    projectile->direction.x = cos((angle/(2*3.1415926535)));
    projectile->direction.y = -fabs(sin((angle/(2*3.1415926535))));
    fukaBullets.push_back(projectile);
    }
}

void SceneMain::playerFukaUpdate(float deltaTime)
{
    fukaeffect.position.x = player.position.x + player.width/2 - fukaeffect.width/2 - 3.85;
    fukaeffect.position.y = player.position.y + player.height/2 - fukaeffect.height/2 - 4;
    if(fukaeffect.active)
    {
        fukaeffect.timer += deltaTime;
        if(fukaeffect.timer > 2)
        {
            fukaeffect.timer = 0;
            fukaeffect.active = false;
            player.fukaCurrent--;
        }
    }
    
    // 厉遍符卡子弹
    for(auto it = fukaBullets.begin(); it != fukaBullets.end();)
    {         
        auto projectile = (*it);
        //无敌人时，子弹直线飞行
        if((enemyNumber == 0))
            { 
            projectile->position.y += projectile->speed*deltaTime*projectile->direction.y/2;
            projectile->position.x += projectile->speed*deltaTime*projectile->direction.x/2;
            }     
        else{                  
                    //厉遍B敌人
                    for(auto ite = enemyBs.begin(); ite != enemyBs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        //看是否与当前B敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
                    //厉遍A敌人
                    for(auto ite = enemyAs.begin(); ite != enemyAs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        //看是否与当前A敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
                    //厉遍C敌人
                    for(auto ite = enemyCs.begin(); ite != enemyCs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        //看是否与当前C敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
            //扇形向前
            projectile->position.y += projectile->speed*deltaTime*projectile->direction.y;
            projectile->position.x += projectile->speed*deltaTime*projectile->direction.x;
            projectile->minDistanceEnemy.chasestep++;
            }
            //如果超出屏幕，则删除
            if((projectile->position.y < screenUpOffset) || (projectile->position.y > WindowplayHeight + screenUpOffset)
                || (projectile->position.x < screenLeftOffset) || (projectile->position.x > WindowplayWidth + screenLeftOffset))
            {
                delete projectile;
                it = fukaBullets.erase(it);
                continue;
            }
        if(projectile->hit)
        {
            delete projectile;
            it = fukaBullets.erase(it);
            continue;   
        }
    it++;
    }
}

void SceneMain::playerFukaRender()
{   if(fukaeffect.active)
    {SDL_SetTextureAlphaMod(fukaeffect.texture, 20);}
    else if(!fukaeffect.active)
    {SDL_SetTextureAlphaMod(fukaeffect.texture, 100);}
    SDL_Rect rect = {fukaeffect.position.x, fukaeffect.position.y, fukaeffect.width, fukaeffect.height};
    SDL_RenderCopy(game.getRenderer(), fukaeffect.texture, NULL, &rect);
    //渲染符卡子弹
    for(auto it = fukaBullets.begin(); it != fukaBullets.end();)
    {
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
}

void SceneMain::renderUI()
{   
    SDL_Rect rect = {screenLeftOffset+WindowplayWidth,screenUpOffset,title02.width,title02.height};
    SDL_RenderCopy(game.getRenderer(), title02.texture, NULL, &rect);

    SDL_Color color = {255, 255, 255, 255};
    //需要将整型score转换为字符串
    std::string scoreText = "Score: " + std::to_string(game.score);
    std::string healthText = "Health: " + std::to_string(player.currenthealth);
    std::string FukaText = "Fuka: " + std::to_string(player.fukaCurrent);
    //创建材质
    SDL_Surface* scoresurface = TTF_RenderUTF8_Solid(font,scoreText.c_str(), color);
    SDL_Texture* scoretexture = SDL_CreateTextureFromSurface(game.getRenderer(), scoresurface);

    SDL_Surface* healthsurface = TTF_RenderUTF8_Solid(font,healthText.c_str(), color);
    SDL_Texture* healthtexture = SDL_CreateTextureFromSurface(game.getRenderer(), healthsurface);

    SDL_Surface* fukasurface = TTF_RenderUTF8_Solid(font,FukaText.c_str(), color);
    SDL_Texture* fukatexture = SDL_CreateTextureFromSurface(game.getRenderer(), fukasurface);
    //设置渲染位置
    SDL_Rect rectText1 = {screenLeftOffset+WindowplayWidth+100,
                         screenUpOffset + title02.height + 10,
                         scoresurface->w,
                         scoresurface->h};
    SDL_Rect rectText2 = {screenLeftOffset+WindowplayWidth+100,
                         screenUpOffset + title02.height + 10 + 50,
                         healthsurface->w,
                         healthsurface->h};                     
    SDL_Rect rectText3 = {screenLeftOffset+WindowplayWidth+100,
                         screenUpOffset + title02.height + 10 + 100,
                         fukasurface->w,
                         fukasurface->h};
    //渲染                  
    SDL_RenderCopy(game.getRenderer(),scoretexture, NULL, &rectText1);
    SDL_RenderCopy(game.getRenderer(),healthtexture, NULL, &rectText2);
    SDL_RenderCopy(game.getRenderer(),fukatexture, NULL, &rectText3);
    //释放资源
    SDL_FreeSurface(scoresurface);
    SDL_DestroyTexture(scoretexture);
    SDL_FreeSurface(healthsurface);
    SDL_DestroyTexture(healthtexture);
    SDL_FreeSurface(fukasurface);
    SDL_DestroyTexture(fukatexture);

    
}

void SceneMain::renderBoss()
{   std::cout<<boss.currenthealth<<std::endl;
    SDL_Rect dstrect = {boss.position.x, boss.position.y, boss.width, boss.height};
    SDL_RenderCopy(game.getRenderer(), boss.textureStill, NULL, &dstrect);
}

void SceneMain::bossShootMode1()
{
    // 螺旋弹攻击逻辑
    if(gameCurrentTime - boss.lastShootingTime > boss.coolDownTime)
    {   //三种子弹循环
        for(int type = 0; type < 3; type++)
       { // 生成螺旋弹幕
        const int bulletCount = 20; // 每圈子弹数
        const float radius = 100.0f; // 螺旋半径
        //控制螺旋旋转速度（值越大转得越快）
        const float rotationSpeed = 0.3f; 
        // 添加时间旋转因子：使弹幕整体随时间旋转
        const float timeOffset = (SDL_GetTicks() % 360000) * rotationSpeed; 
        const float speed = 0.5f;    // 子弹速度
        const float typePhase = type * 120.0f; // 子弹类型偏移角度
            if(type == 0)
            {
            for(int i = 0; i < bulletCount; i++) {
                Mix_PlayChannel(0, sounds["tan0"], 0);
                auto projectile = new EnemyProjectileA(enemyProjectileATemplate);
                // 计算复合角度：基础角度 + 类型偏移 + 时间旋转
                float angle = (360.0f/bulletCount)*i + typePhase + timeOffset;
                projectile->direction.x = cos(angle * M_PI / 180.0f)/1.2;
                projectile->direction.y = sin(angle * M_PI / 180.0f)/1.2;
                
                // 设置起始位置（Boss周围）
                projectile->position.x = boss.position.x + boss.width/2 + 
                    radius * cos(angle * M_PI / 180.0f);
                projectile->position.y = boss.position.y + boss.height/2 + 
                    radius * sin(angle * M_PI / 180.0f);
                enemyProjectileAs.push_back(projectile);
                }
            }
        else if(type == 1)
            {
            for(int i = 0; i < bulletCount; i++) {
                Mix_PlayChannel(0, sounds["tan1"], 0);
                auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
                // 计算复合角度：基础角度 + 类型偏移 + 时间旋转
                float angle = (360.0f/bulletCount)*i + typePhase + timeOffset;
                projectile->direction.x = cos(angle * M_PI / 180.0f)/1.2;
                projectile->direction.y = sin(angle * M_PI / 180.0f)/1.2;

                // 设置起始位置（Boss周围）
                projectile->position.x = boss.position.x + boss.width/2 + 
                    radius * cos(angle * M_PI / 180.0f);
                projectile->position.y = boss.position.y + boss.height/2 + 
                    radius * sin(angle * M_PI / 180.0f);
                enemyProjectileBs.push_back(projectile);
                }
            }
        else if(type == 2)
            {
            for(int i = 0; i < bulletCount; i++) {
                Mix_PlayChannel(0, sounds["tan2"], 0);
                auto projectile = new EnemyProjectileC(enemyProjectileCTemplate);
               // 计算复合角度：基础角度 + 类型偏移 + 时间旋转
               float angle = (360.0f/bulletCount)*i + typePhase + timeOffset;
                projectile->direction.x = cos(angle * M_PI / 180.0f)/1.2;
                projectile->direction.y = sin(angle * M_PI / 180.0f)/1.2;
                // 设置起始位置（Boss周围）
                projectile->position.x = boss.position.x + boss.width/2 + 
                    radius * cos(angle * M_PI / 180.0f);
                projectile->position.y = boss.position.y + boss.height/2 + 
                    radius * sin(angle * M_PI / 180.0f);
                enemyProjectileCs.push_back(projectile);
                }
            }
        }
        boss.lastShootingTime = gameCurrentTime;
    }       
}

void SceneMain::bossShootMode2()
{
    if(gameCurrentTime - boss.lastShootingTime > boss.coolDownTime)
    {   static Uint32 phasestart = SDL_GetTicks();
        const int points = 10;
        const float basicridus = 60.0f;
        const float speed = 0.1f;
        static int timer = 0;
        const Uint32 fireDuration = 2000;
        const Uint32 pauseDuration = 200;
        // 计算当前阶段已持续时间
        Uint32 elapsed = SDL_GetTicks() - phasestart;
        if(elapsed < fireDuration){
        //生成五角星角度
        for(int i = 0; i < points; i++) {
            auto projectile = new EnemyProjectileB(enemyProjectileBTemplate);
            float angle = i*36.0f + (SDL_GetTicks()%360000)*0.01f;
            float effectiveRadius = (i%2 == 0) ? basicridus : basicridus*0.5f;
            projectile->direction.x = cos(angle * M_PI / 180.0f);
            projectile->direction.y = sin(angle * M_PI / 180.0f);
            projectile->position.x = boss.position.x + boss.width/2 + effectiveRadius * cos(angle * M_PI / 180.0f);
            projectile->position.y = boss.position.y + boss.height/2 + effectiveRadius * sin(angle * M_PI / 180.0f);
            projectile->width /= 2;
            projectile->height /= 2;
            enemyProjectileBs.push_back(projectile);
            timer++;
            }
        }
         // 阶段周期结束重置
         if(elapsed > (fireDuration + pauseDuration)) {
            phasestart = SDL_GetTicks(); // 重置计时
        }
    }
}

void SceneMain::bossShootMode3()
{ 
    if(gameCurrentTime - boss.lastShootingTime > boss.coolDownTime)
    {
        const int linecount = 1;
        const float swingPhase = SDL_GetTicks() * 0.01f;
        const float swingOffset = sin(swingPhase)*75 + 90;
        //双线生成
        for(int side:{-1,1}){
            const float baseX = boss.position.x + boss.width/2 + side*35.0f;
            for(int i = 0; i < linecount; i++) {
                auto projectile = new EnemyProjectileA(enemyProjectileATemplate);
                float angle = swingOffset;
                projectile->direction.x = cos(angle * M_PI / 180.0f)/3;
                projectile->direction.y = sin(angle * M_PI / 180.0f)/5;
                projectile->position.x = baseX;
                projectile->position.y = boss.position.y + boss.height/2 + 40.0f;
                enemyProjectileAs.push_back(projectile);
            }
        }
    }
}

void SceneMain::renderPlayerProjectile()
{
    for(auto it = playerProjectileAs.begin(); it != playerProjectileAs.end();)
    {
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
    for(auto it = playerProjectileBs.begin(); it != playerProjectileBs.end();)
    {   
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
}

void SceneMain::renderLogo()
{   
    SDL_SetTextureAlphaMod(logo01.texture, (Uint8)logo01.alpha);
    SDL_Rect rect01 = {screenLeftOffset + 50, screenUpOffset, logo01.width, logo01.height};
    SDL_RenderCopy(game.getRenderer(), logo01.texture, NULL, &rect01);
    SDL_SetTextureAlphaMod(logo02.texture, (Uint8)logo02.alpha);
    SDL_Rect rect02 = {screenLeftOffset + 400, screenUpOffset + logo02.height, logo02.width, logo02.height};
    SDL_RenderCopy(game.getRenderer(), logo02.texture, NULL, &rect02);
    // 重置透明度避免影响其他元素
    SDL_SetTextureAlphaMod(logo01.texture, 255);
    SDL_SetTextureAlphaMod(logo02.texture, 255);
}

void SceneMain::renderHitBox()
{
    
    SDL_Rect rect = {hitBox.position.x, hitBox.position.y, hitBox.width, hitBox.height};
    SDL_RenderCopy(game.getRenderer(), hitBox.texture, NULL, &rect);
}

void SceneMain::renderEnemyProjectile()
{
    for(auto it = enemyProjectileAs.begin(); it != enemyProjectileAs.end();)
    {
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
    for(auto it = enemyProjectileBs.begin(); it != enemyProjectileBs.end();)
    {
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
    for(auto it = enemyProjectileCs.begin(); it != enemyProjectileCs.end();)
    {
        auto projectile = (*it);
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &rect);
        ++it;
    }
}

void SceneMain::renderMoveBackground()
{
    //背景2
    for(int posY = movebackground2.offset; posY < WindowplayHeight; posY += movebackground2.height)
    {   
        for(int posX = screenLeftOffset; posX < WindowplayWidth; posX += movebackground2.width)
        {
            SDL_Rect srcRect = {0, 0, movebackground2.width, movebackground2.height};
            SDL_Rect destRect = {posX, posY, movebackground2.width, movebackground2.height};
            SDL_RenderCopy(game.getRenderer(), movebackground2.texture, &srcRect, &destRect);
    }
    }
    //背景1
    for(int posY = movebackground1.offset; posY < WindowplayHeight; posY += movebackground1.height)
    {   
        for(int posX = screenLeftOffset; posX < WindowplayWidth; posX += movebackground1.width)
        {
            SDL_Rect srcRect = {0, 0, movebackground1.width, movebackground1.height};
            SDL_Rect destRect = {posX, posY, movebackground1.width, movebackground1.height};
            SDL_RenderCopy(game.getRenderer(), movebackground1.texture, &srcRect, &destRect);
    }
    }
}
void SceneMain::renderStillBackground()
{
    SDL_Rect stillrect = {0, 0, game.getWindowWidth(), game.getWindowHeight()+200};
    SDL_RenderCopy(game.getRenderer(), stillbackground.texture, NULL, &stillrect);
    SDL_Rect viewport = {
        screenLeftOffset, 
        screenUpOffset,
        WindowplayWidth,
        WindowplayHeight
    };
}
void SceneMain::updatePlayerProjectile(float deltaTime)
{   //厉遍A子弹
    for(auto it = playerProjectileAs.begin(); it != playerProjectileAs.end();)
    {
        auto projectile = (*it);
        projectile->position.y -= projectile->speed*deltaTime;
        //子弹撞到敌人就删除,by hit=true
        for(auto ite = enemyAs.begin(); ite != enemyAs.end(); ++ite)
        {
            auto enemy = (*ite);
            SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
            SDL_Rect projectileRect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
            if(SDL_HasIntersection(&enemyRect, &projectileRect))
            {
                enemy->health -= projectile->damage;            
                projectile->hit = true;
            }
        }
        for(auto ite = enemyBs.begin(); ite != enemyBs.end(); ++ite)
        {
            auto enemy = (*ite);
            SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
            SDL_Rect projectileRect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
            if(SDL_HasIntersection(&enemyRect, &projectileRect))
            {
                enemy->health -= projectile->damage;            
                projectile->hit = true;
            }
        }
        for(auto ite = enemyCs.begin(); ite != enemyCs.end(); ++ite)
        {
            auto enemy = (*ite);
            SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
            SDL_Rect projectileRect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
            if(SDL_HasIntersection(&enemyRect, &projectileRect))
            {
                enemy->health -= projectile->damage;            
                projectile->hit = true;
            }
        }
        //撞到boss
        SDL_Rect enemyRect = {boss.position.x, boss.position.y, boss.width, boss.height};
            SDL_Rect projectileRect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
            if(SDL_HasIntersection(&enemyRect, &projectileRect))
            {
                boss.currenthealth -= projectile->damage;            
                projectile->hit = true;
            }
        //如果子弹超出屏幕，则删除
        if(projectile->position.y < 0)
        {
            projectile->hit = true;
        }
        //需要删除就删除
        if(projectile->hit)
        {
            delete projectile;
            it = playerProjectileAs.erase(it);
        }
        //否则让它存在，厉遍下一个子弹
        else
        {
            ++it;
        }
    }
    // 厉遍B子弹
    for(auto it = playerProjectileBs.begin(); it != playerProjectileBs.end();)
    {         
        auto projectile = (*it);
        //无敌人时，子弹直线飞行
        if((enemyNumber == 0))
            { 
            projectile->position.y += projectile->speed*deltaTime*projectile->direction.y/2;
            projectile->position.x += projectile->speed*deltaTime*projectile->direction.x/2;
            }     
        else{                  
                    //厉遍B敌人
                    for(auto ite = enemyBs.begin(); ite != enemyBs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        auto currentDistance = 
                        sqrt(pow(projectile->position.x - enemy->position.x, 2) + pow(projectile->position.y - enemy->position.y, 2));
                         //如果与当前厉遍敌人是最近且已经追了上一个最小距离20次更新，则追踪它
                         if((currentDistance < projectile->minDistanceEnemy.distance)&&(projectile->minDistanceEnemy.chasestep<=20))
                         {     
                             projectile->direction.y =(enemy->position.y - projectile->position.y)/currentDistance;
                             projectile->direction.x =(enemy->position.x -  projectile->position.x)/currentDistance;
                             projectile->minDistanceEnemy.distance = currentDistance;
                             projectile->minDistanceEnemy.chasestep = 1;
                         }
                        //看是否与当前B敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
                    //厉遍A敌人
                    for(auto ite = enemyAs.begin(); ite != enemyAs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        auto currentDistance = 
                        sqrt(pow(projectile->position.x - enemy->position.x, 2) + pow(projectile->position.y - enemy->position.y, 2));
                        //如果与当前厉遍敌人是最近且已经追了上一个最小距离20次更新，则追踪它
                        if((currentDistance < projectile->minDistanceEnemy.distance)&&(projectile->minDistanceEnemy.chasestep<=20))
                        {     
                            projectile->direction.y =(enemy->position.y - projectile->position.y)/currentDistance;
                            projectile->direction.x =(enemy->position.x -  projectile->position.x)/currentDistance;
                            projectile->minDistanceEnemy.distance = currentDistance;
                            projectile->minDistanceEnemy.chasestep = 1;
                        }
                        //看是否与当前A敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
                    //厉遍C敌人
                    for(auto ite = enemyCs.begin(); ite != enemyCs.end(); ++ite)
                    {
                        auto enemy = (*ite);
                        auto currentDistance = 
                        sqrt(pow(projectile->position.x - enemy->position.x, 2) + pow(projectile->position.y - enemy->position.y, 2));
                      //如果与当前厉遍敌人是最近且已经追了上一个最小距离70次更新，则追踪它
                      if((currentDistance < projectile->minDistanceEnemy.distance)&&(projectile->minDistanceEnemy.chasestep<=20))
                      {     
                          projectile->direction.y =(enemy->position.y - projectile->position.y)/currentDistance;
                          projectile->direction.x =(enemy->position.x -  projectile->position.x)/currentDistance;
                          projectile->minDistanceEnemy.distance = currentDistance;
                          projectile->minDistanceEnemy.chasestep = 1;
                      }
                        //看是否与当前C敌人相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {enemy->position.x, enemy->position.y, enemy->width, enemy->height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            enemy->health -= projectile->damage;
                            projectile->hit = true;
                        }
                    }
            //Boss
            {auto currentDistance = 
                        sqrt(pow(projectile->position.x - boss.position.x, 2) + pow(projectile->position.y - boss.position.y, 2));
                      //如果与当前厉遍敌人是最近且已经追了上一个最小距离70次更新，则追踪它
                      if((currentDistance < projectile->minDistanceEnemy.distance)&&(projectile->minDistanceEnemy.chasestep<=20))
                      {     
                          projectile->direction.y =(boss.position.y - projectile->position.y)/currentDistance;
                          projectile->direction.x =(boss.position.x -  projectile->position.x)/currentDistance;
                          projectile->minDistanceEnemy.distance = currentDistance;
                          projectile->minDistanceEnemy.chasestep = 1;
                      }
                        //看是否与当前Boss相撞
                        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width, projectile->height};
                        SDL_Rect enemyRect = {boss.position.x, boss.position.y, boss.width, boss.height};
                        if(SDL_HasIntersection(&rect, &enemyRect))
                        {   
                            boss.currenthealth -= projectile->damage;
                            projectile->hit = true;
                        }}
            //追踪最小距离敌人
            projectile->position.y += projectile->speed*deltaTime*projectile->direction.y;
            projectile->position.x += projectile->speed*deltaTime*projectile->direction.x;
            projectile->minDistanceEnemy.chasestep++;
            }
            //如果超出屏幕，则删除
            if((projectile->position.y < screenUpOffset) || (projectile->position.y > WindowplayHeight + screenUpOffset)
                || (projectile->position.x < screenLeftOffset) || (projectile->position.x > WindowplayWidth + screenLeftOffset))
            {
                delete projectile;
                it = playerProjectileBs.erase(it);
                continue;
            }
        if(projectile->hit)
        {
            delete projectile;
            it = playerProjectileBs.erase(it);
            continue;   
        }
    it++;
    }
}

void SceneMain::updateEnemyProjectile(float deltaTime)
{
    for(auto it = enemyProjectileAs.begin(); it != enemyProjectileAs.end();)
    {
        auto projectile = (*it);
        projectile->position.y += projectile->speed*deltaTime*projectile->direction.y;
        projectile->position.x += projectile->speed*deltaTime*projectile->direction.x;
         //如果超出屏幕或灵梦Recover，则删除
         if((projectile->position.y < screenUpOffset) ||(projectile->position.y > WindowplayHeight + screenUpOffset)
         || (projectile->position.x < screenLeftOffset) || (projectile->position.x > WindowplayWidth + screenLeftOffset)
         || (player.isRecovering))
        {
            delete projectile;
            it = enemyProjectileAs.erase(it);
            continue;
        }
        //如果撞到hitBox，玩家扣命
        if((!player.isRecovering) && (!fukaeffect.active)){
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width/2, projectile->height/2};
        SDL_Rect hitBoxRect = {hitBox.position.x, hitBox.position.y, hitBox.width/3, hitBox.height/3};
        if(SDL_HasIntersection(&rect, &hitBoxRect))
        {   
            playerDiedEffect();
            player.currenthealth--;
            delete projectile;
            it = enemyProjectileAs.erase(it);
            continue;
        }
        }
        it++;
    }
    for(auto it = enemyProjectileBs.begin(); it != enemyProjectileBs.end();)
    {
        auto projectile = (*it);
        projectile->position.y += projectile->speed*deltaTime*projectile->direction.y;
        projectile->position.x += projectile->speed*deltaTime*projectile->direction.x;
        //如果撞到hitBox，玩家扣命
        if((!player.isRecovering) && (!fukaeffect.active)){
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width/2, projectile->height/2};
        SDL_Rect hitBoxRect = {hitBox.position.x, hitBox.position.y, hitBox.width/3, hitBox.height/3};
        if(SDL_HasIntersection(&rect, &hitBoxRect))
        {  
            playerDiedEffect();
            player.currenthealth--;
            delete projectile;
            it = enemyProjectileBs.erase(it);
            continue;
        }
        }
         //如果超出屏幕或灵梦Recover，则删除
         if((projectile->position.y < screenUpOffset) ||(projectile->position.y > WindowplayHeight + screenUpOffset)
         || (projectile->position.x < screenLeftOffset) || (projectile->position.x > WindowplayWidth + screenLeftOffset)
         || (player.isRecovering))
        {
            delete projectile;
            it = enemyProjectileBs.erase(it);
            continue;
        }
        it++;
    }
    for(auto it = enemyProjectileCs.begin(); it != enemyProjectileCs.end();)
    {
        auto projectile = (*it);
        projectile->position.y += projectile->speed*deltaTime*projectile->direction.y/3;
        projectile->position.x += projectile->speed*deltaTime*projectile->direction.x/3;
        if(projectile->timer > 360)
        {
            projectile->timer = 0;
        }
        //如果撞到hitBox，玩家扣命
        if((!player.isRecovering) && (!fukaeffect.active)){
        SDL_Rect rect = {projectile->position.x, projectile->position.y, projectile->width/3, projectile->height/3};
        SDL_Rect hitBoxRect = {hitBox.position.x, hitBox.position.y, hitBox.width/3, hitBox.height/3};
        if(SDL_HasIntersection(&rect, &hitBoxRect))
        {   
            playerDiedEffect();
            player.currenthealth--;
            delete projectile;
            it = enemyProjectileCs.erase(it);
            continue;
        }
        }
       //如果超出屏幕或灵梦Recover，则删除
       if((projectile->position.y < screenUpOffset) ||(projectile->position.y > WindowplayHeight + screenUpOffset)
          || (projectile->position.x < screenLeftOffset) || (projectile->position.x > WindowplayWidth + screenLeftOffset)
          || (player.isRecovering))
        {
            delete projectile;
            it = enemyProjectileCs.erase(it);
            continue;
        }
        it++;
    }
}

void SceneMain::updateBackground(float deltaTime)
{
    movebackground1.offset += movebackground1.speed*deltaTime*5;
    if(movebackground1.offset > 0)
    {
        movebackground1.offset = -movebackground1.height;
    }
    movebackground2.offset += movebackground2.speed*deltaTime*2.5;
    if(movebackground2.offset > 0)
    {
        movebackground2.offset = -movebackground2.height;
    }

}

void SceneMain::updateBoss(float deltaTime)
{
    if(bossIsAlive)
    {   //Running Into
        if(boss.isRunningInto)
        {  
            boss.position.x += boss.direction.x * boss.speed * deltaTime/3;
            boss.position.y += boss.direction.y * boss.speed * deltaTime/5;
            boss.direction.y *= 0.999;
            if(boss.position.y > screenUpOffset + boss.height - 50)
            {
                boss.isRunningInto = false;
            }
        }
        if(boss.currenthealth > 1800)
        {
            bossShootMode1();
        }
        else if((boss.currenthealth > 1000) && (boss.currenthealth <= 1800))
        {
            bossShootMode2();
        }
        else if((boss.currenthealth > 0) && (boss.currenthealth <= 1800))
        {
            bossShootMode3();
        }
    }   
    if((boss.currenthealth <= 0) && bossIsAlive)
    {   
        bossIsAlive = false;
        auto scene = new SceneEnd();
        game.changeScene(scene);  
    }
}


void SceneMain::renderItem()
{
    for(auto it = itemAs.begin(); it != itemAs.end(); it++)
    {
        auto item = (*it);
        SDL_Rect rect = {item->position.x, item->position.y, item->width, item->height};
        SDL_RenderCopy(game.getRenderer(), item->texture, NULL, &rect);
    }
    for(auto it = itemBs.begin(); it != itemBs.end(); it++)
    {
        auto item = (*it);
        SDL_Rect rect = {item->position.x, item->position.y, item->width, item->height};
        SDL_RenderCopy(game.getRenderer(), item->texture, NULL, &rect);
    }
    for(auto it = itemCs.begin(); it != itemCs.end(); it++)
    {
        auto item = (*it);
        SDL_Rect rect = {item->position.x, item->position.y, item->width, item->height};
        SDL_RenderCopy(game.getRenderer(), item->texture, NULL, &rect);
    }
}
