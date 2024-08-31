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
    roomPrintX=5,roomPrintY=4,roomX=50,roomY=23,
    cardSelectPrintX=1,cardSelectPrintY=31,cardSelectPrintX2=29,cardSelectPrintY2=39,
    cardPrintX=38,cardPrintY=32,cardPrintX2=51,cardPrintY2=39;
Room room[10];

int main()
{
    initUI();
    printUI();
    Player::addcard(new AttackCard("打击",{"打击"},0,1,1,5,1));
    Player::addcard(new AttackCard("打击",{"打击"},0,1,1,5,1));
    Player::addcard(new AttackCard("打击",{"打击"},0,1,1,5,1));
    Player::addcard(new AttackCard("完美闪击",{"完美闪击"},1,2,3,10,1));
    Player::addcard(new AttackCard("死亡收割",{"死亡收割"},2,3,5,15,1));
    extern vector<Card> have;
    for (int i=0; i<Player::card.size(); i++)
    {
        have.push_back(*Player::card[i]);
    }
    EnemyObject tenemyobject;
    Enemy tenemy;
    tenemyobject.name="????";
    tenemyobject.x=4;
    tenemyobject.y=4;
    tenemyobject.enemy.name="几牢";
    tenemyobject.enemy.HP_Max=10;
    print("按任意键开始战斗",0,0);
    getch();
    while(attack(&tenemy));
    room[0].object.clear();
    room[0].enemyobject.push_back(tenemyobject);
    room[0].RIGHT_ID=1;
    room[0].LEFT_ID=2;
    room[0].UP_ID=3;
    room[0].DOWN_ID=4;
    getch();
    while(playermove());
    return 0;
}