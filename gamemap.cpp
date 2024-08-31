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
    extern int have_s,hand_s,used_s;
    extern std::vector<Card> have,hand,used;
    extern Enemy *currentenemy;
    have_s=Player::card.size();
    hand_s=0;
    used_s=0;
    for (int i=0; i<have_s; i++)
    {
        have.push_back(*Player::card[i]);
    }
    currentenemy=&enemy;
    while(attack(&enemy));
}