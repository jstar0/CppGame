#include<vector>
class Enemy;
class Card{
public:
    std::string name;
    std::vector<std::string> description;
    int ID,cost,rarity;
    virtual void effect();
    friend void print(Card card);
};
class AttackCard:public Card{
public:
    int damage;
    void effect(Enemy enemy);
};

