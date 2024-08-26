#include<iostream>
#include<windows.h>
#include<conio.h>
#include"run.h"
#include"console.h"
#include"gamemap.h"
using namespace std;
extern int playerCurrentX,playerCurrentY,playerCurrentRoom,playerSpeedX,playerSpeedY,
           roomPrintX,roomPrintY;
extern Room room[];
bool playermove()
{
    clear();
    print(room[playerCurrentRoom]);
    setcolor("white","blue");
    print("我",playerCurrentX,playerCurrentY);
    char r=getch();
    clear();
    if (r=='W' || r=='w') 
    {
        if (playerCurrentY>0) playerCurrentY-=playerSpeedY;
        else 
        {
            if (room[playerCurrentRoom].UP_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+to_string(room[playerCurrentRoom].UP_ID),0,17);
            }
        }
    }
    if (r=='S' || r=='s') 
    {
        if (playerCurrentY<8) playerCurrentY+=playerSpeedY;
        else 
        {
            if (room[playerCurrentRoom].DOWN_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+to_string(room[playerCurrentRoom].DOWN_ID),0,17);
            }
        }
    }
    if (r=='A' || r=='a') 
    {
        if (playerCurrentX>0) playerCurrentX-=playerSpeedX;
        else 
        {
            if (room[playerCurrentRoom].LEFT_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+to_string(room[playerCurrentRoom].LEFT_ID),0,17);
            }
        }
    }
    if (r=='D' || r=='d') 
    {
        if (playerCurrentX<16) playerCurrentX+=playerSpeedX;
        else 
        {
            if (room[playerCurrentRoom].RIGHT_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+to_string(room[playerCurrentRoom].RIGHT_ID),0,17);
            }
        }
    }
    print(room[playerCurrentRoom]);
    setcolor("white","blue");
    print("我",playerCurrentX,playerCurrentY);
    for (int i=0; i<room[playerCurrentRoom].object_s; i++)
    {
        if (playerCurrentX==room[playerCurrentRoom].object[i].x && playerCurrentY==room[playerCurrentRoom].object[i].y) 
        {
            clear();
            setcolor("red","black");
            print("按任意键开始战斗",0,0);
            while(attack());
        }
    }
    Sleep(100);
    return true;
}
bool attack()
{
    string select[3]={"攻击","防御","逃跑"};
    static int currentSelect=0;
    char r=getch();
    clear();
    if (r=='W' || r=='w') currentSelect=(currentSelect+2)%3;
    if (r=='S' || r=='s') currentSelect=(currentSelect+1)%3;
    if (r=='E' || r=='e') 
    {
        if (currentSelect==2) return false;
        else 
        {
            setcolor("green","black");
            print("执行"+select[currentSelect],0,5);
        }
    }
    for (int i=0; i<=2; i++)
    {
        if (currentSelect==i) setcolor("red","white");
        else setcolor("red","black");
        print(to_string(i+1)+"."+select[i],0,i);
    }
    
    Sleep(100);
    return true;
}