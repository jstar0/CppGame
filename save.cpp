#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include"UI.h"
#include"save.h"
#include"gamemap.h"
#include"player.h"

std::vector<int> getMapID()
{
    std::vector<int> mapID;
    std::string line;
    std::ifstream fin("./maps/MapList.data");
    while (getline(fin,line))
    {
        std::string name;
        int ID,UP_ID,DOWN_ID,LEFT_ID,RIGHT_ID;
        std::string filePath;
        std::stringstream ss(line);
        getline(ss,name,',');
        ss>>ID;
        mapID.push_back(ID);
    }
    return mapID;
}

void save()
{
    std::vector<int> mapID=getMapID();
    extern std::vector<Room> rooms;
    extern int playerCurrentX,playerCurrentY,playerCurrentRoom;
    //将rooms中的每个Room对象整体写入文件
    std::ofstream fout("./save/save.data");  
    fout.write(reinterpret_cast<const char*>(&mapID),sizeof(mapID));
    for (int i=0; i<mapID.size(); i++) 
    {
        fout.write(reinterpret_cast<const char*>(&rooms[i]),sizeof(rooms[i]));
    }
    fout.write(reinterpret_cast<const char*>(&Player::HP),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::HPMax),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::MPMax),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::money),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::handMax),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::EXP),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::level),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&Player::card),sizeof(Player::card));
    fout.write(reinterpret_cast<const char*>(&Player::prop),sizeof(Player::prop));
    fout.write(reinterpret_cast<const char*>(&playerCurrentX),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&playerCurrentY),sizeof(int));
    fout.write(reinterpret_cast<const char*>(&playerCurrentRoom),sizeof(int));
    fout.close();
    message("保存成功","green");
}

void load()
{
    std::vector<int> mapID=getMapID();
    extern std::vector<Room> rooms;
    extern int playerCurrentX,playerCurrentY,playerCurrentRoom;
    //从文件中读取Room对象并存入rooms
    std::ifstream fin("./save/save.data");
    for (int i=0; i<mapID.size(); i++)  
    {
        fin.read(reinterpret_cast<char*>(&rooms[i]),sizeof(rooms[i]));
        message(rooms[i].name); 
        message(std::to_string(rooms[i].ID));
        message(std::to_string(rooms[i].UP_ID));
        message(std::to_string(rooms[i].DOWN_ID));
        message(std::to_string(rooms[i].LEFT_ID));
        message(std::to_string(rooms[i].RIGHT_ID));
        message(rooms[i].filePath);
    }
    fin.read(reinterpret_cast<char*>(&Player::HP),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::HPMax),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::MPMax),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::money),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::handMax),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::EXP),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::level),sizeof(int));
    fin.read(reinterpret_cast<char*>(&Player::card),sizeof(Player::card));
    fin.read(reinterpret_cast<char*>(&Player::prop),sizeof(Player::prop));
    fin.read(reinterpret_cast<char*>(&playerCurrentX),sizeof(int));
    fin.read(reinterpret_cast<char*>(&playerCurrentY),sizeof(int));
    fin.read(reinterpret_cast<char*>(&playerCurrentRoom),sizeof(int));
    fin.close();
    message("读取成功","green");
}