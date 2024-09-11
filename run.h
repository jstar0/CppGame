#ifndef RUN_H
#define RUN_H
#include "enemy.h"
#include "gamemap.h"

int getDigits(int number);
void movePlayer(int deltax, int deltay);
void printMap();
void printSmallMap();
void printPlayerState();
bool playerMoveMainLoop();
void drawCard(int n);
bool endFight();
void printCard();
bool fightMainLoop();
bool selectCard();
void printGoods();
bool shoppingMainLoop();
void printStory(int ID);

#endif