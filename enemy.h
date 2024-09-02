#ifndef ENEMY_H
#define ENEMY_H
#include<string>
#include<vector>
#include"card.h"

class Card;

class EnemyState{
public:
    EnemyState();
    EnemyState(int s,int d);
    void EnemyStateSet();
    int strength=0;
    int defense=0;
};

class EnemyIntention{
public:
    EnemyIntention();
    std::vector<std::string> description;
    bool isattack,isdefend,isstrengthen,isgivecard;
    int damage,damagetimes;
    int defense;
    int strength;
    std::vector<Card*> givecard;
    void setattack(int damage,int times);
    void setdefend(int defense);
    void setstrengthen(int strength);
    void setgivecard(std::vector<Card*> givecard);
    void effect();
};

class EnemyIntentionAttack:public EnemyIntention{
public:
    EnemyIntentionAttack();
    EnemyIntentionAttack(std::vector<std::string> description,int damage,int damagetimes);
};

class EnemyIntentionDefend:public EnemyIntention{
public:
    EnemyIntentionDefend();
    EnemyIntentionDefend(std::vector<std::string> description,int defense);
};

class EnemyIntentionStrengthen:public EnemyIntention{
public:
    EnemyIntentionStrengthen();
    EnemyIntentionStrengthen(std::vector<std::string> description,int strength);
};

class EnemyIntentionGiveCard:public EnemyIntention{
public:
    EnemyIntentionGiveCard();
    EnemyIntentionGiveCard(std::vector<std::string> description,std::vector<Card*> givecard);
};

class Enemy{
public:
    Enemy();
    Enemy(std::string name,std::vector<std::string> description,int HP_Max);
    std::string name;
    std::vector<std::string> description;
    int HP,HP_Max;
    EnemyState state;
    std::vector<EnemyIntention*> intention;
    EnemyIntention currentintention;
    int damage(int d);
    void getdamage(int gd); 
    void init();
    void addintention(EnemyIntention *intention);
    friend void print(Enemy *enemy);
};

#endif
