#include<iostream>
#include"gamemap.h"
#include"console.h"
#include"card.h"
#include"Player.h"
#include"run.h"
#include"UI.h"
extern int roomPrintX,roomPrintY;

Object::Object()
{
    name="未知";
    forecolor="white";
    backcolor="black";
    x=0;
    y=0;
}

Object::Object(std::string name,int x,int y,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
}

EnemyObject::EnemyObject()
{
    name="未知";
    forecolor="white";
    backcolor="black";
    x=0;
    y=0;
    enemy=Enemy("未知",{"未知"},0);
    enemy.intention.clear();
}

EnemyObject::EnemyObject(std::string name,int x,int y,Enemy enemy,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
    this->enemy=enemy;
}

Room::Room()
{
    name="未知";
    ID=0;
    UP_ID=-1;
    DOWN_ID=-1;
    LEFT_ID=-1;
    RIGHT_ID=-1;
    object.clear();
}

Room::Room(std::string name,int ID,int UP_ID,int DOWN_ID,int LEFT_ID,int RIGHT_ID)
{
    this->name=name;
    this->ID=ID;
    this->UP_ID=UP_ID;
    this->DOWN_ID=DOWN_ID;
    this->LEFT_ID=LEFT_ID;
    this->RIGHT_ID=RIGHT_ID;
    object.clear();
}

void print(Object *object)
{
    setcolor(object->forecolor,object->backcolor);
    print(object->name,roomPrintX+object->x,roomPrintY+object->y);
}
void print(Room room)
{
    for (int i=0; i<room.object.size(); i++)
    {
        print(room.object[i]);
    }
}

void Room::addobject(Object *object)
{
    this->object.push_back(object);
}

void Object::run()
{
    message("碰到了"+name);
}

void EnemyObject::run()
{
    extern std::vector<Card> have,hand,used;
    extern Enemy *currentenemy;
    currentenemy=&this->enemy;
    for (int i=0; i<Player::card.size(); i++)
    {
        have.push_back(*Player::card[i]);
    }
    message("开始战斗:"+currentenemy->name);
    while(fight(currentenemy));
}