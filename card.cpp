#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<random>
#include<ctime>
#include<string>
#include"card.h"
#include"console.h"
#include"enemy.h"
#include"player.h"
#include"UI.h"
#include"run.h"
#include"config.h"

Card::Card()
{
    name="未知";
    description={"未知"};
    ID=0;
    cost=0;
    rarity=0;
    kind=CardKind();
}

Card::Card(std::string name,std::vector<std::string> description,int ID,int cost,int rarity)
{
    this->name=name;
    this->description=description;
    this->ID=ID;
    this->cost=cost;
    this->rarity=rarity;
    kind=CardKind();
}

Card& Card::operator=(const Card &other)
{
    if (this==&other) return *this; 
    name=other.name;
    description=other.description;
    ID=other.ID;
    cost=other.cost;
    rarity=other.rarity;
    kind=other.kind;
    return *this;
}

Card::Card(const Card &other)
{
    name=other.name;
    description=other.description;
    ID=other.ID;
    cost=other.cost;
    rarity=other.rarity;
    kind=other.kind;
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

CardKind& CardKind::operator=(const CardKind &other)
{
    if (this==&other) return *this;
    isattack=other.isattack;
    isdefend=other.isdefend;
    isdraw=other.isdraw;
    isstrengthen=other.isstrengthen;
    damage=other.damage;
    damagetimes=other.damagetimes;
    defense=other.defense;
    drawtimes=other.drawtimes;
    strength=other.strength;
    return *this;
}

CardKind::CardKind(const CardKind &other)
{
    isattack=other.isattack;
    isdefend=other.isdefend;
    isdraw=other.isdraw;
    isstrengthen=other.isstrengthen;
    damage=other.damage;
    damagetimes=other.damagetimes;
    defense=other.defense;
    drawtimes=other.drawtimes;
    strength=other.strength;
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
    setPrintColor(card->getcolor());
    print(card->description,DescriptionConfig::printX,DescriptionConfig::printY);
}

void Card::effect()
{
    if (name=="坚守")
    {
        message("使用"+name);
        Player::state.defense+=kind.defense*CardConfig::hand.size();    
        drawCard(-CardConfig::hand.size());
    }
    else if (name=="盛阳剑法")
    {
        message("对"+GameConfig::currentEnemy->name+"使用"+name);
        for (int i=1; i<=Player::HP/10; i++)
        {
            GameConfig::currentEnemy->getdamage(Player::damage(kind.damage));
        }
    }
    else if (name=="阳炎")
    {
        message("获得"+std::to_string(kind.strength)+"点攻势");
        Player::state.strength+=kind.strength*(Player::HP/10);
    }
    else if (name=="铁牛功")
    {
        message("对"+GameConfig::currentEnemy->name+"使用"+name);
        GameConfig::currentEnemy->getdamage(Player::damage(kind.damage*Player::HP/100));
    }
    else if (name=="裂地崩")
    {
        message("对"+GameConfig::currentEnemy->name+"使用"+name);
        if (Player::HP==Player::HPMax)
            GameConfig::currentEnemy->getdamage(2*Player::damage(kind.damage));
        else GameConfig::currentEnemy->getdamage(Player::damage(kind.damage));
    }
    else if (name=="极阴剑诀")
    {
        message("对"+GameConfig::currentEnemy->name+"使用"+name);
        for (int i=0; i<=(Player::HPMax-Player::HP)/8; i++)
        {
            GameConfig::currentEnemy->getdamage(Player::damage(kind.damage));
        }
    }
    else if (name=="阴雷")
    {
        message("获得"+std::to_string(kind.strength)+"点攻势");
        Player::state.strength+=kind.strength*((Player::HPMax-Player::HP)/8);
    }
    else if (name=="血魔功")
    {
        message("陷入疯狂","red");
        Player::state.strength+=10;
        Player::HP/=2;
    }
    else if (name=="走火入魔")
    {
        message("彻底疯狂","red");
        GameConfig::currentEnemy->getdamage(Player::damage(kind.damage*(Player::HPMax-Player::HP)/2));
        Player::HP=1;
    }
    else if (name=="妙手")
    {
        if (CardConfig::hand.size()<3) 
        {
            message("妙手回春","green");    
            message("抽取"+std::to_string(kind.drawtimes)+"张卡牌");
            drawCard(kind.drawtimes);
        }
        else
        {
            message("发动失败","green");
        }
    }
    else
    {
        if (kind.isstrengthen)
        {
            message("获得"+std::to_string(kind.strength)+"点攻势");
            Player::state.strength+=kind.strength;
        }
        if (kind.isattack) 
        {
            message("对"+GameConfig::currentEnemy->name+"使用"+name);
            for (int i=1; i<=kind.damagetimes; i++)
            {
                GameConfig::currentEnemy->getdamage(Player::damage(kind.damage));
            }   
        }
        if (kind.isdefend) 
        {
            message("使用"+name);
            Player::state.defense+=kind.defense;
        }
        if (kind.isdraw)
        {
            if (kind.drawtimes>0)
            {
                message("抽取"+std::to_string(kind.drawtimes)+"张卡牌");
                drawCard(kind.drawtimes);
            }
            if (kind.drawtimes<0)
            {
                message("弃置"+std::to_string(-kind.drawtimes)+"张卡牌");
                drawCard(kind.drawtimes);
            }
        }
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
    Card::effect();
    message("放入牌堆","red");
    for (int i=0; i<changehavecard.size(); i++)
    {
        CardConfig::have.push_back(changehavecard[i]);
        message("放入牌堆","red");
    }
}