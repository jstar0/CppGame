#ifndef CARD_H
#define CARD_H
#include<string>
#include<vector>
class Enemy;
class Card{
public:
    std::string name;
    std::vector<std::string> description;
    int ID,cost,rarity;
    void effect();
    friend void print(Card card);
};
class AttackCard:public Card{
public:
    int damage;
    void effect(Enemy enemy);
};

#endif