#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<vector>
#include"console.h"
using namespace std;
void setscreensize(int cols,int lines)
{
    char cmd[64];
	sprintf(cmd, "mode con cols=%d lines=%d",cols,lines);
	system(cmd);
}
void setcolor(int fore/* =7 */,int back/* =0 */)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(back<<4)+fore);
}
void setcolor(string fore_s,string back_s)
{
    int fore=-1,back=-1;
    if (back_s=="black") back=0;
    if (back_s=="deepblue") back=1;
    if (back_s=="deepgreen") back=2;
    if (back_s=="lightblue") back=3;
    if (back_s=="red") back=4;
    if (back_s=="deeppurple") back=5;
    if (back_s=="yellow") back=6;
    if (back_s=="lightgray") back=7;
    if (back_s=="gray") back=8;
    if (back_s=="blue") back=9;
    if (back_s=="green") back=10;
    if (back_s=="cyan") back=11;
    if (back_s=="lightred") back=12;
    if (back_s=="purple") back=13;
    if (back_s=="lightyellow") back=14;
    if (back_s=="white") back=15;
    if (fore_s=="black") fore=0;
    if (fore_s=="deepblue") fore=1;
    if (fore_s=="deepgreen") fore=2;
    if (fore_s=="lightblue") fore=3;
    if (fore_s=="red") fore=4;
    if (fore_s=="deeppurple") fore=5;
    if (fore_s=="yellow") fore=6;
    if (fore_s=="lightgray") fore=7;
    if (fore_s=="gray") fore=8;
    if (fore_s=="blue") fore=9;
    if (fore_s=="green") fore=10;
    if (fore_s=="cyan") fore=11;
    if (fore_s=="lightred") fore=12;
    if (fore_s=="purple") fore=13;
    if (fore_s=="lightyellow") fore=14;
    if (fore_s=="white") fore=15;
    setcolor(fore,back);
}
void setposition(int x/* =1 */,int y/* =1 */)
{
    COORD cursorposition;
    cursorposition.X=x;
    cursorposition.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursorposition); 
}
void setcursor(bool show/* =true */)
{
    if (!show) 
    {
        CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    }
    else
    {
        CONSOLE_CURSOR_INFO cursor_info = {100, 1};
	    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    }
}
void print(string s,int x/* =0 */,int y/* =0 */)
{
    setposition(x,y);
    cout<<s;
}
void print(vector<string> s,int x/* =0 */,int y/* =0 */,int l/* =-1 */,int r/* =-1 */)
{
    if (l==-1 && r==-1) 
    {
        l=0;
        r=s.size()-1;
    }
    for (int i=l; i<=r; i++) print(s[i],x,y+i);
}
void clear()
{
    setcolor("black","black");
    setposition(0,0);
    for (int i=0; i<=100; i++) cout<<endl;
}
void clear(int X1,int Y1,int X2,int Y2)
{
    setcolor("black","black");
    for (int i=Y1; i<=Y2; i++)
    {
        setposition(X1,i);
        for (int j=X1; j<=X2; j++) cout<<" ";
    }
}
