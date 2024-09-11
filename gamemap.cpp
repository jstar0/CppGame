#include <iostream>
#include <string>
#include <algorithm>
#include "gamemap.h"
#include "console.h"
#include "card.h"
#include "Player.h"
#include "run.h"
#include "UI.h"
#include "save.h"
#include "config.h"

std::string whichObject(Object *object)
{
    if (dynamic_cast<WallObject *>(object))
        return "Wall";
    else if (dynamic_cast<EnemyObject *>(object))
        return "Enemy";
    else if (dynamic_cast<StoreObject *>(object))
        return "Store";
    else
        return "Object";
}

ObjectKind::ObjectKind()
{
    isenemy = false;
    isstory = false;
    isgivecard = false;
    isgiveprop = false;
    isgiveEXP = false;
    isgivemoney = false;
    ismove = false;
    enemyID = 0;
    storyID = 0;
    cardID = 0;
    propID = 0;
    EXP = 0;
    money = 0;
    moveID = 0;
    moveX = 0;
    moveY = 0;
}

ObjectKind::ObjectKind(const ObjectKind &other)
{
    isenemy = other.isenemy;
    isstory = other.isstory;
    isgivecard = other.isgivecard;
    isgiveprop = other.isgiveprop;
    isgiveEXP = other.isgiveEXP;
    isgivemoney = other.isgivemoney;
    ismove = other.ismove;
    enemyID = other.enemyID;
    storyID = other.storyID;
    cardID = other.cardID;
    propID = other.propID;
    EXP = other.EXP;
    money = other.money;
    moveID = other.moveID;
    moveX = other.moveX;
    moveY = other.moveY;
}

ObjectKind &ObjectKind::operator=(const ObjectKind &other)
{
    if (this == &other)
        return *this;
    isenemy = other.isenemy;
    isstory = other.isstory;
    isgivecard = other.isgivecard;
    isgiveprop = other.isgiveprop;
    isgiveEXP = other.isgiveEXP;
    isgivemoney = other.isgivemoney;
    ismove = other.ismove;
    enemyID = other.enemyID;
    storyID = other.storyID;
    cardID = other.cardID;
    propID = other.propID;
    EXP = other.EXP;
    money = other.money;
    moveID = other.moveID;
    moveX = other.moveX;
    moveY = other.moveY;
    return *this;
}

// 一般事件----------------------------------------------------------------------------------------------------------
Object::Object()
{
    name = "未知";
    forecolor = "white";
    backcolor = "black";
    x = 0;
    y = 0;
    times = -1;
    kind = ObjectKind();
}

Object::Object(std::string name, int x, int y, int times /* =-1 */, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->times = times;
    kind = ObjectKind();
}

Object::Object(const Object &object)
{
    name = object.name;
    forecolor = object.forecolor;
    backcolor = object.backcolor;
    x = object.x;
    y = object.y;
    kind = object.kind;
}

void Object::setstory(int storyID)
{
    kind.isstory = true;
    kind.storyID = storyID;
}

void Object::setgivecard(int cardID)
{
    kind.isgivecard = true;
    kind.cardID = cardID;
}

void Object::setgiveprop(int propID)
{
    kind.isgiveprop = true;
    kind.propID = propID;
}

void Object::setgiveEXP(int EXP)
{
    kind.isgiveEXP = true;
    kind.EXP = EXP;
}

void Object::setgivemoney(int money)
{
    kind.isgivemoney = true;
    kind.money = money;
}

void Object::setmove(int moveID, int moveX, int moveY)
{
    kind.ismove = true;
    kind.moveID = moveID;
    kind.moveX = moveX;
    kind.moveY = moveY;
}

void Object::run()
{
    if (times == 0)
        return;
    else if (times != 0)
    {
        times--;
        if (times == 0)
        {
            this->x = -10;
            this->y = -10;
        }
        if (kind.isstory)
        {
            printStory(kind.storyID);
            clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
            printMap();
            printSmallMap();
            printPlayerState();
        }
        if (kind.isgivecard)
        {
            Player::addcard(CardConfig::cards[kind.cardID]);
            message("获得卡牌" + CardConfig::cards[kind.cardID]->name);
            printPlayerState();
        }
        if (kind.isgiveprop)
        {
            Player::addprop(GameConfig::props[kind.propID]);
            message("获得道具" + GameConfig::props[kind.propID]->name);
        }
        if (kind.isgivemoney)
        {
            Player::money += kind.money;
            message("获得金币" + std::to_string(kind.money), "yellow");
            printPlayerState();
        }
        if (kind.isgiveEXP)
        {
            Player::getEXP(kind.EXP);
            printPlayerState();
        }
        if (kind.ismove)
        {
            PlayerConfig::currentRoom = kind.moveID;
            PlayerConfig::currentX = kind.moveX;
            PlayerConfig::currentY = kind.moveY;
            clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
            printMap();
            printSmallMap();
            printPlayerState();
        }
    }
}

void print(Object *object)
{
    setPrintColor(object->forecolor, object->backcolor);
    if (object->times != 0)
        print(object->name, RoomConfig::printX + object->x, RoomConfig::printY + object->y);
}

Object *Object::clone()
{
    return new Object(*this);
}

// 房间----------------------------------------------------------------------------------------------------------
Room::Room()
{
    name = "未知";
    ID = 0;
    UP_ID = -1;
    DOWN_ID = -1;
    LEFT_ID = -1;
    RIGHT_ID = -1;
    filePath = "";
    isload = false;
    object.clear();
}

Room::Room(std::string name, int ID, int UP_ID, int DOWN_ID, int LEFT_ID, int RIGHT_ID, std::string filePath /* ="" */)
{
    this->name = name;
    this->ID = ID;
    this->UP_ID = UP_ID;
    this->DOWN_ID = DOWN_ID;
    this->LEFT_ID = LEFT_ID;
    this->RIGHT_ID = RIGHT_ID;
    this->filePath = filePath;
    isload = false;
    object.clear();
}

void print(Room room)
{
    for (int i = 0; i < room.object.size(); i++)
    {
        print(room.object[i]);
    }
}

void Room::addObject(Object *object)
{
    this->object.push_back(object);
}

void Room::addObject(Object *object, std::vector<__xy> xy)
{
    for (int i = 0; i < xy.size(); i++)
    {
        Object *tobject = object->clone();
        tobject->x = xy[i].x;
        tobject->y = xy[i].y;
        this->object.push_back(tobject);
    }
}

Object *Room::getObject(int x, int y)
{
    for (int i = 0; i < object.size(); i++)
    {
        if (object[i]->x == x && object[i]->y == y)
            return object[i];
    }
    return nullptr;
}

void addroom(Room room)
{
    if (room.ID > GameConfig::rooms.size() - 1)
        GameConfig::rooms.resize(room.ID + 1);
    message("resize");
    GameConfig::rooms[room.ID] = room;
}

// 墙----------------------------------------------------------------------------------------------------------
WallObject::WallObject()
{
    name = "墙";
    x = 0;
    y = 0;
    forecolor = "white";
    backcolor = "black";
    warning = "撞到了墙";
}

WallObject::WallObject(std::string name)
{
    this->name = name;
    x = 0;
    y = 0;
    forecolor = "white";
    backcolor = "black";
    warning = "撞到了" + name;
}

WallObject::WallObject(std::string name, std::string warning)
{
    this->name = name;
    x = 0;
    y = 0;
    forecolor = "white";
    backcolor = "black";
    this->warning = warning;
}

WallObject::WallObject(std::string name, int x, int y, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    warning = "撞到了" + name;
}

WallObject::WallObject(std::string name, std::string warning, int x, int y, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->warning = warning;
}

WallObject::WallObject(const WallObject &other)
{
    name = other.name;
    forecolor = other.forecolor;
    backcolor = other.backcolor;
    x = other.x;
    y = other.y;
    warning = other.warning;
}

void WallObject::run()
{
    message(warning);
}

WallObject *WallObject::clone()
{
    return new WallObject(*this);
}

// 敌人事件----------------------------------------------------------------------------------------------------------
EnemyObject::EnemyObject()
{
    name = "未知";
    forecolor = "white";
    backcolor = "black";
    x = 0;
    y = 0;
    times = -1;
    enemy = Enemy("未知", 0);
    enemy.intention.clear();
}

EnemyObject::EnemyObject(std::string name, int x, int y, int enemyID, int times /* =-1 */, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->times = times;
    this->enemy = GameConfig::enemies[enemyID];
}

void EnemyObject::run()
{
    GameConfig::currentEnemy = &this->enemy;
    CardConfig::have = Player::card;
    GameConfig::currentEnemy->init();
    Player::init();
    message("开始战斗:" + GameConfig::currentEnemy->name);
    while (fightMainLoop())
        ;
    if (Player::HP > 0)
        Object::run();
    clear(DescriptionConfig::printX, DescriptionConfig::printY, DescriptionConfig::printX2, DescriptionConfig::printY2);
    printMap();
    printSmallMap();
    printPlayerState();
}

// 商品----------------------------------------------------------------------------------------------------------
Goods::Goods()
{
    price = 0;
    number = 0;
    color = "white";
    name = "未知???";
    description = {"未知"};
}

void Goods::buy()
{
    message("购买了" + name);
    number--;
}

// 卡牌商品----------------------------------------------------------------------------------------------------------
CardGoods::CardGoods(int cardID, int price, int number /* =1 */)
{
    this->card = CardConfig::cards[cardID];
    this->price = price;
    this->number = number;
    this->color = card->getcolor();
    this->name = "卡牌  " + card->name;
    this->description = card->description;
}

void CardGoods::buy()
{
    Player::addcard(card);
    message("购买了" + name);
    number--;
}

// 道具商品----------------------------------------------------------------------------------------------------------
PropGoods::PropGoods(int propID, int price, int number /* =1 */)
{
    this->prop = GameConfig::props[propID];
    this->price = price;
    this->number = number;
    this->color = prop->forecolor;
    this->name = "道具  " + prop->name;
    this->description = prop->description;
}

void PropGoods::buy()
{
    Player::addprop(prop);
    message("购买了" + name);
    number--;
}

// 商店事件----------------------------------------------------------------------------------------------------------
StoreObject::StoreObject()
{
    name = "商店";
    forecolor = "yellow";
    backcolor = "black";
    x = 0;
    y = 0;
    times = -1;
    goodss.clear();
}

StoreObject::StoreObject(std::string name, int x, int y, std::vector<Goods *> goodss, std::string forecolor /* ="yellow" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    times = -1;
    this->goodss = goodss;
}

void StoreObject::run()
{
    message("进入了" + name);
    StoreConfig::currentSelectGoods = 0;
    StoreConfig::currentGoods = &goodss;
    printGoods();
    while (shoppingMainLoop())
        ;
    message("成功退出商店");
    printMap();
    printSmallMap();
    printPlayerState();
}

// 传送事件----------------------------------------------------------------------------------------------------------
MoveObject::MoveObject()
{
    name = "楼梯";
    x = 0;
    y = 0;
    moveX = 0;
    moveY = 0;
    moveID = 0;
    times = -1;
    forecolor = "white";
    backcolor = "black";
}

MoveObject::MoveObject(std::string name, int x, int y, int moveID, int moveX, int moveY, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->times = -1;
    this->moveID = moveID;
    this->moveX = moveX;
    this->moveY = moveY;
}

MoveObject::MoveObject(const MoveObject &other)
{
    name = other.name;
    forecolor = other.forecolor;
    backcolor = other.backcolor;
    x = other.x;
    y = other.y;
    times = other.times;
    moveID = other.moveID;
    moveX = other.moveX;
    moveY = other.moveY;
}

void MoveObject::run()
{
    message("传送到了" + GameConfig::rooms[moveID].name);
    PlayerConfig::currentX = moveX;
    PlayerConfig::currentY = moveY;
    PlayerConfig::currentRoom = moveID;
    printMap();
    printSmallMap();
}

MoveObject *MoveObject::clone()
{
    return new MoveObject(*this);
}

// NPC事件----------------------------------------------------------------------------------------------------------
NPCObject::NPCObject()
{
    name = "NPC";
    forecolor = "white";
    backcolor = "black";
    x = 0;
    y = 0;
    storyID = 0;
    times = -1;
}

NPCObject::NPCObject(std::string name, int x, int y, int storyID, int times /* =-1 */, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->storyID = storyID;
    this->times = times;
}

void NPCObject::run()
{
    Object::run();
    printStory(storyID);
    clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
    printMap();
    printSmallMap();
    printPlayerState();
}

// 睡觉事件----------------------------------------------------------------------------------------------------------
SleepObject::SleepObject()
{
    name = "床";
    forecolor = "white";
    backcolor = "black";
    x = 0;
    y = 0;
    times = -1;
}

SleepObject::SleepObject(std::string name, int x, int y, std::string forecolor /* ="white" */, std::string backcolor /* ="black" */)
{
    this->name = name;
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    this->x = x;
    this->y = y;
    this->times = -1;
}

void SleepObject::run()
{
    message("在床上睡了一觉", "red");
    Player::HP = Player::HPMax;
    message("体力恢复了!", "red");
    printMap();
    printSmallMap();
    printPlayerState();
}