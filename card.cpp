#include<iostream>
#include<string>
#include<vector>
#include"card.h"
#include"console.h"
#include"enemy.h"
#include"player.h"
#include"UI.h"
#include"run.h"
#include<algorithm>
#include<random>
#include<ctime>

extern int cardPrintX,cardPrintY;

Card::Card()
{
    name="未知";
    description={"未知"};
    ID=0;
    cost=0;
    rarity=0;
}

Card::Card(std::string name,std::vector<std::string> description,int ID,int cost,int rarity)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
}

CardKind::CardKind()
{
    isattack=false;
    isdefend=false;
    isdraw=false;
    isstrengthen=false;
    damage=0;
    damagetimes=0;
    defense=0;
    drawtimes=0;
    strength=0;
}

void Card::setattack(int damage,int times)
{
    kind.isattack=true;
    kind.damage=damage;
    kind.damagetimes=times;
}

void Card::setdefend(int defense)
{
    kind.isdefend=true;
    kind.defense=defense;
}

void Card::setdraw(int times)
{
    kind.isdraw=true;
    kind.drawtimes=times;
}

void Card::setstrengthen(int strength)
{
    kind.isstrengthen=true;
    kind.strength=strength;
}

std::string Card::getcolor()
{
    if (rarity==1) return "green";
    if (rarity==2) return "blue";
    if (rarity==3) return "purple";
    if (rarity==4) return "red";
    return "white";
}

void print(Card *card)
{
    setcolor(card->getcolor());
    print(card->description,cardPrintX,cardPrintY);
}

extern Enemy *currentenemy;
void Card::effect()
{
    if (kind.isstrengthen)
    {
        message("获得"+std::to_string(kind.strength)+"点攻势");
        Player::state.strength+=kind.strength;
    }
    if (kind.isattack) 
    {
        message("对"+currentenemy->name+"使用"+name);
        for (int i=1; i<=kind.damagetimes; i++)
        {
            currentenemy->getdamage(Player::damage(kind.damage));
        }
    }
    if (kind.isdefend) 
    {
        message("使用"+name);
        Player::state.defense+=kind.defense;
    }
    if (kind.isdraw)
    {
        message("抽取"+std::to_string(kind.drawtimes)+"张卡牌");
        drawcard(kind.drawtimes);
    }
}

AttackCard::AttackCard()
{
    name="攻击卡";
    description={"攻击卡"};
    ID=0;
    cost=0;
    rarity=0;
    setattack(0,0);
}

AttackCard::AttackCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int damage,int times)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    setattack(damage,times);
}

DefendCard::DefendCard()
{
    name="防御卡";
    description={"防御卡"};
    ID=0;
    cost=0;
    rarity=0;
    setdefend(0);
}

DefendCard::DefendCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int defense)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    setdefend(defense);
}

DrawCard::DrawCard()
{
    name="抽取卡";
    description={"抽取卡"};
    ID=0;
    cost=0;
    rarity=0;
    setdraw(0);
}

DrawCard::DrawCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int times)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    setdraw(times);
}

StrengthenCard::StrengthenCard()
{
    name="强化卡";
    description={"强化卡"};
    ID=0;
    cost=0;
    rarity=0;
    setstrengthen(0);
}

StrengthenCard::StrengthenCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int strength)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    setstrengthen(strength);
}

ChangeHaveCard::ChangeHaveCard()
{
    name="改变牌库卡";
    description={"改变牌库卡"};
    ID=0;
    cost=0;
    rarity=0;
    changehavecard.clear();
}

ChangeHaveCard::ChangeHaveCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,std::vector<Card*> changehavecard)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    this->changehavecard=changehavecard;
}

void ChangeHaveCard::effect()
{
    extern std::vector<Card*> have;
    Card::effect();
    message("放入牌堆","red");
    for (int i=0; i<changehavecard.size(); i++)
    {
        have.push_back(changehavecard[i]);
        message("放入牌堆","red");
    }
}