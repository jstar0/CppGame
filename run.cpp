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
extern std::vector<Room> room;
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
    for (int i=0; i<room[playerCurrentRoom].object.size(); i++)
    {
        if (playerCurrentX==room[playerCurrentRoom].object[i]->x && playerCurrentY==room[playerCurrentRoom].object[i]->y) 
        {
            room[playerCurrentRoom].object[i]->run();
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

bool fightend()
{
    if (currentenemy->HP==0 || Player::HP==0)
    {
        message("按任意键退出战斗","red");
        getch();
        clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
        hand.clear();
        have.clear();
        used.clear();
        currentenemy=nullptr;
        return true;
    }
    return false;
}

bool fight(Enemy *enemy)
{
    srand(time(0));
    currentenemy=enemy;
    Player::turnset();
    currentenemy->currentintention=*currentenemy->intention[rand()%currentenemy->intention.size()];
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    printPlayer();
    print(currentenemy);
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
    if (fightend()) return false;
    currentenemy->currentintention.effect();
    message("回合结束","lightblue");
    return true;
}

bool selectcardend()
{
    if (currentenemy->HP==0)
    {
        message("你打败了"+currentenemy->name,"red");
        return true;
    }
    if (Player::HP==0)
    {
        message("你被"+currentenemy->name+"打败了","red");
        return true;
    }
    return false;
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
            if (selectcardend()) return false;
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
                print(currentenemy);
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
                if (selectcardend()) return false;
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
        selectcardend();
        return false;
    }
    Sleep(100);
    return true;
}