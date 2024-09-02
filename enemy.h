#ifndef ENEMY_H
#define ENEMY_H
#include<string>
#include<vector>
using namespace std;

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
    string name;
};

class Enemy{
public:
    Enemy();
    Enemy(string name,vector<string> description,int HP_Max);
    string name;
    vector<std::string> description;
    int HP,HP_Max,intention_s;
    EnemyState state;
    vector<EnemyIntention> intention;
    int damage(int d);
    void getdamage(int gd); 
    void init();
    friend void print(Enemy enemy);
};

#endif
