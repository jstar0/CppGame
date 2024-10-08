#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"

class Card;
class Prop;

class PlayerState
{
public:
    PlayerState();
    PlayerState(int strength, int defense);
    int strength = 0;
    int defense = 0;
};

class Player
{
public:
    static int HP, HPMax, MP, MPMax, handMax;
    static int money;
    static int EXP, level;
    static std::vector<Card *> card;
    static std::vector<Prop *> prop;
    static PlayerState state;
    Player();
    static void init();
    static void addCard(Card *card);
    static void addProp(Prop *prop);
    static int damage(int d);
    static void getDamage(int gd);
    static void getEXP(int e);
    static int calculatelevel(int level);
    static void turnSet();
    friend void printPlayer();
};

class Prop
{
public:
    Prop(std::string name, std::vector<std::string> description, std::string forecolor = "white", std::string backcolor = "black");

    std::string getName() { return name; }
    std::vector<std::string> getDescription() { return description; }
    std::string getForecolor() { return forecolor; }
    std::string getBackcolor() { return backcolor; }

private:
    std::string name, forecolor, backcolor;
    std::vector<std::string> description;
};

void printPlayer();

#endif