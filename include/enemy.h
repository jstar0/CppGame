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
    int getStrength() { return strength; }
    int getDefense() { return defense; }
    void setStrength(int s) { strength = s; }
    void setDefense(int d) { defense = d; }

private:
    int strength = 0;
    int defense = 0;
};

class EnemyIntention
{
public:
    std::string description;
    bool isattack, isdefend, isstrengthen, isgivecard;
    int damage, damagetimes;
    int defense;
    int strength;
    std::vector<Card *> givecard;

    EnemyIntention();

    
    void setAttack(int damage, int times);
    void setDefend(int defense);
    void setStrengthen(int strength);
    void setGiveCard(std::vector<Card *> givecard);
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
    std::vector<EnemyIntention *> intention;
    EnemyIntention currentintention;

    Enemy();
    Enemy(std::string name, int HPMax);
    

    int damage(int d);
    void getDamage(int gd);
    void init();
    void turnSet();
    void addIntention(int EnemyIntention);
    void addIntention(EnemyIntention *intention);
    friend void print(Enemy *enemy);

    std::string getName() { return name; }
    int getHP() { return HP; }
    int getHPMax() { return HPMax; }
    int getEXP() { return giveEXP; }
    int getMoney() { return giveMoney; }
    int getProp() { return giveProp; }
    int getCard() { return giveCard; }
    void setHP(int h) { HP = h; }
    void setHPMax(int h) { HPMax = h; }
    void setEXP(int e) { giveEXP = e; }
    void setMoney(int m) { giveMoney = m; }
    void setProp(int p) { giveProp = p; }
    void setCard(int c) { giveCard = c; }
    int getStrength() { return state.getStrength(); }
    int getDefense() { return state.getDefense(); }
    void setStrength(int s) { state.setStrength(s); }
    void setDefense(int d) { state.setDefense(d); }

private:
    std::string name;
    int HP, HPMax;
    int giveEXP = -1, giveMoney = -1, giveProp = -1, giveCard = -1;
    EnemyState state;
};

#endif
