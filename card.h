#ifndef CARD_H
#define CARD_H
#include<string>
#include<vector>
#include"enemy.h"
#include"player.h"
using namespace std;

class CardKind{
public:
    bool isattack,isdefend;
    int damage,damagetimes,defense;
    CardKind();
    CardKind(bool isattack,bool isdefend);
    void setattack(int damage,int times);
    void setdefend(int defense);
};

class Card{
public:
    string name;
    vector<string> description;
    int ID,cost,rarity;
    CardKind kind;
    Card();
    Card(string name,vector<string> description,int ID,int cost,int rarity);
    void effect();
    string getcolor();
    friend void print(Card *card);
};

class AttackCard:public Card{
public:
    AttackCard();
    AttackCard(string name,vector<string> description,int ID,int cost,int rarity,int damage,int times);
};

class DefendCard:public Card{
public:
    DefendCard();
    DefendCard(string name,vector<string> description,int ID,int cost,int rarity,int defense);
};
#endif