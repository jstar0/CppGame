/**
 * @file run.cpp
 * @author 《2024年夏·程序设计基础实践》21组
 * @brief 包含游戏运行相关函数
 * @version 1.0
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include "run.h"
#include "console.h"
#include "gamemap.h"
#include "card.h"
#include "player.h"
#include "UI.h"
#include "loaddata.h"
#include "save.h"
#include "config.h"

/**
 * @brief 封装的获取数字位数函数
 * 
 * @param number 
 * @return int 
 */
int getDigits(int number)
{
    if (number == 0)
        return 1;
    return std::log10(std::abs(number)) + 1;
}

// -------------- 玩家地图相关 --------------

/**
 * @brief 移动玩家
 * 
 * @param deltax 
 * @param deltay 
 */
void movePlayer(int deltax, int deltay)
{
    Object *deltaobject = GameConfig::rooms[PlayerConfig::currentRoom].getObject(PlayerConfig::currentX + deltax, PlayerConfig::currentY + deltay);
    if (deltaobject != nullptr)
    {
        if (whichObject(deltaobject) == "Wall")
        {
            deltaobject->run();
            return;
        }
    }
    clear(RoomConfig::printX + PlayerConfig::currentX, RoomConfig::printY + PlayerConfig::currentY, RoomConfig::printX + PlayerConfig::currentX + 1, RoomConfig::printY + PlayerConfig::currentY);
    for (int i = 0; i < GameConfig::rooms[PlayerConfig::currentRoom].object.size(); i++)
    {
        if (PlayerConfig::currentX >= GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getxy().x && PlayerConfig::currentX <= GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getxy().x + GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getName().size() - 2 && PlayerConfig::currentY == GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getxy().y)
        {
            extern void print(Object * object);
            print(GameConfig::rooms[PlayerConfig::currentRoom].object[i]);
            break;
        }
    }
    PlayerConfig::currentX += deltax;
    PlayerConfig::currentY += deltay;
    setPrintColor("white", "blue");
    print("我", RoomConfig::printX + PlayerConfig::currentX, RoomConfig::printY + PlayerConfig::currentY);
}

/**
 * @brief 打印地图
 * 
 */
bool printMap()
{
    clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
    print(GameConfig::rooms[PlayerConfig::currentRoom]);
    movePlayer(0, 0);
    setPrintColor("white");
    if (GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID() < 0)
        for (int i = 3; i < 55; i++)
            print("墙", i, 3);
    else
        for (int i = 3; i < 55; i++)
            print("空", i, 3);
    if (GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID() < 0)
        for (int i = 3; i <= 55; i++)
            print("墙", i, 27);
    else
        for (int i = 3; i <= 55; i++)
            print("空", i, 27);
    if (GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID() < 0)
        for (int i = 3; i <= 27; i++)
            print("墙", 3, i);
    else
        for (int i = 3; i <= 27; i++)
            print("空", 3, i);
    if (GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID() < 0)
        for (int i = 3; i <= 27; i++)
            print("墙", 55, i);
    else
        for (int i = 3; i <= 27; i++)
            print("空", 55, i);
    
    return true;
}

/**
 * @brief 打印小地图
 * 
 */
bool printSmallMap()
{
    int smallmapCenterX = SmallMapConfig::x + (SmallMapConfig::width - 1) / 2, smallmapCenterY = SmallMapConfig::y + (SmallMapConfig::height - 1) / 2;
    clear(SmallMapConfig::x, SmallMapConfig::y, SmallMapConfig::x + SmallMapConfig::width - 1, SmallMapConfig::y + SmallMapConfig::height - 1);
    setPrintColor("blue", "white");
    print(GameConfig::rooms[PlayerConfig::currentRoom].getName(), smallmapCenterX - GameConfig::rooms[PlayerConfig::currentRoom].getName().size() / 2 + 1, smallmapCenterY);
    setPrintColor("white");
    if (GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID() >= 0)
    {
        print("↑", smallmapCenterX, smallmapCenterY - 1);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID()].getName(), smallmapCenterX - GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID()].getName().size() / 2 + 1, smallmapCenterY - 2);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID() >= 0)
    {
        print("↓", smallmapCenterX, smallmapCenterY + 1);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID()].getName(), smallmapCenterX - GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID()].getName().size() / 2 + 1, smallmapCenterY + 2);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID() >= 0)
    {
        print("←", smallmapCenterX - GameConfig::rooms[PlayerConfig::currentRoom].getName().size() / 2 - 1, smallmapCenterY);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID()].getName(), smallmapCenterX - GameConfig::rooms[PlayerConfig::currentRoom].getName().size() / 2 - 1 - GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID()].getName().size(), smallmapCenterY);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID() >= 0)
    {
        print("→", smallmapCenterX + GameConfig::rooms[PlayerConfig::currentRoom].getName().size() / 2 + 1, smallmapCenterY);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID()].getName(), smallmapCenterX + GameConfig::rooms[PlayerConfig::currentRoom].getName().size() / 2 + 3, smallmapCenterY);
    }
    return true;
}

/**
 * @brief 打印玩家状态
 * 
 */
bool printPlayerState()
{
    clear(PlayerConfig::statePrintX, PlayerConfig::statePrintY, PlayerConfig::statePrintX2, PlayerConfig::statePrintY2);
    setPrintColor("white", "black");
    setPrintColor("lightred");
    print("体力:" + std::to_string(Player::HP) + "/" + std::to_string(Player::HPMax), PlayerConfig::statePrintX, PlayerConfig::statePrintY);
    setPrintColor("lightblue");
    print("灵力上限:" + std::to_string(Player::MPMax), PlayerConfig::statePrintX + 21, PlayerConfig::statePrintY);
    setPrintColor("deepgreen");
    print("等级:" + std::to_string(Player::level) + "(" + std::to_string(Player::EXP) + "/" + std::to_string(Player::calculatelevel(Player::level)) + ")", PlayerConfig::statePrintX, PlayerConfig::statePrintY + 1);
    setPrintColor("yellow");
    print("金币:" + std::to_string(Player::money), PlayerConfig::statePrintX + 21, PlayerConfig::statePrintY + 1);
    setPrintColor("gray");
    print("牌库:" + std::to_string(Player::card.size()) + "张牌", PlayerConfig::statePrintX, PlayerConfig::statePrintY + 2);
    print("手牌上限:" + std::to_string(Player::handMax), PlayerConfig::statePrintX + 21, PlayerConfig::statePrintY + 2);
    setPrintColor("red");
    print("按Q保存游戏", PlayerConfig::statePrintX, PlayerConfig::statePrintY + 3);
    print("按L读取存档", PlayerConfig::statePrintX + 21, PlayerConfig::statePrintY + 3);
    setPrintColor("white");
    print("注:人物和地图存档不互通，可以反复刷级", PlayerConfig::statePrintX, PlayerConfig::statePrintY + 4);
    return true;
}

/**
 * @brief 玩家移动循环
 * 
 * @return true 
 * @return false 
 */
bool playerMoveMainLoop()
{
    // printMap();
    // printSmallMap();
    char r = getch();
    // clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
    if (r == 'Q' || r == 'q')
    {
        save();
    }
    if (r == 'L' || r == 'l')
    {
        load();
    }
    if (r == 'W' || r == 'w')
    {
        if (PlayerConfig::currentY > 0)
            movePlayer(0, -PlayerConfig::speedY);
        else
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID() >= 0)
            {
                message("进入房间" + GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID()].getName(), "red");
                PlayerConfig::currentRoom = GameConfig::rooms[PlayerConfig::currentRoom].getUP_ID();
                PlayerConfig::currentY = RoomConfig::height - 1;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r == 'S' || r == 's')
    {
        if (PlayerConfig::currentY < RoomConfig::height - 1)
            movePlayer(0, PlayerConfig::speedY);
        else
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID() >= 0)
            {
                message("进入房间" + GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID()].getName(), "red");
                PlayerConfig::currentRoom = GameConfig::rooms[PlayerConfig::currentRoom].getDOWN_ID();
                PlayerConfig::currentY = 0;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r == 'A' || r == 'a')
    {
        if (PlayerConfig::currentX > 0)
            movePlayer(-PlayerConfig::speedX, 0);
        else
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID() >= 0)
            {
                message("进入房间" + GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID()].getName(), "red");
                PlayerConfig::currentRoom = GameConfig::rooms[PlayerConfig::currentRoom].getLEFT_ID();
                PlayerConfig::currentX = RoomConfig::width - 2;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r == 'D' || r == 'd')
    {
        if (PlayerConfig::currentX < RoomConfig::width - 2)
            movePlayer(PlayerConfig::speedX, 0);
        else
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID() >= 0)
            {
                message("进入房间" + GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID()].getName(), "red");
                PlayerConfig::currentRoom = GameConfig::rooms[PlayerConfig::currentRoom].getRIGHT_ID();
                PlayerConfig::currentX = 0;
                printMap();
                printSmallMap();
            }
        }
    }
    for (int i = 0; i < GameConfig::rooms[PlayerConfig::currentRoom].object.size(); i++)
    {
        if (__xy(PlayerConfig::currentX, PlayerConfig::currentY) == GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getxy())
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].object[i]->getTimes() != 0)
                GameConfig::rooms[PlayerConfig::currentRoom].object[i]->run();
        }
    }
    Sleep(1000 / GameConfig::FPS);
    return true;
}

// ----------------- 战斗相关 -----------------

/**
 * @brief 抽取卡牌到手牌
 * 
 * @param n 
 */
void drawCard(int n = 1)
{
    if (n > 0)
    {
        int end = n + CardConfig::hand.size() < Player::handMax ? n + CardConfig::hand.size() : Player::handMax;
        while (CardConfig::hand.size() < end)
        {
            if (!CardConfig::have.empty())
            {
                auto dre = std::default_random_engine{static_cast<unsigned>(std::time(nullptr))};
                std::shuffle(CardConfig::have.begin(), CardConfig::have.end(), dre);
                CardConfig::hand.push_back(CardConfig::have.back());
                CardConfig::have.pop_back();
            }
            else
            {
                if (CardConfig::used.size() > 0)
                {
                    CardConfig::have = CardConfig::used;
                    CardConfig::used.clear();
                }
                else
                    break;
            }
        }
    }
    if (n < 0)
    {
        int end = n + CardConfig::hand.size() > 0 ? n + CardConfig::hand.size() : 0;
        while (CardConfig::hand.size() > end)
        {
            CardConfig::used.push_back(CardConfig::hand.back());
            CardConfig::hand.pop_back();
        }
    }
}

/**
 * @brief 战斗结束相关工作
 * 
 * @return true 
 * @return false 
 */
bool endFight()
{
    if (GameConfig::currentEnemy->getHP() == 0 || Player::HP == 0)
    {
        message("按任意键退出战斗", "red");
        getch();
        clear(CardConfig::selectPrintX, CardConfig::selectPrintY, CardConfig::selectPrintX2, CardConfig::selectPrintY2);
        CardConfig::hand.clear();
        CardConfig::have.clear();
        CardConfig::used.clear();
        GameConfig::currentEnemy = nullptr;
        return true;
    }
    return false;
}

/**
 * @brief 打印选择的卡牌
 * 
 */
void printCard()
{
    clear(CardConfig::selectPrintX, CardConfig::selectPrintY, CardConfig::selectPrintX2, CardConfig::selectPrintY2);
    for (int i = 0; i < CardConfig::hand.size(); i++)
    {
        if (CardConfig::currentSelectCard == i)
            setPrintColor(CardConfig::hand[i]->getColor(), "white");
        else
            setPrintColor(CardConfig::hand[i]->getColor(), "black");
        print(std::to_string(CardConfig::hand[i]->getCost()) + "费  " + CardConfig::hand[i]->getName(), CardConfig::selectPrintX, CardConfig::selectPrintY + i);
    }
    clear(DescriptionConfig::printX, DescriptionConfig::printY, DescriptionConfig::printX2, DescriptionConfig::printY2);
    setPrintColor(CardConfig::hand[CardConfig::currentSelectCard]->getColor(), "black");
    print(CardConfig::hand[CardConfig::currentSelectCard]->getDescription(), DescriptionConfig::printX, DescriptionConfig::printY);
}

/**
 * @brief 战斗主循环
 * 
 * @return true 
 * @return false 
 */
bool fightMainLoop()
{
    srand(time(0));
    Player::turnset();
    GameConfig::currentEnemy->turnset();
    GameConfig::currentEnemy->currentintention = *GameConfig::currentEnemy->intention[rand() % GameConfig::currentEnemy->intention.size()];
    clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
    printPlayer();
    print(GameConfig::currentEnemy);
    drawCard(5);
    CardConfig::currentSelectCard = 0;
    printCard();
    while (selectCard())
        ;
    if (endFight())
        return false;
    GameConfig::currentEnemy->currentintention.effect();
    printPlayerState();
    message("回合结束", "lightblue");
    return true;
}

/**
 * @brief 选择卡牌时的判断
 * 
 * @return true 
 * @return false 
 */
bool selectCardEnd()
{
    if (GameConfig::currentEnemy->getHP() == 0)
    {
        message("你打败了" + GameConfig::currentEnemy->getName(), "red");
        if (GameConfig::currentEnemy->getCard() >= 0)
        {
            Player::addcard(CardConfig::cards[GameConfig::currentEnemy->getCard()]);
            message("获得卡牌" + CardConfig::cards[GameConfig::currentEnemy->getCard()]->getName());
        }
        if (GameConfig::currentEnemy->getProp() >= 0)
        {
            Player::addprop(GameConfig::props[GameConfig::currentEnemy->getProp()]);
            message("获得道具" + GameConfig::props[GameConfig::currentEnemy->getProp()]->getName());
        }
        if (GameConfig::currentEnemy->getMoney() > 0)
        {
            Player::money += GameConfig::currentEnemy->getMoney();
            message("获得金币" + std::to_string(GameConfig::currentEnemy->getMoney()), "yellow");
        }
        if (GameConfig::currentEnemy->getEXP() > 0)
        {
            Player::getEXP(GameConfig::currentEnemy->getEXP());
        }
        return true;
    }
    if (Player::HP == 0)
    {
        message("你被" + GameConfig::currentEnemy->getName() + "打败了", "red");
        return true;
    }
    return false;
}

/**
 * @brief 选择卡牌
 * 
 * @return true 
 * @return false 
 */
bool selectCard()
{
    char r = getch();
    if (CardConfig::hand.size() > 0)
    {
        if (r == 'W' || r == 'w')
            CardConfig::currentSelectCard += CardConfig::hand.size() - 1;
        if (r == 'S' || r == 's')
            CardConfig::currentSelectCard += 1;
        CardConfig::currentSelectCard %= CardConfig::hand.size();
        printCard();
        if (r == '\r')
        {
            if (selectCardEnd())
                return false;
            if (Player::MP >= CardConfig::hand[CardConfig::currentSelectCard]->getCost())
            {
                Player::MP -= CardConfig::hand[CardConfig::currentSelectCard]->getCost();
                message("打出卡牌" + CardConfig::hand[CardConfig::currentSelectCard]->getName());
                CardConfig::hand[CardConfig::currentSelectCard]->effect();
                CardConfig::used.push_back(CardConfig::hand[CardConfig::currentSelectCard]);
                CardConfig::hand.erase(CardConfig::hand.begin() + CardConfig::currentSelectCard);
                if (CardConfig::currentSelectCard > CardConfig::hand.size() - 1)
                    CardConfig::currentSelectCard = CardConfig::hand.size() - 1;
                clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
                printPlayer();
                print(GameConfig::currentEnemy);
                if (CardConfig::hand.size() > 0)
                    printCard();
                else
                    clear(CardConfig::selectPrintX, CardConfig::selectPrintY, CardConfig::selectPrintX2, CardConfig::selectPrintY2);
                if (selectCardEnd())
                    return false;
            }
            else
                message("费用不够", "red");
        }
    }
    else
    {
        clear(CardConfig::selectPrintX, CardConfig::selectPrintY, CardConfig::selectPrintX2, CardConfig::selectPrintY2);
        message("没有卡牌", "red");
    }
    if (r == 'E' || r == 'e')
    {
        int n = CardConfig::hand.size();
        for (int i = 0; i < n; i++)
        {
            CardConfig::used.push_back(CardConfig::hand[0]);
            CardConfig::hand.erase(CardConfig::hand.begin());
        }
        CardConfig::hand.resize(0);
        selectCardEnd();
        return false;
    }
    Sleep(1000 / GameConfig::FPS);
    return true;
}

// -------------- 商店相关 --------------

/**
 * @brief 打印商店列表
 * 
 */
void printGoods()
{
    clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
    setPrintColor("white", "black");
    print("商店", StoreConfig::printX, StoreConfig::printY);
    print("   商品", GoodsConfig::printX, GoodsConfig::printY - 1);
    print("价格", GoodsConfig::pricePrintX, GoodsConfig::printY - 1);
    print("数量", GoodsConfig::numberPrintX, GoodsConfig::printY - 1);
    for (int i = 0; i < StoreConfig::currentGoods->size(); i++)
    {
        if (StoreConfig::currentSelectGoods == i)
            setPrintColor((*StoreConfig::currentGoods)[i]->getColor(), "white");
        else
            setPrintColor((*StoreConfig::currentGoods)[i]->getColor(), "black");
        print((*StoreConfig::currentGoods)[i]->getName(), GoodsConfig::printX + getDigits(i) + 2, GoodsConfig::printY + i);
        setPrintColor("white", "black");
        print(std::to_string(i + 1) + ".", GoodsConfig::printX, GoodsConfig::printY + i);
        print(std::to_string((*StoreConfig::currentGoods)[i]->getPrice()), GoodsConfig::pricePrintX, GoodsConfig::printY + i);
        print(std::to_string((*StoreConfig::currentGoods)[i]->getNumber()), GoodsConfig::numberPrintX, GoodsConfig::printY + i);
    }
    clear(DescriptionConfig::printX, DescriptionConfig::printY, DescriptionConfig::printX2, DescriptionConfig::printY2);
    if (StoreConfig::currentSelectGoods != StoreConfig::currentGoods->size())
    {
        setPrintColor((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->getColor(), "black");
        print((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->getDescription(), DescriptionConfig::printX, DescriptionConfig::printY);
        setPrintColor("blue", "black");
    }
    else
        setPrintColor("blue", "white");
    print("退出商店", GoodsConfig::printX, GoodsConfig::printY + (*StoreConfig::currentGoods).size());
}

/**
 * @brief 商店主循环
 * 
 * @return true 
 * @return false 
 */
bool shoppingMainLoop()
{
    char r = getch();
    if (r == 'W' || r == 'w')
        StoreConfig::currentSelectGoods += ((*StoreConfig::currentGoods).size() + 1) - 1;
    if (r == 'S' || r == 's')
        StoreConfig::currentSelectGoods += 1;
    StoreConfig::currentSelectGoods %= (*StoreConfig::currentGoods).size() + 1;
    printGoods();
    if (r == '\r')
    {
        if (StoreConfig::currentSelectGoods < StoreConfig::currentGoods->size())
        {
            if (Player::money >= (*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->getPrice())
            {
                Player::money -= (*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->getPrice();
                (*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->buy();
                if ((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->getNumber() == 0)
                    (*StoreConfig::currentGoods).erase((*StoreConfig::currentGoods).begin() + StoreConfig::currentSelectGoods);
                printGoods();
                printPlayerState();
            }
            else
                message("你的钱不够", "red");
        }
        else
        {
            message("退出商店", "red");
            return false;
        }
    }
    Sleep(1000 / GameConfig::FPS);
    return true;
}

// -------------- 剧情相关 --------------

/**
 * @brief 打印剧情
 * 
 * @param ID 
 */
void printStory(int ID)
{
    int x = RoomConfig::printX, y = RoomConfig::printY;
    std::string forecolor = "white", backcolor = "black";
    clear(x, y, x + RoomConfig::width - 1, y + RoomConfig::height - 1);
    int i = 0;
    while (i < GameConfig::story[ID].size())
    {
        if (GameConfig::story[ID][i] == '&')
        {
            int next = GameConfig::story[ID].find(",", i + 1);
            forecolor = GameConfig::story[ID].substr(i + 1, next - i - 1);
            i = next;
            next = GameConfig::story[ID].find("&", i + 1);
            backcolor = GameConfig::story[ID].substr(i + 1, next - i - 1);
            i = next;
        }
        else if (GameConfig::story[ID][i] == '$')
        {
            x = RoomConfig::printX;
            y++;
            if (y >= RoomConfig::printY + RoomConfig::height)
            {
                y = RoomConfig::printY;
                clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
            }
            setPrintColor("white");
            print("(按任意键继续)", x, y);
            getch();
            clear(x, y, x + 14, y);
        }
        else
        {
            std::string gbk_char = GameConfig::story[ID].substr(i, 2);
            setPrintColor(forecolor, backcolor);
            print(gbk_char, x, y);
            Sleep(10);
            x += 2;
            if (x >= RoomConfig::printX + RoomConfig::width)
            {
                x = RoomConfig::printX;
                y++;
                if (y >= RoomConfig::printY + RoomConfig::height)
                {
                    y = RoomConfig::printY;
                    clear(RoomConfig::printX, RoomConfig::printY, RoomConfig::printX + RoomConfig::width - 1, RoomConfig::printY + RoomConfig::height - 1);
                }
            }
            i += 1;
        }
        i += 1;
    }
}