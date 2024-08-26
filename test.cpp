#include<iostream>
#include<conio.h>
#include<windows.h>
#include"console.h"
#include"gamemap.h"
#include"run.h"
using namespace std;

int playerCurrentX=0,playerCurrentY=0,playerCurrentRoom=0,playerSpeedX=2,playerSpeedY=1,
    roomPrintX=0,roomPrintY=0;
Room room[10];

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    room[0].object_s=1;
    room[0].object[0].name="好吃的";
    room[0].object[0].x=2;
    room[0].object[0].y=2;
    room[0].RIGHT_ID=1;
    room[0].LEFT_ID=2;
    room[0].UP_ID=3;
    room[0].DOWN_ID=4;
    setscreensize(120,40);
    setcursor(false);
    system("color 0C");
    while(playermove());
    return 0;
}