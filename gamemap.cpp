#include<iostream>
#include"gamemap.h"
#include"console.h"
#include"card.h"
#include"Player.h"
#include"run.h"
extern int roomPrintX,roomPrintY;
void print(Object object)
{
    setcolor(object.forecolor,object.backcolor);
    print(object.name,roomPrintX+object.x,roomPrintY+object.y);
}
void print(Room room)
{
    for (int i=0; i<room.object_s; i++)
    {
        print(room.object[i]);
    }
}
void Object::run()
{
    return ;
}
void EnemyObject::run()
{
    extern std::vector<Card> have,hand,used;
    extern Enemy *currentenemy;
    for (int i=0; i<have.size(); i++)
    {
        have.push_back(*Player::card[i]);
    }
    currentenemy=&enemy;
    while(attack(&enemy));
}