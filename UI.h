#ifndef UI_H
#define UI_H
#include <string>

class Message
{
public:
    Message(std::string s, std::string fore = "white", std::string back = "black") : s(s), fore(fore), back(back) {}
    std::string getS() { return s; }
    std::string getForeColor() { return fore; }
    std::string getBackColor() { return back; }

private:
    std::string s;
    std::string fore, back;
};

bool initUI();
bool printUI();
void message(std::string s, std::string fore = "white", std::string back = "black");
#endif