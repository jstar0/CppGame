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

int playerCurrentX=0,playerCurrentY=0,playerCurrentRoom=0,playerSpeedX=2,playerSpeedY=1,
    roomPrintX=5,roomPrintY=4,roomWidth=50,roomHeight=23,
    cardSelectPrintX=1,cardSelectPrintY=31,cardSelectPrintX2=29,cardSelectPrintY2=39,
    cardPrintX=38,cardPrintY=32,cardPrintX2=51,cardPrintY2=39,
    attackPlayerPrintX=15,attackPlayerPrintY=10,attackEnemyPrintX=40,attackEnemyPrintY=10,
    messagePrintX=61,messagePrintY=16,messagePrintX2=99,messagePrintY2=34,messageMax=19,
    storePrintX=5+50/2-2,storePrintY=4,
    goodsPrintX=5,goodsPricePrintX=40,goodsNumberPrintX=48,goodsPrintY=7;
std::vector<Room> room;
std::vector<Card> have,hand,used;
Enemy *currentenemy=nullptr;
std::vector<Goods*> *currentgoodss=nullptr;
int currentselectcard,currentselectgoods;

int main()
{
    initUI();
    printUI();
    Player::money=1000;
    Player::addcard(new AttackCard("决斗",{"决斗"},0,0,1,5,1));
    Player::addcard(new AttackCard("雷杀",{"雷杀"},0,1,1,5,1));
    Player::addcard(new AttackCard("火杀",{"火杀"},0,1,1,5,1));
    Player::addcard(new StrengthenCard("酒",{"酒"},0,1,4,10));
    Player::addcard(new AttackCard("杀",{"杀"},0,1,1,5,1));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new DefendCard("闪",{"闪"},3,1,1,5));
    Player::addcard(new AttackCard("闪电",{"闪电","造成6X2点伤害"},1,2,3,6,2));
    Player::addcard(new AttackCard("南蛮入侵",{"南蛮入侵","造成5X3点伤害"},2,3,4,5,3));
    for (int i=0; i<Player::card.size(); i++)
    {
        have.push_back(*Player::card[i]);
    }
    EnemyObject tenemyobject;
    Enemy tenemy=Enemy("于景一",{"于景一"},100);
    tenemy.state.defense=100;
    tenemy.addintention(new EnemyIntentionAttack({"攻击20点"},20,1));
    tenemy.addintention(new EnemyIntentionAttack({"攻击6X3点"},6,3));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionAttack({"攻击8X2点"},8,2));
    tenemy.addintention(new EnemyIntentionDefend({"防御20点"},20));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量10点"},10));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量10点"},10));
    tenemy.addintention(new EnemyIntentionStrengthen({"力量10点"},10));
    tenemy.addintention(new EnemyIntentionGiveCard({"施加混乱"},{new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1),new Card("混乱",{"混乱"},0,99,1)}));
    room.push_back(Room("起始房间",0,-1,-1,-1,-1));
    room[0].addobject(new EnemyObject("人",4,4,tenemy));
    std::vector<Goods*> goodss={new CardGoods(new DrawCard("无中生有",{"无中生有","摸2张牌"},4,0,4,2),200,3),new PropGoods(new Prop("灵石",{"似乎蕴含着一些神奇的力量"},"red"),100,1)};
    room[0].addobject(new StoreObject("黑市",20,10,goodss));
    while(playermove());
    return 0;
}