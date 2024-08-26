#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<string>
#include<vector>
#include"enemy.h"
class Object{
public:
    std::string name="",forecolor="white",backcolor="black";
    int x,y;
    void run();
    friend void print(Object object);
};
class EnemyObject:public Object{
public:
    void run();
    Enemy enemy;
};
class Room{
public:
    int ID,UP_ID,DOWN_ID,RIGHT_ID,LEFT_ID,object_s;
    bool store,enemy;
    std::string name="";
    std::vector<Object> object;
    std::vector<EnemyObject> enemyobject;
    friend void print(Room room);
};
#endif
