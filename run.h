#ifndef RUN_H
#define RUN_H
#include<vector>
#include"enemy.h"
#include"gamemap.h"
void moveme(int deltax,int deltay); 
void printMap();
void printSmallMap();
void printPlayerState();
bool playerMove();
void drawcard(int n);
bool fightend();
void printcard();   
bool fight();
bool selectcard();
int getdigits(int number);
void printgoods();
bool shopping();
void printStory(int ID);
#endif