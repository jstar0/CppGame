#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include"enemy.h"
#include"console.h"
#include"UI.h"
#include"card.h"
#include"config.h"

Enemy::Enemy()
{
    name="未知";
    HP=0;
    HPMax=0;
    intention.clear();
}

Enemy::Enemy(std::string name,int HPMax)
{
    this->name=name;
    this->HPMax=HPMax;
}
void Enemy::addIntention(int intentionID)
{
    intention.push_back(GameConfig::enemyIntentions[intentionID]);
}
void Enemy::addIntention(EnemyIntention *intention)
{
    this->intention.push_back(intention);
}

int Enemy::damage(int d)
{
    return d+state.getStrength();
}

void Enemy::getDamage(int gd)
{
    int gde=gd-state.getDefense()>0?gd-state.getDefense():0;
    if (gde>0) message(name+"受到"+std::to_string(gd-state.getDefense())+"点伤害!","purple");
    else 
    {
        srand(time(0));
        int x=rand()%3;
        if (x==0) message(name+"完美格挡!","purple");
        if (x==1) message(name+"觉得不痛不痒","purple");
        if (x==2) message(name+"说你没吃饭","purple");
    }
    HP=HP-gde>0?HP-gde:0;
    state.setDefense((state.getDefense()-gd>0)?state.getDefense()-gd:0);
}

void print(Enemy *enemy)
{
    int x=AttackConfig::enemyPrintX,y=AttackConfig::enemyPrintY;
    setPrintColor("deepgreen");
    print(enemy->currentintention.description,x,--y);
    y++;
    setPrintColor("white");
    print(enemy->name,x,y++);
    print("HP:"+std::to_string(enemy->HP)+"/"+std::to_string(enemy->HPMax),x,y++);
    if (enemy->state.getStrength()>0) print("力量:"+std::to_string(enemy->state.getStrength()),x,y++);
    if (enemy->state.getDefense()>0) print("防御:"+std::to_string(enemy->state.getDefense()),x,y++);
}

void Enemy::init()
{
    HP=HPMax;
    state.EnemyStateSet();
}

void Enemy::turnSet()
{
    state.setDefense(0);
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
    description="未知";
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
    if (isattack) 
    {
        message(GameConfig::currentEnemy->getName()+"对你发动攻击");
        for (int i=1; i<=damagetimes; i++)
        {
            Player::getDamage(GameConfig::currentEnemy->damage(damage));
        }
    }
    if (isdefend) 
    {
        message(GameConfig::currentEnemy->getName()+"进行防御");
        GameConfig::currentEnemy->setDefense(GameConfig::currentEnemy->getDefense()+defense);
    }
    if (isstrengthen)
    {
        message(GameConfig::currentEnemy->getName()+"获得"+std::to_string(strength)+"点攻势");
        GameConfig::currentEnemy->setStrength(GameConfig::currentEnemy->getStrength()+strength);
    }
    if (isgivecard)
    {
        std::string givecardname="";
        for (int i=0; i<givecard.size(); i++)
        {
            givecardname+=givecard[i]->getName()+" ";
            CardConfig::have.push_back(givecard[i]);
        }
        message(GameConfig::currentEnemy->getName()+"塞给你:"+givecardname);
    }
}

void EnemyIntention::setAttack(int damage,int times)
{
    isattack=true;
    this->damage=damage;
    this->damagetimes=times;
}

void EnemyIntention::setDefend(int defense)
{
    isdefend=true;
    this->defense=defense;
}

void EnemyIntention::setStrengthen(int strength)
{
    isstrengthen=true;
    this->strength=strength;
}

void EnemyIntention::setGiveCard(std::vector<Card*> givecard)
{
    isgivecard=true;
    this->givecard=givecard;
}

EnemyIntentionAttack::EnemyIntentionAttack()
{
    description={"攻击"};
    setAttack(0,0);
}

EnemyIntentionAttack::EnemyIntentionAttack(std::string description,int damage,int damagetimes)
{
    this->description=description;
    setAttack(damage,damagetimes);
}

EnemyIntentionDefend::EnemyIntentionDefend()
{
    description={"防御"};
    setDefend(0);
}

EnemyIntentionDefend::EnemyIntentionDefend(std::string description,int defense)
{
    this->description=description;
    setDefend(defense);
}

EnemyIntentionStrengthen::EnemyIntentionStrengthen()
{
    description={"强化"};
    setStrengthen(0);
}

EnemyIntentionStrengthen::EnemyIntentionStrengthen(std::string description,int strength)
{
    this->description=description;
    setStrengthen(strength);
}

EnemyIntentionGiveCard::EnemyIntentionGiveCard()
{
    description={"给卡"};
    setGiveCard({});
}

EnemyIntentionGiveCard::EnemyIntentionGiveCard(std::string description,std::vector<Card*> givecard)
{
    this->description=description;
    setGiveCard(givecard);
}

