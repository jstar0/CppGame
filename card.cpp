#include<iostream>
#include<string>
#include<vector>
#include"card.h"
#include"console.h"
#include"enemy.h"
#include"player.h"
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

AttackCard::AttackCard()
{
    name="未知";
    description={"未知"};
    ID=0;
    cost=0;
    rarity=0;
    damage=0;
    times=0;
}

AttackCard::AttackCard(string name,vector<string> description,int ID,int cost,int rarity,int damage,int times)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    this->damage=damage;
    this->times=times;
}

string Card::getcolor()
{
    if (rarity==1) return "white";
    if (rarity==2) return "green";
    if (rarity==3) return "blue";
    if (rarity==4) return "purple";
    if (rarity==5) return "red";
    return "white";
}

void print(Card *card)
{
    setcolor(card->getcolor());
    print(card->description,cardPrintX,cardPrintY);
}

void Card::effect()
{
    
}
void AttackCard::effect(Enemy *enemy)
{
    for (int i=1; i<=times; i++)
    {
        enemy->getdamage(damage);
    }
}