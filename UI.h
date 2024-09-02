#ifndef UI_H
#define UI_H
#include<string>

class Message{
public:
    Message(std::string s,std::string fore="white",std::string back="black"):s(s),fore(fore),back(back){}
    std::string s;
    std::string fore,back;
};

void initUI();
void printUI();
void message(std::string s,std::string fore="white",std::string back="black");
#endif