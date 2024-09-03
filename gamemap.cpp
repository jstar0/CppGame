#include<iostream>
#include"gamemap.h"
#include"console.h"
#include"card.h"
#include"Player.h"
#include"run.h"
#include"UI.h"
extern int roomPrintX,roomPrintY;

//一般事件----------------------------------------------------------------------------------------------------------
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

void Object::run()
{
    message("碰到了"+name);
}

void print(Object *object)
{
    setcolor(object->forecolor,object->backcolor);
    print(object->name,roomPrintX+object->x,roomPrintY+object->y);
}

//房间----------------------------------------------------------------------------------------------------------
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

//敌人事件----------------------------------------------------------------------------------------------------------
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

void EnemyObject::run()
{
    extern std::vector<Card> have,hand,used;
    extern Enemy *currentenemy;
    currentenemy=&this->enemy;
    for (int i=0; i<Player::card.size(); i++)
    {
        have.push_back(*Player::card[i]);
    }
    currentenemy->init();
    Player::init();
    message("开始战斗:"+currentenemy->name);
    while(fight(currentenemy));
}

//商品----------------------------------------------------------------------------------------------------------
Goods::Goods()
{
    price=0;
    number=0;
    color="white";
    name="未知???";
}

void Goods::buy()
{
    message("购买了"+name);
    number--;
}

//卡牌商品----------------------------------------------------------------------------------------------------------
CardGoods::CardGoods(Card *card,int price,int number/* =1 */)
{
    this->card=card;
    this->price=price;
    this->number=number;
    this->color=card->getcolor();
    this->name="卡牌  "+card->name;
}

void CardGoods::buy()
{
    Player::addcard(card);
    message("购买了"+name);
    number--;
}

//道具商品----------------------------------------------------------------------------------------------------------
PropGoods::PropGoods(Prop *prop,int price,int number/* =1 */)
{
    this->prop=prop;
    this->price=price;
    this->number=number;
    this->color=prop->forecolor;
    this->name="道具  "+prop->name;
}

void PropGoods::buy()
{
    Player::addprop(prop);
    message("购买了"+name);
    number--;
}

//商店事件----------------------------------------------------------------------------------------------------------
StoreObject::StoreObject()
{
    name="商店";
    forecolor="yellow";
    backcolor="black";
    x=0;
    y=0;
    goodss.clear();
}

StoreObject::StoreObject(std::string name,int x,int y,std::vector<Goods*> goodss,std::string forecolor/* ="yellow" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
    this->goodss=goodss;
}

void StoreObject::run()
{
    message("进入了"+name);
    extern int currentselectgoods;
    extern std::vector<Goods*> *currentgoodss;
    currentselectgoods=0;
    currentgoodss=&goodss;
    printgoods();
    while(shopping());
    message("成功退出商店");
}