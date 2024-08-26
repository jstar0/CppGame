#include"player.h"
#include"card.h"
#include<vector>
int Player::HP_Max=100;
int Player::HP=Player::HP_Max;
int Player::MP_Max=3;
int Player::MP=Player::MP_Max;
std::vector<Card> Player::card;
Player::Player()
{
    Player::card.clear();
}
