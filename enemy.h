#ifndef ENEMY_H
#define ENEMY_H
#include<string>
#include<vector>
class EnemyIntention{
public:
    std::string name;
};

class Enemy{
public:
    std::string name;
    std::vector<std::string> description;
    int HP,HP_Max,intention_s;
    std::vector<EnemyIntention> intention;
};

#endif