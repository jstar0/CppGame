#ifndef CARD_H
#define CARD_H
#include<string>
#include<vector>
#include"enemy.h"
#include"player.h"
using namespace std;

class Card{
public:
    string name;
    vector<string> description;
    int ID,cost,rarity;
    Card();
    Card(string name,vector<string> description,int ID,int cost,int rarity);
    void effect();
    string getcolor();
    friend void print(Card *card);
};

class AttackCard:public Card{
public:
    int damage,times;
    AttackCard();
    AttackCard(string name,vector<string> description,int ID,int cost,int rarity,int damage,int times);
    void effect(Enemy *enemy);
};

#endif