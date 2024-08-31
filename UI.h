#ifndef UI_H
#define UI_H
#include<string>
using namespace std;

class Message{
public:
    Message(string s,string fore="white",string back="black"):s(s),fore(fore),back(back){}
    string s;
    string fore,back;
};

void initUI();
void printUI();
void message(string s,string fore="white",string back="black");
#endif