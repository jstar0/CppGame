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
    initUI();
    startSceneMainLoop();
    if (exitGame)
        return 0;
    printUI();
    getCardList();
    getEnemyIntentionList();
    getEnemyList();
    for (int i = 1; i <= 4; i++)
        Player::addcard(CardConfig::cards[0]);
    for (int i = 1; i <= 4; i++)
        Player::addcard(CardConfig::cards[3]);
    for (int i = 1; i <= 2; i++)
        Player::addcard(CardConfig::cards[1]);
    for (int i = 1; i <= 1; i++)
        Player::addcard(CardConfig::cards[2]);
    getMapList();
    getStoryList();
    getStoreList();
    printMap();
    printSmallMap();
    printPlayerState();
    while (playerMoveMainLoop());
    return 0;
}
