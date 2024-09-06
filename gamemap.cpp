#include<iostream>
#include<string>
#include"gamemap.h"
#include"console.h"
#include"card.h"
#include"Player.h"
#include"run.h"
#include"UI.h"
extern int roomPrintX,roomPrintY;

std::string whichObject(Object *object)
{
    if (dynamic_cast<WallObject*>(object)) return "Wall";
    else if (dynamic_cast<EnemyObject*>(object)) return "Enemy";
    else if (dynamic_cast<StoreObject*>(object)) return "Store";
    else return "Object";
}

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

Object::Object(const Object &object)
{
    name=object.name;
    forecolor=object.forecolor;
    backcolor=object.backcolor;
    x=object.x;
    y=object.y;
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

Object* Object::clone()
{
    return new Object(*this);
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
    filePath="";
    object.clear();
}

Room::Room(std::string name,int ID,int UP_ID,int DOWN_ID,int LEFT_ID,int RIGHT_ID,std::string filePath/* ="" */)
{
    this->name=name;
    this->ID=ID;
    this->UP_ID=UP_ID;
    this->DOWN_ID=DOWN_ID;
    this->LEFT_ID=LEFT_ID;
    this->RIGHT_ID=RIGHT_ID;
    this->filePath=filePath;
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

void Room::addobject(Object *object,std::vector<xy> xy)
{
    for (int i=0; i<xy.size(); i++)
    {
        Object *tobject=object->clone();
        tobject->x=xy[i].x;
        tobject->y=xy[i].y;
        this->object.push_back(tobject);
    }
}

Object* Room::getobject(int x,int y)
{
    for (int i=0; i<object.size(); i++)
    {
        if (object[i]->x==x && object[i]->y==y) return object[i];
    }
    return nullptr;
}

void addroom(Room room)
{
    extern std::vector<Room> rooms;
    if (room.ID>rooms.size()-1) rooms.resize(room.ID+1);
    message("resize");
    rooms[room.ID]=room;
}

//墙----------------------------------------------------------------------------------------------------------
WallObject::WallObject()
{
    name="墙";
    x=0;
    y=0;
    forecolor="white";
    backcolor="black";
    warning="撞到了墙";
}

WallObject::WallObject(std::string name)
{
    this->name=name;
    x=0;
    y=0;
    forecolor="white";
    backcolor="black";
    warning="撞到了"+name;
}

WallObject::WallObject(std::string name,std::string warning)
{
    this->name=name;
    x=0;
    y=0;
    forecolor="white";
    backcolor="black";
    this->warning=warning;
}

WallObject::WallObject(std::string name,int x,int y,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
    warning="撞到了"+name;
}

WallObject::WallObject(std::string name,std::string warning,int x,int y,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
    this->warning=warning;
}

WallObject::WallObject(const WallObject &other)
{
    name=other.name;
    forecolor=other.forecolor;
    backcolor=other.backcolor;
    x=other.x;
    y=other.y;
    warning=other.warning;  
}

void WallObject::run()
{
    message(warning);
}

WallObject* WallObject::clone()
{
    return new WallObject(*this);
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
    extern std::vector<Card*> have,hand,used;
    extern Enemy *currentenemy;
    currentenemy=&this->enemy;
    have=Player::card;
    currentenemy->init();
    Player::init();
    message("开始战斗:"+currentenemy->name);
    while(fight());
    printmap();
    printsmallmap();
}

//商品----------------------------------------------------------------------------------------------------------
Goods::Goods()
{
    price=0;
    number=0;
    color="white";
    name="未知???";
    description={"未知"};
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
    this->description=card->description;
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
    this->description=prop->description;
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
    printmap();
    printsmallmap();
}

//传送事件----------------------------------------------------------------------------------------------------------
moveObject::moveObject()
{
    name="楼梯";
    x=0;
    y=0;
    moveX=0;
    moveY=0;
    moveID=0;
    forecolor="white";
    backcolor="black";
}

moveObject::moveObject(std::string name,int x,int y,int moveID,int moveX,int moveY,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->x=x;
    this->y=y;
    this->moveID=moveID;
    this->moveX=moveX;
    this->moveY=moveY;
}

void moveObject::run()
{
    extern int playerCurrentX,playerCurrentY,playerCurrentRoom;
    extern std::vector<Room> rooms;
    message("传送到了"+rooms[moveID].name);
    playerCurrentX=moveX;
    playerCurrentY=moveY;
    playerCurrentRoom=moveID;
    printmap();
    printsmallmap();
}