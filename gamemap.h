#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <string>
#include <vector>
#include "enemy.h"
#include "UI.h"
class Prop;

/**
 * @brief 坐标结构体
 * 
 */
class __xy
{
public:
    __xy(int x, int y) : x(x), y(y) {}
    int x, y;
    bool operator==(const __xy &other) { return x == other.x && y == other.y; }
};

class ObjectKind
{
public:
    ObjectKind();
    ObjectKind(const ObjectKind &other);
    ObjectKind &operator=(const ObjectKind &other);
    bool isenemy, isstory, isgivecard, isgiveprop, isgiveEXP, isgivemoney, ismove;
    int enemyID, storyID, cardID, propID, EXP, money, moveID, moveX, moveY;
};

class Object
{
public:
    Object();
    Object(std::string name, int x, int y, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    Object(const Object &object);
    
    // void setenemy(int enemyID);
    void setstory(int storyID);
    void setgivecard(int cardID);
    void setgiveprop(int propID);
    void setgiveEXP(int EXP);
    void setgivemoney(int money);
    void setmove(int moveID, int moveX, int moveY);
    virtual void run();
    friend void print(Object *object);
    virtual Object *clone();
    void setxy(int x, int y) { this->x = x; this->y = y; }
    __xy getxy() { return __xy(x, y); }
    std::string getName() { return name; }
    void setTimes(int times) { this->times = times; }
    int getTimes() { return times; }

protected:
    ObjectKind kind;
    std::string name, forecolor, backcolor;
    int x, y;
    int times = -1;
};

std::string whichObject(Object *object);

class Room
{
public:
    std::vector<Object *> object;

    Room();
    Room(std::string name, int ID, int UP_ID, int DOWN_ID, int LEFT_ID, int RIGHT_ID, std::string filePath = "");
    
    void addObject(Object *object);
    void addObject(Object *object, std::vector<__xy> xy);
    Object *getObject(int x, int y);
    friend void print(Room room);
    int getID() { return ID; }
    int getUP_ID() { return UP_ID; }
    int getDOWN_ID() { return DOWN_ID; }
    int getLEFT_ID() { return LEFT_ID; }
    int getRIGHT_ID() { return RIGHT_ID; }
    std::string getName() { return name; }
    std::string getFilePath() { return filePath; }

private:
    int ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID, initX, initY;
    bool isload;
    std::string name;
    std::string filePath;
    
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
    void run() override;
    WallObject *clone() override;

private:
    std::string warning;
};

class EnemyObject : public Object
{
public:
    EnemyObject();
    EnemyObject(std::string name, int x, int y, int enemyID, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    void run() override;

private:
    Enemy enemy;
};

class Goods
{
public:
    Goods();
    virtual void buy();
    int getPrice() { return price; }
    int getNumber() { return number; }
    std::string getColor() { return color; }
    std::string getName() { return name; }
    std::vector<std::string> getDescription() { return description; }

protected:
    int price, number;
    std::string color, name;
    std::vector<std::string> description;
};

class CardGoods : public Goods
{
public:
    CardGoods(int cardID, int price, int number = 1);
    void buy() override;

private:
    Card *card;
};

class PropGoods : public Goods
{
public:
    PropGoods(int propID, int price, int number = 1);
    void buy() override;

private:
    Prop *prop;
};

class StoreObject : public Object
{
public:
    StoreObject();
    StoreObject(std::string name, int x, int y, std::vector<Goods *> goodss, std::string forecolor = "yellow", std::string backcolor = "black");
    void run() override;

private:
    std::vector<Goods *> goodss;
};

class MoveObject : public Object
{
public:
    MoveObject();
    MoveObject(std::string name, int x, int y, int moveID, int moveX, int moveY, std::string forecolor = "white", std::string backcolor = "black");
    MoveObject(const MoveObject &other);
    void run() override;
    MoveObject *clone() override;

private:
    int moveX, moveY, moveID;
};

class NPCObject : public Object
{
public:
    NPCObject();
    NPCObject(std::string name, int x, int y, int storyID, int times = -1, std::string forecolor = "white", std::string backcolor = "black");
    void run() override;

private:
    int storyID;
};

class SleepObject : public Object
{
public:
    SleepObject();
    SleepObject(std::string name, int x, int y, std::string forecolor = "white", std::string backcolor = "black");
    void run() override;
};

#endif
