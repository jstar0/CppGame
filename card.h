#ifndef CARD_H
#define CARD_H
#include<string>
#include<vector>
#include"enemy.h"
#include"player.h"

class CardKind{
public:
    bool isattack,isdefend,isdraw,isstrengthen;
    int damage,damagetimes;
    int defense;
    int drawtimes;
    int strength;
    CardKind();
};

class Card{
public:
    std::string name;
    std::vector<std::string> description;
    int ID,cost,rarity;
    CardKind kind;
    Card();
    Card(std::string name,std::vector<std::string> description,int ID,int cost,int rarity);
    void setattack(int damage,int times);
    void setdefend(int defense);
    void setdraw(int times);
    void setstrengthen(int strength);
    virtual void effect();
    std::string getcolor();
    friend void print(Card *card);
};

class AttackCard:public Card{
public:
    AttackCard();
    AttackCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int damage,int times);
};

class DefendCard:public Card{
public:
    DefendCard();
    DefendCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int defense);
};

class DrawCard:public Card{
public:
    DrawCard();
    DrawCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int times);
};

class StrengthenCard:public Card{
public:
    StrengthenCard();
    StrengthenCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,int strength);
};

class ChangeHaveCard:public Card{
public:
    ChangeHaveCard();
    ChangeHaveCard(std::string name,std::vector<std::string> description,int ID,int cost,int rarity,std::vector<Card*> changehavecard={});
    std::vector<Card*> changehavecard;
    void effect() override;
};
#endif