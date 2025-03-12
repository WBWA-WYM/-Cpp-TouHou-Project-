#pragma once
#include "Scene.h"
#include "Object.h"
#include "Game.h"
#include <list>
#include <random>
#include <map>
#include "SDL_mixer.h"
#include "SDL_ttf.h"


class SceneMain : public Scene{
public:
SceneMain();
~SceneMain();
virtual void init() override;
virtual void handleEvents(SDL_Event* event) override;
virtual void update(float deltaTime) override;
void updatereimu(float deltaTime);
void updateEnemy(float deltaTime);
void updatePlayerProjectile(float deltaTime);
void updateEnemyProjectile(float deltaTime);
void updateBackground(float deltaTime);
void updateBoss(float deltaTime);
virtual void render() override;
void renderItem();
void renderReimu();
void renderEnemy();
void renderHitBox();
void renderEnemyProjectile();
void renderMoveBackground();
void renderStillBackground();
void renderPlayerProjectile();
void renderLogo();
virtual void clean() override;
void updateKeyBoard(float deltaTime);
void updateItem(float deltaTime);
void updateLogo(float deltaTime);
void spawnEnemy(float x,float y, int type,int movementType);
void spawnBoss(float x,float y);
void playerNormalShoot();
void playerDiedEffect();
void enemyAShoot(EnemyA* enemy);
void enemyBShoot(EnemyB* enemy);
void enemyCShoot(EnemyC* enemy);
void playerFuka();
void playerFukashoot();
void playerFukaUpdate(float deltTime);
void playerFukaRender();
void renderUI();
void renderBoss();
void bossShootMode1();
void bossShootMode2();
void bossShootMode3();
//Boss
Mix_Chunk* bossmusic;
Boss boss;
Uint32 fadeStarTime = 20000;
Uint32 fadeDuration = 15000;
int screenLeftOffset = 25;
int screenUpOffset = 12;
int WindowplayWidth = 680;
int WindowplayHeight = 720;
Uint32 lastEnemySpawnTime = 0;
Uint32  gameCurrentTime;
Uint32  gameStartTime;
Uint32 BossSpawnTime = 0;
bool xKeyPreviousState = false;
bool bossIsAlive = false;
//标题
Title02 title02;
Logo01 logo01;
Logo02 logo02;
//创建模板
EnemyA enemyATemplate;
EnemyB enemyBTemplate;
EnemyC enemyCTemplate;
PlayerProjectileB playerProjectileBTemplate;
PlayerProjectileA playerProjectileATemplate;
EnemyProjectileA enemyProjectileATemplate;
EnemyProjectileB enemyProjectileBTemplate;
EnemyProjectileC enemyProjectileCTemplate;
FukaBullet fukaBulletTemplate;
FukaEffect fukaeffect;
ItemA itemATemplate;
ItemB itemBTemplate;
ItemC itemCTemplate;
//创建敌人容器
std::list<EnemyA*> enemyAs;
std::list<EnemyB*> enemyBs;
std::list<EnemyC*> enemyCs;
std::list<FukaBullet*> fukaBullets;
//创建玩家子弹容器
std::list<PlayerProjectileA*> playerProjectileAs;
std::list<PlayerProjectileB*> playerProjectileBs;
//创建敌人子弹容器
std::list<EnemyProjectileA*> enemyProjectileAs;
std::list<EnemyProjectileB*> enemyProjectileBs;
std::list<EnemyProjectileC*> enemyProjectileCs;
//创建物品容器
std::list<ItemA*> itemAs;
std::list<ItemB*> itemBs;
std::list<ItemC*> itemCs;
Player player;
HitBox hitBox;
std::mt19937 gen;//随机数生成器 
std::uniform_real_distribution<float> dis;//随机数分布器
//音效
std::map<std::string,Mix_Chunk*> sounds;
//音乐
Mix_Music* music;
//背景
MoveBackground1 movebackground1;
MoveBackground2 movebackground2;
MoveBackground3 movebackground3;
MoveBackground4 movebackground4;
StillBackground stillbackground;
//Logo淡入淡出
bool isFadingIn = false;
bool isFadingOut = false;
//字体
TTF_Font* font;
private:
std::vector<SpawnEvent> timeline; //时间轴序列
int currentEventIndex = 0;        //执行到第几个事件
int FPS = 120;
int enemyNumber = 0;
int enemyKilledNunber = 0;
TaMaLeft taMaLeft;
TaMaRight taMaRight;
};