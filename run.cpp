#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<algorithm>
#include<random>
#include<ctime>
#include<cmath>
#include"run.h"
#include"console.h"
#include"gamemap.h"
#include"card.h"
#include"player.h"
#include"UI.h"
#include"loaddata.h"
#include"save.h"
extern int FPS,
           playerCurrentX,playerCurrentY,playerCurrentRoom,playerSpeedX,playerSpeedY,
           roomPrintX,roomPrintY,roomWidth,roomHeight;
extern std::vector<Room> rooms;

extern std::string whichObject(Object *object);
void moveme(int deltax,int deltay)
{
    Object* deltaobject=rooms[playerCurrentRoom].getobject(playerCurrentX+deltax,playerCurrentY+deltay);
    if (deltaobject!=nullptr) 
    {
        if (whichObject(deltaobject)=="Wall") 
        {
            deltaobject->run();
            return;
        }
    }
    clear(roomPrintX+playerCurrentX,roomPrintY+playerCurrentY,roomPrintX+playerCurrentX+1,roomPrintY+playerCurrentY);
    for (int i=0; i<rooms[playerCurrentRoom].object.size(); i++)
    {
        if (playerCurrentX>=rooms[playerCurrentRoom].object[i]->x && playerCurrentX<=rooms[playerCurrentRoom].object[i]->x+rooms[playerCurrentRoom].object[i]->name.size()-2 && playerCurrentY==rooms[playerCurrentRoom].object[i]->y) 
        {
            extern void print(Object *object);
            print(rooms[playerCurrentRoom].object[i]);
            break;
        }
    }
    playerCurrentX+=deltax;
    playerCurrentY+=deltay;
    setcolor("white","blue");
    print("我",roomPrintX+playerCurrentX,roomPrintY+playerCurrentY);
}

void printmap()
{
    loadMap(playerCurrentRoom);
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    print(rooms[playerCurrentRoom]);
    moveme(0,0);
    setcolor("white");
    if (rooms[playerCurrentRoom].UP_ID<0) for (int i=3; i<55; i++) print("墙",i,3);
    else for (int i=3; i<55; i++) print("空",i,3);
    if (rooms[playerCurrentRoom].DOWN_ID<0) for (int i=3; i<=55; i++) print("墙",i,27);
    else for (int i=3; i<=55; i++) print("空",i,27);
    if (rooms[playerCurrentRoom].LEFT_ID<0) for (int i=3; i<=27; i++) print("墙",3,i);
    else for (int i=3; i<=27; i++) print("空",3,i);
    if (rooms[playerCurrentRoom].RIGHT_ID<0) for (int i=3; i<=27; i++) print("墙",55,i);
    else for (int i=3; i<=27; i++) print("空",55,i); 
}

void printsmallmap()
{
    extern int smallmapX,smallmapY,smallmapWidth,smallmapHeight;
    int smallmapCenterX=smallmapX+(smallmapWidth-1)/2,smallmapCenterY=smallmapY+(smallmapHeight-1)/2;
    clear(smallmapX,smallmapY,smallmapX+smallmapWidth-1,smallmapY+smallmapHeight-1);
    setcolor("blue","white");
    print(rooms[playerCurrentRoom].name,smallmapCenterX-rooms[playerCurrentRoom].name.size()/2+1,smallmapCenterY);
    setcolor("white");
    if (rooms[playerCurrentRoom].UP_ID>=0) 
    {
        print("↑",smallmapCenterX,smallmapCenterY-1);
        print(rooms[rooms[playerCurrentRoom].UP_ID].name,smallmapCenterX-rooms[rooms[playerCurrentRoom].UP_ID].name.size()/2+1,smallmapCenterY-2);
    }
    if (rooms[playerCurrentRoom].DOWN_ID>=0) 
    {
        print("↓",smallmapCenterX,smallmapCenterY+1);
        print(rooms[rooms[playerCurrentRoom].DOWN_ID].name,smallmapCenterX-rooms[rooms[playerCurrentRoom].DOWN_ID].name.size()/2+1,smallmapCenterY+2);
    }
    if (rooms[playerCurrentRoom].LEFT_ID>=0) 
    {
        print("←",smallmapCenterX-rooms[playerCurrentRoom].name.size()/2-1,smallmapCenterY);
        print(rooms[rooms[playerCurrentRoom].LEFT_ID].name,smallmapCenterX-rooms[playerCurrentRoom].name.size()/2-1-rooms[rooms[playerCurrentRoom].LEFT_ID].name.size(),smallmapCenterY);
    }
    if (rooms[playerCurrentRoom].RIGHT_ID>=0) 
    {
        print("→",smallmapCenterX+rooms[playerCurrentRoom].name.size()/2+1,smallmapCenterY);
        print(rooms[rooms[playerCurrentRoom].RIGHT_ID].name,smallmapCenterX+rooms[playerCurrentRoom].name.size()/2+3,smallmapCenterY);
    }
}

void printPlayerState()
{
    extern int playerStatePrintX,playerStatePrintY,playerStatePrintX2,playerStatePrintY2;
    clear(playerStatePrintX,playerStatePrintY,playerStatePrintX2,playerStatePrintY2);
    setcolor("white","black");
    setcolor("lightred");
    print("体力:"+std::to_string(Player::HP)+"/"+std::to_string(Player::HPMax),playerStatePrintX,playerStatePrintY);
    setcolor("lightblue");  
    print("灵力上限:"+std::to_string(Player::MPMax),playerStatePrintX+21,playerStatePrintY);
    setcolor("deepgreen");
    print("经验:"+std::to_string(Player::EXP)+"/"+std::to_string(Player::calculatelevel(Player::level)),playerStatePrintX,playerStatePrintY+1);
    setcolor("yellow");
    print("金币:"+std::to_string(Player::money),playerStatePrintX+21,playerStatePrintY+1);
    setcolor("gray");
    print("牌库:"+std::to_string(Player::card.size())+"张牌",playerStatePrintX,playerStatePrintY+2);
    print("手牌上限:"+std::to_string(Player::handMax),playerStatePrintX+21,playerStatePrintY+2);
    setcolor("red");
    print("按Q保存游戏",playerStatePrintX,playerStatePrintY+3);
    print("按L读取存档",playerStatePrintX+21,playerStatePrintY+3);
}

bool playermove()
{
    //printmap();
    //printsmallmap();
    char r=getch();
    //clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    if (r=='Q' || r=='q') 
    {
        save();
    }
    if (r=='L' || r=='l')
    {
        load();
    }
    if (r=='W' || r=='w') 
    {
        if (playerCurrentY>0) moveme(0,-playerSpeedY);
        else 
        {
            if (rooms[playerCurrentRoom].UP_ID>=0) 
            {
                message("进入房间"+rooms[rooms[playerCurrentRoom].UP_ID].name,"red");
                playerCurrentRoom=rooms[playerCurrentRoom].UP_ID;
                playerCurrentY=roomHeight-1;
                printmap();
                printsmallmap();
            }
        }
    }
    if (r=='S' || r=='s') 
    {
        if (playerCurrentY<roomHeight-1) moveme(0,playerSpeedY);
        else 
        {
            if (rooms[playerCurrentRoom].DOWN_ID>=0) 
            {
                message("进入房间"+rooms[rooms[playerCurrentRoom].DOWN_ID].name,"red");
                playerCurrentRoom=rooms[playerCurrentRoom].DOWN_ID;
                playerCurrentY=0;
                printmap();
                printsmallmap();
            }
        }
    }
    if (r=='A' || r=='a') 
    {
        if (playerCurrentX>0) moveme(-playerSpeedX,0);
        else 
        {
            if (rooms[playerCurrentRoom].LEFT_ID>=0) 
            {
                message("进入房间"+rooms[rooms[playerCurrentRoom].LEFT_ID].name,"red");
                playerCurrentRoom=rooms[playerCurrentRoom].LEFT_ID;
                playerCurrentX=roomWidth-2;
                printmap();
                printsmallmap();
            }
        }
    }
    if (r=='D' || r=='d') 
    {
        if (playerCurrentX<roomWidth-2) moveme(playerSpeedX,0);
        else 
        {
            if (rooms[playerCurrentRoom].RIGHT_ID>=0) 
            {
                message("进入房间"+rooms[rooms[playerCurrentRoom].RIGHT_ID].name,"red");
                playerCurrentRoom=rooms[playerCurrentRoom].RIGHT_ID;
                playerCurrentX=0;
                printmap();
                printsmallmap();
            }
        }
    }
    for (int i=0; i<rooms[playerCurrentRoom].object.size(); i++)
    {
        if (playerCurrentX==rooms[playerCurrentRoom].object[i]->x && playerCurrentY==rooms[playerCurrentRoom].object[i]->y) 
        {
            rooms[playerCurrentRoom].object[i]->run();
        }
    }
    Sleep(1000/FPS);
    return true;
}

extern std::vector<Card*> have,hand,used;
extern Enemy *currentenemy;
extern int currentselectcard;
extern int cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2,
           descriptionPrintX,descriptionPrintY,descriptionPrintX2,descriptionPrintY2;
void printPlayer();
void drawcard(int n=1)
{
    extern std::vector<Card*> have,hand,used;
    if (n>0)
    {
        int end=n+hand.size()<Player::handMax?n+hand.size():Player::handMax;
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
    if (n<0)
    {
        int end=n+hand.size()>0?n+hand.size():0;
        while(hand.size()>end)
        {
            used.push_back(hand.back());
            hand.pop_back();
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

void printcard()
{
    extern int currentselectcard;
    extern std::vector<Card*> hand;
    clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
    for (int i=0; i<hand.size(); i++) 
    {
        if (currentselectcard==i) setcolor(hand[i]->getcolor(),"white");
        else setcolor(hand[i]->getcolor(),"black");
        print(std::to_string(hand[i]->cost)+"费  "+hand[i]->name,cardSelectPrintX,cardSelectPrintY+i);
    }
    clear(descriptionPrintX,descriptionPrintY,descriptionPrintX2,descriptionPrintY2);
    setcolor(hand[currentselectcard]->getcolor(),"black");
    print(hand[currentselectcard]->description,descriptionPrintX,descriptionPrintY);
}

bool fight()
{
    srand(time(0));
    Player::turnset();
    currentenemy->turnset();
    currentenemy->currentintention=*currentenemy->intention[rand()%currentenemy->intention.size()];
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    printPlayer();
    print(currentenemy);
    drawcard(5);
    currentselectcard=0;
    printcard();
    while(selectcard());
    if (fightend()) return false;
    currentenemy->currentintention.effect();
    printPlayerState();
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
        if (r=='W' || r=='w') currentselectcard+=hand.size()-1;
        if (r=='S' || r=='s') currentselectcard+=1;
        currentselectcard%=hand.size();
        printcard();
        if (r=='\r') 
        {
            if (selectcardend()) return false;
            if (Player::MP>=hand[currentselectcard]->cost)
            {
                Player::MP-=hand[currentselectcard]->cost;
                message("打出卡牌"+hand[currentselectcard]->name);
                hand[currentselectcard]->effect();
                used.push_back(hand[currentselectcard]);
                hand.erase(hand.begin()+currentselectcard);
                if (currentselectcard>hand.size()-1) currentselectcard=hand.size()-1;
                clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
                printPlayer();
                print(currentenemy);
                if (hand.size()>0) printcard();
                else clear(cardSelectPrintX,cardSelectPrintY,cardSelectPrintX2,cardSelectPrintY2);
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
        hand.resize(0);
        selectcardend();
        return false;
    }
    Sleep(1000/FPS);
    return true;
}

extern int storePrintX,storePrintY,
           goodsPrintX,goodsPricePrintX,goodsNumberPrintX,goodsPrintY;
extern int currentselectgoods;  
int getdigits(int number) 
{
    if (number==0) return 1;
    return std::log10(std::abs(number)) + 1;
}
void printgoods()
{
    extern std::vector<Goods*> *currentgoodss;
    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
    setcolor("white","black");
    print("商店",storePrintX,storePrintY);
    print("   商品",goodsPrintX,goodsPrintY-1);
    print("价格",goodsPricePrintX,goodsPrintY-1);
    print("数量",goodsNumberPrintX,goodsPrintY-1);
    for (int i=0; i<currentgoodss->size(); i++) 
    {
        if (currentselectgoods==i) setcolor((*currentgoodss)[i]->color,"white");
        else setcolor((*currentgoodss)[i]->color,"black");
        print((*currentgoodss)[i]->name,goodsPrintX+getdigits(i)+2,goodsPrintY+i);
        setcolor("white","black");
        print(std::to_string(i+1)+".",goodsPrintX,goodsPrintY+i);
        print(std::to_string((*currentgoodss)[i]->price),goodsPricePrintX,goodsPrintY+i);
        print(std::to_string((*currentgoodss)[i]->number),goodsNumberPrintX,goodsPrintY+i);
    }
    clear(descriptionPrintX,descriptionPrintY,descriptionPrintX2,descriptionPrintY2);
    if (currentselectgoods!=currentgoodss->size()) 
    {
        setcolor((*currentgoodss)[currentselectgoods]->color,"black");
        print((*currentgoodss)[currentselectgoods]->description,descriptionPrintX,descriptionPrintY);
        setcolor("blue","black");
    }
    else setcolor("blue","white");
    print("退出商店",goodsPrintX,goodsPrintY+(*currentgoodss).size());
}

bool shopping()
{
    char r=getch();
    extern std::vector<Goods*> *currentgoodss;
    if (r=='W' || r=='w') currentselectgoods+=((*currentgoodss).size()+1)-1;
    if (r=='S' || r=='s') currentselectgoods+=1;
    currentselectgoods%=(*currentgoodss).size()+1;
    printgoods();
    if (r=='\r') 
    {
        if (currentselectgoods<currentgoodss->size())
        {
            if (Player::money>=(*currentgoodss)[currentselectgoods]->price)
            {
                Player::money-=(*currentgoodss)[currentselectgoods]->price;
                (*currentgoodss)[currentselectgoods]->buy();
                if ((*currentgoodss)[currentselectgoods]->number==0) (*currentgoodss).erase((*currentgoodss).begin()+currentselectgoods);
                printgoods();
                printPlayerState();
            }
            else message("你的钱不够","red");
        }
        else 
        {
            message("退出商店","red");
            return false;
        }
    }
    Sleep(1000/FPS);
    return true;
}

void printStory(int ID)
{
    extern std::vector<std::string> story;
    int x=roomPrintX,y=roomPrintY;
    std::string forecolor="white",backcolor="black";
    clear(x,y,x+roomWidth-1,y+roomHeight-1);
    int i=0;
    while(i<story[ID].size())
    {
        if (story[ID][i]=='&')
        {
            int next=story[ID].find(",",i+1);
            forecolor=story[ID].substr(i+1,next-i-1);
            i=next;
            next=story[ID].find("&",i+1);
            backcolor=story[ID].substr(i+1,next-i-1);
            i=next;
        }
        else if (story[ID][i]=='$')
        {
            x=roomPrintX;
            y++;
            if (y>=roomPrintY+roomHeight) 
            {
                y=roomPrintY;
                clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
            }
            setcolor("white");
            print("(按任意键继续)",x,y);
            getch();
            clear(x,y,x+14,y);
        }
        else
        {
            std::string gbk_char=story[ID].substr(i,2);
            setcolor(forecolor,backcolor);
            print(gbk_char,x,y);
            Sleep(10);
            x+=2;
            if (x>=roomPrintX+roomWidth)
            {
                x=roomPrintX;
                y++;
                if (y>=roomPrintY+roomHeight) 
                {
                    y=roomPrintY;
                    clear(roomPrintX,roomPrintY,roomPrintX+roomWidth-1,roomPrintY+roomHeight-1);
                }
            }
            i+=1;
        }
        i+=1;
    }
}