/**
 * @file main.cpp
 * @author 《2024年夏·程序设计基础实践》21组
 * @brief 程序入口，包含主函数
 * @version 1.0
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <exception>
#include "console.h"
#include "gamemap.h"
#include "run.h"
#include "player.h"
#include "card.h"
#include "enemy.h"
#include "UI.h"
#include "loaddata.h"
#include "save.h"
#include "startscene.h"
#include "config.h"

int main()
{
    try
    {
        // ---- 开始界面 ----
        if (!initUI())
        {
            message("初始化UI失败。", "red");
            return 1;
        }
        startSceneMainLoop();
        if (exitGame)
            return 0;
        // ---- 开始界面结束 ----

        // ---- 初始化 ----
        if (!printUI())
        {
            message("打印UI失败。", "red");
            return 1;
        }
        if (!getCardList())
        {
            message("获取卡牌列表失败。", "red");
            return 1;
        }
        if (!getEnemyIntentionList())
        {
            message("获取敌人意图列表失败。", "red");
            return 1;
        }
        if (!getEnemyList())
        {
            message("获取敌人列表失败。", "red");
            return 1;
        }
        for (int i = 1; i <= 4; i++)
            Player::addcard(CardConfig::cards[0]);
        for (int i = 1; i <= 4; i++)
            Player::addcard(CardConfig::cards[3]);
        for (int i = 1; i <= 2; i++)
            Player::addcard(CardConfig::cards[1]);
        for (int i = 1; i <= 1; i++)
            Player::addcard(CardConfig::cards[2]);
        if (!getMapList())
        {
            message("获取地图列表失败。", "red");
            return 1;
        }
        if (!getStoryList())
        {
            message("获取故事列表失败。", "red");
            return 1;
        }
        if (!getStoreList())
        {
            message("获取商店列表失败。", "red");
            return 1;
        }
        if (!printMap())
        {
            message("打印地图失败。", "red");
            return 1;
        }
        if (!printSmallMap())
        {
            message("打印小地图失败。", "red");
            return 1;
        }
        if (!printPlayerState())
        {
            message("打印玩家状态失败。", "red");
            return 1;
        }
        // ---- 初始化结束 ----

        // ---- 主循环 ----
        while (playerMoveMainLoop());
        // ---- 主循环结束 ----
    }
    catch (const std::exception &e)
    {
        message(std::string("发生错误: ") + e.what(), "red");
        return 1;
    }
    catch (...)
    {
        message("发生未知错误。", "red");
        return 1;
    }

    return 0;
}