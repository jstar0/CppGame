#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<string>
#include"console.h"
#include"gamemap.h"
#include"run.h"
#include"card.h"
#include"enemy.h"
#include"Player.h"
#include"UI.h"

int playerCurrentX=0,playerCurrentY=0,playerCurrentRoom=0,playerSpeedX=2,playerSpeedY=1,
    roomPrintX=5,roomPrintY=4,roomX=47,roomY=22,
    handPrintX=1,handPrintY=31,
    cardPrintX=0,cardPrintY=20;
Room room[10];

int main()
{
    EnemyObject tenemyobject;
    Enemy tenemy;
    tenemyobject.name="????";
    tenemyobject.x=4;
    tenemyobject.y=4;
    tenemyobject.enemy.name="几牢";
    tenemyobject.enemy.HP_Max=10;
    room[0].object.clear();
    room[0].enemyobject.push_back(tenemyobject);
    room[0].RIGHT_ID=1;
    room[0].LEFT_ID=2;
    room[0].UP_ID=3;
    room[0].DOWN_ID=4;
    Card tcard;
    tcard.name="死亡收割";
    tcard.rarity=5;
    tcard.description=
    {
        "死亡收割"
    };
    Player::card.push_back(tcard);
    tcard.name="完美闪击";
    tcard.rarity=3;
    tcard.description=
    {
        "完美闪击"
    };
    Player::card.push_back(tcard);
    Player::card.push_back(tcard);
    tcard.name="打击";
    tcard.rarity=1;
    tcard.description=
    {
        "打击"
    };
    Player::card.push_back(tcard);
    initUI();
    printUI();
    getch();
    while(playermove());
    return 0;
}