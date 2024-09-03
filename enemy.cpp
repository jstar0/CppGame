#include<iostream>
#include<cstdlib>
#include<ctime>
#include"enemy.h"
#include"console.h"
#include"UI.h"
#include"card.h"

Enemy::Enemy()
{
    name="未知";
    description={"未知"};
    HP=0;
    HPMax=0;
    intention.clear();
}

Enemy::Enemy(std::string name,std::vector<std::string> description,int HPMax)
{
    this->name=name;
    this->description=description;
    this->HPMax=HPMax;
}

void Enemy::addintention(EnemyIntention *intention)
{
    this->intention.push_back(intention);
}

int Enemy::damage(int d)
{
    return d+state.strength;
}

void Enemy::getdamage(int gd)
{
    int gde=gd-state.defense>0?gd-state.defense:0;
    if (gde>0) message(name+"受到"+std::to_string(gd-state.defense)+"点伤害!","purple");
    else 
    {
        srand(time(0));
        int x=rand()%3;
        if (x==0) message(name+"完美格挡!","purple");
        if (x==1) message(name+"觉得不痛不痒","purple");
        if (x==2) message(name+"说你没吃饭","purple");
    }
    HP=HP-gde>0?HP-gde:0;
    state.defense=(state.defense-gd>0)?state.defense-gd:0;
}

void print(Enemy *enemy)
{
    extern int attackEnemyPrintX,attackEnemyPrintY;
    int x=attackEnemyPrintX,y=attackEnemyPrintY;
    setcolor("deepgreen");
    print(enemy->currentintention.description,x,--y);
    y++;
    setcolor("white");
    print(enemy->name,x,y++);
    print("HP:"+std::to_string(enemy->HP)+"/"+std::to_string(enemy->HPMax),x,y++);
    if (enemy->state.strength>0) print("力量:"+std::to_string(enemy->state.strength),x,y++);
    if (enemy->state.defense>0) print("防御:"+std::to_string(enemy->state.defense),x,y++);
}

void Enemy::init()
{
    HP=HPMax;
    state.EnemyStateSet();
}

EnemyState::EnemyState()
{
    strength=0;
    defense=0;
}

EnemyState::EnemyState(int s,int d)
{
    strength=s;
    defense=d;
}

void EnemyState::EnemyStateSet()
{
    strength=0;
    defense=0;
}

EnemyIntention::EnemyIntention()
{
    description={"未知"};
    damage=0;
    damagetimes=0;
    defense=0;
    strength=0;
    givecard.clear();
    isattack=false;
    isdefend=false;
    isstrengthen=false;
    isgivecard=false;
}

void EnemyIntention::effect()
{
    extern Enemy *currentenemy;
    if (isattack) 
    {
        message(currentenemy->name+"对你发动攻击");
        for (int i=1; i<=damagetimes; i++)
        {
            Player::getdamage(currentenemy->damage(damage));
        }
    }
    if (isdefend) 
    {
        message(currentenemy->name+"进行防御");
        currentenemy->state.defense+=defense;
    }
    if (isstrengthen)
    {
        message(currentenemy->name+"获得"+std::to_string(strength)+"点攻势");
        currentenemy->state.strength+=strength;
    }
    if (isgivecard)
    {
        std::string givecardname="";
        extern std::vector<Card*> have;
        for (int i=0; i<givecard.size(); i++)
        {
            givecardname+=givecard[i]->name+" ";
            have.push_back(givecard[i]);
        }
        message(currentenemy->name+"塞给你:"+givecardname);
    }
}

void EnemyIntention::setattack(int damage,int times)
{
    isattack=true;
    this->damage=damage;
    this->damagetimes=times;
}

void EnemyIntention::setdefend(int defense)
{
    isdefend=true;
    this->defense=defense;
}

void EnemyIntention::setstrengthen(int strength)
{
    isstrengthen=true;
    this->strength=strength;
}

void EnemyIntention::setgivecard(std::vector<Card*> givecard)
{
    isgivecard=true;
    this->givecard=givecard;
}

EnemyIntentionAttack::EnemyIntentionAttack()
{
    description={"攻击"};
    setattack(0,0);
}

EnemyIntentionAttack::EnemyIntentionAttack(std::vector<std::string> description,int damage,int damagetimes)
{
    this->description=description;
    setattack(damage,damagetimes);
}

EnemyIntentionDefend::EnemyIntentionDefend()
{
    description={"防御"};
    setdefend(0);
}

EnemyIntentionDefend::EnemyIntentionDefend(std::vector<std::string> description,int defense)
{
    this->description=description;
    setdefend(defense);
}

EnemyIntentionStrengthen::EnemyIntentionStrengthen()
{
    description={"强化"};
    setstrengthen(0);
}

EnemyIntentionStrengthen::EnemyIntentionStrengthen(std::vector<std::string> description,int strength)
{
    this->description=description;
    setstrengthen(strength);
}

EnemyIntentionGiveCard::EnemyIntentionGiveCard()
{
    description={"给卡"};
    setgivecard({});
}

EnemyIntentionGiveCard::EnemyIntentionGiveCard(std::vector<std::string> description,std::vector<Card*> givecard)
{
    this->description=description;
    setgivecard(givecard);
}

