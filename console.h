#ifndef CONSOLE_H
#define CONSOLE_H
#include<string>
#include<vector>
#include"card.h"
void setscreensize(int cols,int lines);
void setcolor(int fore=7,int back=0);
void setcolor(std::string fore_s,std::string back_s="black");
void setcolor(Card card);
void setposition(int x=1,int y=1);
void setcursor(bool show=true);
void print(std::string s,int x=0,int y=0);
void print(int s,int x=0,int y=0);
void print(char s,int x=0,int y=0);
void print(std::vector<std::string> s,int x=0,int y=0,int l=-1,int r=-1);
void clear();
void clear(int X1,int Y1,int X2,int Y2);
#endif