#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "loaddata.h"
#include "gamemap.h"
#include "card.h"
#include "console.h"
#include "config.h"
using namespace std;

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
        Room newRoom;
        string name;
        int ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID;
        string filePath;
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> ID;
        ss.ignore(1);
        ss >> UP_ID;
        ss.ignore(1);
        ss >> DOWN_ID;
        ss.ignore(1);
        ss >> LEFT_ID;
        ss.ignore(1);
        ss >> RIGHT_ID;
        ss.ignore(1);
        getline(ss, filePath);
        newRoom = Room(name, ID, UP_ID, DOWN_ID, LEFT_ID, RIGHT_ID, filePath);
        GameConfig::rooms.push_back(newRoom);
        loadMap(ID);
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
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string name, type, s;
        int ID, cost, rarity;
        std::vector<std::string> description;
        // A,攻击,{对敌人造成5点伤害},0,1,1,5,1
        getline(ss, type, ',');
        if (type == "add")
        {
            getline(ss, type, ',');
            ss >> ID;
            ss.ignore(1);
            if (type == "A")
            {
                int damage, times;
                ss >> damage;
                ss.ignore(1);
                ss >> times;
                CardConfig::cards[ID]->setattack(damage, times);
            }
            else if (type == "D")
            {
                int defense;
                ss >> defense;
                ss.ignore(1);
                CardConfig::cards[ID]->setdefend(defense);
            }
            else if (type == "S")
            {
                int strength;
                ss >> strength;
                ss.ignore(1);
                CardConfig::cards[ID]->setstrengthen(strength);
            }
            else if (type == "R")
            {
                int times;
                ss >> times;
                ss.ignore(1);
                CardConfig::cards[ID]->setdraw(times);
            }
        }
        else
        {
            getline(ss, name, ',');
            ss.ignore(1);
            getline(ss, s, '}');
            while (s.find("$") != std::string::npos)
            {
                description.push_back(s.substr(0, s.find("$")));
                s = s.substr(s.find("$") + 1);
            }
            description.push_back(s);
            ss.ignore(1);
            ss >> ID;
            if (ID > CardConfig::cards.size() - 1)
                CardConfig::cards.resize(ID + 1);
            ss.ignore(1);
            ss >> cost;
            ss.ignore(1);
            ss >> rarity;
            ss.ignore(1);
            if (type == "A")
            {
                int damage, times;
                ss >> damage;
                ss.ignore(1);
                ss >> times;
                CardConfig::cards[ID] = new AttackCard(name, description, ID, cost, rarity, damage, times);
            }
            else if (type == "D")
            {
                int defense;
                ss >> defense;
                ss.ignore(1);
                CardConfig::cards[ID] = new DefendCard(name, description, ID, cost, rarity, defense);
            }
            else if (type == "S")
            {
                int strength;
                ss >> strength;
                ss.ignore(1);
                CardConfig::cards[ID] = (new StrengthenCard(name, description, ID, cost, rarity, strength));
            }
            else if (type == "R")
            {
                int times;
                ss >> times;
                ss.ignore(1);
                CardConfig::cards[ID] = (new DrawCard(name, description, ID, cost, rarity, times));
            }
        }
    }
    fin.close();
}

void getEnemyIntentionList()
{
    ifstream fin("./enemys/EnemyIntentionList.data");
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        int ID;
        getline(ss, type, ',');
        if (type == "add")
        {
            getline(ss, type, ',');
            if (type == "A")
            {
                int damage, times;
                ss >> ID;
                ss.ignore(1);
                ss >> damage;
                ss.ignore(1);
                ss >> times;
                GameConfig::enemyIntentions[ID]->setattack(damage, times);
            }
            if (type == "D")
            {
                int defense;
                ss >> ID;
                ss.ignore(1);
                ss >> defense;
                GameConfig::enemyIntentions[ID]->setdefend(defense);
            }
            if (type == "S")
            {
                int strength;
                ss >> ID;
                ss.ignore(1);
                ss >> strength;
                GameConfig::enemyIntentions[ID]->setstrengthen(strength);
            }
            if (type == "G")
            {
                vector<Card *> givecard;
                // G,0,1,2,3,4,5,6,7,8,9读入左边形式
                string cardID;
                ss >> ID;
                ss.ignore(1);
                while (getline(ss, cardID, ','))
                    givecard.push_back(CardConfig::cards[stoi(cardID)]);
                GameConfig::enemyIntentions[ID]->setgivecard(givecard);
            }
        }
        else
        {
            string description, cardID;
            getline(ss, description, ',');
            if (type == "A")
            {
                int damage, times;
                ss >> ID;
                ss.ignore(1);
                ss >> damage;
                ss.ignore(1);
                ss >> times;
                GameConfig::enemyIntentions[ID] = new EnemyIntentionAttack(description, damage, times);
            }
            if (type == "D")
            {
                int defense;
                ss >> ID;
                ss.ignore(1);
                ss >> defense;
                GameConfig::enemyIntentions[ID] = new EnemyIntentionDefend(description, defense);
            }
            if (type == "S")
            {
                int strength;
                ss >> ID;
                ss.ignore(1);
                ss >> strength;
                GameConfig::enemyIntentions[ID] = new EnemyIntentionStrengthen(description, strength);
            }
            if (type == "G")
            {
                vector<Card *> givecard;
                ss >> ID;
                ss.ignore(1);
                while (getline(ss, cardID, ','))
                    givecard.push_back(CardConfig::cards[stoi(cardID)]);
                GameConfig::enemyIntentions[ID] = new EnemyIntentionGiveCard(description, givecard);
            }
        }
    }
    fin.close();
}

void getEnemyList()
{
    ifstream fin("./enemys/EnemyList.data");
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        getline(ss, type, ',');
        if (type == "new")
        {
            string name;
            int HP, ID;
            getline(ss, name, ',');
            ss >> ID;
            ss.ignore(1);
            ss >> HP;
            GameConfig::enemies[ID] = Enemy(name, HP);
        }
        if (type == "add")
        {
            int intentionID, ID;
            ss >> ID;
            ss.ignore(1);
            ss >> intentionID;
            GameConfig::enemies[ID].addintention(GameConfig::enemyIntentions[intentionID]);
        }
        if (type == "EXP")
        {
            int EXP, ID;
            ss >> ID;
            ss.ignore(1);
            ss >> EXP;
            GameConfig::enemies[ID].giveEXP = EXP;
        }
        if (type == "money")
        {
            int money, ID;
            ss >> ID;
            ss.ignore(1);
            ss >> money;
            GameConfig::enemies[ID].giveMoney = money;
        }
        if (type == "card")
        {
            int cardID, ID;
            ss >> ID;
            ss.ignore(1);
            ss >> cardID;
            GameConfig::enemies[ID].giveCard = cardID;
        }
        if (type == "prop")
        {
            int propID, ID;
            ss >> ID;
            ss.ignore(1);
            ss >> propID;
            GameConfig::enemies[ID].giveProp = propID;
        }
    }
    fin.close();
}

void getStoreList()
{
    GameConfig::rooms[3].addobject(new StoreObject("商店", 4, 4, {new CardGoods(26, 300, 4), new CardGoods(27, 375, 4), new CardGoods(18, 400, 3), new CardGoods(24, 350, 2), new CardGoods(23, 400, 3)}, "yellow", "black"));
    GameConfig::rooms[3].addobject(new SleepObject("旅店", 4, 6));
}

void getStoryList()
{
    // 从文件./story/StoryList.data中读取剧情列表
    // 读取成功后将剧情列表存入全局变量story中
    // 读取失败则抛出异常
    // 每一行一个剧情，格式如下
    // 剧情内容
    // 编码为GBK
    int i = 0;
    ifstream fin("./story/StoryList.data");
    if (!fin)
    {
        throw "无法打开剧情列表文件";
    }
    string line;
    while (getline(fin, line))
    {
        GameConfig::story[i] = line;
        i++;
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

    // std::string testPath="./maps/1/00-KeTing.mapdata";
    // ifstream fin(testPath);
    ifstream fin("./maps" + GameConfig::rooms[mapIndex].filePath);
    if (!fin)
    {
        message("无法打开地图文件");
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string type;
        getline(ss, type, ',');
        if (type == "add")
        {
            Object *object = GameConfig::rooms[mapIndex].object[GameConfig::rooms[mapIndex].object.size() - 1];
            getline(ss, type, ',');
            if (type == "story")
            {
                int storyID;
                ss >> storyID;
                object->setstory(storyID);
            }
            if (type == "card")
            {
                int cardID;
                ss >> cardID;
                object->setgivecard(cardID);
            }
            if (type == "prop")
            {
                int propID;
                ss >> propID;
                object->setgiveprop(propID);
            }
            if (type == "money")
            {
                int money;
                ss >> money;
                object->setgivemoney(money);
            }
            if (type == "EXP")
            {
                int EXP;
                ss >> EXP;
                object->setgiveEXP(EXP);
            }
            if (type == "move")
            {
                int moveID, moveX, moveY;
                ss >> moveID;
                ss.ignore(1);
                ss >> moveX;
                ss.ignore(1);
                ss >> moveY;
                object->setmove(moveID, moveX, moveY);
            }
        }
        else if (type == "S")
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
            string wallName, forecolor, backcolor, warning;
            int x, y;
            getline(ss, wallName, ',');
            getline(ss, warning, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new WallObject(wallName, warning, x, y, forecolor, backcolor));
        }
        else if (type == "WL")
        {
            string wallName, forecolor, backcolor, warning;
            int number, x, y;
            vector<xy> xy;
            getline(ss, wallName, ',');
            getline(ss, warning, ',');
            ss >> number;
            for (int i = 0; i < number; i++)
            {
                ss.ignore(2);
                ss >> x;
                ss.ignore(1);
                ss >> y;
                ss.ignore(1);
                xy.push_back({x, y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new WallObject(wallName, warning, 0, 0, forecolor, backcolor), xy);
        }
        else if (type == "E")
        {
            string enemyName, forecolor, backcolor;
            int x, y, times, enemyID;
            getline(ss, enemyName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            ss >> enemyID;
            ss.ignore(1);
            ss >> times;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new EnemyObject(enemyName, x, y, enemyID, times, forecolor, backcolor));
        }
        else if (type == "O")
        {
            string objectName, forecolor, backcolor;
            int x, y, times;
            getline(ss, objectName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            ss >> times;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new Object(objectName, x, y, times, forecolor, backcolor));
        }
        else if (type == "N")
        {
            string NPCName, forecolor, backcolor;
            int x, y, times, storyID;
            getline(ss, NPCName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            ss >> storyID;
            ss.ignore(1);
            ss >> times;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new NPCObject(NPCName, x, y, storyID, times, forecolor, backcolor));
        }
        else if (type == "OL")
        {
            string objectName, forecolor, backcolor, warning;
            int number, x, y;
            vector<xy> xy;
            getline(ss, objectName, ',');
            ss >> number;
            for (int i = 0; i < number; i++)
            {
                ss.ignore(2);
                ss >> x;
                ss.ignore(1);
                ss >> y;
                ss.ignore(1);
                xy.push_back({x, y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new Object(objectName, 0, 0, -1, forecolor, backcolor), xy);
        }
        else if (type == "M")
        {
            string objectName, forecolor, backcolor;
            int x, y, moveID, moveX, moveY;
            getline(ss, objectName, ',');
            ss >> x;
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            ss >> moveID;
            ss.ignore(1);
            ss >> moveX;
            ss.ignore(1);
            ss >> moveY;
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new MoveObject(objectName, x, y, moveID, moveX, moveY, forecolor, backcolor));
        }
        else if (type == "ML")
        {
            string objectName, forecolor, backcolor;
            int x, y, moveID, moveX, moveY, number;
            vector<xy> xy;
            getline(ss, objectName, ',');
            ss >> moveID;
            ss.ignore(1);
            ss >> moveX;
            ss.ignore(1);
            ss >> moveY;
            ss.ignore(1);
            ss >> number;
            for (int i = 0; i < number; i++)
            {
                ss.ignore(2);
                ss >> x;
                ss.ignore(1);
                ss >> y;
                ss.ignore(1);
                xy.push_back({x, y});
            }
            ss.ignore(1);
            // 颜色可缺省
            if (!getline(ss, forecolor, ','))
                forecolor = "white";
            if (!(ss >> backcolor))
                backcolor = "black";
            GameConfig::rooms[mapIndex].addobject(new MoveObject(objectName, 0, 0, moveID, moveX, moveY, forecolor, backcolor), xy);
        }
    }
    fin.close();
}
