#ifndef RUN_H
#define RUN_H
#include<vector>
#include"enemy.h"
#include"gamemap.h"
void moveme(int deltax,int deltay); 
void printmap();
void printsmallmap();
bool playermove();
void drawcard(int n);
bool fightend();
void printcard();   
bool fight();
bool selectcard();
int getdigits(int number);
void printgoods();
bool shopping();
#endif