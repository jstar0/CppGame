#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>
#include "enemy.h"
#include "player.h"

class CardKind
{
public:
    bool isattack, isdefend, isdraw, isstrengthen;
    int damage, damagetimes;
    int defense;
    int drawtimes;
    int strength;

    CardKind();
    CardKind(const CardKind &other);

    // 重载=运算符
    CardKind &operator=(const CardKind &other);
};

class Card
{
public:
    Card();
    Card(std::string name, std::vector<std::string> description, int ID, int cost, int rarity);
    Card(const Card &other);

    // 重载=运算符
    Card &operator=(const Card &other);
    void setAttack(int damage, int times);
    void setDefend(int defense);
    void setDraw(int times);
    void setStrengthen(int strength);
    virtual void effect();
    std::string getColor();
    friend void print(Card *card);

    int getID() { return ID; }
    int getCost() { return cost; }
    int getRarity() { return rarity; }
    std::string getName() { return name; }
    std::vector<std::string> getDescription() { return description; }

protected:
    CardKind kind;
    std::string name;
    std::vector<std::string> description;
    int ID, cost, rarity;
};

class AttackCard : public Card
{
public:
    AttackCard();
    AttackCard(std::string name, std::vector<std::string> description, int ID, int cost, int rarity, int damage, int times);
};

class DefendCard : public Card
{
public:
    DefendCard();
    DefendCard(std::string name, std::vector<std::string> description, int ID, int cost, int rarity, int defense);
};

class DrawCard : public Card
{
public:
    DrawCard();
    DrawCard(std::string name, std::vector<std::string> description, int ID, int cost, int rarity, int times);
};

class StrengthenCard : public Card
{
public:
    StrengthenCard();
    StrengthenCard(std::string name, std::vector<std::string> description, int ID, int cost, int rarity, int strength);
};

#endif