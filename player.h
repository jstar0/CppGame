#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include"card.h"
using namespace std;

class Card;

class PlayerState{
public:
    PlayerState();
    PlayerState(int s,int d);
    void PlayerStateSet();
    int strength=0;
    int defense=0;
};

class Player{
public:
    static int HP,HP_Max,MP,MP_Max;
    static vector<Card*> card;
    static PlayerState state;
    Player();
    static void addcard(Card* card);
    static void clearcard();
    static int damage(int d);
    static int getdamage(int gd);
    static void turnset();
};
#endif