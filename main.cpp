#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<string>
#include"console.h"
#include"gamemap.h"
#include"run.h"
#include"player.h"
#include"card.h"
#include"enemy.h"
#include"UI.h"
#include"loaddata.h"
#include"save.h"
#include"startscene.h"

int FPS=30,
    playerCurrentX=24,playerCurrentY=20,playerCurrentRoom=14,playerSpeedX=2,playerSpeedY=1,
    roomPrintX=5,roomPrintY=4,roomWidth=50,roomHeight=23,
    cardSelectPrintX=1,cardSelectPrintY=31,cardSelectPrintX2=29,cardSelectPrintY2=39,
    descriptionPrintX=38,descriptionPrintY=32,descriptionPrintX2=51,descriptionPrintY2=39,
    attackPlayerPrintX=15,attackPlayerPrintY=10,attackEnemyPrintX=40,attackEnemyPrintY=10,
    messagePrintX=61,messagePrintY=16,messagePrintX2=99,messagePrintY2=34,messageMax=19,
    storePrintX=5+50/2-2,storePrintY=4,
    goodsPrintX=5,goodsPricePrintX=40,goodsNumberPrintX=48,goodsPrintY=7,
    smallmapX=61,smallmapY=1,smallmapWidth=39,smallmapHeight=14,
    playerStatePrintX=61,playerStatePrintY=36,playerStatePrintX2=99,playerStatePrintY2=40;
std::vector<Room> rooms;
std::vector<Card*> cards(1000);
std::vector<Enemy> enemys(100);
std::vector<Prop*> props(100);
std::vector<EnemyIntention*> enemyintentions(100);
std::vector<Card*> have,hand,used;
std::vector<std::string> story(100);
Enemy *currentenemy=nullptr;
std::vector<Goods*> *currentgoodss=nullptr;
int currentselectcard,currentselectgoods;

extern bool exitGame;

int main()
{
    initUI();
    startSceneMainLoop();
    if(exitGame)
        return 0;
    printUI();
    getCardList();
    getEnemyIntentionList();
    getEnemyList();
    for (int i=1; i<=4; i++) Player::addcard(cards[0]);
    for (int i=1; i<=4; i++) Player::addcard(cards[3]);
    for (int i=1; i<=2; i++) Player::addcard(cards[1]);
    for (int i=1; i<=1; i++) Player::addcard(cards[2]);
    getMapList(); 
    getStoryList();
    getStoreList();
    printMap();
    printSmallMap();
    printPlayerState();
    while(playerMove());
    return 0;
}

