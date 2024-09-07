#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<string>
#include<vector>
#include"enemy.h"
#include"UI.h"
class Prop;

struct xy{
    int x,y;
    xy(int x,int y):x(x),y(y){}
};

class Object{
public:
    Object();
    Object(std::string name,int x,int y,std::string forecolor="white",std::string backcolor="black");
    Object(const Object &object);
    std::string name,forecolor,backcolor;
    int x,y;
    virtual void run();
    friend void print(Object object);
    virtual ~Object()=default;
    virtual Object* clone();
};

std::string whichObject(Object *object);

class Room{
public:
    Room();
    Room(std::string name,int ID,int UP_ID,int DOWN_ID,int LEFT_ID,int RIGHT_ID,std::string filePath="");  
    //Room(const Room &other);  
    int ID,UP_ID,DOWN_ID,LEFT_ID,RIGHT_ID,initX,initY;
    std::string name;
    std::string filePath;
    std::vector<Object*> object;
    void addobject(Object *object);
    void addobject(Object *object,std::vector<xy> xy);
    Object* getobject(int x,int y);
    friend void print(Room room);
    //Room& operator=(const Room& other);
};

void addroom(Room room);

class WallObject:public Object{ 
public:
    WallObject();
    WallObject(std::string name);
    WallObject(std::string name,std::string warining);
    WallObject(std::string name,int x,int y,std::string forecolor="white",std::string backcolor="black");
    WallObject(std::string name,std::string warning,int x,int y,std::string forecolor="white",std::string backcolor="black");
    WallObject(const WallObject &other);
    std::string warning;
    void run() override;
    WallObject* clone() override;
};

class EnemyObject:public Object{
public:
    EnemyObject();
    EnemyObject(std::string name,int x,int y,Enemy enemy,std::string forecolor="white",std::string backcolor="black");
    Enemy enemy;
    void run() override;
};

class Goods{
public:
    Goods();
    int price,number;
    std::string color,name;
    std::vector<std::string> description;
    virtual void buy();
};

class CardGoods:public Goods{
public:
    CardGoods(int cardID,int price,int number=1);
    Card *card;
    void buy() override;
};

class PropGoods:public Goods{
public:
    PropGoods(int propID,int price,int number=1);
    Prop *prop;
    void buy() override;
};

class StoreObject:public Object{
public:
    StoreObject();
    StoreObject(std::string name,int x,int y,std::vector<Goods*> goodss,std::string forecolor="yellow",std::string backcolor="black");
    std::vector<Goods*> goodss;
    void run() override;
};

class moveObject:public Object{
public:
    moveObject();
    moveObject(std::string name,int x,int y,int moveID,int moveX,int moveY,std::string forecolor="white",std::string backcolor="black");
    moveObject(const moveObject &other);
    int moveX,moveY,moveID;
    void run() override;
    moveObject* clone() override;
};

#endif


/* Room::Room(const Room &room)
{
    message("1copy0");
    name=room.name;
    ID=room.ID;
    UP_ID=room.UP_ID;
    DOWN_ID=room.DOWN_ID;
    LEFT_ID=room.LEFT_ID;
    RIGHT_ID=room.RIGHT_ID;
    message("1copy1");
    object.clear();
    message("1clear");
    if (room.object.size()==0) return;
    message("1not resize");
    for (int i=0; i<room.object.size(); i++)
    {
        object.push_back(room.object[i]->clone());
    }
    message("1copyright");
}

Room& Room::operator=(const Room& other)
{
    message("copy0");
    //this->name=other.name;
    message("namecopy");
    this->ID=other.ID;
    this->UP_ID=other.UP_ID;
    this->DOWN_ID=other.DOWN_ID;
    this->LEFT_ID=other.LEFT_ID;
    this->RIGHT_ID=other.RIGHT_ID; 
    message("copy1");
    if (other.object.empty()) return *this;
    else 
    {
        this->object.clear();
        message("clear");
        for (int i=0; i<other.object.size(); i++)
        {
            this->object.push_back(other.object[i]);
        }
    }
    return *this;
} */