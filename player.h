#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include"card.h"

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
    static std::vector<Card*> card;
    static PlayerState state;
    Player();
    static void addcard(Card* card);
    static void clearcard();
    static int damage(int d);
    static void getdamage(int gd);
    static void turnset();
    friend void printPlayer();
};
#endif