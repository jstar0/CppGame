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
#include"datamap.h"
#include"loadmap.h"

int FPS=30,
    playerCurrentX=0,playerCurrentY=0,playerCurrentRoom=0,playerSpeedX=2,playerSpeedY=1,
    roomPrintX=5,roomPrintY=4,roomWidth=50,roomHeight=23,
    cardSelectPrintX=1,cardSelectPrintY=31,cardSelectPrintX2=29,cardSelectPrintY2=39,
    cardPrintX=38,cardPrintY=32,cardPrintX2=51,cardPrintY2=39,
    attackPlayerPrintX=15,attackPlayerPrintY=10,attackEnemyPrintX=40,attackEnemyPrintY=10,
    messagePrintX=61,messagePrintY=16,messagePrintX2=99,messagePrintY2=34,messageMax=19,
    storePrintX=5+50/2-2,storePrintY=4,
    goodsPrintX=5,goodsPricePrintX=40,goodsNumberPrintX=48,goodsPrintY=7,
    smallmapX=61,smallmapY=1,smallmapWidth=39,smallmapHeight=14;
std::vector<Room> rooms;
std::vector<Card*> have,hand,used;
Enemy *currentenemy=nullptr;
std::vector<Goods*> *currentgoodss=nullptr;
int currentselectcard,currentselectgoods;

int main()
{
    initUI();
    printUI();
    Player::money=1000;
    playerCurrentX=roomWidth/2-1;
    playerCurrentY=roomHeight/2;
    Player::addcard(new AttackCard("杀",{"杀"},0,1,1,5,1));
    Player::addcard(new AttackCard("杀",{"杀"},0,1,1,5,1));
    Player::addcard(new AttackCard("杀",{"杀"},0,1,1,5,1));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Enemy tenemy=Enemy("于景一",{"于景一"},100);
    tenemy.state.defense=100;
    tenemy.addintention(new EnemyIntentionAttack({"攻击20点"},20,1));
    tenemy.addintention(new EnemyIntentionAttack({"攻击10X3点"},10,3));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionDefend({"防御100点"},100));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量30点"},30));
    tenemy.addintention(new EnemyIntentionGiveCard({"施加混乱"},{new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1)}));
    getMapList();
    message("getMapList");
    message(rooms[0].filePath);
    message(rooms[1].filePath);
    //loadMap(0);
    /* rooms[0].addobject(new EnemyObject("人",4,4,tenemy));
    ChangeHaveCard juedou=ChangeHaveCard("决斗",{"决斗","对敌人造成6点","伤害同时将一张","决斗加入你的","摸牌堆"},5,0,4);
    juedou.setattack(6,1);
    juedou.changehavecard.push_back(&juedou);
    std::vector<Goods*> goodss={new CardGoods(&juedou,50,10),new CardGoods(new StrengthenCard("酒",{"酒"},0,1,4,10),100,5),new CardGoods(new DrawCard("无中生有",{"无中生有","摸2张牌"},4,0,4,2),100,5),new PropGoods(new Prop("灵石",{"似乎蕴含着一些神奇的力量"},"red"),100,1)};
    rooms[0].addobject(new StoreObject("黑市",4,0,goodss));
    rooms[0].addobject(new WallObject("墙","撞墙了，好痛"),{{10,0},{10,1},{10,2},{10,3},{10,4},{10,5},{10,6}});  */ 
    rooms[5].addobject(new moveObject("楼梯",0,0,9,0,0));
    rooms[5].addobject(new moveObject("楼梯",0,1,9,0,0));
    rooms[9].addobject(new moveObject("楼梯",0,0,5,0,0));
    rooms[9].addobject(new moveObject("楼梯",0,0,5,0,0));
    playerCurrentRoom=0; 
    printmap();
    printsmallmap();
    while(playermove());
    return 0;
}