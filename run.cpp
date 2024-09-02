#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<algorithm>
#include<random>
#include<ctime>
#include"run.h"
#include"console.h"
#include"gamemap.h"
#include"card.h"
#include"player.h"
#include"UI.h"
extern int playerCurrentX,playerCurrentY,playerCurrentRoom,playerSpeedX,playerSpeedY,
           roomPrintX,roomPrintY,roomWidth,roomHeight;
extern Room room[];
bool playermove()
{
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    print(room[playerCurrentRoom]);
    setcolor("white","blue");
    print("我",roomPrintX+playerCurrentX,roomPrintY+playerCurrentY);
    char r=getch();
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    if (r=='W' || r=='w') 
    {
        if (playerCurrentY>0) playerCurrentY-=playerSpeedY;
        else 
        {
            if (room[playerCurrentRoom].UP_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+std::to_string(room[playerCurrentRoom].UP_ID),1,2);
            }
        }
    }
    if (r=='S' || r=='s') 
    {
        if (playerCurrentY<roomHeight-1) playerCurrentY+=playerSpeedY;
        else 
        {
            if (room[playerCurrentRoom].DOWN_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+std::to_string(room[playerCurrentRoom].DOWN_ID),1,2);
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
                print("进入房间"+std::to_string(room[playerCurrentRoom].LEFT_ID),1,2);
            }
        }
    }
    if (r=='D' || r=='d') 
    {
        if (playerCurrentX<roomWidth-2) playerCurrentX+=playerSpeedX;
        else 
        {
            if (room[playerCurrentRoom].RIGHT_ID>=0) 
            {
                setcolor("red","black");
                print("进入房间"+std::to_string(room[playerCurrentRoom].RIGHT_ID),1,2);
            }
        }
    }
    print(room[playerCurrentRoom]);
    setcolor("white","blue");
    print("我",roomPrintX+playerCurrentX,roomPrintY+playerCurrentY);
    /* for (int i=0; i<room[playerCurrentRoom].object.size(); i++)
    {
        if (playerCurrentX==room[playerCurrentRoom].object[i].x && playerCurrentY==room[playerCurrentRoom].object[i].y) 
        {
        }
    } */
    for (int i=0; i<room[playerCurrentRoom].enemyobject.size(); i++)
    {
        if (playerCurrentX==room[playerCurrentRoom].enemyobject[i].x && playerCurrentY==room[playerCurrentRoom].enemyobject[i].y) 
        {
            clear();
            setcolor("red","black");
            print("按任意键开始战斗",0,0);
            while(attack(&room[playerCurrentRoom].enemyobject[i].enemy));
        }
    }
    Sleep(100);
    return true;
}

extern std::vector<Card> have,hand,used;
extern Enemy *currentenemy;
extern int currentselect;
extern int cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2,
           cardPrintX,cardPrintY,cardPrintX2,cardPrintY2;
void printPlayer();
void drawcard(int n=1)
{
    extern std::vector<Card> have,hand,used;
    int end=n+hand.size();
    while(hand.size()<end)
    {
        if (!have.empty())
        {
            auto dre=std::default_random_engine{static_cast<unsigned>(std::time(nullptr))};
            std::shuffle(have.begin(),have.end(),dre);
            hand.push_back(have.back());
            have.pop_back();
        }
        else
        {
            if (used.size()>0)
            {
                have=used;
                used.clear();
            }
            else break;
        }
    }
}
bool attack(Enemy *enemy)
{
    currentenemy=enemy;
    Player::turnset();
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    printPlayer();
    print(*currentenemy);
    drawcard(5);
    currentselect=0;
    clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
    for (int i=0; i<hand.size(); i++) 
    {
        if (currentselect==i) setcolor(hand[i].getcolor(),"white");
        else setcolor(hand[i].getcolor(),"black");
        print(std::to_string(hand[i].cost)+"费  "+hand[i].name,cardSelectPrintX,cardSelectPrintY+i);
    }
    clear(cardPrintX,cardPrintY,cardPrintX2,cardPrintY2);
    setcolor("white","black");
    print(hand[currentselect].description,cardPrintX,cardPrintY);
    while(selectcard());
    message("回合结束","lightblue");
    return attack(enemy);
}

bool selectcard()
{
    char r=getch();
    if (hand.size()>0)
    {
        if (r=='W' || r=='w') currentselect+=hand.size()-1;
        if (r=='S' || r=='s') currentselect+=1;
        currentselect%=hand.size();
        clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
        for (int i=0; i<hand.size(); i++) 
        {
            if (currentselect==i) setcolor(hand[i].getcolor(),"white");
            else setcolor(hand[i].getcolor(),"black");
            print(std::to_string(hand[i].cost)+"费  "+hand[i].name,cardSelectPrintX,cardSelectPrintY+i);
        }
        clear(cardPrintX,cardPrintY,cardPrintX2,cardPrintY2);
        setcolor("white","black");
        print(hand[currentselect].description,cardPrintX,cardPrintY);
        if (r=='\r') 
        {
            if (Player::MP>=hand[currentselect].cost)
            {
                Player::MP-=hand[currentselect].cost;
                message("打出卡牌"+hand[currentselect].name);
                hand[currentselect].effect();
                used.push_back(hand[currentselect]);
                hand.erase(hand.begin()+currentselect);
                if (currentselect>hand.size()-1) currentselect=hand.size()-1;
                clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
                printPlayer();
                print(*currentenemy);
                if (hand.size()>0)
                {
                    clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
                    for (int i=0; i<hand.size(); i++) 
                    {
                        if (currentselect==i) setcolor(hand[i].getcolor(),"white");
                        else setcolor(hand[i].getcolor(),"black");
                        print(std::to_string(hand[i].cost)+"费  "+hand[i].name,cardSelectPrintX,cardSelectPrintY+i);
                    }
                    clear(cardPrintX,cardPrintY,cardPrintX2,cardPrintY2);
                    setcolor("white","black");
                    print(hand[currentselect].description,cardPrintX,cardPrintY);
                }
                else 
                {
                    clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
                    message("没有卡牌","red");
                }
            }
            else message("费用不够","red");
        }
    }
    else 
    {
        clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
        message("没有卡牌","red");    
    }
    if (r=='E' || r=='e') 
    {
        for (int i=0; i<hand.size(); i++)
        {
            used.push_back(hand[0]);
            hand.erase(hand.begin());
        }
        return false;
    }
    Sleep(100);
    return true;
}