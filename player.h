#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include"card.h"
class Player{
public:
    static int HP,HP_Max,MP,MP_Max;
    static std::vector<Card> card;
    Player();
};
#endif