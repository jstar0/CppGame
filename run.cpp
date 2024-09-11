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
#include"config.h"

void moveme(int deltax,int deltay)
{
    Object* deltaobject=GameConfig::rooms[PlayerConfig::currentRoom].getobject(PlayerConfig::currentX+deltax,PlayerConfig::currentY+deltay);
    if (deltaobject!=nullptr) 
    {
        if (whichObject(deltaobject)=="Wall") 
        {
            deltaobject->run();
            return;
        }
    }
    clear(RoomConfig::printX+PlayerConfig::currentX,RoomConfig::printY+PlayerConfig::currentY,RoomConfig::printX+PlayerConfig::currentX+1,RoomConfig::printY+PlayerConfig::currentY);
    for (int i=0; i<GameConfig::rooms[PlayerConfig::currentRoom].object.size(); i++)
    {
        if (PlayerConfig::currentX>=GameConfig::rooms[PlayerConfig::currentRoom].object[i]->x && PlayerConfig::currentX<=GameConfig::rooms[PlayerConfig::currentRoom].object[i]->x+GameConfig::rooms[PlayerConfig::currentRoom].object[i]->name.size()-2 && PlayerConfig::currentY==GameConfig::rooms[PlayerConfig::currentRoom].object[i]->y) 
        {
            extern void print(Object *object);
            print(GameConfig::rooms[PlayerConfig::currentRoom].object[i]);
            break;
        }
    }
    PlayerConfig::currentX+=deltax;
    PlayerConfig::currentY+=deltay;
    setcolor("white","blue");
    print("我",RoomConfig::printX+PlayerConfig::currentX,RoomConfig::printY+PlayerConfig::currentY);
}

void printMap()
{
    clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
    print(GameConfig::rooms[PlayerConfig::currentRoom]);
    moveme(0,0);
    setcolor("white");
    if (GameConfig::rooms[PlayerConfig::currentRoom].UP_ID<0) for (int i=3; i<55; i++) print("墙",i,3);
    else for (int i=3; i<55; i++) print("空",i,3);
    if (GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID<0) for (int i=3; i<=55; i++) print("墙",i,27);
    else for (int i=3; i<=55; i++) print("空",i,27);
    if (GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID<0) for (int i=3; i<=27; i++) print("墙",3,i);
    else for (int i=3; i<=27; i++) print("空",3,i);
    if (GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID<0) for (int i=3; i<=27; i++) print("墙",55,i);
    else for (int i=3; i<=27; i++) print("空",55,i); 
}

void printSmallMap()
{
    int smallmapCenterX=SmallMapConfig::x+(SmallMapConfig::width-1)/2,smallmapCenterY=SmallMapConfig::y+(SmallMapConfig::height-1)/2;
    clear(SmallMapConfig::x,SmallMapConfig::y,SmallMapConfig::x+SmallMapConfig::width-1,SmallMapConfig::y+SmallMapConfig::height-1);
    setcolor("blue","white");
    print(GameConfig::rooms[PlayerConfig::currentRoom].name,smallmapCenterX-GameConfig::rooms[PlayerConfig::currentRoom].name.size()/2+1,smallmapCenterY);
    setcolor("white");
    if (GameConfig::rooms[PlayerConfig::currentRoom].UP_ID>=0) 
    {
        print("↑",smallmapCenterX,smallmapCenterY-1);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].UP_ID].name,smallmapCenterX-GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].UP_ID].name.size()/2+1,smallmapCenterY-2);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID>=0) 
    {
        print("↓",smallmapCenterX,smallmapCenterY+1);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID].name,smallmapCenterX-GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID].name.size()/2+1,smallmapCenterY+2);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID>=0) 
    {
        print("←",smallmapCenterX-GameConfig::rooms[PlayerConfig::currentRoom].name.size()/2-1,smallmapCenterY);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID].name,smallmapCenterX-GameConfig::rooms[PlayerConfig::currentRoom].name.size()/2-1-GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID].name.size(),smallmapCenterY);
    }
    if (GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID>=0) 
    {
        print("→",smallmapCenterX+GameConfig::rooms[PlayerConfig::currentRoom].name.size()/2+1,smallmapCenterY);
        print(GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID].name,smallmapCenterX+GameConfig::rooms[PlayerConfig::currentRoom].name.size()/2+3,smallmapCenterY);
    }
}

void printPlayerState()
{
    clear(PlayerConfig::statePrintX,PlayerConfig::statePrintY,PlayerConfig::statePrintX2,PlayerConfig::statePrintY2);
    setcolor("white","black");
    setcolor("lightred");
    print("体力:"+std::to_string(Player::HP)+"/"+std::to_string(Player::HPMax),PlayerConfig::statePrintX,PlayerConfig::statePrintY);
    setcolor("lightblue");  
    print("灵力上限:"+std::to_string(Player::MPMax),PlayerConfig::statePrintX+21,PlayerConfig::statePrintY);
    setcolor("deepgreen");
    print("等级:"+std::to_string(Player::level)+"("+std::to_string(Player::EXP)+"/"+std::to_string(Player::calculatelevel(Player::level))+")",PlayerConfig::statePrintX,PlayerConfig::statePrintY+1);
    setcolor("yellow");
    print("金币:"+std::to_string(Player::money),PlayerConfig::statePrintX+21,PlayerConfig::statePrintY+1);
    setcolor("gray");
    print("牌库:"+std::to_string(Player::card.size())+"张牌",PlayerConfig::statePrintX,PlayerConfig::statePrintY+2);
    print("手牌上限:"+std::to_string(Player::handMax),PlayerConfig::statePrintX+21,PlayerConfig::statePrintY+2);
    setcolor("red");
    print("按Q保存游戏",PlayerConfig::statePrintX,PlayerConfig::statePrintY+3);
    print("按L读取存档",PlayerConfig::statePrintX+21,PlayerConfig::statePrintY+3);
    setcolor("white");
    print("注:人物和地图存档不互通，可以反复刷级",PlayerConfig::statePrintX,PlayerConfig::statePrintY+4);
}

bool playerMove()
{
    //printMap();
    //printSmallMap();
    char r=getch();
    //clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
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
        if (PlayerConfig::currentY>0) moveme(0,-PlayerConfig::speedY);
        else 
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].UP_ID>=0) 
            {
                message("进入房间"+GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].UP_ID].name,"red");
                PlayerConfig::currentRoom=GameConfig::rooms[PlayerConfig::currentRoom].UP_ID;
                PlayerConfig::currentY=RoomConfig::height-1;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r=='S' || r=='s') 
    {
        if (PlayerConfig::currentY<RoomConfig::height-1) moveme(0,PlayerConfig::speedY);
        else 
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID>=0) 
            {
                message("进入房间"+GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID].name,"red");
                PlayerConfig::currentRoom=GameConfig::rooms[PlayerConfig::currentRoom].DOWN_ID;
                PlayerConfig::currentY=0;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r=='A' || r=='a') 
    {
        if (PlayerConfig::currentX>0) moveme(-PlayerConfig::speedX,0);
        else 
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID>=0) 
            {
                message("进入房间"+GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID].name,"red");
                PlayerConfig::currentRoom=GameConfig::rooms[PlayerConfig::currentRoom].LEFT_ID;
                PlayerConfig::currentX=RoomConfig::width-2;
                printMap();
                printSmallMap();
            }
        }
    }
    if (r=='D' || r=='d') 
    {
        if (PlayerConfig::currentX<RoomConfig::width-2) moveme(PlayerConfig::speedX,0);
        else 
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID>=0) 
            {
                message("进入房间"+GameConfig::rooms[GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID].name,"red");
                PlayerConfig::currentRoom=GameConfig::rooms[PlayerConfig::currentRoom].RIGHT_ID;
                PlayerConfig::currentX=0;
                printMap();
                printSmallMap();
            }
        }
    }
    for (int i=0; i<GameConfig::rooms[PlayerConfig::currentRoom].object.size(); i++)
    {
        if (PlayerConfig::currentX==GameConfig::rooms[PlayerConfig::currentRoom].object[i]->x && PlayerConfig::currentY==GameConfig::rooms[PlayerConfig::currentRoom].object[i]->y) 
        {
            if (GameConfig::rooms[PlayerConfig::currentRoom].object[i]->times!=0) GameConfig::rooms[PlayerConfig::currentRoom].object[i]->run();
        }
    }
    Sleep(1000/GameConfig::FPS);
    return true;
}

void printPlayer();
void drawcard(int n=1)
{
    if (n>0)
    {
        int end=n+CardConfig::hand.size()<Player::handMax?n+CardConfig::hand.size():Player::handMax;
        while(CardConfig::hand.size()<end)
        {
            if (!CardConfig::have.empty())
            {
                auto dre=std::default_random_engine{static_cast<unsigned>(std::time(nullptr))};
                std::shuffle(CardConfig::have.begin(),CardConfig::have.end(),dre);
                CardConfig::hand.push_back(CardConfig::have.back());
                CardConfig::have.pop_back();
            }
            else
            {
                if (CardConfig::used.size()>0)
                {
                    CardConfig::have=CardConfig::used;
                    CardConfig::used.clear();
                }
                else break;
            }
        }
    }
    if (n<0)
    {
        int end=n+CardConfig::hand.size()>0?n+CardConfig::hand.size():0;
        while(CardConfig::hand.size()>end)
        {
            CardConfig::used.push_back(CardConfig::hand.back());
            CardConfig::hand.pop_back();
        }
    }
}

bool fightend()
{
    if (GameConfig::currentEnemy->HP==0 || Player::HP==0)
    {
        message("按任意键退出战斗","red");
        getch();
        clear(CardConfig::selectPrintX,CardConfig::selectPrintY,CardConfig::selectPrintX2,CardConfig::selectPrintY2);
        CardConfig::hand.clear();
        CardConfig::have.clear();
        CardConfig::used.clear();
        GameConfig::currentEnemy=nullptr;
        return true;
    }
    return false;
}

void printcard()
{
    clear(CardConfig::selectPrintX,CardConfig::selectPrintY,CardConfig::selectPrintX2,CardConfig::selectPrintY2);
    for (int i=0; i<CardConfig::hand.size(); i++) 
    {
        if (CardConfig::currentSelectCard==i) setcolor(CardConfig::hand[i]->getcolor(),"white");
        else setcolor(CardConfig::hand[i]->getcolor(),"black");
        print(std::to_string(CardConfig::hand[i]->cost)+"费  "+CardConfig::hand[i]->name,CardConfig::selectPrintX,CardConfig::selectPrintY+i);
    }
    clear(DescriptionConfig::printX,DescriptionConfig::printY,DescriptionConfig::printX2,DescriptionConfig::printY2);
    setcolor(CardConfig::hand[CardConfig::currentSelectCard]->getcolor(),"black");
    print(CardConfig::hand[CardConfig::currentSelectCard]->description,DescriptionConfig::printX,DescriptionConfig::printY);
}

bool fight()
{
    srand(time(0));
    Player::turnset();
    GameConfig::currentEnemy->turnset();
    GameConfig::currentEnemy->currentintention=*GameConfig::currentEnemy->intention[rand()%GameConfig::currentEnemy->intention.size()];
    clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
    printPlayer();
    print(GameConfig::currentEnemy);
    drawcard(5);
    CardConfig::currentSelectCard=0;
    printcard();
    while(selectcard());
    if (fightend()) return false;
    GameConfig::currentEnemy->currentintention.effect();
    printPlayerState();
    message("回合结束","lightblue");
    return true;
}

bool selectcardend()
{
    if (GameConfig::currentEnemy->HP==0)
    {
        message("你打败了"+GameConfig::currentEnemy->name,"red");
        if (GameConfig::currentEnemy->giveCard>=0)
        {
            Player::addcard(CardConfig::cards[GameConfig::currentEnemy->giveCard]);
            message("获得卡牌"+CardConfig::cards[GameConfig::currentEnemy->giveCard]->name);
        }
        if (GameConfig::currentEnemy->giveProp>=0)
        {
            Player::addprop(GameConfig::props[GameConfig::currentEnemy->giveProp]);
            message("获得道具"+GameConfig::props[GameConfig::currentEnemy->giveProp]->name);
        }
        if (GameConfig::currentEnemy->giveMoney>0)
        {
            Player::money+=GameConfig::currentEnemy->giveMoney;
            message("获得金币"+std::to_string(GameConfig::currentEnemy->giveMoney),"yellow");
        }
        if (GameConfig::currentEnemy->giveEXP>0)
        {
            Player::getEXP(GameConfig::currentEnemy->giveEXP);
        }
        return true;
    }
    if (Player::HP==0)
    {
        message("你被"+GameConfig::currentEnemy->name+"打败了","red");
        return true;
    }
    return false;
}

bool selectcard()
{
    char r=getch(); 
    if (CardConfig::hand.size()>0)
    {
        if (r=='W' || r=='w') CardConfig::currentSelectCard+=CardConfig::hand.size()-1;
        if (r=='S' || r=='s') CardConfig::currentSelectCard+=1;
        CardConfig::currentSelectCard%=CardConfig::hand.size();
        printcard();
        if (r=='\r') 
        {
            if (selectcardend()) return false;
            if (Player::MP>=CardConfig::hand[CardConfig::currentSelectCard]->cost)
            {
                Player::MP-=CardConfig::hand[CardConfig::currentSelectCard]->cost;
                message("打出卡牌"+CardConfig::hand[CardConfig::currentSelectCard]->name);
                CardConfig::hand[CardConfig::currentSelectCard]->effect();
                CardConfig::used.push_back(CardConfig::hand[CardConfig::currentSelectCard]);
                CardConfig::hand.erase(CardConfig::hand.begin()+CardConfig::currentSelectCard);
                if (CardConfig::currentSelectCard>CardConfig::hand.size()-1) CardConfig::currentSelectCard=CardConfig::hand.size()-1;
                clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
                printPlayer();
                print(GameConfig::currentEnemy);
                if (CardConfig::hand.size()>0) printcard();
                else clear(CardConfig::selectPrintX,CardConfig::selectPrintY,CardConfig::selectPrintX2,CardConfig::selectPrintY2);
                if (selectcardend()) return false;
            }
            else message("费用不够","red");
        }
    }
    else 
    {
        clear(CardConfig::selectPrintX,CardConfig::selectPrintY,CardConfig::selectPrintX2,CardConfig::selectPrintY2);
        message("没有卡牌","red");    
    }
    if (r=='E' || r=='e') 
    {
        int n=CardConfig::hand.size();
        for (int i=0; i<n; i++)
        {
            CardConfig::used.push_back(CardConfig::hand[0]);
            CardConfig::hand.erase(CardConfig::hand.begin());
        }
        CardConfig::hand.resize(0);
        selectcardend();
        return false;
    }
    Sleep(1000/GameConfig::FPS);
    return true;
}

int getdigits(int number) 
{
    if (number==0) return 1;
    return std::log10(std::abs(number)) + 1;
}
void printgoods()
{
    clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
    setcolor("white","black");
    print("商店",StoreConfig::printX,StoreConfig::printY);
    print("   商品",GoodsConfig::printX,GoodsConfig::printY-1);
    print("价格",GoodsConfig::pricePrintX,GoodsConfig::printY-1);
    print("数量",GoodsConfig::numberPrintX,GoodsConfig::printY-1);
    for (int i=0; i<StoreConfig::currentGoods->size(); i++) 
    {
        if (StoreConfig::currentSelectGoods==i) setcolor((*StoreConfig::currentGoods)[i]->color,"white");
        else setcolor((*StoreConfig::currentGoods)[i]->color,"black");
        print((*StoreConfig::currentGoods)[i]->name,GoodsConfig::printX+getdigits(i)+2,GoodsConfig::printY+i);
        setcolor("white","black");
        print(std::to_string(i+1)+".",GoodsConfig::printX,GoodsConfig::printY+i);
        print(std::to_string((*StoreConfig::currentGoods)[i]->price),GoodsConfig::pricePrintX,GoodsConfig::printY+i);
        print(std::to_string((*StoreConfig::currentGoods)[i]->number),GoodsConfig::numberPrintX,GoodsConfig::printY+i);
    }
    clear(DescriptionConfig::printX,DescriptionConfig::printY,DescriptionConfig::printX2,DescriptionConfig::printY2);
    if (StoreConfig::currentSelectGoods!=StoreConfig::currentGoods->size()) 
    {
        setcolor((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->color,"black");
        print((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->description,DescriptionConfig::printX,DescriptionConfig::printY);
        setcolor("blue","black");
    }
    else setcolor("blue","white");
    print("退出商店",GoodsConfig::printX,GoodsConfig::printY+(*StoreConfig::currentGoods).size());
}

bool shopping()
{
    char r=getch();
    if (r=='W' || r=='w') StoreConfig::currentSelectGoods+=((*StoreConfig::currentGoods).size()+1)-1;
    if (r=='S' || r=='s') StoreConfig::currentSelectGoods+=1;
    StoreConfig::currentSelectGoods%=(*StoreConfig::currentGoods).size()+1;
    printgoods();
    if (r=='\r') 
    {
        if (StoreConfig::currentSelectGoods<StoreConfig::currentGoods->size())
        {
            if (Player::money>=(*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->price)
            {
                Player::money-=(*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->price;
                (*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->buy();
                if ((*StoreConfig::currentGoods)[StoreConfig::currentSelectGoods]->number==0) (*StoreConfig::currentGoods).erase((*StoreConfig::currentGoods).begin()+StoreConfig::currentSelectGoods);
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
    Sleep(1000/GameConfig::FPS);
    return true;
}

void printStory(int ID)
{
    int x=RoomConfig::printX,y=RoomConfig::printY;
    std::string forecolor="white",backcolor="black";
    clear(x,y,x+RoomConfig::width-1,y+RoomConfig::height-1);
    int i=0;
    while(i<GameConfig::story[ID].size())
    {
        if (GameConfig::story[ID][i]=='&')
        {
            int next=GameConfig::story[ID].find(",",i+1);
            forecolor=GameConfig::story[ID].substr(i+1,next-i-1);
            i=next;
            next=GameConfig::story[ID].find("&",i+1);
            backcolor=GameConfig::story[ID].substr(i+1,next-i-1);
            i=next;
        }
        else if (GameConfig::story[ID][i]=='$')
        {
            x=RoomConfig::printX;
            y++;
            if (y>=RoomConfig::printY+RoomConfig::height) 
            {
                y=RoomConfig::printY;
                clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
            }
            setcolor("white");
            print("(按任意键继续)",x,y);
            getch();
            clear(x,y,x+14,y);
        }
        else
        {
            std::string gbk_char=GameConfig::story[ID].substr(i,2);
            setcolor(forecolor,backcolor);
            print(gbk_char,x,y);
            Sleep(10);
            x+=2;
            if (x>=RoomConfig::printX+RoomConfig::width)
            {
                x=RoomConfig::printX;
                y++;
                if (y>=RoomConfig::printY+RoomConfig::height) 
                {
                    y=RoomConfig::printY;
                    clear(RoomConfig::printX,RoomConfig::printY,RoomConfig::printX+RoomConfig::width-1,RoomConfig::printY+RoomConfig::height-1);
                }
            }
            i+=1;
        }
        i+=1;
    }
}