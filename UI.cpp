#include<windows.h>
#include<vector>
#include<string>
#include"console.h"
#include"UI.h"
using namespace std;
void initUI()
{
    setcursor(false);
    setscreensize(101,42);
    HWND consoleWindow = GetConsoleWindow(); // 获取控制台窗口句柄 
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE); // 获取当前窗口样式 
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX); // 禁用最大化按钮和调整窗口大小 
    SetWindowLong(consoleWindow, GWL_STYLE, style); // 设置新的窗口样式 
    system("color 0C");
}
void printUI()
{
    setcolor("white","black");
    for (int i=0; i<100; i++) print("#",i,0);
    for (int i=0; i<=40; i++) print("#",0,i);
    for (int i=0; i<=40; i++) print("#",100,i);
    for (int i=0; i<=100; i++) print("#",i,41);
    for (int i=1; i<60; i++) print("=",i,30);
    for (int i=60; i<100; i++) print("=",i,35);
    for (int i=60; i<100; i++) print("=",i,15);
    for (int i=31; i<=40; i++) print("|",30,i);
    vector<string> s1=
    {
        "┌──────────────┐",
        "│              │",
        "│              │",
        "│              │",
        "│              │",
        "│              │",
        "│              │",
        "│              │",
        "│              │",
        "└──────────────┘"
    };
    vector<string> s2=
    {
        "  死亡收割",
        "",
        "对所有敌人造成",
        "4点伤害，未被",
        "格挡的伤害将会",
        "回复你的生命值"
    };
    print(s1,37,31);
    print(s2,38,32);
    for (int i=1; i<=40; i++) print("|",60,i);
    for (int i=3; i<55; i++) print("墙",i,3);
    for (int i=3; i<=27; i++) print("墙",3,i);
    for (int i=3; i<=27; i++) print("墙",55,i);
    for (int i=3; i<=55; i++) print("墙",i,27);
}

vector<Message> messagebox;
extern int messagePrintX,messagePrintY,messagePrintX2,messagePrintY2,messageMax;
void message(string s,string fore/* ="white" */,string back/* ="black" */)
{
    if (messagebox.size()>=messageMax) messagebox.erase(messagebox.begin());
    messagebox.push_back(Message(s,fore,back));
    clear(messagePrintX,messagePrintY,messagePrintX2,messagePrintY2);
    for (int i=0; i<messagebox.size(); i++)
    {
        setcolor(messagebox[i].fore,messagebox[i].back);
        print(messagebox[i].s,messagePrintX,messagePrintY+i);
    }
}