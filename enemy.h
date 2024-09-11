#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <vector>
#include "card.h"

class Card;

class EnemyState
{
public:
    EnemyState();
    EnemyState(int s, int d);
    void EnemyStateSet();
    int strength = 0;
    int defense = 0;
};

class EnemyIntention
{
public:
    EnemyIntention();
    std::string description;
    bool isattack, isdefend, isstrengthen, isgivecard;
    int damage, damagetimes;
    int defense;
    int strength;
    std::vector<Card *> givecard;
    void setattack(int damage, int times);
    void setdefend(int defense);
    void setstrengthen(int strength);
    void setgivecard(std::vector<Card *> givecard);
    void effect();
};

class EnemyIntentionAttack : public EnemyIntention
{
public:
    EnemyIntentionAttack();
    EnemyIntentionAttack(std::string description, int damage, int damagetimes);
};

class EnemyIntentionDefend : public EnemyIntention
{
public:
    EnemyIntentionDefend();
    EnemyIntentionDefend(std::string description, int defense);
};

class EnemyIntentionStrengthen : public EnemyIntention
{
public:
    EnemyIntentionStrengthen();
    EnemyIntentionStrengthen(std::string description, int strength);
};

class EnemyIntentionGiveCard : public EnemyIntention
{
public:
    EnemyIntentionGiveCard();
    EnemyIntentionGiveCard(std::string description, std::vector<Card *> givecard);
};

class Enemy
{
public:
    Enemy();
    Enemy(std::string name, int HPMax);
    std::string name;
    int HP, HPMax;
    int giveEXP = -1, giveMoney = -1, giveProp = -1, giveCard = -1;
    EnemyState state;
    std::vector<EnemyIntention *> intention;
    EnemyIntention currentintention;
    int damage(int d);
    void getdamage(int gd);
    void init();
    void turnset();
    void addintention(int EnemyIntention);
    void addintention(EnemyIntention *intention);
    friend void print(Enemy *enemy);
};

#endif
