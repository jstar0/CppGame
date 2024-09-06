#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "loadmap.h"
#include "gamemap.h"
using namespace std;

extern vector<Room> rooms;

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
    while (getline(fin, line))
    {
        line.erase(0, 1); // 去掉开头的$
        Room newRoom;
        string name;
        int ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID;
        string filePath;
        stringstream ss(line);
        getline(ss, name, '$');
        ss >> ID;
        ss.ignore(1);
        ss >> UP_ID;
        ss.ignore(1);
        ss >> DOWN_ID;
        ss.ignore(1);
        ss >> LEFT_ID;
        ss.ignore(1);
        ss >> RIGHT_ID;
        ss.ignore(2);
        getline(ss, filePath, '$');
        newRoom = Room(name, ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID, filePath);
        rooms.push_back(newRoom);
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

    //std::string testPath = "./maps/1/00-KeTing.mapdata";
    //ifstream fin(testPath);
    ifstream fin("./maps" + rooms[mapIndex].filePath);
    if (!fin)
    {
        getchar();
        throw "无法打开地图文件";
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        getline(ss, type, ',');
        if (type == "S")
        {
            string storeName, filePath, forecolor, backcolor;
            int x, y;
            getline(ss, storeName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            getline(ss, filePath, ',');
            ss >> forecolor;
            ss.ignore(1);
            ss >> backcolor;
            // rooms[mapIndex].addobject(new StoreObject(storeName, x, y, filePath, forecolor, backcolor));
        }
        else if (type == "W")
        {
            string wallName, forecolor, backcolor;
            int x, y;
            getline(ss, wallName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            // rooms[mapIndex].addobject(new WallObject(wallName, x, y, forecolor, backcolor));
        }
        else if (type == "L")
        {
            string wallName, forecolor, backcolor;
            int number, x, y;
            vector<xy> xy;
            getline(ss, wallName, ',');
            ss >> number;
            for (int i = 0; i < number; i++)
            {
                ss.ignore(1);
                ss >> x;
                ss.ignore(1);
                ss >> y;
                xy.push_back({x, y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            // rooms[mapIndex].addobject(new WallObject(wallName, xy, forecolor, backcolor));
        }
        else if (type == "E")
        {
            string enemyName, filePath, forecolor, backcolor;
            int x, y;
            getline(ss, enemyName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            getline(ss, filePath, ',');
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            // rooms[mapIndex].addobject(new EnemyObject(enemyName, x, y, filePath, forecolor, backcolor));
        }
        else if (type == "O")
        {
            string objectName, forecolor, backcolor;
            int x, y;
            getline(ss, objectName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);

            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";

            // rooms[mapIndex].addobject(new Object(objectName, x, y, forecolor, backcolor));
        }
    }
    fin.close();
}

// goodss（商品）文件结构示例
// 分为卡牌CardGoods，道具PropGoods两种
// = 卡牌分为攻击卡牌AttackCard，防御卡牌DefendCard，强化卡牌StrengthenCard，摸牌卡牌DrawCard，转换卡牌ChangeHaveCard（添加它本身）
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
        ss >> type;
        if (type == "卡牌")
        {
            string cardName;
            int price, number;
            ss.ignore(1);
            getline(ss, cardName, ',');
            ss >> price;
            ss.ignore(1);
            ss >> number;
            // goodss.push_back(new CardGoods(new Card(cardName), price, number));
        }
        else if (type == "道具")
        {
            string propName;
            int price, number;
            ss.ignore(1);
            getline(ss, propName, ',');
            ss >> price;
            ss.ignore(1);
            ss >> number;
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
        ss >> HP;
        ss.ignore(1);
        ss >> attack;
        ss.ignore(1);
        ss >> defense;
        ss.ignore(1);
        getline(ss, forecolor, ',');
        ss >> backcolor;
        // enemies.push_back(new Enemy(enemyName, HP, attack, defense, forecolor, backcolor));
    }
    fin.close();
}