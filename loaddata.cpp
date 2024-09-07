#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "loaddata.h"
#include "gamemap.h"
#include "card.h"
using namespace std;

extern vector<Room> rooms;
extern vector<Card*> cards;

// mapList文件结构示例
// $客厅(1F)$0,1,2,3,4,$/1/00-KeTing.mapdata$
// $练功房$1,-1,0,-1,-1,$/1/01-LianGongFang.mapdata$
// $书房$2,0,-1,-1,-1,$/2/02-ShuFang.mapdata$
// $厕所$3,-1,-1,-1,0,$/2/03-CeSuo.mapdata$
// $卧室$4,-1,-1,0,-1,$/2/04-WoShi.mapdata$

void getMapList()
{
    // 从文件./maps/MapList.data中读取地图列表
    // 读取成功后将地图列表存入全局变量room中
    // 读取失败则抛出异常
    // 每一行一个房间，格式如上所示
    // 编码为GBK

    ifstream fin("./maps/MapList.data");
    if (!fin)
    {
        throw "无法打开地图列表文件";
    }
    string line;
    while (getline(fin,line))
    {
        Room newRoom;
        string name;
        int ID,UP_ID,DOWN_ID,LEFT_ID,RIGHT_ID;
        string filePath;
        stringstream ss(line);
        getline(ss,name,',');
        ss>>ID;
        ss.ignore(1);
        ss>>UP_ID;
        ss.ignore(1);
        ss>>DOWN_ID;
        ss.ignore(1);
        ss>>LEFT_ID;
        ss.ignore(1);
        ss>>RIGHT_ID;
        ss.ignore(1);
        getline(ss,filePath);
        newRoom=Room(name,ID,UP_ID,DOWN_ID,LEFT_ID,RIGHT_ID,filePath);
        rooms.push_back(newRoom);
    }
    fin.close();
}

void getCardList()
{
    // 从文件./cards/CardList.data中读取卡牌列表
    // 读取成功后将卡牌列表存入全局变量cards中
    // 读取失败则抛出异常
    // 每一行一个卡牌，格式如下
    // 卡牌类型，卡牌名，卡牌描述，卡牌编号，卡牌花费，卡牌稀有度，对应类型参数
    // 编码为GBK
    // 卡牌类型：A-攻击卡牌，D-防御卡牌，S-强化卡牌，R-摸牌卡牌，C-转换卡牌
    ifstream fin("./cards/CardList.data");
    if (!fin)
    {
        throw "无法打开卡牌列表文件";
    }
    string line;
    while (getline(fin,line))
    {
        stringstream ss(line);
        string name,type,s;
        int ID,cost,rarity;
        std::vector<std::string> description;
        //A,攻击,{对敌人造成5点伤害},0,1,1,5,1
        getline(ss,type,',');
        if (type=="add")
        {
            getline(ss,type,',');
            ss>>ID;
            ss.ignore(1);
            if (type=="A")
            {
                int damage,times;
                ss>>damage;
                ss.ignore(1);
                ss>>times;
                cards[ID]->setattack(damage,times);
            }
            else if (type=="D")
            {
                int defense;
                ss>>defense;
                ss.ignore(1);
                cards[ID]->setdefend(defense);
            }
            else if (type=="S")
            {
                int strength;
                ss>>strength;
                ss.ignore(1);
                cards[ID]->setstrengthen(strength);
            }
            else if (type=="R")
            {
                int times;
                ss>>times;
                ss.ignore(1);
                cards[ID]->setdraw(times);
            }
        }
        else
        {
            getline(ss,name,',');
            ss.ignore(1);
            getline(ss,s,'}');
            while(s.find("$")!=std::string::npos)
            {
                description.push_back(s.substr(0,s.find("$")));
                s=s.substr(s.find("$")+1);
            }
            description.push_back(s);
            ss.ignore(1);
            ss>>ID;
            if (ID>cards.size()-1) cards.resize(ID+1);
            ss.ignore(1);
            ss>>cost;
            ss.ignore(1);
            ss>>rarity;
            ss.ignore(1);
            if (type=="A")
            {
                int damage,times;
                ss>>damage;
                ss.ignore(1);
                ss>>times;
                cards[ID]=new AttackCard(name,description,ID,cost,rarity,damage,times);
            }
            else if (type=="D")
            {
                int defense;
                ss>>defense;
                ss.ignore(1);
                cards[ID]=new DefendCard(name,description,ID,cost,rarity,defense);
            }
            else if (type=="S")
            {
                int strength;
                ss>>strength;
                ss.ignore(1);
                cards[ID]=(new StrengthenCard(name,description,ID,cost,rarity,strength));
            }
            else if (type=="R")
            {
                int times;
                ss>>times;
                ss.ignore(1);
                cards[ID]=(new DrawCard(name,description,ID,cost,rarity,times));
            }
        }
    }
    fin.close();
}

// 一行一个Object，格式如下
// S,商店名字,横坐标,纵坐标,goodss文件路径,前景色,背景色
// W,墙名字,横坐标,纵坐标,前景色,背景色
// L,墙名字,数量,横坐标1,纵坐标1,横坐标2,纵坐标2,...,前景色,背景色
// E,敌人名字,横坐标,纵坐标,enemy文件路径,前景色,背景色
// O,一般事件名称,横坐标,纵坐标,前景色,背景色
// 前景色和背景色可以省略，默认为白色和黑色
// ！只要有一个颜色省略，则本行结束必须加逗号！

// ----------------------------WIP----------------------------

void loadMap(int mapIndex)
{
    // 从 rooms[mapIndex].filePath 中读取地图数据

    //std::string testPath="./maps/1/00-KeTing.mapdata";
    //ifstream fin(testPath);
    ifstream fin("./maps"+rooms[mapIndex].filePath);
    if (!fin)
    {
        //getchar();
        message("无法打开地图文件");
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        getline(ss,type,',');
        if (type=="S")
        {
            string storeName, filePath, forecolor, backcolor;
            int x, y;
            getline(ss,storeName,',');
            ss>>x;
            ss.ignore(1);
            ss>>y;
            ss.ignore(1);
            getline(ss,filePath,',');
            ss>>forecolor;
            ss.ignore(1);
            ss>>backcolor;
            // rooms[mapIndex].addobject(new StoreObject(storeName, x, y, filePath, forecolor, backcolor));
        }
        else if (type=="W")
        {
            string wallName,forecolor,backcolor,warning;
            int x, y;
            getline(ss,wallName,',');
            getline(ss,warning,',');
            ss>>x;
            ss.ignore(1);
            ss>>y;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new WallObject(wallName,warning,x,y,forecolor,backcolor));
        }
        else if (type=="WL")
        {
            string wallName,forecolor,backcolor,warning;
            int number,x,y;
            vector<xy>xy;
            getline(ss,wallName,',');
            getline(ss,warning,',');
            ss>>number;
            for (int i=0; i<number; i++)
            {
                ss.ignore(2);
                ss>>x;
                ss.ignore(1);
                ss>>y;
                ss.ignore(1);
                xy.push_back({x,y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss,forecolor,',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new WallObject(wallName,warning,0,0,forecolor,backcolor),xy);
        }
        else if (type=="E")
        {
            string enemyName, filePath, forecolor, backcolor;
            int x, y;
            getline(ss,enemyName,',');
            ss>>x;
            ss.ignore(1);
            ss>>y;
            ss.ignore(1);
            getline(ss,filePath,',');
            // 颜色可缺省
            if (!getline(ss, forecolor,',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            // rooms[mapIndex].addobject(new EnemyObject(enemyName, x, y, filePath, forecolor, backcolor));
        }
        else if (type=="O")
        {
            string objectName,forecolor,backcolor;
            int x, y;
            getline(ss,objectName,',');
            ss>>x;
            ss.ignore(1);
            ss>>y;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss,forecolor,',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new Object(objectName,x,y,forecolor,backcolor));
        }
        else if (type=="OL")
        {
            string objectName,forecolor,backcolor,warning;
            int number,x,y;
            vector<xy> xy;
            getline(ss,objectName,',');
            ss>>number;
            for (int i=0; i<number; i++)
            {
                ss.ignore(2);
                ss>>x;
                ss.ignore(1);
                ss>>y;
                ss.ignore(1);
                xy.push_back({x,y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss,forecolor,',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new Object(objectName,0,0,forecolor,backcolor),xy);
        }
        else if (type=="M")
        {
            string objectName,forecolor,backcolor;
            int x,y,moveID,moveX,moveY;
            getline(ss,objectName,',');
            ss>>x;
            ss.ignore(1);
            ss>>y;
            ss.ignore(1);
            ss>>moveID;
            ss.ignore(1);
            ss>>moveX;
            ss.ignore(1);
            ss>>moveY;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new moveObject(objectName,x,y,moveID,moveX,moveY,forecolor,backcolor));
        }
        else if (type=="ML")
        {   
            string objectName,forecolor,backcolor;
            int x,y,moveID,moveX,moveY,number;
            vector<xy> xy;
            getline(ss,objectName,',');
            ss>>moveID;
            ss.ignore(1);
            ss>>moveX;
            ss.ignore(1);
            ss>>moveY;
            ss.ignore(1);
            ss>>number;
            for (int i=0; i<number; i++)
            {
                ss.ignore(2);
                ss>>x;
                ss.ignore(1);
                ss>>y;
                ss.ignore(1);
                xy.push_back({x,y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ',')) forecolor="white";
            if (!(ss>>backcolor)) backcolor="black";
            rooms[mapIndex].addobject(new moveObject(objectName,0,0,moveID,moveX,moveY,forecolor,backcolor),xy);
        }
    }
    fin.close();
}

// goodss（商品）文件结构示例
// 分为卡牌CardGoods，道具PropGoods两种
//=卡牌分为攻击卡牌AttackCard，防御卡牌DefendCard，强化卡牌StrengthenCard，摸牌卡牌DrawCard，转换卡牌ChangeHaveCard（添加它本身）
// 第一行为售卖的：卡牌数量,道具数量
// 第二行开始，先读取卡牌，再读取道具（每一行是一个卡牌，卡牌结束后是道具，如果卡牌是0，则上来就是道具，反之亦然）
// 对于ChangeHaveCard，特别的根据卡牌名字来读取（写死在程序）

void readGoodss(string filePath)
{
    // 从 filePath 中读取商品数据
    // 读取成功后将商品数据存入全局变量goodss中
    // 读取失败则抛出异常
    // 每一行一个商品，格式如下
    // 卡牌,卡牌名,价格,数量
    // 道具,道具名,价格,数量
    // 编码为GBK

    ifstream fin(filePath);
    if (!fin)
    {
        throw "无法打开商品文件";
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        ss>>type;
        if (type=="卡牌")
        {
            string cardName;
            int price, number;
            ss.ignore(1);
            getline(ss, cardName, ',');
            ss>>price;
            ss.ignore(1);
            ss>>number;
            // goodss.push_back(new CardGoods(new Card(cardName), price, number));
        }
        else if (type=="道具")
        {
            string propName;
            int price, number;
            ss.ignore(1);
            getline(ss, propName, ',');
            ss>>price;
            ss.ignore(1);
            ss>>number;
            // goodss.push_back(new PropGoods(new Prop(propName), price, number));
        }
    }
    fin.close();
}


// enemy文件结构示例
// 敌人名字$敌人介绍$HPMax$力量(tenemy.state.strength)$防御(tenemy.state.defense)
// 敌人意图1(A)$介绍$攻击力$攻击次数
// 敌人意图2(D)$介绍$防御力
// 敌人意图3(S)$介绍$强化力
// 敌人意图4(C)$介绍$给予卡牌总数$卡牌1$卡牌2$卡牌3...
// ...

void readEnemy(string filePath)
{
    // 从 filePath 中读取敌人数据
    // 读取成功后将敌人数据存入全局变量enemies中
    // 读取失败则抛出异常
    // 每一行一个敌人，格式如下
    // 敌人名,HP,攻击力,防御力,前景色,背景色
    // 编码为GBK

    ifstream fin(filePath);
    if (!fin)
    {
        throw "无法打开敌人文件";
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string enemyName;
        int HP, attack, defense;
        string forecolor, backcolor;
        ss.ignore(1);
        getline(ss, enemyName, ',');
        ss>>HP;
        ss.ignore(1);
        ss>>attack;
        ss.ignore(1);
        ss>>defense;
        ss.ignore(1);
        getline(ss, forecolor, ',');
        ss>>backcolor;
        // enemies.push_back(new Enemy(enemyName, HP, attack, defense, forecolor, backcolor));
    }
    fin.close();
}