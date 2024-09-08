#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<string>
#include"console.h"
#include"gamemap.h"
#include"startscene.h"
#include"run.h"
#include"player.h"
#include"card.h"
#include"enemy.h"
#include"UI.h"
#include"loaddata.h"
#include"save.h"

int FPS=30,
    playerCurrentX=24,playerCurrentY=7,playerCurrentRoom=14,playerSpeedX=2,playerSpeedY=1,
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
std::vector<Enemy*> enemys(100);
std::vector<Prop*> props(100);
std::vector<Card*> have,hand,used;
std::vector<std::string> story(10);
Enemy *currentenemy=nullptr;
std::vector<Goods*> *currentgoodss=nullptr;
int currentselectcard,currentselectgoods;

int main()
{
    initUI();
    startSceneMainLoop();

    printUI();
    Player::money=1000;
    getCardList();
    for (int i=0; i<=29; i++) 
    {
        Player::addcard(cards[i]);
    }
    Enemy tenemy=Enemy("汪希",{"汪希"},100);
    tenemy.state.defense=100;
    tenemy.addintention(new EnemyIntentionAttack({"攻击20点"},20,1));
    tenemy.addintention(new EnemyIntentionAttack({"攻击10X3点"},10,3));
    tenemy.addintention(new EnemyIntentionAttack({"攻击10X3点"},10,3));
    tenemy.addintention(new EnemyIntentionAttack({"攻击10X3点"},10,3));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionDefend({"防御100点"},100));
    tenemy.addintention(new EnemyIntentionDefend({"防御100点"},100));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量30点"},30));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量30点"},30));
    tenemy.addintention(new EnemyIntentionGiveCard({"施加混乱"},{new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1)}));
    tenemy.addintention(new EnemyIntentionGiveCard({"施加混乱"},{new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1)}));
    getMapList();
    tenemy.giveEXP=100;
    tenemy.giveMoney=100;
    rooms[0].addobject(new StoreObject("黑市",4,0,{new CardGoods(66,50,10)}));  
    getStoryList();
    printmap();
    printsmallmap();
    printPlayerState();
    while(playermove());
    return 0;
}

