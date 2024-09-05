#include"gamemap.h"
#include"UI.h"
#include<vector>

extern std::vector<Room> rooms;
void datamap1()
{
    rooms.push_back((Room("广场",0,1,-1,2,3)));
    rooms.push_back((Room("长生湖",1,4,0,5,6)));
    rooms.push_back((Room("主殿",2,-1,-1,-1,0)));   
    rooms.push_back((Room("商店",3,6,-1,0,-1)));   
    rooms.push_back((Room("接待室",4,-1,1,-1,7)));   
    rooms.push_back((Room("宿舍(1F)",5,8,-1,-1,1)));   
    rooms.push_back((Room("宿舍(1F)",6,7,3,1,-1)));   
    rooms.push_back((Room("牢房",7,-1,6,4,-1)));   
    rooms.push_back((Room("资料室(1F)",8,-1,5,-1,-1)));   
    rooms.push_back((Room("宿舍(2F)",9,-1,-1,-1,-1)));   
    rooms.push_back((Room("宿舍(2F)",10,-1,-1,-1,-1)));   
    rooms.push_back((Room("资料室(2F)",11,-1,-1,-1,-1)));  
    rooms.push_back((Room("广场",12,13,-1,-1,-1)));
    rooms.push_back((Room("长生湖",13,4,-1,-1,-1)));
}