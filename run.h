#ifndef RUN_H
#define RUN_H
#include<vector>
#include"enemy.h"
#include"gamemap.h"
bool playermove();
void drawcard(int n);
bool fightend();
void printcard();   
bool fight(Enemy *enemy);
bool selectcard();
int getdigits(int number);
void printgoods();
bool shopping();
#endif