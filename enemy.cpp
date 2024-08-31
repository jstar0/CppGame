#include<iostream>
#include"enemy.h"
using namespace std;

Enemy::Enemy()
{
    name="未知";
    description={"未知"};
    HP=0;
    HP_Max=0;
    intention_s=0;
}

Enemy::Enemy(string name,vector<string> description,int HP,int HP_Max)
{
    this->name=name;
    this->description=description;
    this->HP=HP;
    this->HP_Max=HP_Max;
    intention_s=0;
}

int Enemy::damage(int d)
{
    return d+state.strength;
}

int Enemy::getdamage(int gd)
{
    HP-=gd-state.defense>0;
    state.defense=(gd-state.defense>0)?gd-state.defense:0;
    return gd-state.defense;
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