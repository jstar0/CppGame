#include"player.h"
#include"card.h"
#include<vector>
using namespace std;
int Player::HP_Max=100;
int Player::HP=Player::HP_Max;
int Player::MP_Max=99;
int Player::MP=Player::MP_Max;
vector<Card*> Player::card;
PlayerState Player::state;
Player::Player()
{
    Player::card.clear();
}
void Player::addcard(Card* card)
{
    Player::card.push_back(card);
}

void Player::clearcard()
{
    for (int i=0; i<card.size(); i++)
    {
        delete card[i];
    }
    Player::card.clear();
}

int Player::damage(int d)
{
    return d+Player::state.strength;
}

int Player::getdamage(int gd)
{
    HP-=gd-Player::state.defense;
    state.defense=(gd-Player::state.defense>0)?gd-Player::state.defense:0;
    return gd-Player::state.defense;
}

void Player::turnset()
{
    MP=MP_Max;
    Player::state.PlayerStateSet();
}

PlayerState::PlayerState()
{
    strength=0;
    defense=0;
}

PlayerState::PlayerState(int s,int d)
{
    strength=s;
    defense=d;
}

void PlayerState::PlayerStateSet()
{
    defense=0;
}
