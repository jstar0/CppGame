#include"player.h"
#include"card.h"
#include"console.h"
#include"UI.h"
#include<vector>
using namespace std;
int Player::HP_Max=100;
int Player::HP=Player::HP_Max;
int Player::MP_Max=6;
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

void Player::getdamage(int gd)
{
    int gde=gd-Player::state.defense>0?gd-Player::state.defense:0;
    if (gde>0) message("受到"+to_string(gd-Player::state.defense)+"点伤害!","red");
    else message("全部防下来了","red");
    HP-=gde;
    state.defense=(Player::state.defense-gd>0)?Player::state.defense-gd:0;
}

void Player::turnset()
{
    MP=MP_Max;
    Player::state.PlayerStateSet();
}

void printPlayer()
{
    extern int attackPlayerPrintX,attackPlayerPrintY;
    int x=attackPlayerPrintX,y=attackPlayerPrintY;
    setcolor("white");
    print("我",x,y++);
    print("HP:"+to_string(Player::HP)+"/"+to_string(Player::HP_Max),x,y++);
    print("MP:"+to_string(Player::MP)+"/"+to_string(Player::MP_Max),x,y++);
    if (Player::state.strength>0) print("力量:"+to_string(Player::state.strength),x,y++);
    if (Player::state.defense>0) print("防御:"+to_string(Player::state.defense),x,y++);
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

