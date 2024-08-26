#include <iostream>

#include <string>
#include <vector>

class Card {
    public:
        int id;
        bool updated = 0;
        int  rarity;
        std::string name;
        int cost;
        std::vector<std::string> Description;
        std::string elementtype;
        virtual void effect() = 0;
};

class AttackCard : public Card {
    public:
        void effect(int n) override{
            // std::cout << "玩家催动法力，身边 " << elementtype << 元素汇聚 << "使出了" << name << "，造成了" << n << "点伤害。" << std::endl;

        }
        void effect(int n,std::string s);
};

class 