#include<iostream>
#include<cstdlib>
#include"enemy.h"
#include"console.h"
#include"UI.h"
using namespace std;

Enemy::Enemy()
{
    name="未知";
    description={"未知"};
    HP=0;
    HP_Max=0;
    intention_s=0;
}

Enemy::Enemy(string name,vector<string> description,int HP_Max)
{
    this->name=name;
    this->description=description;
    this->HP_Max=HP_Max;
    intention_s=0;
}

int Enemy::damage(int d)
{
    return d+state.strength;
}

void Enemy::getdamage(int gd)
{
    int gde=gd-state.defense>0?gd-state.defense:0;
    if (gde>0) message(name+"受到"+to_string(gd-state.defense)+"点伤害!","purple");
    else 
    {
        srand(time(0));
        int x=rand()%3;
        if (x==0) message(name+"完美格挡!","purple");
        if (x==1) message(name+"觉得不痛不痒","purple");
        if (x==2) message(name+"说你没吃饭","purple");
    }
    HP-=gde;
    state.defense=(state.defense-gd>0)?state.defense-gd:0;
}

void print(Enemy enemy)
{
    extern int attackEnemyPrintX,attackEnemyPrintY;
    int x=attackEnemyPrintX,y=attackEnemyPrintY;
    setcolor("white");
    print(enemy.name,x,y++);
    print("HP:"+to_string(enemy.HP)+"/"+to_string(enemy.HP_Max),x,y++);
    if (enemy.state.strength>0) print("力量:"+to_string(enemy.state.strength),x,y++);
    if (enemy.state.defense>0) print("防御:"+to_string(enemy.state.defense),x,y++);
}

void Enemy::init()
{
    HP=HP_Max;
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
    defense=0;
}