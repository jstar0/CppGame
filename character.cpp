#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Char {
    private:
        string name;//角色名
        int maxHP;//最大生命值
        int cost;//费用
        int cost_gain;//每回合获取费用,
        vector<int> deck;//卡组
        vector<int> hand;//手牌
        vector<int> discard_pile;//弃牌堆
        vector<int> exhaust_pile;//抽牌堆
        int draw_num;//每回合抽牌数
        int block;//格挡值
        bool alive;//是否存活
        int money;//交易资源
        vector<int> relics;//装备或者遗物
        vector<int> potion;//消耗品
        int potionSize;//消耗品栏大小        
};