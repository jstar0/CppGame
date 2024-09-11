#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <string>
#include <vector>
#include "enemy.h"
#include "UI.h"
class Prop;

struct xy
{
    int x, y;
    xy(int x, int y) : x(x), y(y) {}
};

class ObjectKind
{
public:
    bool isenemy, isstory, isgivecard, isgiveprop, isgiveEXP, isgivemoney, ismove;
    int enemyID, storyID, cardID, propID, EXP, money, moveID, moveX, moveY;
    ObjectKind();
    ObjectKind(const ObjectKind &other);
    ObjectKind &operator=(const ObjectKind &other);
};

class Object
{
public:
    Object();
    Object(std::string name, int x, int y, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    Object(const Object &object);
    ObjectKind kind;
    std::string name, forecolor, backcolor;
    int x, y;
    int times = -1;
    // void setenemy(int enemyID);
    void setstory(int storyID);
    void setgivecard(int cardID);
    void setgiveprop(int propID);
    void setgiveEXP(int EXP);
    void setgivemoney(int money);
    void setmove(int moveID, int moveX, int moveY);
    virtual void run();
    friend void print(Object object);
    virtual Object *clone();
};

std::string whichObject(Object *object);

class Room
{
public:
    Room();
    Room(std::string name, int ID, int UP_ID, int DOWN_ID, int LEFT_ID, int RIGHT_ID, std::string filePath = "");
    // Room(const Room &other);
    int ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID, initX, initY;
    bool isload;
    std::string name;
    std::string filePath;
    std::vector<Object *> object;
    void addobject(Object *object);
    void addobject(Object *object, std::vector<xy> xy);
    Object *getobject(int x, int y);
    friend void print(Room room);
    // Room& operator=(const Room& other);
};

void addroom(Room room);

class WallObject : public Object
{
public:
    WallObject();
    WallObject(std::string name);
    WallObject(std::string name, std::string warining);
    WallObject(std::string name, int x, int y, std::string forecolor = "white", std::string backcolor = "black");
    WallObject(std::string name, std::string warning, int x, int y, std::string forecolor = "white", std::string backcolor = "black");
    WallObject(const WallObject &other);
    std::string warning;
    void run() override;
    WallObject *clone() override;
};

class EnemyObject : public Object
{
public:
    EnemyObject();
    EnemyObject(std::string name, int x, int y, int enemyID, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    Enemy enemy;
    void run() override;
};

class Goods
{
public:
    Goods();
    int price, number;
    std::string color, name;
    std::vector<std::string> description;
    virtual void buy();
};

class CardGoods : public Goods
{
public:
    CardGoods(int cardID, int price, int number = 1);
    Card *card;
    void buy() override;
};

class PropGoods : public Goods
{
public:
    PropGoods(int propID, int price, int number = 1);
    Prop *prop;
    void buy() override;
};

class StoreObject : public Object
{
public:
    StoreObject();
    StoreObject(std::string name, int x, int y, std::vector<Goods *> goodss, std::string forecolor = "yellow", std::string backcolor = "black");
    std::vector<Goods *> goodss;
    void run() override;
};

class MoveObject : public Object
{
public:
    MoveObject();
    MoveObject(std::string name, int x, int y, int moveID, int moveX, int moveY, std::string forecolor = "white", std::string backcolor = "black");
    MoveObject(const MoveObject &other);
    int moveX, moveY, moveID;
    void run() override;
    MoveObject *clone() override;
};

class NPCObject : public Object
{
public:
    NPCObject();
    NPCObject(std::string name, int x, int y, int storyID, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    int storyID;
    void run() override;
};

class SleepObject : public Object
{
public:
    SleepObject();
    SleepObject(std::string name, int x, int y, std::string forecolor = "white", std::string backcolor = "black");
    void run() override;
};

#endif
