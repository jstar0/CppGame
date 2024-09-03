#include"player.h"
#include"card.h"
#include"console.h"
#include"UI.h"
#include<vector>
int Player::HPMax=100,
    Player::HP=Player::HPMax,
    Player::MPMax=3,
    Player::MP=Player::MPMax,
    Player::money=0,
    Player::handMax=7;
std::vector<Card*> Player::card;
std::vector<Prop*> Player::prop;
PlayerState Player::state;
Player::Player()
{
    Player::card.clear();
    Player::prop.clear();
}

void Player::init()
{
    Player::MP=Player::MPMax;
    Player::state.defense=0;
    Player::state.strength=0;
}

void Player::addcard(Card* card)
{
    Player::card.push_back(card);
}

void Player::addprop(Prop* prop)
{
    Player::prop.push_back(prop);
}

int Player::damage(int d)
{
    return d+Player::state.strength;
}

void Player::getdamage(int gd)
{
    int gde=gd-Player::state.defense>0?gd-Player::state.defense:0;
    if (gde>0) message("受到"+std::to_string(gd-Player::state.defense)+"点伤害!","red");
    else message("全部防下来了","red");
    HP=HP-gde>0?HP-gde:0;
    state.defense=(Player::state.defense-gd>0)?Player::state.defense-gd:0;
}

void Player::turnset()
{
    MP=MPMax;
}

void printPlayer()
{
    extern int attackPlayerPrintX,attackPlayerPrintY;
    int x=attackPlayerPrintX,y=attackPlayerPrintY;
    setcolor("white");
    print("我",x,y++);
    print("HP:"+std::to_string(Player::HP)+"/"+std::to_string(Player::HPMax),x,y++);
    print("MP:"+std::to_string(Player::MP)+"/"+std::to_string(Player::MPMax),x,y++);
    if (Player::state.strength>0) print("力量:"+std::to_string(Player::state.strength),x,y++);
    if (Player::state.defense>0) print("防御:"+std::to_string(Player::state.defense),x,y++);
}

PlayerState::PlayerState()
{
    strength=0;
    defense=0;
}

PlayerState::PlayerState(int strength,int defense)
{
    this->strength=strength;
    this->defense=defense;
}

//物品----------------------------------------------------------------------------------------------------------
Prop::Prop(std::string name,std::vector<std::string> description,std::string forecolor/* ="white" */,std::string backcolor/* ="black" */)
{
    this->name=name;
    this->forecolor=forecolor;
    this->backcolor=backcolor;
    this->description=description;
}

