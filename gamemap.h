#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<string>
#include<vector>
#include"enemy.h"
#include"UI.h"
class Object{
public:
    Object();
    Object(std::string name,int x,int y,std::string forecolor="white",std::string backcolor="black");
    std::string name,forecolor,backcolor;
    int x,y;
    virtual void run();
    friend void print(Object object);
};

class EnemyObject:public Object{
public:
    EnemyObject();
    EnemyObject(std::string name,int x,int y,Enemy enemy,std::string forecolor="white",std::string backcolor="black");
    Enemy enemy;
    void run() override;
};

class Room{
public:
    Room();
    Room(std::string name,int ID,int UP_ID,int DOWN_ID,int LEFT_ID,int RIGHT_ID);
    int ID,UP_ID,DOWN_ID,LEFT_ID,RIGHT_ID;
    std::string name;
    std::vector<Object*> object;
    void addobject(Object *object);
    friend void print(Room room);
};
#endif
