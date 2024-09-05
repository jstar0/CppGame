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
    // 编码为UTF-8

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
// S,商店,横坐标,纵坐标,goodss文件路径,前景色,背景色
// W,"墙名字",横坐标,纵坐标,前景色,背景色
// WList,"墙名字",数量,横坐标1,纵坐标1,横坐标2,纵坐标2,...,前景色,背景色
// E,"敌人名字",横坐标,纵坐标,enemy文件路径,前景色,背景色
// O,"一般事件名称",横坐标,纵坐标,前景色,背景色

void loadMap(int mapIndex)
{
    
}