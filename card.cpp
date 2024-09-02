#include<iostream>
#include<string>
#include<vector>
#include"card.h"
#include"console.h"
#include"enemy.h"
#include"player.h"
#include"UI.h"
using namespace std;

extern int cardPrintX,cardPrintY;

Card::Card()
{
    name="未知";
    description={"未知"};
    ID=0;
    cost=0;
    rarity=0;
}

Card::Card(string name,vector<string> description,int ID,int cost,int rarity)
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
    damage=0;
    damagetimes=0;
    defense=0;
}

CardKind::CardKind(bool isattack,bool isdefend)
{
    this->isattack=isattack;
    this->isdefend=isdefend;
}

void CardKind::setattack(int damage,int times)
{
    this->damage=damage;
    this->damagetimes=times;
}

void CardKind::setdefend(int defense)
{
    this->defense=defense;
}

string Card::getcolor()
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
}

AttackCard::AttackCard()
{
    name="攻击卡";
    description={"攻击卡"};
    ID=0;
    cost=0;
    rarity=0;
    kind=CardKind(true,false);
    kind.setattack(0,0);
}

AttackCard::AttackCard(string name,vector<string> description,int ID,int cost,int rarity,int damage,int times)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    kind=CardKind(true,false);
    kind.setattack(damage,times);
}

DefendCard::DefendCard()
{
    name="防御卡";
    description={"防御卡"};
    ID=0;
    cost=0;
    rarity=0;
    kind=CardKind(false,true);
    kind.setdefend(0);
}

DefendCard::DefendCard(string name,vector<string> description,int ID,int cost,int rarity,int defense)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    kind=CardKind(false,true);
    kind.setdefend(defense);
}